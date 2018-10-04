#include <iostream>
#include <chrono>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main ( int argc, char** argv )
{
    // Read image from argv[1]
    cv::Mat image;
    image = cv::imread ( argv[1] );     //cv::imread: Read the image
    // Judge if the image exists
    if ( image.data == nullptr )
    {
        cerr<<"Image file"<<argv[1]<<"does not exist."<<endl;
        return 0;
    }
    
    // Read basic information from image
    cout<<"Width: "<<image.cols<<", height: "<<image.rows<<", channel number: "<<image.channels()<<endl;
    cv::imshow ( "image", image );      // Display
    cv::waitKey ( 0 );                  // Pause function, press a key to continue
    // Judge the type of image
    if ( image.type() != CV_8UC1 && image.type() != CV_8UC3 )
    {
        // The type does not match our need
        cout<<"Please input a colorful or gray image."<<endl;
        return 0;
    }

    // Loop the whole image, use std::chrono to set a timer
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for ( size_t y=0; y<image.rows; y++ )
    {
        // Get the row pointer of image using cv::Mat::ptr
        unsigned char* row_ptr = image.ptr<unsigned char> ( y );  // row_ptr is the head pointer of the yth row
        for ( size_t x=0; x<image.cols; x++ )
        {
            // access the element of xth col, yth row
            unsigned char* data_ptr = &row_ptr[ x*image.channels() ]; // data_ptr points to the pixel data to be accessed
            // output each channel of this pixel. For gray image only 1 channel
            for ( int c = 0; c != image.channels(); c++ )
            {
                unsigned char data = data_ptr[c]; // Here `data` is the value of cth channel of I(x,y)
            }
        }
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );
    cout<<"For the whole image it takes： "<<time_used.count()<<" seconds。"<<endl;

    // About copy of `cv::Mat`
    // Directly assignment of value does not copy the data
    cv::Mat image_another = image;
    // In this case modify `image_another` will also lead to change of `image` itself!!!
    image_another ( cv::Rect ( 0,0,100,100 ) ).setTo ( 0 ); // Left up corner 100*100 block is set to 0.
    cv::imshow ( "image", image );
    cv::waitKey ( 0 );
    
    // So usually we use `clone` function to copy data
    cv::Mat image_clone = image.clone();
    image_clone ( cv::Rect ( 0,0,100,100 ) ).setTo ( 255 );
    cv::imshow ( "image", image );
    cv::imshow ( "image_clone", image_clone );
    cv::waitKey ( 0 );

    cv::destroyAllWindows();
    return 0;
}
