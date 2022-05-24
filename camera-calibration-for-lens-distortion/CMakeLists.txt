cmake_minimum_required(VERSION 3.10)
project(ethzasl_apriltag2_cmake_starter_code)

add_definitions(-Wall)
find_package(Eigen3 REQUIRED)
find_package(ethzasl_apriltag2 REQUIRED CONFIG)
find_package(OpenCV REQUIRED)
find_package(PkgConfig)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)
if (LIBCONFIG_FOUND)
  include_directories(${LIBCONFIG_INCLUDE_DIRS})
  link_directories(${LIBCONFIG_LIBRARY_DIRS})
endif()

include_directories(include)

file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(main main.cpp ${SOURCE_FILES})
target_link_libraries(main PUBLIC ethzasl_apriltag2)
target_link_libraries(main PUBLIC ethzasl_apriltag2 ${LIBCONFIG_LIBRARIES})

