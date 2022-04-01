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
  AprilTags::Test Grid3 = Grid2;
  float dist1 = Grid3.width;
  cout << "test dist "<< dist1 << endl;
  std::vector<std::vector<cv::Vec2f>> timagepoints1;
  std::vector<std::vector<cv::Vec3f>> tobjectpoints1;
  std::string imagefoldername0 = imagefoldername; 
  std::string cameranum = "_1";
  std::string zeross = "00000";
  int noimg = numberofimagesforcalibration;
  int totalnoimg = totalnumberofimages;
  int accimg = 0;
  for(int i = 0; accimg < noimg; i++){
      std::stringstream input_image_name1;
      //int ii = rand() % totalnoimg;
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
      AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11_other);
      vector<AprilTags::TagDetection> detections1 = tagDetector.extractTags(image1);
      std::vector<cv::Vec2f>  imagepoints1 = Grid3.imgpointstest(detections1);     
      std::vector<cv::Vec3f>  objectpoints1 = Grid3.objpointstest(detections1, Grid3.d11, Grid3.d12, Grid3.d13, Grid3.d14, Grid3.width);
      size_t threshold = 6;
      cout << "detections     " << detections1.size() << endl;
      if(detections1.size() > threshold) {
        timagepoints1.push_back(imagepoints1);

        tobjectpoints1.push_back(objectpoints1);

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
  int flag1 = 0;
  flag1 |= cv::CALIB_FIX_ASPECT_RATIO;
  float reprojerror1 = cv::calibrateCamera(tobjectpoints1, timagepoints1, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  cv::Mat reprojerror = cv::Mat({reprojerror1});
  std::cout << "cameraMatrix of sensor 0: " << cameraMatrix1 << std::endl;
  std::cout << "distCoeffs of sensor 0 : " << distCoeffs1 << std::endl;
  std::cout << "Reprojection error of sensor 0 : " << reprojerror1 << std::endl;




  std::stringstream input_image_test;
  input_image_test << imagefoldername0;
  input_image_test << "/img_0000013_1_1.jpg";
  std::string image_name_test = input_image_test.str();
  cv::Mat imagetest = cv::imread(image_name_test, cv::IMREAD_GRAYSCALE);
  AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11_other);
  vector<AprilTags::TagDetection> detectionstest = tagDetector.extractTags(imagetest);

  std::vector<cv::Vec2f>  imagepointstest = Grid3.imgpointstest(detectionstest);     
  std::vector<cv::Vec3f>  objectpointstest = Grid3.objpointstest(detectionstest, Grid3.d11, Grid3.d12, Grid3.d13, Grid3.d14, Grid3.width);
  cv::Mat objectpointstestmat = cv::Mat(objectpointstest);
  cv::Mat imgpointstestmat = cv::Mat(imagepointstest);


  cv::Mat rotmat = R1.row(13);
  cv::Mat tramat = T1.row(13);
  cv::Mat error;
  cout << "objectpoints are = " << endl << " " << objectpointstestmat << endl;
  for (int i = 0; i < 7; ++i) {
    float cumulerror = 0;
    for (int j = 4*i; j < 4*i+4; ++j){
      cv::Mat Testmat = objectpointstestmat.row(j);
      cv::Mat imgvec;
      cv::projectPoints(Testmat,rotmat,tramat,cameraMatrix1,distCoeffs1,imgvec);
      cv::Mat_<float> img = cv::Mat({imgvec.at<float>(0,0), imgvec.at<float>(0,1)});
      cv::Mat orgimgvec = imgpointstestmat.row(j).t();
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

   
  std::vector<cv::Mat> calibrationmatrices;
  calibrationmatrices.push_back(cameraMatrix1);
  calibrationmatrices.push_back(distCoeffs1);
  calibrationmatrices.push_back(reprojerror);
  calibrationmatrices.push_back(error);   
//   cout << "inside function T is" << T << endl;
return calibrationmatrices;
}

