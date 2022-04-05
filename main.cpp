#include "customCalibration.hpp"
#include "writeconfig.hpp"
#include "apriltags/CustomPattern.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

  // float grid_size = 0.035;
  // float grid_spacing = 0.25;
  // int grid_rows  = 6;
  // int grid_columns = 8;
  // int grid_startID = 0;
  // AprilTags::AprilGrid Grid1(grid_rows,grid_columns,grid_size,grid_spacing,grid_startID);

  
  float grid_d1 = 0.261;
  float grid_d2 = 0.471;
  float grid_d3 = 0.161;
  float grid_d4 = 0.271;
  float grid_width = 0.026;
  AprilTags::CustomPattern Grid(grid_d1,grid_d2,grid_d3,grid_d4,grid_width);
  
  int numberofimages = 21;
  int imagesforcalibration = 21;
  std::string imagefoldername1= "../data/vlogtest";
  int cameranumber1 = 1;
  const std::vector<cv::Mat> matr = customCalibration(Grid,imagefoldername1,cameranumber1,imagesforcalibration,numberofimages);
  
  writeconfig(matr);
  
return 0;
}
