ARG SDK_VERSION=1.0
ARG REPO=axisecp
ARG RUNTIME_IMAGE=arm64v8/ubuntu:20.04
ARG TZ=Europe/Paris \
    DEBIAN_FRONTEND=noninteractive

ARG TARGET_TOOLCHAIN=aarch64-linux-gnu

# Specify which ACAP Computer Vision SDK to use
FROM axisecp/acap-computer-vision-sdk:latest-aarch64-devel AS cv-sdk

# Define the runtime image
FROM ${RUNTIME_IMAGE}

# Get packages from the CV SDK
COPY --from=cv-sdk /axis/python /
COPY --from=cv-sdk /axis/python-tfserving /
COPY --from=cv-sdk /axis/python-numpy /
COPY --from=cv-sdk /axis/openblas /
COPY --from=cv-sdk /axis/opencv /

# Install cmake

RUN apt-get update && \
    apt-get install tzdata
RUN apt-get update && apt-get install -yf --no-install-recommends \
        make \
        git \
        cmake \
        g++-10 \
        gcc \
        libeigen3-dev \
        libconfig++-dev
RUN apt-get install -y build-essential
ENV CXX=g++-10

# Copy the application script to the container
WORKDIR /app
COPY . .

# Clone the AprilTag detection algorithm
ENV GIT_SSL_NO_VERIFY=1
RUN git clone https://github.com/ethz-asl/ethzasl_apriltag2.git
RUN mv CMakeLists-detection.txt ethzasl_apriltag2/CMakeLists.txt

# Compile and run the code
RUN cd ethzasl_apriltag2 && mkdir build && cd build && cmake .. && make && make install
RUN mkdir build && cd build && cmake .. && make

WORKDIR /app/build

CMD ["./main"]
