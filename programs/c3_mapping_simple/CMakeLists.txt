# Declare the minimum requirement of Cmake version
cmake_minimum_required( VERSION 2.8 )

# Declare a project name called "HelloSLAM"
project( mapping_simple )

set( CMAKE_BUILD_TYPE Release )
set( CMAKE_CXX_FLAGS "-std=c++11" )

# 1 opencv 
find_package( OpenCV 3.0 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# 2 eigen
# Add Eigen header file
# If you install eigen using "sudo apt-get install libeigen3-dev"
include_directories( "/usr/include/eigen3" ) 

# For eigen installed from source code
# find_package(Eigen3 3.2 REQUIRED PATHS /usr/local/eigen3)
# include_directories(${EIGEN3_INCLUDE_DIR})

# 3 pcl 
find_package( PCL REQUIRED )
include_directories( ${PCL_INCLUDE_DIRS} )
link_directories(${PCL_LIBRARY_DIRS})
add_definitions( ${PCL_DEFINITIONS} )

# 4 octomap 
find_package( octomap REQUIRED )
include_directories( ${OCTOMAP_INCLUDE_DIRS} )

# Add an executable
# Usage：add_executable( executable_name source_file(s)_related )
# If there are multiple source files, just contenate them (order is not important)
add_executable( pointcloud_mapping pointcloud_mapping.cpp )
target_link_libraries( pointcloud_mapping ${OpenCV_LIBS} ${PCL_LIBRARIES} )

add_executable( octomap_mapping octomap_mapping.cpp )
target_link_libraries( octomap_mapping ${OpenCV_LIBS} ${PCL_LIBRARIES} ${OCTOMAP_LIBRARIES} )
