#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <time.h>
#include <vector>

#include "utils.hpp"

int main(int argc, char** argv) {
    int ddepth = CV_16S;
    cv::namedWindow(argv[1], cv::WINDOW_AUTOSIZE);
    cv::Mat im = cv::imread(argv[1], -1);
    cv::imshow(argv[1], im);
    cv::waitKey(0);
    cv::Mat im_gray;
    cv::cvtColor(im, im_gray, cv::COLOR_RGB2GRAY);
    cv::GaussianBlur(im_gray, im_gray, cv::Size(3, 3), 1., 1.);

    std::cout << utils::type2str(im_gray.type()) << std::endl; // type of gray matrix
    std::cout << (int) (im_gray.at<uint8_t>(8, 12)) << std::endl; // print some random element of this matrix

    int begin = time(NULL);
    cv::Mat grad_x, grad_y;
    cv::Sobel(im_gray, grad_x, ddepth, 1, 0);
    cv::Sobel(im_gray, grad_y, ddepth, 0, 1);

    double min, max; // min max of a grad matrix is not 0 and 255 like normal img matrix
    cv::minMaxIdx(grad_x, &min, &max);
    std::cout << min << " " << max << std::endl;

    // so we must convert back these two mats to u8 space
    cv::Mat abs_grad_x, abs_grad_y;
    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);

    cv::minMaxIdx(abs_grad_x, &min, &max);
    std::cout << min << " " << max << std::endl;

    cv::Mat grad;
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    
    std::cout << utils::type2str(grad.type()) << std::endl;

    uint threshold = atoi(argv[2]);
    cv::Mat canny = cv::Mat::zeros(grad.size(), CV_8UC1);
    cv::MatIterator_<uchar> it = grad.begin<uchar>();
    cv::MatIterator_<uchar> it_ = canny.begin<uchar>();

    for (; it != grad.end<uchar>(); it++, it_++) 
        if (*it > threshold)
            *it_ = 255;
    
    std::cout << "Tlapse: " << time(NULL) - begin << "s" << std::endl;

    // show grad mat
    
    cv::namedWindow("grad mat", cv::WINDOW_AUTOSIZE);
    cv::imshow("grad mat", grad);
    cv::waitKey(0);

    cv::namedWindow("canny", cv::WINDOW_AUTOSIZE);
    cv::imshow("canny", canny);
    cv::waitKey(0);
}