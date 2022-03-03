#ifndef WRITECONFIG_HPP_
#define WRITECONFIG_HPP_

#include <vector>

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


int writeconfig(const std::vector<cv::Mat> stereoparameters, const std::vector<cv::Mat> stereoparameters1, const std::vector<cv::Mat> stereoparameters2);
#endif
