#include "calibration.hpp"
#include "writeconfig.hpp"
#include "AprilGrid.hpp"
#include <stdio.h>

int main(int argc, char* argv[]) {

  // tele
  // float grid_size = 0.024;
  // float grid_spacing = 0.696/2.4;
  // std::string grid_images_path = "../data/aprilgrid_tele";

  // wide
  float grid_size = 0.094;
  float grid_spacing = 2.3/9.4;
  std::string grid_images_path = "../data/aprilgrid_wide";

  AprilGrid Grid(6,6,grid_size,grid_spacing,0);
  
  int numberofimages = 39;
  int imagesforcalibration = 39;
  const std::vector<cv::Mat> matr = calibration(Grid,grid_images_path,imagesforcalibration,numberofimages);
  
  writeconfig(matr);
  
return 0;
}
