# Camera Calibration

This code is used to calibrate an Axis camera using a printed pattern. To know more about the process, visit our [documentation](https://axiscommunications.github.io/acap-documentation/docs/develop/camera-calibration.html).

![calibration_diagram](data/calibration_diagram.svg)


**Usage**

1. [Create](https://github.com/ethz-asl/kalibr/wiki/calibration-targets#a-aprilgrid) and print an AprilTag grid.
2. Take sample pictures with the Axis camera pointing towards the AprilTag grid, including different positions and orientations of the grid.
3. Write the parameters used to create the pattern and the modify the image folder in [`main.cpp`](main.cpp).
4. Build the Docker image that will download and compile all the calibration code.

    ```docker build -t calibration-image .```

5. Run the Docker image. The calibration code will automatically run to obtain the estimated calibration parameters, which are saved in `config.cfg`.

    ```docker run -it --name calibration calibration-image```

6. Copy the calibration parameters.

    ```docker cp calibration:/app/config.cfg .```

Some validation tests were performed with an Axis Q1656 with the following AprilGrid parameters:

- Tele capturing (full zoom):

   ```
   grid_size: 0.024;
   grid_spacing: 0.696/2.4;
   grid_images_path: "../data/aprilgrid_tele";
   rows: 6;
   columns: 6;
   ```

- Wide capturing (no zoom):

   ```
   grid_size: 0.094;
   grid_spacing: 2.3/9.4;
   grid_images_path: "../data/aprilgrid_wide";
   rows: 6;
   columns: 6;
   ```

