/**
 * Copyright (C) 2022 Axis Communications AB, Lund, Sweden
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include "AprilGrid.hpp"
#include "apriltags/TagDetector.h"

std::vector<cv::Vec2f> AprilGrid::imgpoints(const std::vector<AprilTags::TagDetection> detections) {

  std::vector<cv::Vec2f> imagepoints;

  int q = this->start_ID + this->rows*this->columns;
  for (int h = this->start_ID; h < q; h++){
    for (size_t i = 0; i < detections.size(); ++i) {
      const auto& det = detections[i];
      if (det.id == h){
        for (int j = 0; j < 4; ++j){
          cv::Vec2f currentpoint = {det.p[j].first,det.p[j].second};
          //std::cout << currentpoint << endl ;
          imagepoints.push_back(currentpoint);
        }
      }
    }    
  }
  return imagepoints;
}


std::vector<cv::Vec3f> AprilGrid::objpoints(const std::vector<AprilTags::TagDetection> detections) {
  std::vector<cv::Vec3f> newobjectpoints;
  
  float c = this->spacing*this->size;
  float sum = c + this->size;
  int q = this->start_ID + this->rows*this->columns;
  for (int h = this->start_ID; h < q; h++){
    for (size_t i = 0; i < detections.size(); ++i) {
      const auto& det = detections[i];
      if (det.id == h){
        int jdash = h % this->columns;
        int idash = (h-jdash)/this->columns;
        std::vector<cv::Vec3f > obj;
        float toprightx = (float)jdash * sum;
        float toprighty = (float)idash * sum;
        cv::Vec3f topright = {toprightx, toprighty, 0};
        cv::Vec3f topleft = {(float)jdash * sum + this->size, (float)idash * sum, 0};
        cv::Vec3f bottomleft = {(float)jdash * sum + this->size, (float)idash * sum + this->size, 0};
        cv::Vec3f bottomright = {(float)jdash * sum, (float)idash * sum + this->size, 0};
        newobjectpoints.push_back(topright);
        newobjectpoints.push_back(topleft);
        newobjectpoints.push_back(bottomleft);
        newobjectpoints.push_back(bottomright); 
      }
    }    
  }
  return newobjectpoints;
}

