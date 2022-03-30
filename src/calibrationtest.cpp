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
  std::vector<std::vector<cv::Vec2f>> timagepoints2;
  std::vector<std::vector<cv::Vec3f>> tobjectpoints2;
  std::string imagefoldername0 = imagefoldername; 
  std::string cameranum = "_1";
  std::string zeross = "00000";
  int noimg = numberofimagesforcalibration;
  int totalnoimg = totalnumberofimages;
  int accimg = 0;
  for(int i = 0; accimg < noimg; i++){
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
      std::vector<cv::Vec2f>  imagepoints1 = Grid3.imgpointstest(detections1);     
      std::vector<cv::Vec3f>  objectpoints1 = Grid3.objpointstest(detections1, Grid3.d11, Grid3.d12, Grid3.d13, Grid3.d14, Grid3.width);
      std::vector<cv::Vec2f>  imagepoints2 = Grid3.imgpointstest(detections2);     
      std::vector<cv::Vec3f>  objectpoints2 = Grid3.objpointstest(detections2, Grid3.d11, Grid3.d12, Grid3.d13, Grid3.d14, Grid3.width);      
      // cv::Mat objectpointstestmat1 = cv::Mat(objectpoints1);
      // cout << "M = " << endl << " "  << objectpointstestmat1 << endl << endl;
      //int grid_points = 28;
      size_t threshold = 6;
      cout << "detections     " << detections1.size() << endl;
      if(detections1.size() > threshold) {
        timagepoints1.push_back(imagepoints1);

        timagepoints2.push_back(imagepoints2);
        tobjectpoints1.push_back(objectpoints1);

        tobjectpoints2.push_back(objectpoints2);
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
  flag1 |= cv::CALIB_FIX_ASPECT_RATIO;
  double reprojerror1 = cv::calibrateCamera(tobjectpoints1, timagepoints1, cv::Size(3,3), cameraMatrix1, distCoeffs1, R1, T1,flag1);
  double reprojerror2 = cv::calibrateCamera(tobjectpoints2, timagepoints2, cv::Size(3,3), cameraMatrix2, distCoeffs2, R2, T2,flag1);
  newcameraMatrix1 = cv::getOptimalNewCameraMatrix(cameraMatrix1,distCoeffs1,cv::Size(3,3),1,cv::Size(3,3),0);
  newcameraMatrix2 = cv::getOptimalNewCameraMatrix(cameraMatrix2,distCoeffs2,cv::Size(3,3),1,cv::Size(3,3),0);
  std::cout << "cameraMatrix of sensor 0: " << cameraMatrix1 << std::endl;
  std::cout << "distCoeffs of sensor 0 : " << distCoeffs1 << std::endl;
  std::cout << "cameraMatrix of sensor 1: " << cameraMatrix2 << std::endl;
  std::cout << "distCoeffs of sensor 1 : " << distCoeffs2 << std::endl;
  std::cout << "Reprojection error of sensor 0 : " << reprojerror1 << std::endl;
  std::cout << "Reprojection error of sensor 1 : " << reprojerror2 << std::endl;
  std::cout << "New Camera Matrix of sensor 0 : " << newcameraMatrix1 << std::endl;
  std::cout << "Rotation Matrix of sensor 0 : " << R1.rows << " " << endl << T1.rows << T1.cols << std::endl;




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

  //  cv::Mat reprojimgpointstest = cameraMatrix1*objectpointstestmat;

  //  cv::resize(objectpointstestmat,objectpointstestmat, cv::Size(3,7));
  // cv::Mat_<float> Testmat = objectpointstestmat.row(0).t();
  // cv::Mat_<float> imgTestmat = imgpointstestmat.row(0).t();

  // float var = Testmat.at<float>(0,1);
  // cv::Mat objvec = cv::Mat({Testmat.at<float>(0,0), Testmat.at<float>(0,1), Testmat.at<float>(0,2)});
  // cv::Mat imgvec = cv::Mat({imgTestmat.at<float>(0,0), imgTestmat.at<float>(0,1), Testmat.at<float>(0,2)});
  // std::vector<cv::Vec3f> v1(Testmat.begin(), Testmat.end());
  // int rows = objvec.rows;
  // int cols = objvec.cols;
  // std::cout << rows << " " << cols << std::endl;
  // cv::Mat_<float> cammat = cameraMatrix1;
  // cv::Mat reprojimgpointstest = cammat*objvec ;
  // cv::Mat error = imgvec - reprojimgpointstest;
  // std::cout << cv::norm(error, cv::NORM_L2)<< std::endl;
  // cout << "M = " << endl << " "  << R1 << endl << endl << imgvec << endl << endl << reprojimgpointstest << endl;


  cv::Mat rotmat = R1.row(13);
  cv::Mat tramat = T1.row(13);
  
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
    cout << "error for tag " << i << endl << cumulerror/4 << endl;
  }
  // cout << "error is " << endl << endl << cumulerror/28 << endl;
  // cout << "projected img points = " << endl << " " << img << endl << "original image points = " << endl << orgimg << endl << endl << "error is " << endl << endl << cumulerror << endl;
  // for (int i = 1; i < 8; ++i) {
  //   float error = 0;
  //   for (int j = 4*i - 4; i < 4*i; ++j) {
  //     cv::Mat_<float> Testmat = objectpointstestmat.row(j);
  //     cv::Mat imgvec;
  //     cv::projectPoints(Testmat,rotmat,tramat,cameraMatrix1,distCoeffs1,imgvec);
  //     cv::Mat orgimgvec = imgpointstestmat.row(j);
  //     error = cv::norm(orgimgvec - imgvec, cv::NORM_L2);
  //   }
  //   err.push_back(error);
  // }
  // cout << "M = " << endl << " " << err << endl << imgvec << endl << endl << orgimgvec;

  // for (size_t i = 0; i < objectpointstest.size(); ++i) {

  //   cv::Mat_<float> Testmat = objectpointstestmat.row(i).t();
  //   cv::Mat_<float> imgTestmat = imgpointstestmat.row(i).t();

  //   cv::Mat objvec = cv::Mat({Testmat.at<float>(0,0), Testmat.at<float>(0,1), Testmat.at<float>(0,2)});
  //   cv::Mat reprojimgpointstest = cammat*objvec ;
  //   cv::Mat imgvec = cv::Mat({imgTestmat.at<float>(0,0), imgTestmat.at<float>(0,1), Testmat.at<float>(0,2)});




  



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

