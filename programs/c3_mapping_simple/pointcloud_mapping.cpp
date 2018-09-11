#include <iostream>
#include <fstream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Geometry>
#include <boost/format.hpp>  // for formating strings
#include <pcl/point_types.h>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/statistical_outlier_removal.h>

boost::shared_ptr<pcl::visualization::PCLVisualizer> simpleVis (pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud1,
                                                                pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud2)
{
    int v1(0);
    int v2(0);
    // --------------------------------------------
    // -----Open 3D viewer and add point cloud-----
    // --------------------------------------------
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    viewer->createViewPort(0.0, 0.0, 0.5, 1.0, v1);
    viewer->setBackgroundColor (0, 0, 0, v1);
    viewer->addText("raw cloud", 10, 10, "left", v1);
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud1);
    viewer->addPointCloud<pcl::PointXYZRGB> (cloud1, rgb, "raw cloud", v1);

    viewer->createViewPort(0.5, 0.0, 1.0, 1.0, v2);
    viewer->setBackgroundColor (0, 0, 0, v2);
    viewer->addText("filtered cloud", 10, 10, "right", v2);
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb2(cloud2);
    viewer->addPointCloud<pcl::PointXYZRGB> (cloud2, rgb2, "filtered cloud", v2);

    viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "raw cloud");
    viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "filtered cloud");
    viewer->addCoordinateSystem (1.0);
    viewer->initCameraParameters ();
    return (viewer);
}



int main( int argc, char** argv )
{
    vector<cv::Mat> colorImgs, depthImgs;    // Colorful image and depth image
    vector<Eigen::Isometry3d> poses;         // camera poses

    ifstream fin("../data/pose.txt");
    if (!fin)
    {
        cerr<<"cannot find pose file"<<endl;
        return 1;
    }

    for ( int i=0; i<5; i++ )
    {
//        boost::format fmt( "../data2/%s/%s%06d.%s" );
//        colorImgs.push_back( cv::imread( (fmt%"color"%"left"%(i+1)%"png").str() ));
//        depthImgs.push_back( cv::imread( (fmt%"depth"%"depth"%(i+1)%"png").str(), -1 )); // use -1 to read raw data
        boost::format fmt( "../data/%s/%d.%s" );
        colorImgs.push_back( cv::imread( (fmt%"color"%(i+1)%"png").str() ));
        depthImgs.push_back( cv::imread( (fmt%"depth"%(i+1)%"pgm").str(), -1 )); // use -1 to read raw data

        double data[7] = {0};
        for ( int i=0; i<7; i++ )
        {
            fin>>data[i];
        }
        Eigen::Quaterniond q( data[6], data[3], data[4], data[5] );
        Eigen::Isometry3d T(q);
        T.pretranslate( Eigen::Vector3d( data[0], data[1], data[2] ));
        poses.push_back( T );
    }

    // calculate point cloud and stitch
    // camera intrinsic
    double cx = 325.5;
    double cy = 253.5;
    double fx = 518.0;
    double fy = 519.0;
    double depthScale = 1000.0;

//    double cx = 949.751;
//    double cy = 572.642;
//    double fx = 1399.25;
//    double fy = 1399.25;
//    double depthScale = 1000.0;

    cout<<"Now converting image into point cloud..."<<endl;

    // Define the format of point cloud, here use XYZRGB
    typedef pcl::PointXYZRGB PointT;            // One single point
    typedef pcl::PointCloud<PointT> PointCloud; // Set of points -> point cloud

    // Create a reference point cloud, this will be the final output.
    PointCloud::Ptr pointCloud( new PointCloud );
    for ( int i=0; i<5; i++ )
    {
        PointCloud::Ptr current( new PointCloud );
        cout<<"image " << i+1 << " is now converting..." << endl;
        cv::Mat color = colorImgs[i];
        cv::Mat depth = depthImgs[i];
        Eigen::Isometry3d T = poses[i];
        for ( int v=0; v<color.rows; v++ )
            for ( int u=0; u<color.cols; u++ )
            {
                unsigned int d = depth.ptr<unsigned short> ( v )[u]; // depth info
                if ( d==0 ) continue;                                // eliminate 0 value which means no measurement
                if ( d >= 8000 ) continue;                           // eliminate depth value being too big
                Eigen::Vector3d point;
                point[2] = double(d)/depthScale;
                point[0] = (u-cx)*point[2]/fx;
                point[1] = (v-cy)*point[2]/fy;
                Eigen::Vector3d pointWorld = T*point;                // Important! Transform local camera coordinate to world coordinate

                PointT p ;                                           // 3D point under world coordinate
                p.x = pointWorld[0];
                p.y = pointWorld[1];
                p.z = pointWorld[2];
                p.b = color.data[ v*color.step+u*color.channels() ];    // This is OpenCV convention: bgr order!
                p.g = color.data[ v*color.step+u*color.channels()+1 ];
                p.r = color.data[ v*color.step+u*color.channels()+2 ];
                current->points.push_back( p );
            }
        // depth filter and statistical removal
        PointCloud::Ptr tmp ( new PointCloud );
        pcl::StatisticalOutlierRemoval<PointT> statistical_filter;
        statistical_filter.setMeanK(50);
        statistical_filter.setStddevMulThresh(1.0);
        statistical_filter.setInputCloud(current);
        statistical_filter.filter( *tmp );
        (*pointCloud) += *tmp;
    }

    pointCloud->is_dense = false;
    cout<<"Generated point cloud has totally: "<<pointCloud->size()<<" points."<<endl;

    // voxel filter
    pcl::VoxelGrid<PointT> voxel_filter;
    voxel_filter.setLeafSize( 0.01, 0.01, 0.01 );       // resolution
    PointCloud::Ptr tmp ( new PointCloud );
    voxel_filter.setInputCloud( pointCloud );
    voxel_filter.filter( *tmp );
//    tmp->swap( *pointCloud );

    cout<<"After voxel filtering, generated point cloud has totally: "<<tmp->size()<<" points."<<endl;

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    viewer = simpleVis(pointCloud, tmp);

    while (!viewer->wasStopped ())
    {
        viewer->spinOnce (100);
        boost::this_thread::sleep (boost::posix_time::microseconds (100000));
    }
//    pcl::io::savePCDFileBinary("map.pcd", *pointCloud );
    return 0;
}
