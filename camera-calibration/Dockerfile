ARG SDK_VERSION=1.0
ARG REPO=axisecp
ARG TZ=Europe/Paris \
    DEBIAN_FRONTEND=noninteractive

ARG TARGET_TOOLCHAIN=aarch64-linux-gnu

# Specify which ACAP Computer Vision SDK to use
FROM axisecp/acap-computer-vision-sdk:latest-aarch64-devel AS cv-sdk

# Define the runtime image
FROM arm64v8/ubuntu:20.04

# Get packages from the CV SDK
COPY --from=cv-sdk /axis/python /
COPY --from=cv-sdk /axis/python-tfserving /
COPY --from=cv-sdk /axis/python-numpy /
COPY --from=cv-sdk /axis/openblas /
COPY --from=cv-sdk /axis/opencv /

# Install cmake
RUN apt-get update && \
    apt-get install -y --no-install-recommends tzdata && \
    rm -rf /var/lib/apt/lists/*
RUN apt-get update && apt-get install -yf --no-install-recommends \
        make \
        git \
        cmake \
        g++-10 \
        gcc \
        libeigen3-dev \
        libconfig++-dev \
        build-essential && \
    rm -rf /var/lib/apt/lists/*
ENV CXX=g++-10

# Copy the application script to the container
WORKDIR /app
COPY . .

# Clone the AprilTag detection algorithm
ENV GIT_SSL_NO_VERIFY=1
RUN git clone https://github.com/ethz-asl/ethzasl_apriltag2.git

# Compile and run the code
RUN mkdir ethzasl_apriltag2/build && \ 
    mv CMakeLists-detection.txt ethzasl_apriltag2/CMakeLists.txt
WORKDIR /app/ethzasl_apriltag2/build
RUN cmake .. && make && make install
WORKDIR /app
RUN mkdir build
WORKDIR /app/build
RUN cmake .. && make

CMD ["./main"]
