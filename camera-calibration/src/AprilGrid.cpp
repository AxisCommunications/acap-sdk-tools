#include <stdio.h>
#include "AprilGrid.hpp"
#include "apriltags/TagDetector.h"

/**

// example of instantiation of tag family:

#include "apriltags/TagFamily.h"
#include "apriltags/Tag36h11.h"
TagFamily *tag36h11 = new TagFamily(tagCodes36h11);

// available tag families:

#include "apriltags/Tag16h5.h"
#include "apriltags/Tag16h5_other.h"
#include "apriltags/Tag25h7.h"
#include "apriltags/Tag25h9.h"
#include "apriltags/Tag36h11.h"
#include "apriltags/Tag36h11_other.h"
#include "apriltags/Tag36h9.h"

*/

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

