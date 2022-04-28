#include "libconfig.h++"
#include "opencv2/opencv.hpp"
#include <stdio.h>

using namespace std;
using namespace libconfig;

int writeconfig(const std::vector<cv::Mat> parameters) {

  cv::Mat CameraMatrix = parameters[0];
  cv::Mat distortion = parameters[1];
  cv::Mat reprojectionError = parameters[2];
  cv::Mat tagError = parameters[3];
  std::cout << tagError.cols << std::endl;
  static const char *output_file = "../config.cfg";
  
  Config cfg;

  Setting & root = cfg.getRoot();
  Setting & Header = root.add("Calibration", Setting::TypeGroup);
  Setting & Results = Header.add("Results", Setting::TypeGroup);

  Setting & Intrinsics = Results.add("Intrinsics", Setting::TypeGroup);
  Setting & fx = Intrinsics.add ("fx", libconfig::Setting::TypeFloat);
  fx = CameraMatrix.at<double>(0,0);
  Setting & fy = Intrinsics.add ("fy", libconfig::Setting::TypeFloat);
  fy = CameraMatrix.at<double>(1,1);
  Setting & cx = Intrinsics.add ("cx", libconfig::Setting::TypeFloat);
  cx = CameraMatrix.at<double>(0,2);
  Setting & cy = Intrinsics.add ("cy", libconfig::Setting::TypeFloat);
  cy = CameraMatrix.at<double>(1,2);

  Setting & Distortion = Results.add("DistortionCoefficients", Setting::TypeGroup);
  std::vector<std::string> distNames = {"k1", "k2", "p1", "p2", "k3"};
  for(int i = 0; i < distortion.cols; i++) {

    Setting & dist = Distortion.add (distNames[i], libconfig::Setting::TypeFloat);
    dist = distortion.at<double>(i);
  }

  Setting & Validation = Results.add("Validation", Setting::TypeGroup);
  Setting & reproj = Validation.add ("ReprojectionError", libconfig::Setting::TypeFloat);
  reproj = reprojectionError.at<float>(0,0);
  for(int i = 0; i < tagError.rows; i++) {

    std::stringstream name_stream;
    name_stream << "ErrorForTag" << std::to_string(i);
    Setting & error = Validation.add (name_stream.str(), libconfig::Setting::TypeFloat);
    error = tagError.at<float>(i,0);
  }

  try {
    cfg.writeFile(output_file);
    cerr << "New configuration successfully written to: " << output_file << endl;
  } catch(const FileIOException &fioex) {
    cerr << "I/O error while writing file: " << output_file << endl;
    return(EXIT_FAILURE);
  }

  return(EXIT_SUCCESS);
}
