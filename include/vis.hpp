#ifndef VIS_HPP_
#define VIS_HPP_

#include <vector>

#include "apriltags/TagDetection.h"
#include "opencv2/opencv.hpp"

void displayDetection(const cv::Mat& image,
                      const std::vector<AprilTags::TagDetection>& detections);
#endif  // A_HPP_
