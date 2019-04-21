#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>

int main(int argc, char** argv) {
    int ddepth = CV_16S, kernel_size = 3, scale = 1, delta = 0;
    cv::namedWindow(argv[1], cv::WINDOW_AUTOSIZE);
    cv::Mat im = cv::imread(argv[1], -1);
    if (im.empty()) {
        std::cout << "Unable to read file!" << std::endl;
        return -1;
    }
    cv::Mat im_gray;
    cv::cvtColor(im, im_gray, cv::COLOR_RGB2GRAY);
    cv::GaussianBlur(im_gray, im_gray, cv::Size(5, 5), 3., 3.);

    cv::Mat lap;
    cv::Laplacian(im_gray, lap, ddepth, kernel_size, scale, delta);

    cv::convertScaleAbs(lap, lap);
    cv::imshow(argv[1], lap);
    cv::waitKey(0);
}