# Mapping Simple Demo

## Introduction
1. PCL


2. Octomap

API Documentation: http://octomap.github.io/octomap/doc/.
## Prerequisites

1. Ubuntu 16.04
2. OpenCV 3.0 or above
3. Eigen
### Option1 -- apt-package
```
 sudo apt-get update
 sudo apt-get install libeigen3-dev
```
Then Eigen3 will be installed in `/usr/include/eigen3`
Note: This is not the latest version. In Ubuntu 16.04, eigen 3.3 is installed; in Ubuntu 14.04, eigen 3.2.

### Option2 -- source code
Download and extract from [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)
Suggest use eigen 3.2.10
```
cd Eigen3.2.10
mkdir build && cd build
cmake .. && sudo make install
```
4. PCL library
Refer to [Download Page](https://github.com/PointCloudLibrary/pcl/releases) and [Compiling Page](http://pointclouds.org/documentation/tutorials/compiling_pcl_posix.php).

5. Octomap library
Refer to [Installation Guide](https://github.com/OctoMap/octomap/wiki/Compilation-and-Installation-of-OctoMap).

## Run
