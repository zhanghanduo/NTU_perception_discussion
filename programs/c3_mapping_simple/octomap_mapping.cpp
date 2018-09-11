#include <iostream>
#include <fstream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <octomap/octomap.h>    // for octomap
#include <octomap/ColorOcTree.h>

#include <Eigen/Geometry>
#include <boost/format.hpp>  // for formating strings

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

    cout<<"Now converting image into octomap..."<<endl;

    // octomap tree
//    octomap::OcTree tree( 0.05 ); // parameter denotes resolution
    octomap::ColorOcTree tree( 0.05 );

    for ( int i=0; i<5; i++ )
    {
        cout<<"image " << i+1 << " is now converting..." << endl;
        cv::Mat color = colorImgs[i];
        cv::Mat depth = depthImgs[i];
        Eigen::Isometry3d T = poses[i];

        octomap::Pointcloud cloud;  // the point cloud in octomap

        for ( int v=0; v<color.rows; v++ )
            for ( int u=0; u<color.cols; u++ )
            {
                unsigned int d = depth.ptr<unsigned short> ( v )[u]; // depth value
                if ( d==0 ) continue;                                // eliminate 0 value which means no measurement
                if ( d >= 7000 ) continue;                           // eliminate depth value being too big
                Eigen::Vector3d point;
                point[2] = double(d)/depthScale;
                point[0] = (u-cx)*point[2]/fx;
                point[1] = (v-cy)*point[2]/fy;
                Eigen::Vector3d pointWorld = T*point;
                // Put 3D world coordinate points into cloud
                cloud.push_back( pointWorld[0], pointWorld[1], pointWorld[2] );
            }

        // Store point cloud into octomap. Given origin calculate projection rays
        tree.insertPointCloud( cloud, octomap::point3d( T(0,3), T(1,3), T(2,3) ) );

//            for (auto p:cloud.points)
//                tree.integrateNodeColor(p.x, p.y, p.z, p.r, p.g, p.b);
    }

    // Update the occupied information of inner nodes
    tree.updateInnerOccupancy();

    cout<<"saving octomap ... "<<endl;
    tree.writeBinary( "../octomap.bt" );
    return 0;
}

