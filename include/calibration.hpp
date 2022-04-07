#ifndef CALIBRATION_HPP_
#define CALIBRATION_HPP_

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "apriltags/TagDetection.h"
#include "opencv2/opencv.hpp"
#include "apriltags/Tag36h11.h"
#include "apriltags/TagDetector.h"
#include <string>
#include <vector>
#include <sstream>
#include "apriltags/Tag36h11.h"
#include "apriltags/TagDetector.h"
#include "apriltags/AprilGrid.h"
#include "apriltags/CustomPattern.h"
#include "opencv2/opencv.hpp"
#include "vis.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


std::vector<cv::Mat> calibration(AprilTags::AprilGrid Grid, std::string imagefoldername, int numberofimagesforcalibration, int totalnumberofimages);
#endif
