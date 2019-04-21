#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

std::string type2str(int type) {
    std::string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch ( depth ) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }

    r += "C";
    r += (chans+'0');

    return r;
}

void smoothing(const cv::Mat &im) {
    cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("after", cv::WINDOW_AUTOSIZE);
    cv::Mat im_;
    
    cv::GaussianBlur(im, im_, cv::Size(5, 5), 3, 3);

    std::cout << type2str(im.type()) << std::endl;
    cv::imshow("original", im);
    cv::waitKey(0);
    cv::imshow("after", im_);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void pyrDown(const cv::Mat &im) {
    cv::Mat out, canny;
    cv::pyrDown(im, out);
    cv::namedWindow("pyrdown", cv::WINDOW_AUTOSIZE);
    cv::imshow("pyrdown", out);
    cv::waitKey(0);
    cv::destroyWindow("pyrdown");
    cv::cvtColor(im, canny, cv::COLOR_BGR2GRAY);
    cv::Canny(canny, canny, 10, 100, 3, true);
    cv::namedWindow("canny", cv::WINDOW_AUTOSIZE);
    cv::imshow("canny", canny);
    cv::waitKey(0);
    cv::destroyWindow("canny");
}

void blur(const cv::Mat &im) {
    cv::Mat out;
    cv::GaussianBlur(im, out, cv::Size(31, 31), 5., 5., CV_HAL_BORDER_REFLECT); // size of a gaussian kernel must be odd
    cv::namedWindow("gaussian", cv::WINDOW_AUTOSIZE);
    cv::imshow("gaussian", out);
    cv::waitKey(0);
}

int main(int argc, char** argv) {
    cv::Mat im = cv::imread(argv[1], -1);
    
    if (im.empty()) return -1;
    smoothing(im);
    blur(im);
    pyrDown(im);

    return 0;
}