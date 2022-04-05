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

std::vector<cv::Mat> calibration(const AprilTags::AprilGrid Grid, const std::string imagefoldername, const int cameranumber, const int numberofimagesforcalibration, const int totalnumberofimages) {
  AprilTags::AprilGrid Grid1 = Grid;

  std::vector<std::vector<cv::Vec2f>> timagepoints1;
  std::vector<std::vector<cv::Vec3f>> tobjectpoints1;
  std::vector<std::vector<cv::Vec2f>> timagepoints2;
  std::vector<std::vector<cv::Vec3f>> tobjectpoints2;
  std::string imagefoldername0 = imagefoldername; 
  std::string cameranum = "_1";
  
  if(cameranumber == 0){
      cameranum = "_0";
  }else if(cameranumber == 1){
      cameranum = "_1";
  }else if(cameranumber == 2){
      cameranum = "_2";
  }else {
      std::cout << "wrong camera number, please enter from 0, 1 and 2. the default value is 0 and the results are given with default value" << endl;
  }
  std::string zeross = "00000";
  int noimg = numberofimagesforcalibration;
  int accimg = 0;
  for(int i = 0; accimg < noimg; i++){
      std::stringstream input_image_name1;
      //int ii = rand() % totalnumberofimages;
      string str;
      stringstream ss;  
      ss << i;  
      ss >> str; 
      input_image_name1 << imagefoldername0;
      input_image_name1 << "/img_";
      input_image_name1 << zeross;
      input_image_name1 << str;
      input_image_name1 << cameranum;
      input_image_name1 << "_1";
      input_image_name1 << ".jpg";
      std::string image_name1 = input_image_name1.str();
      cv::Mat image1 = cv::imread(image_name1, cv::IMREAD_GRAYSCALE);
      AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11);
      vector<AprilTags::TagDetection> detections1 = tagDetector.extractTags(image1);
      std::vector<cv::Vec2f>  imagepoints1 = Grid1.imgpoints(detections1,Grid1.rows,Grid1.columns,Grid1.start_ID);
      std::vector<cv::Vec3f>  objectpoints1 = Grid1.objpoints(detections1,Grid1.rows,Grid1.columns,Grid1.start_ID,Grid1.size,Grid1.spacing);
      int grid_points = Grid1.columns*Grid1.rows*4;
      int threshold = grid_points/4;
      cout << "objectpoints1     " << objectpoints1.size() << endl;
      if(objectpoints1.size() > threshold) {
      timagepoints1.push_back(imagepoints1);
      tobjectpoints1.push_back(objectpoints1);
      cout << "image number"<< i << " accepted" << endl;
      accimg = accimg + 1;
      }else {
          cout << "image number" << i << " rejected" << endl;
      }
      int th =  37;
      if(i > th){
          cout << "not enough good images" << endl;
          break;
      }
  }


  std::cout << "calibrating underway for camera " << cameranumber <<  std::endl;
  cv::destroyAllWindows();
  cv::Mat cameraMatrix1,distCoeffs1,R1,T1,newcameraMatrix1;
  int flag1 = 0;
  flag1 |= cv::CALIB_FIX_K3 + cv::CALIB_ZERO_TANGENT_DIST;
  float reprojerror1 = cv::calibrateCamera(tobjectpoints1, timagepoints1, cv::Size(Grid1.rows,Grid1.columns), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  cv::Mat reprojerror = cv::Mat({reprojerror1});
  std::cout << "cameraMatrix of sensor 0: " << cameraMatrix1 << std::endl;
  std::cout << "distCoeffs of sensor 0 : " << distCoeffs1 << std::endl;
  std::cout << "Reprojection error of sensor 0 : " << reprojerror1 << std::endl;


  std::stringstream input_image_test;
  input_image_test << imagefoldername0;
  input_image_test << "/img_0000013_1_1.jpg";
  std::string image_name_test = input_image_test.str();
  cv::Mat imagetest = cv::imread(image_name_test, cv::IMREAD_GRAYSCALE);
  AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11);
  vector<AprilTags::TagDetection> detectionstest = tagDetector.extractTags(imagetest);

  std::vector<cv::Vec2f>  imagepointstest = Grid1.imgpoints(detectionstest,Grid1.rows,Grid1.columns,Grid1.start_ID);     
  std::vector<cv::Vec3f>  objectpointstest = Grid1.objpoints(detectionstest,Grid1.rows,Grid1.columns,Grid1.start_ID,Grid1.size,Grid1.spacing);
  cv::Mat objectpointstestmat = cv::Mat(objectpointstest);
  cv::Mat imgpointstestmat = cv::Mat(imagepointstest);


  cv::Mat rotmat = R1.row(13);
  cv::Mat tramat = T1.row(13);
  cv::Mat error;
  cv::Mat detectedIDs;
  cout << "objectpoints are = " << endl << " " << objectpointstestmat.size() << endl;


  for (int i = 0; i < Grid1.rows*Grid1.columns; ++i){
    for (size_t j = 0; j < detectionstest.size(); ++j) {
        const auto& det = detectionstest[j];
        if (det.id == i){
            detectedIDs.push_back(det.id);
            float cumulerror = 0;
            for (int h = 4*j; h < 4*j+4; ++h){
                cv::Mat Testmat = objectpointstestmat.row(h);
                cv::Mat imgvec;
                cv::projectPoints(Testmat,rotmat,tramat,cameraMatrix1,distCoeffs1,imgvec);
                cv::Mat_<float> img = cv::Mat({imgvec.at<float>(0,0), imgvec.at<float>(0,1)});
                cv::Mat orgimgvec = imgpointstestmat.row(h).t();
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
  

   std::vector<cv::Mat> calibrationmatrices;
   calibrationmatrices.push_back(cameraMatrix1);
   calibrationmatrices.push_back(distCoeffs1);
   calibrationmatrices.push_back(reprojerror);
   calibrationmatrices.push_back(error);
   calibrationmatrices.push_back(detectedIDs);
   cout << "detectedIDS rows " << detectedIDs.rows << endl;
return calibrationmatrices;
}

