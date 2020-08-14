# The list of visual SLAM / Visual Odometry opensource projects, libraries, dataset, tools, and tutorials

### What is odometry?
Have you seen that little gadget on a car’s dashboard that tells you how much distance the car has travelled? It’s called an odometer. It (probably) measures the number of rotations that the wheel is undergoing, and multiplies that by the circumference to get an estimate of the distance travlled by the car. Odometry in Robotics is a more general term, and often refers to estimating not only the distance traveled, but the entire trajectory of a moving robot. So for every time instance t, there is a vector [$x^t, y^t, z^t, \alpha^t, \beta^t, \gamma^t$] which describes the complete pose of the robot at that instance. Note that $\alpha^t, \beta^t, \gamma^t$ here are the euler angles, while $x^t, y^t, z^t$ are Cartesian coordinates of the robot.

### What’s visual odometry?
There are more than one ways to determine the trajectory of a moving robot, but the one that we will focus on in this blog post is called Visual Odometry. In this approach we have a camera (or an array of cameras) rigidly attached to a moving object (such as a car or a robot), and our job is to construct a `6-DOF` trajectory using the video stream coming from this camera(s). When we are using just one camera, it’s called Monocular Visual Odometry. When we’re using two (or more) cameras, it’s refered to as Stereo Visual Odometry.

### Why stereo, or why monocular?
There are certain advantages and disadvantages associated with both the stereo and the monocular scheme of things. The advantage of stereo is that you can estimate the exact trajectory, while in monocular you can only estimate the trajectory, unique only up to a scale factor. So, in monocular VO, you can only say that you moved one unit in x, two units in y, and so on, while in stereo, you can say that you moved one meter in x, two meters in y, and so on. 

Moreover, stereo VO is usually much more robust (due to more data being available). But, in cases where the distance of the objects from the camera are too high ( as compared to the distance between to the two cameras of the stereo system), the stereo case degenerates to the monocular case. So, let’s say you have a very small robot (like the robobees), then it’s useless to have a stereo system, and you would be much better off with a monocular VO algorithm like SVO. Also, there’s a general trend of drones becoming smaller and smaller, so groups like those of Davide Scaramuzza are now focusing more on monocular VO approaches.


## Index
* [Libraries](#libraries)
* [Dataset](#dataset)
* [Tools](#tools)
* [OpenSource](#OpenSource)
* [Learn](learn.md)
* [Miscellaneous](miscellaneous.md)

## Libraries
###### Basic vision and trasformation libraries
- [OpenCV](http://opencv.org/)  (Most **Popular** computer vision library)
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) (Most **Popular** algebra representation and calculation library)
- [Sophus](https://github.com/strasdat/Sophus)  (Lie group representation and calculation library. Suggest use **a621ff** commit)
- [ROS](http://www.ros.org/) (Most **Popular** robotics framework)
- [PointCloud](http://pointclouds.org/) (Most **Popular** point cloud processing library. Also called **PCL** library)

###### Loop detection
- [DLoopDetector](https://github.com/dorian3d/DLoopDetector)
- [DBoW2](https://github.com/dorian3d/DBoW2) (Library for indexing and converting images into a bag-of-word representation)

###### Graph Optimization
- [ceres-solver](https://github.com/ceres-solver/ceres-solver)  (**Suggested**, General library for modeling and solving large, complicated optimization problems)
- [g2o](https://github.com/RainerKuemmerle/g2o)  (Specifically for graph based linear square optimization problem; more popular than *gtsam*, but not well documented)
- [gtsam](https://bitbucket.org/gtborg/gtsam/src/develop/)  (Similar to *g2o*, mainly for factor graph optimization, integrated with Preintegrated IMU Factor and iSAM2 implementation)

## Dataset

Dataset for benchmark/test/experiment/evalutation

- [TUM Universtiy](http://vision.in.tum.de/data/datasets/rgbd-dataset/download) (For RGB-D camera)
- [EUROC MAV Dataset](https://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets) (**Popular**, for UAVs indoor SLAM)
- [KTTI Vision benchmark](http://www.cvlibs.net/datasets/kitti/eval_odometry.php) (**Popular**, for vehicle outdoor SLAM)
- [UNI-Freiburg](https://lmb.informatik.uni-freiburg.de/resources/datasets/StereoEgomotion.en.html) (For small scale ego-motion)

## Tools
- [rgbd-dataset tool from TUM](https://vision.in.tum.de/data/datasets/rgbd-dataset/tools)
- [evo - evaluation tool for different trajectory formats](https://github.com/MichaelGrupp/evo)

## OpenSource

#### Simple Demos

- [mono-vo-c++](https://github.com/avisingh599/mono-vo)
- [mono-vo-python](https://github.com/yoshimasa1700/mono_vo_python)
- [monoVO-python](https://github.com/uoip/monoVO-python)
- [mono-SLAM](https://github.com/felixchenfy/Monocular-Visual-Odometry)

###### RGB (Monocular):

- [PTAM](https://github.com/Oxford-PTAM/PTAM-GPL)
> [1] Georg Klein and David Murray, "Parallel Tracking and Mapping for Small AR Workspaces", Proc. ISMAR 2007

> [2] Georg Klein and David Murray, "Improving the Agility of Keyframe-based SLAM", Proc. ECCV 2008

- [Libviso2](http://www.cvlibs.net/software/libviso/) (**Recommended**, simple enough to read)
> [1] Geiger, A., Ziegler, J., & Stiller, C. (2011, June). Stereoscan: Dense 3d reconstruction in real-time. In Intelligent Vehicles Symposium (IV), 2011

> [2] Kitt, B., Geiger, A., & Lategahn, H. (2010, June). Visual odometry based on stereo image sequences with ransac-based outlier rejection scheme. In Intelligent Vehicles Symposium (IV), 2010

- [DSO](https://github.com/JakobEngel/dso_ros). Available on ROS
>Direct Sparse Odometry, J. Engel, V. Koltun, D. Cremers, In arXiv:1607.02565, 2016

>A Photometrically Calibrated Benchmark For Monocular Visual Odometry, J. Engel, V. Usenko, D. Cremers, In arXiv:1607.02555, 2016

- [LSD-SLAM](https://github.com/tum-vision/lsd_slam). Available on ROS
>LSD-SLAM: Large-Scale Direct Monocular SLAM, J. Engel, T. Schöps, D. Cremers, ECCV '14

>Semi-Dense Visual Odometry for a Monocular Camera, J. Engel, J. Sturm, D. Cremers, ICCV '13

- [ORB-SLAM](https://github.com/raulmur/ORB_SLAM). Available on ROS
> [1] Raúl Mur-Artal, J. M. M. Montiel and Juan D. Tardós. ORB-SLAM: A Versatile and Accurate Monocular SLAM System. IEEE > Transactions on Robotics, vol. 31, no. 5, pp. 1147-1163, 2015. (2015 IEEE Transactions on Robotics Best Paper Award)

> [2] Dorian Gálvez-López and Juan D. Tardós. Bags of Binary Words for Fast Place Recognition in Image Sequences. IEEE > Transactions on Robotics, vol. 28, no. 5, pp. 1188-1197, 2012

- [Nister's Five Point Algorithm for Essential Matrix estimation, and FAST features, with a KLT tracker](https://github.com/avisingh599/mono-vo)
> D. Nister, “An efficient solution to the five-point relative pose problem,” Pattern Analysis and Machine Intelligence, IEEE Transactions on, vol. 26, no. 6, pp. 756–770, 2004.

- [SVO-SLAM](https://github.com/uzh-rpg/rpg_svo). Available on ROS
> Christian Forster, Matia Pizzoli, Davide Scaramuzza, "SVO: Fast Semi-direct Monocular Visual Odometry," IEEE International Conference on Robotics and Automation, 2014.

###### RGB and Depth (Called RGBD):
- [OpenCV RGBD-Odometry (Visual Odometry based RGB-D images)](https://github.com/tzutalin/OpenCV-RgbdOdometry)
> Real-Time Visual Odometry from Dense RGB-D Images, F. Steinbucker, J. Strum, D. Cremers, ICCV, 2011

- [Dense Visual SLAM for RGB-D Cameras](https://github.com/tum-vision/dvo_slam). Available on ROS
>[1]Dense Visual SLAM for RGB-D Cameras (C. Kerl, J. Sturm, D. Cremers), In Proc. of the Int. Conf. on Intelligent Robot Systems (IROS), 2013

>[2]Robust Odometry Estimation for RGB-D Cameras (C. Kerl, J. Sturm, D. Cremers), In Proc. of the IEEE Int. Conf. on Robotics and Automation (ICRA), 2013

>[3]Real-Time Visual Odometry from Dense RGB-D Images (F. Steinbruecker, J. Sturm, D. Cremers), In Workshop on Live Dense Reconstruction with Moving Cameras at the Intl. Conf. on Computer Vision (ICCV), 2011


- [RTAB MAP - Real-Time Appearance-Based Mapping](https://github.com/introlab/rtabmap). Available on ROS
> Online Global Loop Closure Detection for Large-Scale Multi-Session Graph-Based SLAM, 2014

> Appearance-Based Loop Closure Detection for Online Large-Scale and Long-Term Operation, 2013

- [ORB2-SLAM](https://github.com/raulmur/ORB_SLAM2). Available on ROS (ALso supports **Stereo** and **Monocular** sensors)
> [1] Raúl Mur-Artal, J. M. M. Montiel and Juan D. Tardós. ORB-SLAM: A Versatile and Accurate Monocular SLAM System. IEEE > Transactions on Robotics, vol. 31, no. 5, pp. 1147-1163, 2015. (2015 IEEE Transactions on Robotics Best Paper Award)

> [2] Dorian Gálvez-López and Juan D. Tardós. Bags of Binary Words for Fast Place Recognition in Image Sequences. IEEE Transactions on Robotics, vol. 28, no. 5, pp. 1188-1197, 2012

- [InfiniTAM∞ v2](http://www.robots.ox.ac.uk/~victor/infinitam/index.html)
> Kahler, O. and Prisacariu, V.~A. and Ren, C.~Y. and Sun, X. and Torr, P.~H.~S and Murray, D.~W. Very High Frame Rate Volumetric Integration of Depth Images on Mobile Device. IEEE Transactions on Visualization and Computer Graphics (Proceedings International Symposium on Mixed and Augmented Reality 2015

- [Kintinuous](https://github.com/mp3guy/Kintinuous)
> Real-time Large Scale Dense RGB-D SLAM with Volumetric Fusion, T. Whelan, M. Kaess, H. Johannsson, M.F. Fallon, J. J. Leonard and J.B. McDonald, IJRR '14

- [ElasticFusion](https://github.com/mp3guy/ElasticFusion)
> [1] ElasticFusion: Real-Time Dense SLAM and Light Source Estimation, T. Whelan, R. F. Salas-Moreno, B. Glocker, A. J. Davison and S. Leutenegger, IJRR '16

> [2] ElasticFusion: Dense SLAM Without A Pose Graph, T. Whelan, S. Leutenegger, R. F. Salas-Moreno, B. Glocker and A. J. Davison, RSS '15

- [Co-Fusion](http://visual.cs.ucl.ac.uk/pubs/cofusion/index.html)
> Martin Rünz and Lourdes Agapito. Co-Fusion: Real-time Segmentation, Tracking and Fusion of Multiple Objects. 2017 IEEE International Conference on Robotics and Automation (ICRA)

###### RGBD and LIDAR:
- [Google's cartographer](https://github.com/googlecartographer/cartographer). Available on ROS



## Other Visual SLAM lists:

* [awesome-visual-slam](https://github.com/tzutalin/awesome-visual-slam)

* [SFM-Visual-SLAM](https://github.com/marknabil/SFM-Visual-SLAM.git)
* [For Chinese readers](https://youjiexia.github.io/2018/03/10/Awesome-SLAM-Repos-on-GitHub/)

