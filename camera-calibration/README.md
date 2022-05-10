*Copyright (C) 2022, Axis Communications AB, Lund, Sweden. All Rights Reserved.*

# Camera calibration

Images captured by an Axis camera are sometimes visibly distorted in the edges. That is because Axis cameras prioritize capturing a wide area over producing rectilinear images. Distortion can make it difficult to detect objects or to measure distances. To correct this, we can calibrate the image and straighten it.

This README file explains how to obtain calibration parameters of an Axis camera using a dataset of images captured by the same camera and Apriltag detection library from [ETH-Z](https://github.com/ethz-asl/ethzasl_apriltag2).

We go through a step by step process needed, starting from making a dataset with the Axis camera and finally calibrating it. To know more about the process indepth, visit our [documentation](https://axiscommunications.github.io/acap-documentation/docs/develop/camera-calibration.html).

![Calibration_diagram](data/calibration_diagram.svg)

## Requirements

- [Docker](https://docs.docker.com/get-docker/) version 20.10.14 or higher

## Structure of this tool

Below is the structure and scripts used in the tool:

```sh
camera-calibration
├── data
│   ├── aprilgrid_tele
│   └── aprilgird_wide
├── include
│    ├── AprilGrid.hpp
│    ├── calibration.hpp
│    └── writeconfig.hpp
├── src
│    ├── AprilGrid.cpp
│    ├── calibration.cpp
│    └── writeconfig.cpp
├── CMakelists.txt
├── CMakelists-detection.txt
├── Dockerfile
├── main.cpp
└── README.md
```

- **data/aprilgrid_tele** - Dataset consisting of AprilGrid images captured in Tele mode using an Axis camera.
- **data/aprilgrid_wide** - Dataset consisting of AprilGrid images captured in Wide mode using an Axis camera.
- **src/AprilGrid.cpp** - Defines two functions to compute object and image points.
- **src/calibration.cpp** - Collects each image from the captured dataset, detects tags and computes calibration parameters.
- **Dockerfile** - Dockerfile which builds the image that runs the whole calibration procedure explained below.
- **main.cpp** - Updating/Replacing the AprilTag grid parameters such as `rows`, `columns`, `grid_size`, `grid_spacing` and path to the image folder should be done in this file.

## Quicksteps

1. [Create](https://github.com/ethz-asl/kalibr/wiki/calibration-targets#a-aprilgrid) and print an AprilTag grid.
2. Take sample pictures with the Axis camera pointing towards the AprilTag grid, including different positions and orientations of the grid.
3. Write the parameters used to create the pattern and the modify the image folder in [`main.cpp`](main.cpp).
4. Build the Docker image that will download and compile all the calibration code.

    ```sh
    docker build . -t <APP_IMAGE>
    ```

    where `<APP_IMAGE>` is the desired name of the Docker image, e.g. *calibration*

5. Run the Docker image. The calibration code will automatically run to obtain the estimated calibration parameters, which are saved in `config.cfg`.

    ```sh
    docker run -it --name <APP_CONTAINER> <APP_IMAGE>
    ```
    
    where `<APP_CONTAINER>` is the desired name of the Docker container, e.g. *calibration-container*

6. Copy the calibration parameters.

    ```sh
    docker cp <APP_CONTAINER>:/app/config.cfg .
    ```

### Validation results

Some validation tests were performed with an Axis Q1656 with the following AprilGrid parameters:

- Tele capturing (full zoom):

   ```cpp
   grid_size = 0.024;
   grid_spacing = 0.696/2.4;
   grid_images_path = "../data/aprilgrid_tele";
   rows = 6;
   columns = 6;
   ```

- Wide capturing (no zoom):

   ```cpp
   grid_size = 0.094;
   grid_spacing = 2.3/9.4;
   grid_images_path = "../data/aprilgrid_wide";
   rows = 6;
   columns = 6;
   ```

## License

[Apache 2.0](../LICENSE)

## References

- [https://github.com/ethz-asl/ethzasl_apriltag2](https://github.com/ethz-asl/ethzasl_apriltag2)
- [https://docs.opencv.org](https://docs.opencv.org)
