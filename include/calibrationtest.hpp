#ifndef CALIBRATIONTEST_HPP_
#define CALIBRATIONTEST_HPP_

#include "apriltags/Test.h"
#include <stdio.h>

std::vector<cv::Mat> calibrationtest(AprilTags::Test Grid, std::string imagefoldername, int cameranumber, int numberofimagesforcalibration,  int totalnumberofimages);
#endif
