Installation of **OpenCV** and **Eigen3** is essential before starting the cmake.

Update: Install non-catkin version of ethzasl_apriltag2 from this repository https://github.com/AxisCommunications/acap-cv-tools to use the AprilGrid Test
**Build**
```
mkdir build && cd build
cmake ..
make
```

**Running sample data**
```
./main
```
**Undistorting and rectifying images**
```
./undistort
```
**Creating disparity maps**
```
cd ..
python match.py
```
