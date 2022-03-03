#include "apriltags/Tag36h11.h"
#include "apriltags/TagDetector.h"
#include "opencv2/opencv.hpp"
#include "vis.hpp"
#include "apriltags/Tag36h11.h"
#include "apriltags/TagDetector.h"
#include "apriltags/AprilGrid.h"
#include "opencv2/opencv.hpp"
#include "apriltags/TagDetector.h"
#include "opencv2/opencv.hpp"
#include "vis.hpp"
#include "libconfig.h++"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
using namespace libconfig;

int writeconfig(const std::vector<cv::Mat> stereoparameters0, const std::vector<cv::Mat> stereoparameters1, const std::vector<cv::Mat> stereoparameters2){

cv::Mat CameraMatrix1 = stereoparameters0[0];
cv::Mat distortion1 = stereoparameters0[1];
cv::Mat CameraMatrix2 = stereoparameters0[2];
cv::Mat distortion2 = stereoparameters0[3];
cv::Mat Rotmat12 = stereoparameters0[4];
cv::Mat Translmat12 = stereoparameters0[5];

static const char *output_file = "../newconfig1.cfg";
  Config cfg;

  Setting &root = cfg.getRoot();

  // Setting &string = root.add("undistort", Setting::TypeString)
  Setting & undistort = root.add ("undistort", libconfig::Setting::TypeBoolean);
  undistort = true;
  Setting & device0 = root.add ("device-0", libconfig::Setting::TypeString);
  device0 = "/dev/video0";
  Setting & device1 = root.add ("device-1", libconfig::Setting::TypeString);
  device1 = "/dev/video1";
  Setting & device2 = root.add ("device-2", libconfig::Setting::TypeString);
  device2 = "/dev/video2";
  Setting & device3 = root.add ("device-3", libconfig::Setting::TypeString);
  device3 = "/dev/video3";
  Setting & device4 = root.add ("device-4", libconfig::Setting::TypeString);
  device4 = "/dev/video4";
  Setting & device5 = root.add ("device-5", libconfig::Setting::TypeString);
  device5 = "/dev/video5";
  Setting & intshift = root.add ("intensity-shift", libconfig::Setting::TypeInt);
  intshift = 6;



  Setting &Header = root.add("Header", Setting::TypeGroup);
  Setting & version = Header.add ("version", libconfig::Setting::TypeString);
  version = "1.0";
  Setting & ncameras = Header.add ("ncameras", libconfig::Setting::TypeInt);
  ncameras = 3;



  Setting &Camera0 = Header.add("Camera0", Setting::TypeGroup);
  Setting & nsensors = Camera0.add ("nsensors", libconfig::Setting::TypeInt);
  nsensors = 2;
  Setting & colortype = Camera0.add ("color-type", libconfig::Setting::TypeInt);
  colortype = 0;
  Setting &dim = Camera0.add("dim", Setting::TypeArray);
  dim.add(Setting::TypeInt) = 752;
  dim.add(Setting::TypeInt) = 480;
  dim.add(Setting::TypeInt) = 1;
  dim.add(Setting::TypeInt) = 1;


  Setting &Sensor0 = Camera0.add("Sensor0", Setting::TypeGroup);


  Setting & rotation = Sensor0.add ("rotated", libconfig::Setting::TypeBoolean);
  rotation = false;


  Setting &Intr = Sensor0.add("Intrinsics", Setting::TypeGroup);
  Setting & fx = Intr.add ("fx", libconfig::Setting::TypeFloat);
  fx = CameraMatrix1.at<double>(0,0);
  Setting & fy = Intr.add ("fy", libconfig::Setting::TypeFloat);
  fy = CameraMatrix1.at<double>(1,1);
  Setting & cx = Intr.add ("cx", libconfig::Setting::TypeFloat);
  cx = CameraMatrix1.at<double>(0,2);
  Setting & cy = Intr.add ("cy", libconfig::Setting::TypeFloat);
  cy = CameraMatrix1.at<double>(1,2);


  Setting &Dist = Sensor0.add("Dist", Setting::TypeGroup);
  Setting & k1 = Dist.add ("k1", libconfig::Setting::TypeFloat);
  k1 = distortion1.at<double>(0);
  Setting & k2 = Dist.add ("k2", libconfig::Setting::TypeFloat);
  k2 = distortion1.at<double>(1);
  Setting & p1 = Dist.add ("p1", libconfig::Setting::TypeFloat);
  p1 = distortion1.at<double>(2);
  Setting & p2 = Dist.add ("p2", libconfig::Setting::TypeFloat);
  p2 = distortion1.at<double>(3);
  Setting & k3 = Dist.add ("k3", libconfig::Setting::TypeFloat);
  k3 = distortion1.at<double>(4);
  Setting & k4 = Dist.add ("k4", libconfig::Setting::TypeFloat);
  k4 = 0.0;
  Setting & k5 = Dist.add ("k5", libconfig::Setting::TypeFloat);
  k5 = 0.0;
  Setting & k6 = Dist.add ("k6", libconfig::Setting::TypeFloat);
  k6 = 0.0;


  Setting &Ext = Sensor0.add("Extrinsics", Setting::TypeArray);

  Ext.add(Setting::TypeFloat) = 1.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 1.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 1.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 0.0;
  Ext.add(Setting::TypeFloat) = 1.0;
  



  Setting &Sensor1 = Camera0.add("Sensor1", Setting::TypeGroup);


  Setting & rotation1 = Sensor1.add ("rotated", libconfig::Setting::TypeBoolean);
  rotation1 = false;


  Setting &Intr1 = Sensor1.add("Intrinsics", Setting::TypeGroup);
  Setting & fx1 = Intr1.add ("fx", libconfig::Setting::TypeFloat);
  fx1 = CameraMatrix2.at<double>(0,0);
  Setting & fy1 = Intr1.add ("fy", libconfig::Setting::TypeFloat);
  fy1 = CameraMatrix2.at<double>(1,1);
  Setting & cx1 = Intr1.add ("cx", libconfig::Setting::TypeFloat);
  cx1 = CameraMatrix2.at<double>(0,2);
  Setting & cy1 = Intr1.add ("cy", libconfig::Setting::TypeFloat);
  cy1 = CameraMatrix2.at<double>(1,2);


  Setting &Dist1 = Sensor1.add("Dist", Setting::TypeGroup);
  Setting & k11 = Dist1.add ("k1", libconfig::Setting::TypeFloat);
  k11 = distortion2.at<double>(0);
  Setting & k21 = Dist1.add ("k2", libconfig::Setting::TypeFloat);
  k21 = distortion2.at<double>(1);
  Setting & p11 = Dist1.add ("p1", libconfig::Setting::TypeFloat);
  p11 = distortion2.at<double>(2);
  Setting & p21 = Dist1.add ("p2", libconfig::Setting::TypeFloat);
  p21 = distortion2.at<double>(3);
  Setting & k31 = Dist1.add ("k3", libconfig::Setting::TypeFloat);
  k31 = distortion2.at<double>(4);
  Setting & k41 = Dist1.add ("k4", libconfig::Setting::TypeFloat);
  k41 = 0.0;
  Setting & k51 = Dist1.add ("k5", libconfig::Setting::TypeFloat);
  k51 = 0.0;
  Setting & k61 = Dist1.add ("k6", libconfig::Setting::TypeFloat);
  k61 = 0.0;



  Setting &Ext1 = Sensor1.add("Extrinsics", Setting::TypeArray);

  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(0,0);
  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(0,1);
  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(0,2);
  Ext1.add(Setting::TypeFloat) = Translmat12.at<float>(0,0);
  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(1,0);
  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(1,1);
  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(1,2);
  Ext1.add(Setting::TypeFloat) = Translmat12.at<float>(0,1);
  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(2,0);
  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(2,1);
  Ext1.add(Setting::TypeFloat) = Rotmat12.at<double>(2,2);
  Ext1.add(Setting::TypeFloat) = Translmat12.at<float>(0,2);
  Ext1.add(Setting::TypeFloat) = 0.0;
  Ext1.add(Setting::TypeFloat) = 0.0;
  Ext1.add(Setting::TypeFloat) = 0.0;
  Ext1.add(Setting::TypeFloat) = 1.0;

//Now we do for the second pair

cv::Mat CameraMatrix3 = stereoparameters1[0];
cv::Mat distortion3 = stereoparameters1[1];
cv::Mat CameraMatrix4 = stereoparameters1[2];
cv::Mat distortion4 = stereoparameters1[3];
cv::Mat Rotmat34 = stereoparameters1[4];
cv::Mat Translmat34 = stereoparameters1[5];
  
  Setting &Camera1 = Header.add("Camera1", Setting::TypeGroup);
  Setting & nsensors3 = Camera1.add ("nsensors", libconfig::Setting::TypeInt);
  nsensors3 = 2;
  Setting & colortype3 = Camera1.add ("color-type", libconfig::Setting::TypeInt);
  colortype3 = 0;
  Setting &dim3 = Camera1.add("dim", Setting::TypeArray);
  dim3.add(Setting::TypeInt) = 752;
  dim3.add(Setting::TypeInt) = 480;
  dim3.add(Setting::TypeInt) = 1;
  dim3.add(Setting::TypeInt) = 1;


  Setting &Sensor3 = Camera1.add("Sensor0", Setting::TypeGroup);


  Setting & rotation3 = Sensor3.add ("rotated", libconfig::Setting::TypeBoolean);
  rotation3 = false;


  Setting &Intr3 = Sensor3.add("Intrinsics", Setting::TypeGroup);
  Setting & fx3 = Intr3.add ("fx", libconfig::Setting::TypeFloat);
  fx3 = CameraMatrix3.at<double>(0,0);
  Setting & fy3 = Intr3.add ("fy", libconfig::Setting::TypeFloat);
  fy3 = CameraMatrix3.at<double>(1,1);
  Setting & cx3 = Intr3.add ("cx", libconfig::Setting::TypeFloat);
  cx3 = CameraMatrix3.at<double>(0,2);
  Setting & cy3 = Intr3.add ("cy", libconfig::Setting::TypeFloat);
  cy3 = CameraMatrix3.at<double>(1,2);


  Setting &Dist3 = Sensor3.add("Dist", Setting::TypeGroup);
  Setting & k13 = Dist3.add ("k1", libconfig::Setting::TypeFloat);
  k13 = distortion3.at<double>(0);
  Setting & k23 = Dist3.add ("k2", libconfig::Setting::TypeFloat);
  k23 = distortion3.at<double>(1);
  Setting & p13 = Dist3.add ("p1", libconfig::Setting::TypeFloat);
  p13 = distortion3.at<double>(2);
  Setting & p23 = Dist3.add ("p2", libconfig::Setting::TypeFloat);
  p23 = distortion3.at<double>(3);
  Setting & k33 = Dist3.add ("k3", libconfig::Setting::TypeFloat);
  k33 = distortion3.at<double>(4);
  Setting & k43 = Dist3.add ("k4", libconfig::Setting::TypeFloat);
  k43 = 0.0;
  Setting & k53 = Dist3.add ("k5", libconfig::Setting::TypeFloat);
  k53 = 0.0;
  Setting & k63 = Dist3.add ("k6", libconfig::Setting::TypeFloat);
  k63 = 0.0;


  Setting &Ext3 = Sensor3.add("Extrinsics", Setting::TypeArray);

  Ext3.add(Setting::TypeFloat) = 1.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 1.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 1.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 0.0;
  Ext3.add(Setting::TypeFloat) = 1.0;
  



  Setting &Sensor4 = Camera1.add("Sensor1", Setting::TypeGroup);


  Setting & rotation4 = Sensor4.add ("rotated", libconfig::Setting::TypeBoolean);
  rotation4 = false;


  Setting &Intr4 = Sensor4.add("Intrinsics", Setting::TypeGroup);
  Setting & fx4 = Intr4.add ("fx", libconfig::Setting::TypeFloat);
  fx4 = CameraMatrix4.at<double>(0,0);
  Setting & fy4 = Intr4.add ("fy", libconfig::Setting::TypeFloat);
  fy4 = CameraMatrix4.at<double>(1,1);
  Setting & cx4 = Intr4.add ("cx", libconfig::Setting::TypeFloat);
  cx4 = CameraMatrix4.at<double>(0,2);
  Setting & cy4 = Intr4.add ("cy", libconfig::Setting::TypeFloat);
  cy4 = CameraMatrix4.at<double>(1,2);


  Setting &Dist4 = Sensor4.add("Dist", Setting::TypeGroup);
  Setting & k14 = Dist4.add ("k1", libconfig::Setting::TypeFloat);
  k14 = distortion4.at<double>(0);
  Setting & k24 = Dist4.add ("k2", libconfig::Setting::TypeFloat);
  k24 = distortion4.at<double>(1);
  Setting & p14 = Dist4.add ("p1", libconfig::Setting::TypeFloat);
  p14 = distortion4.at<double>(2);
  Setting & p24 = Dist4.add ("p2", libconfig::Setting::TypeFloat);
  p24 = distortion4.at<double>(3);
  Setting & k34 = Dist4.add ("k3", libconfig::Setting::TypeFloat);
  k34 = distortion4.at<double>(4);
  Setting & k44 = Dist4.add ("k4", libconfig::Setting::TypeFloat);
  k44 = 0.0;
  Setting & k54 = Dist4.add ("k5", libconfig::Setting::TypeFloat);
  k54 = 0.0;
  Setting & k64 = Dist4.add ("k6", libconfig::Setting::TypeFloat);
  k64 = 0.0;



  Setting &Ext4 = Sensor4.add("Extrinsics", Setting::TypeArray);

  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(0,0);
  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(0,1);
  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(0,2);
  Ext4.add(Setting::TypeFloat) = Translmat34.at<float>(0,0);
  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(1,0);
  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(1,1);
  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(1,2);
  Ext4.add(Setting::TypeFloat) = Translmat34.at<float>(0,1);
  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(2,0);
  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(2,1);
  Ext4.add(Setting::TypeFloat) = Rotmat34.at<double>(2,2);
  Ext4.add(Setting::TypeFloat) = Translmat34.at<float>(0,2);
  Ext4.add(Setting::TypeFloat) = 0.0;
  Ext4.add(Setting::TypeFloat) = 0.0;
  Ext4.add(Setting::TypeFloat) = 0.0;
  Ext4.add(Setting::TypeFloat) = 1.0;

//Now we do for the third pair

cv::Mat CameraMatrix5 = stereoparameters2[0];
cv::Mat distortion5 = stereoparameters2[1];
cv::Mat CameraMatrix6 = stereoparameters2[2];
cv::Mat distortion6 = stereoparameters2[3];
cv::Mat Rotmat56 = stereoparameters2[4];
cv::Mat Translmat56 = stereoparameters2[5];
  
  Setting &Camera2 = Header.add("Camera2", Setting::TypeGroup);
  Setting & nsensors5 = Camera2.add ("nsensors", libconfig::Setting::TypeInt);
  nsensors5 = 2;
  Setting & colortype5 = Camera2.add ("color-type", libconfig::Setting::TypeInt);
  colortype5 = 0;
  Setting &dim5 = Camera2.add("dim", Setting::TypeArray);
  dim5.add(Setting::TypeInt) = 752;
  dim5.add(Setting::TypeInt) = 480;
  dim5.add(Setting::TypeInt) = 1;
  dim5.add(Setting::TypeInt) = 1;


  Setting &Sensor5 = Camera2.add("Sensor0", Setting::TypeGroup);


  Setting & rotation5 = Sensor5.add ("rotated", libconfig::Setting::TypeBoolean);
  rotation5 = false;


  Setting &Intr5 = Sensor5.add("Intrinsics", Setting::TypeGroup);
  Setting & fx5 = Intr5.add ("fx", libconfig::Setting::TypeFloat);
  fx5 = CameraMatrix5.at<double>(0,0);
  Setting & fy5 = Intr5.add ("fy", libconfig::Setting::TypeFloat);
  fy5 = CameraMatrix5.at<double>(1,1);
  Setting & cx5 = Intr5.add ("cx", libconfig::Setting::TypeFloat);
  cx5 = CameraMatrix5.at<double>(0,2);
  Setting & cy5 = Intr5.add ("cy", libconfig::Setting::TypeFloat);
  cy5 = CameraMatrix5.at<double>(1,2);


  Setting &Dist5 = Sensor5.add("Dist", Setting::TypeGroup);
  Setting & k15 = Dist5.add ("k1", libconfig::Setting::TypeFloat);
  k15 = distortion5.at<double>(0);
  Setting & k25 = Dist5.add ("k2", libconfig::Setting::TypeFloat);
  k25 = distortion5.at<double>(1);
  Setting & p15 = Dist5.add ("p1", libconfig::Setting::TypeFloat);
  p15 = distortion5.at<double>(2);
  Setting & p25 = Dist5.add ("p2", libconfig::Setting::TypeFloat);
  p25 = distortion5.at<double>(3);
  Setting & k35 = Dist5.add ("k3", libconfig::Setting::TypeFloat);
  k35 = distortion5.at<double>(4);
  Setting & k45 = Dist5.add ("k4", libconfig::Setting::TypeFloat);
  k45 = 0.0;
  Setting & k55 = Dist5.add ("k5", libconfig::Setting::TypeFloat);
  k55 = 0.0;
  Setting & k65 = Dist5.add ("k6", libconfig::Setting::TypeFloat);
  k65 = 0.0;


  Setting &Ext5 = Sensor5.add("Extrinsics", Setting::TypeArray);

  Ext5.add(Setting::TypeFloat) = 1.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 1.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 1.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 0.0;
  Ext5.add(Setting::TypeFloat) = 1.0;



  Setting &Sensor6 = Camera2.add("Sensor1", Setting::TypeGroup);


  Setting & rotation6 = Sensor6.add ("rotated", libconfig::Setting::TypeBoolean);
  rotation6 = false;


  Setting &Intr6 = Sensor6.add("Intrinsics", Setting::TypeGroup);
  Setting & fx6 = Intr6.add ("fx", libconfig::Setting::TypeFloat);
  fx6 = CameraMatrix6.at<double>(0,0);
  Setting & fy6 = Intr6.add ("fy", libconfig::Setting::TypeFloat);
  fy6 = CameraMatrix6.at<double>(1,1);
  Setting & cx6 = Intr6.add ("cx", libconfig::Setting::TypeFloat);
  cx6 = CameraMatrix6.at<double>(0,2);
  Setting & cy6 = Intr6.add ("cy", libconfig::Setting::TypeFloat);
  cy6 = CameraMatrix6.at<double>(1,2);


  Setting &Dist6 = Sensor6.add("Dist", Setting::TypeGroup);
  Setting & k16 = Dist6.add ("k1", libconfig::Setting::TypeFloat);
  k16 = distortion6.at<double>(0);
  Setting & k26 = Dist6.add ("k2", libconfig::Setting::TypeFloat);
  k26 = distortion6.at<double>(1);
  Setting & p16 = Dist6.add ("p1", libconfig::Setting::TypeFloat);
  p16 = distortion6.at<double>(2);
  Setting & p26 = Dist6.add ("p2", libconfig::Setting::TypeFloat);
  p26 = distortion6.at<double>(3);
  Setting & k36 = Dist6.add ("k3", libconfig::Setting::TypeFloat);
  k36 = distortion6.at<double>(4);
  Setting & k46 = Dist6.add ("k4", libconfig::Setting::TypeFloat);
  k46 = 0.0;
  Setting & k56 = Dist6.add ("k5", libconfig::Setting::TypeFloat);
  k56 = 0.0;
  Setting & k66 = Dist6.add ("k6", libconfig::Setting::TypeFloat);
  k66 = 0.0;



  Setting &Ext6 = Sensor6.add("Extrinsics", Setting::TypeArray);

  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(0,0);
  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(0,1);
  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(0,2);
  Ext6.add(Setting::TypeFloat) = Translmat56.at<float>(0,0);
  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(1,0);
  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(1,1);
  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(1,2);
  Ext6.add(Setting::TypeFloat) = Translmat56.at<float>(0,1);
  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(2,0);
  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(2,1);
  Ext6.add(Setting::TypeFloat) = Rotmat56.at<double>(2,2);
  Ext6.add(Setting::TypeFloat) = Translmat56.at<float>(0,2);
  Ext6.add(Setting::TypeFloat) = 0.0;
  Ext6.add(Setting::TypeFloat) = 0.0;
  Ext6.add(Setting::TypeFloat) = 0.0;
  Ext6.add(Setting::TypeFloat) = 1.0;


  try
  {
    cfg.writeFile(output_file);
    cerr << "New configuration successfully written to: " << output_file
         << endl;
  }
  catch(const FileIOException &fioex)
  {
    cerr << "I/O error while writing file: " << output_file << endl;
    return(EXIT_FAILURE);
  }

  return(EXIT_SUCCESS);



}
