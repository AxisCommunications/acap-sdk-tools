#ifndef CUSTOMCALIBRATION_HPP_
#define CUSTOMCALIBRATION_HPP_

#include "apriltags/CustomPattern.h"
#include <stdio.h>

std::vector<cv::Mat> customCalibration(AprilTags::CustomPattern Grid, std::string imagefoldername, int numberofimagesforcalibration,  int totalnumberofimages);
#endif
