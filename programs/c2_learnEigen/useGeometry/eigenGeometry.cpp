#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
// Eigen Geometry module
#include <Eigen/Geometry>

/****************************
* Eigen Geometry modul use
****************************/

int main ( int argc, char** argv )
{
    // Eigen/Geometry module provides all kinds of rotation and translation representation
    // 3D rotation matrix directly uses Matrix3d or Matrix3f (double and float)
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();

    // Rotatoin vector uses AngleAxis
    Eigen::AngleAxisd rotation_vector ( M_PI/4, Eigen::Vector3d ( 0,0,1 ) );     //rotate 45 degree along Z axis
    cout .precision(3);
    cout<<"rotation matrix =\n"<<rotation_vector.matrix() <<endl;                //matrix() convert to matrix
    // Or directly assign value
    rotation_matrix = rotation_vector.toRotationMatrix();

    // Coordinate tranformation using AngleAxis
    Eigen::Vector3d v ( 1,0,0 );
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    // Or use rotation matrix
    v_rotated = rotation_matrix * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    // Euler angel: convert rotation matrix to Euler angle 
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles ( 2,1,0 ); // ZYXorder，i.e. roll pitch yaw order
    cout<<"yaw pitch roll = "<<euler_angles.transpose()<<endl;

    // Euclidean transform matrix uses Eigen::Isometry 
    Eigen::Isometry3d T=Eigen::Isometry3d::Identity();                // Although called 3d, actually 4*4 matrix (Homogeneous)
    T.rotate ( rotation_vector );                                     // rotate according to rotation vector
    T.pretranslate ( Eigen::Vector3d ( 1,3,4 ) );                     // translation value
    cout << "Transform matrix = \n" << T.matrix() <<endl;

    // Coordinate tranformation using transorm matrix
    Eigen::Vector3d v_transformed = T*v;                              // similar to R*v+t
    cout<<"v tranformed = "<<v_transformed.transpose()<<endl;

    // Quaternion
    // AngleAxis <-> Quaternion
    Eigen::Quaterniond q = Eigen::Quaterniond ( rotation_vector );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;   // Order of coeffs is (x,y,z,w), w real part，x,y,z imginary part
    // Rotation matrix -> Quaternion
    q = Eigen::Quaterniond ( rotation_matrix );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;
    // Quaternion times a vector3d by overloading operator *
    v_rotated = q*v; // mathematically is: qvq^{-1}
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    return 0;
}
