#include "apriltags/Tag36h11_other.h"
#include "apriltags/TagDetector.h"
#include "apriltags/CustomPattern.h"
#include "opencv2/opencv.hpp"
#include <stdio.h>

std::vector<cv::Mat> customCalibration(AprilTags::CustomPattern Grid, const std::string image_folder_name, const int numberofimagesforcalibration, const int totalnumberofimages) {
  
  std::vector<std::vector<cv::Vec2f>> timagepoints;
  std::vector<std::vector<cv::Vec3f>> tobjectpoints;
  int noimg = numberofimagesforcalibration;
  int accimg = 0;

  // For each sample image
  for(int i = 0; accimg < noimg; i++){
    std::stringstream input_image_name;
    input_image_name << image_folder_name << "/img_00000" << std::to_string(i) << "_1_1.jpg";
    std::string image_name = input_image_name.str();
    cv::Mat image = cv::imread(image_name, cv::IMREAD_GRAYSCALE);

    // Detect tags and set image and object points
    AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11_other);
    vector<AprilTags::TagDetection> detections = tagDetector.extractTags(image);
    std::vector<cv::Vec2f> imagepoints = Grid.imgpoints(detections);     
    std::vector<cv::Vec3f> objectpoints = Grid.objpoints(detections, Grid.d11, Grid.d12, Grid.d13, Grid.d14, Grid.width);
    size_t threshold = 6; // Only images where 7 tags have been detected will be used for calibration
    std::cout << "detections     " << detections.size() << std::endl;
    if(detections.size() > threshold) {
      timagepoints.push_back(imagepoints);

      tobjectpoints.push_back(objectpoints);

      std::cout << "image number " << i << " accepted" << std::endl;
      accimg = accimg + 1;
    }else {
      std::cout << "image number " << i << " rejected" << std::endl;
    }
    // int th =  totalnumberofimages - 2;
    // if(i > th){
    //   cout << "not enough good images" << endl;
    //   break;
    // }
  }

  std::cout << "calibration underway" << std::endl;
  cv::destroyAllWindows();
  cv::Mat cameraMatrix,distCoeffs,R,T,newcameraMatrix;
  int flag = 0;
  flag |= cv::CALIB_FIX_ASPECT_RATIO;
  float reprojerroR = cv::calibrateCamera(tobjectpoints, timagepoints, cv::Size(3,3), cameraMatrix, distCoeffs, R, T,flag);
  cv::Mat reprojerror = cv::Mat({reprojerroR});
  std::cout << "cameraMatrix of sensor 0: " << cameraMatrix << std::endl;
  std::cout << "distCoeffs of sensor 0: " << distCoeffs << std::endl;
  std::cout << "Reprojection error of sensor 0: " << reprojerroR << std::endl;


  // Calculating error for one sample image
  std::stringstream input_image;
  input_image << image_folder_name << "/img_0000013_1_1.jpg";
  std::string image_name = input_image.str();
  cv::Mat image = cv::imread(image_name, cv::IMREAD_GRAYSCALE);
  AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11_other);
  vector<AprilTags::TagDetection> detections = tagDetector.extractTags(image);

  std::vector<cv::Vec2f> imagepoints = Grid.imgpoints(detections);     
  std::vector<cv::Vec3f> objectpoints = Grid.objpoints(detections, Grid.d11, Grid.d12, Grid.d13, Grid.d14, Grid.width);
  cv::Mat objectpointsmat = cv::Mat(objectpoints);
  cv::Mat imgpointsmat = cv::Mat(imagepoints);

  cv::Mat rotmat = R.row(13);
  cv::Mat tramat = T.row(13);
  cv::Mat error;
  std::cout << "objectpoints are = " << std::endl << " " << objectpointsmat << std::endl;
  // For each tag
  for (int i = 0; i < 7; ++i) {
    float cumulerror = 0;
    // For each corner of the i-th detected tag
    for (int j = 4*i; j < 4*i+4; ++j){

      // Projecting the points into the image plane and calculating the error for each point
      cv::Mat aMat = objectpointsmat.row(j);
      cv::Mat imgvec;
      cv::projectPoints(aMat,rotmat,tramat,cameraMatrix,distCoeffs,imgvec);
      cv::Mat_<float> img = cv::Mat({imgvec.at<float>(0,0), imgvec.at<float>(0,1)});
      cv::Mat orgimgvec = imgpointsmat.row(j).t();
      cv::Mat_<float> orgimg = cv::Mat({orgimgvec.at<float>(0,0), orgimgvec.at<float>(0,1)});
    
      cv::Mat error = img - orgimg;
      float err = cv::norm(orgimg - img, cv::NORM_L2);
      cumulerror = cumulerror + err;
    }
    cumulerror = cumulerror/4;
    std::cout << std::endl << "error for tag " << i << ": " << cumulerror << std::endl;
    error.push_back(cumulerror);
  }

  // Returning found matrices to save
  std::vector<cv::Mat> calibrationmatrices;
  calibrationmatrices.push_back(cameraMatrix);
  calibrationmatrices.push_back(distCoeffs);
  calibrationmatrices.push_back(reprojerror);
  calibrationmatrices.push_back(error);   
return calibrationmatrices;
}

