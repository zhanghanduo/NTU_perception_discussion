# Hello SLAM
This program guides you to the simple use of CMake.
## Prerequisite

### Ubuntu 16.04 with GCC 5.4 (or Ubuntu 14.04 with GCC 4.7 or Ubuntu 18.04 with GCC 7.4)
These GCC compilers all support C++11 new features.
  
### Cmake
Cmake is a tool to manage your C++ projects by creating a `CMakeLists.txt` file.

Install by typing: `sudo apt-get install cmake`

## Use

Get into the folder of `NTU_PERCEPTION_DISCUSSION/programs/c1_hellolSLAM`. Enter the command to link:
```
    cmake .
```
This will generate some compiling information and MakeFile.
Then enter the command to compile:
```
    make -j4
```
This will generate execuatable file `helloSLAM`. To execuate it, type:
```
    ./helloSLAM
```    
which will output: `Hello SLAM!`

  