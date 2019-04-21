#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    cv::Mat im = cv::imread(argv[1], -1);
    if (im.empty()) {
        std::cout << "Unable to open image file!" << std::endl;
        return -1;
    }
    cv::Mat im_gray;
    cv::cvtColor(im, im_gray, cv::COLOR_RGB2GRAY);
    cv::GaussianBlur(im_gray, im_gray, cv::Size(5, 5), 3., 3.);

    // find edges using canny detector
    cv::Mat edges;
    cv::Canny(im_gray, edges, 200, 50);

    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edges, lines, 1., CV_PI / 180., 150, 0., 0.);

    for (auto it = lines.begin(); it != lines.end(); it++) {
        double rho = (*it)[0], theta = (*it)[1];
        cv::Point2f p1, p2;
        double a = std::cos(theta), b = std::sin(theta);
        double x0 = rho * a, y0 = rho * b;
        p1.x = cvRound(x0 + 1000 * (-a));
        p1.y = cvRound(y0 + 1000 * b);
        p2.x = cvRound(x0 + 1000 * a);
        p2.y = cvRound(y0 + 1000 * (-b));
        cv::line(im, p1, p2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
    }

    cv::namedWindow(argv[1], cv::WINDOW_AUTOSIZE);
    cv::imshow(argv[1], im);
    cv::waitKey(0);
    return 0;
}