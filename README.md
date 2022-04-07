# Camera Calibration

This code is used to calibrate an Axis camera using a printed pattern. To know more about the process, visit our [documentation](https://axiscommunications.github.io/acap-documentation/).

**Installation**
1. Installation of **OpenCV** and **Eigen3** is essential before starting the cmake.
2. Install non-catkin version of ethzasl_apriltag2 from this [repository](https://github.com/AxisCommunications/acap-cv-tools) to use AprilGrid.
3. Build:
```
mkdir build && cd build
cmake ..
make
```

**Running sample data**
```
./main
```

**Additional functionality**
Function `displayDetection` in `vis.cpp` displays the AprilTag detections on top of an image.