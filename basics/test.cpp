#include <iostream>

#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat u(3, 5, CV_32FC3, cv::Scalar(1.f, 0.f, 0.f));
    cv::Mat v;
    u.copyTo(v);
    v.at<cv::Vec3f>(2, 4) = cv::Vec3f(0.f, 2.f, 1.f);
    std::cout << cv::format(v, cv::Formatter::FMT_PYTHON) << std::endl;
    std::cout << u.row(2).type() << std::endl;

    
}