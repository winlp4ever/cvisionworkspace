#include <opencv2/opencv.hpp>

#include <iostream>

// learn different ways to initialize a mat: central basic type of OpenCV lib
int main(int argc, char** argv) {
    const int n_mat_size = 5;
    const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
    cv::Mat n_mat0( 3, n_mat_sz, CV_32FC1 );
    cv::Mat n_mat1( 3, n_mat_sz, CV_32FC1 );
    cv::RNG rng;
    rng.fill( n_mat0, cv::RNG::UNIFORM, 0.f, 1.f );
    rng.fill( n_mat1, cv::RNG::UNIFORM, 0.f, 1.f );
}