#include "calibration.hpp"
#include "writeconfig.hpp"
#include "AprilGrid.hpp"
#include <stdio.h>

int main(int argc, char* argv[]) {

  // AprilGrid parameters
  float grid_size = 0.094;
  float grid_spacing = 2.3/9.4;
  std::string grid_images_path = "../data/aprilgrid_wide";
  int rows = 6;
  int columns = 6;

  AprilGrid Grid(rows,columns,grid_size,grid_spacing,0);

  int numberofimages = 39;
  int imagesforcalibration = 39;
  const std::vector<cv::Mat> matr = calibration(Grid,grid_images_path,imagesforcalibration,numberofimages);
  
  writeconfig(matr);
  
  return 0;
}
