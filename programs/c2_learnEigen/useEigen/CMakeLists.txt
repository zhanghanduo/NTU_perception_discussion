cmake_minimum_required( VERSION 2.8 )
project( useEigen )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-O3" )

# Add Eigen header file
# If you install eigen using "sudo apt-get install libeigen3-dev"
include_directories( "/usr/include/eigen3" ) 

# For eigen installed from source code
# find_package(Eigen3 3.2 REQUIRED PATHS /usr/local/eigen3)
# include_directories(${EIGEN3_INCLUDE_DIR})

add_executable( eigenMatrix eigenMatrix.cpp )
