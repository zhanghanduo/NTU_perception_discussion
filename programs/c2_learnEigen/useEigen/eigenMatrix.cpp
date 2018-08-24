#include <iostream>
using namespace std;
#include <ctime>
// Eigen Basic
#include <Eigen/Core>
// Dense matrix calculation (inverse, eigenvalue, etc)
#include <Eigen/Dense>

#define MATRIX_SIZE 50

/*******************************
* Basic Use of Eigen Basic Types
*******************************/

int main( int argc, char** argv )
{
    // All the vectors and matrices are "Eigen::Matrix" which is a template class.
    // The first three params are: data type, row, column

    // Here we declare a 2*3 float matrix
    Eigen::Matrix<float, 2, 3> matrix_23;

    // Eigen provides many internal types
    // i.e.: Vector3d is essentially Eigen::Matrix<double, 3, 1>
    Eigen::Vector3d v_3d;

	// Same as v_3d
    Eigen::Matrix<float,3,1> vd_3d;

    // Matrix3d is essentially Eigen::Matrix<double, 3, 3>
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero(); //Initialize matrix as all zeros

    // For undetermined size of matrix, we can use dynamic size matrix
    Eigen::Matrix< double, Eigen::Dynamic, Eigen::Dynamic > matrix_dynamic;
    // Same and simpler
    Eigen::MatrixXd matrix_x;

    // Operation to matrix
    // Input data (initialize matrix）
    matrix_23 << 1, 2, 3, 4, 5, 6;
    // Output data to screen
    cout << matrix_23 << endl;

    // Use () to access the element of a matrix
    for (int i=0; i<2; i++) {
        for (int j=0; j<3; j++)
            cout<<matrix_23(i,j)<<"\t";
        cout<<endl;
    }

    // Multiplication of matrix with vector (Actually still matrix times matrix)
    v_3d << 3, 2, 1;
    vd_3d << 4,5,6;

    // But is Eigen you cannot mix matrix from two different types
    // Eigen::Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d; This is wrong!
    // You have to explicitly convert
    Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << result << endl;

    Eigen::Matrix<float, 2, 1> result2 = matrix_23 * vd_3d;
    cout << result2 << endl;

    // You cannot mistake the dimension of matrix
    // You can try to uncomment the following line to see what error occurs
    // Eigen::Matrix<double, 2, 3> result_wrong_dimension = matrix_23.cast<double>() * v_3d;

    // Matrix operations
    matrix_33 = Eigen::Matrix3d::Random();      // Random matrix
    cout << matrix_33 << endl << endl;

    cout << matrix_33.transpose() << endl;      // transpose
    cout << matrix_33.sum() << endl;            // All the elements sum up
    cout << matrix_33.trace() << endl;          // trace
    cout << 10*matrix_33 << endl;               // number times matrix
    cout << matrix_33.inverse() << endl;        // inverse
    cout << matrix_33.determinant() << endl;    // determinant

    // Eigen value
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver ( matrix_33.transpose()*matrix_33 );
    cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;

    // Solve equation
    // We try to solve: matrix_NN * x = v_Nd

    Eigen::Matrix< double, MATRIX_SIZE, MATRIX_SIZE > matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random( MATRIX_SIZE, MATRIX_SIZE );
    Eigen::Matrix< double, MATRIX_SIZE,  1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random( MATRIX_SIZE,1 );

    clock_t time_stt = clock(); // Timer
    // Directly get inverse (Not recommended)
    Eigen::Matrix<double,MATRIX_SIZE,1> x = matrix_NN.inverse()*v_Nd;
    cout <<"time use in normal inverse is " << 1000* (clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms"<< endl;
    
    // Usually we use matrix decomposition like QR decomposition which is much faster
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout <<"time use in Qr decomposition is " <<1000*  (clock() - time_stt)/(double)CLOCKS_PER_SEC <<"ms" << endl;

    return 0;
}
