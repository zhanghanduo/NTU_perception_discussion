cmake_minimum_required( VERSION 2.8 )
project( imageBasics )

# Add support for C++ 11 standard
set( CMAKE_CXX_FLAGS "-std=c++11" )

# Look for OpenCV
find_package( OpenCV REQUIRED )
# Add header file
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( imageBasics imageBasics.cpp )
# Link to OpenCV library
target_link_libraries( imageBasics ${OpenCV_LIBS} )