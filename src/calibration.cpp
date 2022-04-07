#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "apriltags/Tag36h11.h"
#include "apriltags/TagDetector.h"
#include "apriltags/AprilGrid.h"
#include "apriltags/CustomPattern.h"
#include "opencv2/opencv.hpp"
#include "vis.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

std::vector<cv::Mat> calibration(AprilTags::AprilGrid Grid, const std::string imagefoldername, const int numberofimagesforcalibration, const int totalnumberofimages) {
  std::vector<std::vector<cv::Vec2f>> timagepoints;
  std::vector<std::vector<cv::Vec3f>> tobjectpoints;
  int noimg = numberofimagesforcalibration;
  int accimg = 0;

  // For each sample image
  for(int i = 0; accimg < noimg; i++){

    std::stringstream input_image_name;
    input_image_name << imagefoldername << "/img_00000" << std::to_string(i) << "_1_1.jpg";
    std::string image_name = input_image_name.str();
    cv::Mat image = cv::imread(image_name, cv::IMREAD_GRAYSCALE);
    AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11);

    // Detect tags and set image and object points
    vector<AprilTags::TagDetection> detections = tagDetector.extractTags(image);
    std::vector<cv::Vec2f> imagepoints = Grid.imgpoints(detections,Grid.rows,Grid.columns,Grid.start_ID);
    std::vector<cv::Vec3f> objectpoints = Grid.objpoints(detections,Grid.rows,Grid.columns,Grid.start_ID,Grid.size,Grid.spacing);
    int grid_points = Grid.columns*Grid.rows*4;
    int threshold = grid_points/4; // Only when a fourth of the corners have been detected will be used for calibration
    cout << "objectpoints     " << objectpoints.size() << endl;
    if(objectpoints.size() > threshold) {
      timagepoints.push_back(imagepoints);

      tobjectpoints.push_back(objectpoints);

      cout << "image number"<< i << " accepted" << endl;
      accimg = accimg + 1;
    }else {
      cout << "image number" << i << " rejected" << endl;
    }
    // int th = 37;
    // if(i > th){
    //   cout << "not enough good images" << endl;
    //   break;
    // }
  }

  std::cout << "calibration underway" << std::endl;
  cv::destroyAllWindows();
  cv::Mat cameraMatrix,distCoeffs,R,T,newcameraMatrix;
  int flag = 0;
  flag |= cv::CALIB_FIX_K3 + cv::CALIB_ZERO_TANGENT_DIST;
  float reprojerroR = cv::calibrateCamera(tobjectpoints, timagepoints, cv::Size(Grid.rows,Grid.columns), cameraMatrix, distCoeffs, R, T,flag);
  cv::Mat reprojerror = cv::Mat({reprojerroR});
  std::cout << "cameraMatrix of sensor 0: " << cameraMatrix << std::endl;
  std::cout << "distCoeffs of sensor 0: " << distCoeffs << std::endl;
  std::cout << "Reprojection error of sensor 0: " << reprojerroR << std::endl;

  // Calculating error for one sample image
  std::stringstream input_image_val;
  input_image_val << imagefoldername << "/img_0000013_1_1.jpg";
  std::string image_name_val = input_image_val.str();
  cv::Mat image_val = cv::imread(image_name_val, cv::IMREAD_GRAYSCALE);
  AprilTags::TagDetector tagDetector_val(AprilTags::tagCodes36h11);

  vector<AprilTags::TagDetection> detections_val = tagDetector_val.extractTags(image_val);
  std::vector<cv::Vec2f> imagepoints_val = Grid.imgpoints(detections_val,Grid.rows,Grid.columns,Grid.start_ID);     
  std::vector<cv::Vec3f> objectpoints_val = Grid.objpoints(detections_val,Grid.rows,Grid.columns,Grid.start_ID,Grid.size,Grid.spacing);
  cv::Mat objectpointsmat_val = cv::Mat(objectpoints_val);
  cv::Mat imgpointsmat_val = cv::Mat(imagepoints_val);


  cv::Mat rotmat_val = R.row(13);
  cv::Mat tramat_val = T.row(13);
  cv::Mat detectedIDs_val;
  cv::Mat error;
  cout << "objectpoints are = " << endl << " " << objectpointsmat_val.size() << endl;


  for (int i = 0; i < Grid.rows*Grid.columns; ++i){
    for (size_t j = 0; j < detections_val.size(); ++j) {
      const auto& det = detections_val[j];
      if (det.id == i){
        detectedIDs_val.push_back(det.id);
        float cumulerror = 0;
        for (int h = 4*j; h < 4*j+4; ++h){
          cv::Mat Mat_val = objectpointsmat_val.row(h);
          cv::Mat imgvec;
          cv::projectPoints(Mat_val,rotmat_val,tramat_val,cameraMatrix,distCoeffs,imgvec);
          cv::Mat_<float> img = cv::Mat({imgvec.at<float>(0,0), imgvec.at<float>(0,1)});
          cv::Mat orgimgvec = imgpointsmat_val.row(h).t();
          cv::Mat_<float> orgimg = cv::Mat({orgimgvec.at<float>(0,0), orgimgvec.at<float>(0,1)});
          
          cv::Mat error = img - orgimg;
          float err = cv::norm(orgimg - img, cv::NORM_L2);
          // cout << "error is " << endl << endl << err << endl;
          cumulerror = cumulerror + err;
        }
        cumulerror = cumulerror/4;
        cout << "error for tag " << i << endl << cumulerror << endl;
        error.push_back(cumulerror);
      } 
    }
  }
  
  // Returning found matrices to save
  std::vector<cv::Mat> calibrationmatrices;
  calibrationmatrices.push_back(cameraMatrix);
  calibrationmatrices.push_back(distCoeffs);
  calibrationmatrices.push_back(reprojerror);
  calibrationmatrices.push_back(error);
  calibrationmatrices.push_back(detectedIDs_val);
  cout << "detectedIDS rows " << detectedIDs_val.rows << endl;
return calibrationmatrices;
}

