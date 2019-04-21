#include <opencv2/opencv.hpp>

void showim(const cv::Mat &img) {
    cv::namedWindow("Example 1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example 1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example 1");
}

int main(int argc, char** argv) {
    cv::Mat img = cv::imread(argv[1], -1);
    if ( img.empty() ) return -1;
    showim(img);
    return 0;
}