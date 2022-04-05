#include "apriltags/Tag36h11.h"
#include "apriltags/TagDetector.h"
#include "apriltags/AprilGrid.h"
#include "vis.hpp"

#include "opencv2/opencv.hpp"
#include "libconfig.h++"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
using namespace std;
using namespace libconfig;

int writeconfig(const std::vector<cv::Mat> stereoparameters){

cv::Mat CameraMatrix = stereoparameters[0];
cv::Mat distortion = stereoparameters[1];
cv::Mat Reprojectionerror = stereoparameters[2];
cv::Mat Tagerror = stereoparameters[3];
static const char *output_file = "../newconfig1.cfg";
  Config cfg;

  Setting &root = cfg.getRoot();
  
  Setting &Header = root.add("Calibration", Setting::TypeGroup);

  Setting &Camera1 = Header.add("Camera1", Setting::TypeGroup);

  Setting &Sensor3 = Camera1.add("Results", Setting::TypeGroup);


  Setting &Intr3 = Sensor3.add("Intrinsics", Setting::TypeGroup);
  Setting & fx3 = Intr3.add ("fx", libconfig::Setting::TypeFloat);
  fx3 = CameraMatrix.at<double>(0,0);
  Setting & fy3 = Intr3.add ("fy", libconfig::Setting::TypeFloat);
  fy3 = CameraMatrix.at<double>(1,1);
  Setting & cx3 = Intr3.add ("cx", libconfig::Setting::TypeFloat);
  cx3 = CameraMatrix.at<double>(0,2);
  Setting & cy3 = Intr3.add ("cy", libconfig::Setting::TypeFloat);
  cy3 = CameraMatrix.at<double>(1,2);


  Setting &Dist3 = Sensor3.add("ValidationandDistCoeffs", Setting::TypeGroup);
  Setting & k13 = Dist3.add ("k1", libconfig::Setting::TypeFloat);
  k13 = distortion.at<double>(0);
  Setting & k23 = Dist3.add ("k2", libconfig::Setting::TypeFloat);
  k23 = distortion.at<double>(1);
  Setting & p13 = Dist3.add ("p1", libconfig::Setting::TypeFloat);
  p13 = distortion.at<double>(2);
  Setting & p23 = Dist3.add ("p2", libconfig::Setting::TypeFloat);
  p23 = distortion.at<double>(3);
  Setting & k33 = Dist3.add ("k3", libconfig::Setting::TypeFloat);
  k33 = distortion.at<double>(4);
  Setting & k43 = Dist3.add ("k4", libconfig::Setting::TypeFloat);
  k43 = 0.0;
  Setting & k53 = Dist3.add ("k5", libconfig::Setting::TypeFloat);
  k53 = 0.0;
  Setting & k63 = Dist3.add ("k6", libconfig::Setting::TypeFloat);
  k63 = 0.0;
  Setting & reproj = Dist3.add ("ReprojectionError", libconfig::Setting::TypeFloat);
  reproj = Reprojectionerror.at<float>(0,0);
  Setting & errorfortag0 = Dist3.add ("Errorfortag0", libconfig::Setting::TypeFloat);
  errorfortag0 = Tagerror.at<float>(0,0);
  Setting & errorfortag1 = Dist3.add ("Errorfortag1", libconfig::Setting::TypeFloat);
  errorfortag1 = Tagerror.at<float>(1,0);
  Setting & errorfortag2 = Dist3.add ("Errorfortag2", libconfig::Setting::TypeFloat);
  errorfortag2 = Tagerror.at<float>(2,0);
  Setting & errorfortag3 = Dist3.add ("Errorfortag3", libconfig::Setting::TypeFloat);
  errorfortag3 = Tagerror.at<float>(3,0);
  Setting & errorfortag4 = Dist3.add ("Errorfortag4", libconfig::Setting::TypeFloat);
  errorfortag4 = Tagerror.at<float>(4,0);
  Setting & errorfortag5 = Dist3.add ("Errorfortag5", libconfig::Setting::TypeFloat);
  errorfortag5 = Tagerror.at<float>(5,0);
  Setting & errorfortag6 = Dist3.add ("Errorfortag6", libconfig::Setting::TypeFloat);
  errorfortag6 = Tagerror.at<float>(6,0);

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
