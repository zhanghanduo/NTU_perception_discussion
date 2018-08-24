# Declare the minimum requirement of Cmake version
cmake_minimum_required( VERSION 2.8 )

# Declare a project name called "HelloSLAM"
project( HelloSLAM )

# Set compiling option "Debug" or "Release"
set( CMAKE_BUILD_TYPE "Debug" )

# Add an executable
# Usage：add_executable( executable_name source_file(s)_related )
# If there are multiple source files, just contenate them (order is not important)
add_executable( helloSLAM helloSLAM.cpp )

# Add a library
add_library( hello libHelloSLAM.cpp )
# Add a shared library
add_library( hello_shared SHARED libHelloSLAM.cpp )

add_executable( useHello useHello.cpp )
# Link the library file to the executable file
target_link_libraries( useHello hello_shared )
