# Necessary Third Party Dependencies

## 1. Eigen 3

Please go to [Learn Eigen](../programs/c2_learnEigen/README.md) to install Eigen3.

## 2. Ceres Solver

#### Prepare:

Download [Ceres](https://github.com/ceres-solver/ceres-solver) library from source code.
```
 git clone https://ceres-solver.googlesource.com/ceres-solver
``` 

It is recommend you follow installation guide: http://ceres-solver.org/installation.html.

Before you install ceres-solver, you need some dependencies:
```
# CMake
sudo apt-get install cmake
# google-glog + gflags
sudo apt-get install libgoogle-glog-dev
# BLAS & LAPACK
sudo apt-get install libatlas-base-dev
# Eigen3
sudo apt-get install libeigen3-dev
# SuiteSparse and CXSparse (optional)
# - If you want to build Ceres as a *static* library (the default)
#   you can use the SuiteSparse package in the main Ubuntu package
#   repository:
sudo apt-get install libsuitesparse-dev
# - However, if you want to build Ceres as a *shared* library, you must
#   add the following PPA:
sudo add-apt-repository ppa:bzindovic/suitesparse-bugfix-1319687
sudo apt-get update
sudo apt-get install libsuitesparse-dev
```
#### Installation:

```
tar zxf ceres-solver-1.14.0.tar.gz
mkdir ceres-bin
cd ceres-bin
cmake ../ceres-solver-1.14.0
make -j3
make test
# Optionally install Ceres, it can also be exported using CMake which
# allows Ceres to be used without requiring installation, see the documentation
# for the EXPORT_BUILD_DIR option for more information.
sudo make install
```

## 3. Sophus

```
tar zxf Sophus.tar.gz
cd Sophus
mkdir build && cd build
cmake .. && make -j4
sudo make install
```

## 4. g2o
(Optional)



