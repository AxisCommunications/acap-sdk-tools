#ifndef CALIBRATION_HPP_
#define CALIBRATION_HPP_

#include "apriltags/AprilGrid.h"
#include <stdio.h>


std::vector<cv::Mat> calibration(AprilTags::AprilGrid Grid, std::string imagefoldername, int numberofimagesforcalibration, int totalnumberofimages);
#endif
