# Learn Eigen3
This folder tells you how to use Eigen3.

## Installation of Eigen3

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

## Check Eigen version
```
pkg-config --modversion eigen3
```
