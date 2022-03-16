#include <string>
#include <sstream> 
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "apriltags/Tag36h11.h"
#include "apriltags/Tag36h11_other.h"
#include "apriltags/TagDetector.h"
#include "apriltags/AprilGrid.h"
#include "apriltags/Test.h"
#include "opencv2/opencv.hpp"
#include "vis.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

std::vector<cv::Mat> calibrationtest(const AprilTags::Test Grid2, const std::string imagefoldername, const int cameranumber, const int numberofimagesforcalibration, const int totalnumberofimages) {
  AprilTags::Test Grid1 = Grid2;

  std::vector<std::vector<cv::Vec2f>> timagepoints1;
  std::vector<std::vector<cv::Vec3f>> tobjectpoints1;
  std::vector<std::vector<cv::Vec2f>> timagepoints2;
  std::vector<std::vector<cv::Vec3f>> tobjectpoints2;
  std::vector<std::vector<cv::Vec2f>> timp0,timp1,timp2,timp3,timp4,timp5,timp6;
  std::vector<std::vector<cv::Vec3f>> tobj0,tobj1,tobj2,tobj3,tobj4,tobj5,tobj6;
  std::string imagefoldername0 = imagefoldername; 
  std::string cameranum = "_1";
  std::string zeross = "00000";
  float d1 = .25;
  float d2 = .47;
  float d3 = .156;
  float d4 = .271;
  float a = .053;
  int noimg = numberofimagesforcalibration;
  int totalnoimg = totalnumberofimages;
  int accimg = 0;
  for(int i = 30; accimg < noimg; i++){
      std::stringstream input_image_name1 ;
      //int ii = rand() % totalnoimg;
      string str;
      stringstream ss;  
      ss << i;  
      ss >> str; 
      input_image_name1 << imagefoldername0;
      input_image_name1 << "/img_";
      input_image_name1 << zeross;
      input_image_name1 << str;
      //input_image_name1 << std::setw(6) << std::setfill('0') << i;
      input_image_name1 << cameranum;
      input_image_name1 << "_1";
      input_image_name1 << ".jpg";
      std::string image_name1 = input_image_name1.str();
      std::stringstream input_image_name2;
      input_image_name2 << imagefoldername0;
      input_image_name2 << "/img_";
      //input_image_name2 << std::setw(4) << std::setfill('0');
      //input_image_name1 << std::setw(6) << std::setfill('0') << i;
      input_image_name2 << zeross;
      input_image_name2 << str;
      input_image_name2 << cameranum;
      input_image_name2 << "_1";
      input_image_name2 << ".jpg";
      std::string image_name2 = input_image_name2.str();
      cv::Mat image1 = cv::imread(image_name1, cv::IMREAD_GRAYSCALE);
      AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11_other);
      vector<AprilTags::TagDetection> detections1 = tagDetector.extractTags(image1);
      cv::Mat image2 = cv::imread(image_name2, cv::IMREAD_GRAYSCALE);
      vector<AprilTags::TagDetection> detections2 = tagDetector.extractTags(image2);
      std::vector<cv::Vec2f>  imagepoints1 = Grid1.imgpointstest(detections1);     
      std::vector<cv::Vec3f>  objectpoints1 = Grid1.objpointstest(detections1, Grid1.d11, Grid1.d12, Grid1.d13, Grid1.d14, Grid1.width);
      std::vector<cv::Vec2f>  imagepoints2 = Grid1.imgpointstest(detections2);     
      std::vector<cv::Vec3f>  objectpoints2 = Grid1.objpointstest(detections2, Grid1.d11, Grid1.d12, Grid1.d13, Grid1.d14, Grid1.width);

      std::vector<cv::Vec2f>  imp0 = Grid1.imtag0(detections1);
      std::vector<cv::Vec2f>  imp1 = Grid1.imtag1(detections1);
      std::vector<cv::Vec2f>  imp2 = Grid1.imtag2(detections1);
      std::vector<cv::Vec2f>  imp3 = Grid1.imtag3(detections1);
      std::vector<cv::Vec2f>  imp4 = Grid1.imtag4(detections1);
      std::vector<cv::Vec2f>  imp5 = Grid1.imtag5(detections1);
      std::vector<cv::Vec2f>  imp6 = Grid1.imtag6(detections1);

      std::vector<cv::Vec3f> obj0,obj1,obj2,obj3,obj4,obj5,obj6;
      

      for (size_t h = 0; h < imp0.size()/4; h++){
        
            int xo = 0;
            int y0 = 0; 
            cv::Vec3f topright = {a*(float)0.5 + xo, a*(float)0.5 + y0, 0};
            cv::Vec3f topleft = {xo - a*(float)0.5, a*(float)0.5 + y0, 0};
            cv::Vec3f bottomleft = {xo - a*(float)0.5, y0 - a*(float)0.5, 0};
            cv::Vec3f bottomright = {xo + a*(float)0.5, y0 - a*(float)0.5, 0};
            obj0.push_back(topright);
            obj0.push_back(topleft);
            obj0.push_back(bottomleft);
            obj0.push_back(bottomright);

      }
      for (size_t h = 0; h < imp1.size()/4; h++){
        
            int xo = d1;
            int y0 = 0; 
            cv::Vec3f topright = {a*(float)0.5 + xo, a*(float)0.5 + y0, 0};
            cv::Vec3f topleft = {xo - a*(float)0.5, a*(float)0.5 + y0, 0};
            cv::Vec3f bottomleft = {xo - a*(float)0.5, y0 - a*(float)0.5, 0};
            cv::Vec3f bottomright = {xo + a*(float)0.5, y0 - a*(float)0.5, 0};
            obj1.push_back(topright);
            obj1.push_back(topleft);
            obj1.push_back(bottomleft);
            obj1.push_back(bottomright);

      }
      for (size_t h = 0; h < imp2.size()/4; h++){
        
            int xo = d2;
            int y0 = 0; 
            cv::Vec3f topright = {a*(float)0.5 + xo, a*(float)0.5 + y0, 0};
            cv::Vec3f topleft = {xo - a*(float)0.5, a*(float)0.5 + y0, 0};
            cv::Vec3f bottomleft = {xo - a*(float)0.5, y0 - a*(float)0.5, 0};
            cv::Vec3f bottomright = {xo + a*(float)0.5, y0 - a*(float)0.5, 0};
            obj2.push_back(topright);
            obj2.push_back(topleft);
            obj2.push_back(bottomleft);
            obj2.push_back(bottomright);

      }
      for (size_t h = 0; h < imp3.size()/4; h++){
        
            int xo = 0;
            int y0 = d3; 
            cv::Vec3f topright = {a*(float)0.5 + xo, a*(float)0.5 + y0, 0};
            cv::Vec3f topleft = {xo - a*(float)0.5, a*(float)0.5 + y0, 0};
            cv::Vec3f bottomleft = {xo - a*(float)0.5, y0 - a*(float)0.5, 0};
            cv::Vec3f bottomright = {xo + a*(float)0.5, y0 - a*(float)0.5, 0};
            obj3.push_back(topright);
            obj3.push_back(topleft);
            obj3.push_back(bottomleft);
            obj3.push_back(bottomright);

      }
      for (size_t h = 0; h < imp4.size()/4; h++){
        
            int xo = d1;
            int y0 = d3; 
            cv::Vec3f topright = {a*(float)0.5 + xo, a*(float)0.5 + y0, 0};
            cv::Vec3f topleft = {xo - a*(float)0.5, a*(float)0.5 + y0, 0};
            cv::Vec3f bottomleft = {xo - a*(float)0.5, y0 - a*(float)0.5, 0};
            cv::Vec3f bottomright = {xo + a*(float)0.5, y0 - a*(float)0.5, 0};
            obj4.push_back(topright);
            obj4.push_back(topleft);
            obj4.push_back(bottomleft);
            obj4.push_back(bottomright);

      }
      for (size_t h = 0; h < imp5.size()/4; h++){
        
            int xo = 0;
            int y0 = d4; 
            cv::Vec3f topright = {a*(float)0.5 + xo, a*(float)0.5 + y0, 0};
            cv::Vec3f topleft = {xo - a*(float)0.5, a*(float)0.5 + y0, 0};
            cv::Vec3f bottomleft = {xo - a*(float)0.5, y0 - a*(float)0.5, 0};
            cv::Vec3f bottomright = {xo + a*(float)0.5, y0 - a*(float)0.5, 0};
            obj5.push_back(topright);
            obj5.push_back(topleft);
            obj5.push_back(bottomleft);
            obj5.push_back(bottomright);

      }
      for (size_t h = 0; h < imp6.size()/4; h++){
        
            int xo = d2;
            int y0 = d4; 
            cv::Vec3f topright = {a*(float)0.5 + xo, a*(float)0.5 + y0, 0};
            cv::Vec3f topleft = {xo - a*(float)0.5, a*(float)0.5 + y0, 0};
            cv::Vec3f bottomleft = {xo - a*(float)0.5, y0 - a*(float)0.5, 0};
            cv::Vec3f bottomright = {xo + a*(float)0.5, y0 - a*(float)0.5, 0};
            obj6.push_back(topright);
            obj6.push_back(topleft);
            obj6.push_back(bottomleft);
            obj6.push_back(bottomright);

      }
      std::cout << "size of imp0: " << imp0.size() << std::endl;
      std::cout << "size of obj0: " << obj0.size() << std::endl;

      //int grid_points = 28;
      size_t threshold = 6;
      cout << "detections     " << detections1.size() << endl;
      if(detections1.size() > threshold) {
        timagepoints1.push_back(imagepoints1);
        timp0.push_back(imp0);
        timp1.push_back(imp1);
        timp2.push_back(imp2);
        timp3.push_back(imp3);
        timp4.push_back(imp4);
        timp5.push_back(imp5);
        timp6.push_back(imp6);
        timagepoints2.push_back(imagepoints2);
        tobjectpoints1.push_back(objectpoints1);
        tobj0.push_back(obj0);
        tobj1.push_back(obj1);
        tobj2.push_back(obj2);
        tobj3.push_back(obj3);
        tobj4.push_back(obj4);
        tobj5.push_back(obj5);
        tobj6.push_back(obj6);
        tobjectpoints2.push_back(objectpoints2);
    //    std::cout << "size of timp0: " << timp0.size() << std::endl;
    //    std::cout << "size of tobj0: " << tobj0.size() << std::endl;
        cout << "image number"<< i << " accepted" << endl;
        accimg = accimg + 1;
      }else {
          cout << "image number" << i << " rejected" << endl;
      }
      int th =  totalnoimg - 2;
      if(i > th){
          cout << "not enough good images" << endl;
          break;
      }
  }


  std::cout << "calibrating underway for camera " << cameranumber <<  std::endl;
  cv::destroyAllWindows();
  cv::Mat cameraMatrix1,distCoeffs1,R1,T1,newcameraMatrix1;
  cv::Mat cameraMatrix2,distCoeffs2,R2,T2,newcameraMatrix2;
  int flag1 = 0;
  flag1 |= cv::CALIB_FIX_K3;
  double reprojtag0 = cv::calibrateCamera(tobj0, timp0, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojtag1 = cv::calibrateCamera(tobj1, timp1, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojtag2 = cv::calibrateCamera(tobj2, timp2, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojtag3 = cv::calibrateCamera(tobj3, timp3, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojtag4 = cv::calibrateCamera(tobj4, timp4, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojtag5 = cv::calibrateCamera(tobj5, timp5, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojtag6 = cv::calibrateCamera(tobj6, timp6, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojerror1 = cv::calibrateCamera(tobjectpoints1, timagepoints1, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
//  double error0 = cv::calibrateCamera(tobjectpoints1(0:3), timagepoints1(0:3), cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojerror2 = cv::calibrateCamera(tobjectpoints2, timagepoints2, cv::Size(3,3), cameraMatrix2, distCoeffs2, R2, T2,flag1);
  newcameraMatrix1 = cv::getOptimalNewCameraMatrix(cameraMatrix1,distCoeffs1,cv::Size(3,3),1,cv::Size(3,3),0);
  newcameraMatrix2 = cv::getOptimalNewCameraMatrix(cameraMatrix2,distCoeffs2,cv::Size(3,3),1,cv::Size(3,3),0);
//  std::cout << "Error for tag 0: " << error0 << std::endl;
  std::cout << "cameraMatrix of sensor 0: " << cameraMatrix1 << std::endl;
  std::cout << "distCoeffs of sensor 0 : " << distCoeffs1 << std::endl;
  std::cout << "cameraMatrix of sensor 1: " << cameraMatrix2 << std::endl;
  std::cout << "distCoeffs of sensor 1 : " << distCoeffs2 << std::endl;
  std::cout << "Reprojection error of sensor 0 : " << reprojerror1 << std::endl;
  std::cout << "Reprojection error of sensor 1 : " << reprojerror2 << std::endl;

  std::cout << "Reprojection error for tag 0 : " << reprojtag0 << std::endl;
  std::cout << "Reprojection error for tag 1 : " << reprojtag1 << std::endl;
  std::cout << "Reprojection error for tag 2 : " << reprojtag2 << std::endl;
  std::cout << "Reprojection error for tag 3 : " << reprojtag3 << std::endl;
  std::cout << "Reprojection error for tag 4 : " << reprojtag4 << std::endl;
  std::cout << "Reprojection error for tag 5 : " << reprojtag5 << std::endl;
  std::cout << "Reprojection error for tag 6 : " << reprojtag6 << std::endl;
  
  cv::Mat K1,K2,R,F,E,D1,D2;
  K1 = newcameraMatrix1;
  K2 = newcameraMatrix2;
  D1 = distCoeffs1;
  D2 = distCoeffs2;
  cv::Vec3d T;
  int flag = 0;
  flag |= cv::CALIB_USE_INTRINSIC_GUESS;
//  std::cout << "stereo calibration underway for camera " << cameranumber << std::endl;
  cv::stereoCalibrate(tobjectpoints1, timagepoints1, timagepoints2, K1, D1, K2, D2, cv::Size(3,3), R, T, E, F,flag);
//  std::cout << "new cameraMatrix of sensor 0: " << K1 << std::endl;
//  std::cout << "new cameraMatrix of sensor 1: " << K2 << std::endl;
//  std::cout << "translation vector is " << T << std::endl;

  cv::Mat rect1, rect2, proj_mat1, proj_mat2, Q;
  cv::stereoRectify(newcameraMatrix1,distCoeffs1,newcameraMatrix2,distCoeffs2,
                    cv::Size(3,3),R,T,rect1,rect2,proj_mat1,proj_mat2,Q,
                    1);
//   std::cout << "stereo rectification underway for camera " << cameranumber <<  std::endl;
//   std::cout << "rectification matrix of sensor 0 is  " << rect1 << std::endl;
//   std::cout << "rectification matrix of sensor 1 is  " << rect2 << std::endl;
//   std::cout << "projection matrix of sensor 0: " << proj_mat1 << std::endl;
//   std::cout << "projection matrix of sensor 1 : " << proj_mat2 << std::endl;
   
   std::vector<cv::Mat> calibrationmatrices;
   calibrationmatrices.push_back(K1);
   calibrationmatrices.push_back(distCoeffs1);
   calibrationmatrices.push_back(K2);
   calibrationmatrices.push_back(distCoeffs2);
   calibrationmatrices.push_back(R);
   cv::Mat Translation = cv::Mat(1,3,CV_32F);
   Translation.col(0).setTo(T[0]);
   Translation.col(1).setTo(T[1]);
   Translation.col(2).setTo(T[2]);
   calibrationmatrices.push_back(Translation);
//   cout << "inside function T is" << T << endl;
return calibrationmatrices;
}

