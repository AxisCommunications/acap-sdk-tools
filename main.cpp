#include <string>
#include <vector>
#include <sstream>
#include "apriltags/Tag36h11.h"
#include "apriltags/TagDetector.h"
#include "apriltags/AprilGrid.h"
#include "apriltags/Test.h"
#include "opencv2/opencv.hpp"
#include "vis.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "calibration.hpp"
#include "calibrationtest.hpp"
#include "writeconfig.hpp"


int main(int argc, char* argv[]) {

  // float grid_size = 0.035;
  // float grid_spacing = 0.25;
  // int grid_rows  = 6;
  // int grid_columns = 8;
  // int grid_startID = 0;
  // AprilTags::AprilGrid Grid1(grid_rows,grid_columns,grid_size,grid_spacing,grid_startID);

  float grid_d1 = 0.19;
  float grid_d2 = 0.36;
  float grid_d3 = 0.12;
  float grid_d4 = 0.2;
  float grid_width = 0.04;
  AprilTags::Test Grid1(grid_d1,grid_d2,grid_d3,grid_d4,grid_width);
  
  int numberofimages = 40;
  int imagesforcalibration = 40;
  std::string imagefoldername1= "../data/vlog1";
  int cameranumber1 = 1;
  std::vector<cv::Mat> matr1 = calibrationtest(Grid1,imagefoldername1,cameranumber1, imagesforcalibration, numberofimages);
  
  int configfilerwrite = writeconfig(matr1,matr1,matr1);
  
return 0;
}
