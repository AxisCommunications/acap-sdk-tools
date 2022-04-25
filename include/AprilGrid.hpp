#ifndef APRILGRID_HPP
#define APRILGRID_HPP

#include <stdio.h>
#include "apriltags/TagDetection.h"

class AprilGrid {
public:

  int rows;
  int columns;
  float size;
  float spacing;
  int start_ID;
  
  AprilGrid(int rows, int columns, float size, float spacing, int start_ID){
    this->rows = rows;
    this->columns = columns;
    this->size = size;
    this->spacing = spacing;
    this->start_ID = start_ID;
  }
  
  std::vector<cv::Vec2f> imgpoints(const std::vector<AprilTags::TagDetection> detections);

  std::vector<cv::Vec3f> objpoints(const std::vector<AprilTags::TagDetection> detections);
};

#endif
