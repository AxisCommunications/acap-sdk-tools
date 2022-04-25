#ifndef CALIBRATION_HPP_
#define CALIBRATION_HPP_

#include "AprilGrid.hpp"
#include <stdio.h>


std::vector<cv::Mat> calibration(AprilGrid Grid, std::string imagefoldername, int numberofimagesforcalibration, int totalnumberofimages);
#endif
