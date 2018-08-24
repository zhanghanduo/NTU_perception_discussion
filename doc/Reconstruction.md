# The list of 3D reconstruction libraries and studies

## Contents
- [Tutorials](#tutorials)
- [Papers](#papaers)
- [OpenSource projects](#opensource)
- [Feature detection](#features)

# Tutorials

## Multi-View Stereo (MVS) Tutorial

- [Multi-View Stereo: A Tutorial](http://www.cse.wustl.edu/~furukawa/papers/fnt_mvs.pdf). Y. Furukawa, C. Hernández. Foundations and Trends® in Computer Graphics and Vision, 2015.

- [State of the Art 3D Reconstruction Techniques](https://docs.google.com/file/d/0B851Hlh7xL0KNGx3X09VcEYzSjg/preview) N. Snavely, Y. Furukawa, CVPR 2014 tutorial slides. 

    - [Introduction](http://www.cse.wustl.edu/~furukawa/papers/cvpr2014_tutorial_intro.pdf) [MVS with priors]
    - (http://www.cse.wustl.edu/~furukawa/papers/cvpr2014_tutorial_mvs_prior.pdf)
    - [Large scale MVS](http://www.cse.wustl.edu/~furukawa/papers/cvpr2014_tutorial_large_scale_mvs.pdf)

- [Introduction of Visual SLAM, Structure from Motion and Multiple View Stereo](http://www.slideshare.net/yuhuang/visual-slam-structure-from-motion-multiple-view-stereo). Yu Huang 2014.

## RGB-D Mapping

- [3D indoor scene modeling from RGB-D data: a survey](http://cg.cs.tsinghua.edu.cn/papers/CVMJ-2015-scene-moddeling.pdf) K. Chen, YK. Lai and SM. Hu. Computational Visual Media 2015.

## Elevation Mapping

## Dense Mapping

# Papers

Will put in the near future.

# Opensource

## Stereo Matching

- [StereoMatch in Parallel](https://github.com/PRiME-project/PRiMEStereoMatch)
- [Pyramid Stereo Matching Network](https://github.com/JiaRenChang/PSMNet) (CVPR2018)

## MVS library
- [openMVS](http://cdcseacave.github.io/openMVS/)
- [DeepMVS](https://github.com/phuang17/DeepMVS) (Deep learning based multi-view stereo framework in [Pytorch](pytorch.org), 2018.)
- [pais-mvs](https://github.com/adahbingee/pais-mvs)

## Map library under ROS

- [ETHZ ASL/Grip Map](https://github.com/ANYbotics/grid_map) (Elevation Mapping)
  ![grid_map](https://github.com/ANYbotics/grid_map/blob/master/grid_map_rviz_plugin/doc/grid_map_rviz_plugin_example.png)
- [OmniMapper](https://github.com/CogRob/omnimapper) (Modular multimodal mapping framework -- quite aged)
- [OctoMap](https://github.com/OctoMap/octomap) (**Recommended**, efficient 3D occupancy grid mapping, suitable for laser/lidar sensors)
  [![Octomap](https://img.youtube.com/vi/7ZsxJzR14rc/0.jpg)](https://www.youtube.com/embed/7ZsxJzR14rc?autoplay=1)
- [ETHZ ASL/MapLab](https://github.com/ethz-asl/maplab) (**Latest**, but complicated, visual-inertial mapping framework)
- [ETHZ ASL/voxblox](https://github.com/ethz-asl/voxblox) (voxel based, incremental 3D Euclidean Signed Distance Fields for **Planning**)
  ![voxblox](https://camo.githubusercontent.com/4c0cf0ddcd11b2a7d6fb3e51a95113b96681c185/68747470733a2f2f692e696d6775722e636f6d2f7076486856734c2e706e67)