#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

#include <iostream>
#include <cmath>

double epsilon = 1e-3;
double pi =3.14159;
double gam = 0.577;

typedef cv::Vec3b pixel;

double dist(const pixel &u, const pixel &v) {
    double d = 0;
    for (int i = 0; i < 3; i++) {
        double tmp = u[i] - v[i];
        d += tmp * tmp;
    }
    return std::sqrt(d);
}

template<class T>
T min(const T &a, const T &b) {
    return (a > b)? b: a;
}

double robust_kl(cv::Mat3b* im_F, int n_samples=20) {
    cv::Mat3b F = *im_F;
    cv::Size size = F.size();
    int d = F.channels();
    int m = size.height;
    int n = size.width;
    cv::Mat H(cv::Size(m, n), CV_32FC1);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            double mini = INFINITY;
            if (i > 0) mini = min(dist(F.at<pixel>(i, j), F.at<pixel>(i - 1, j)), mini);
            if (i < m - 1) mini = min(dist(F.at<pixel>(i + 1, j), F.at<pixel>(i, j)), mini);
            if (j > 0) mini = min(dist(F.at<pixel>(i, j - 1), F.at<pixel>(i, j)), mini);
            if (j < n - 1) mini = min(dist(F.at<pixel>(i, j + 1), F.at<pixel>(i, j)), mini);
            H.at<float>(i, j) = mini;
        }

    double kl = 0;
    for (int i = 0; i <  m; i++)
        for (int j = 0; j < n; j++) {
            double u = std::log(H.at<float>(i, j));
            kl += (u > epsilon)? u: epsilon;
        }
    kl = kl * d / (double) (m * n) + std::log((m * n - 1) * std::pow(pi, d / 2.f) / std::tgamma(1 + d / 2.f)) + gam;
    return kl;
}

int main(int argc, char** argv) {
    cv::namedWindow("F");
    cv::Mat3b F = cv::imread("fruits.jpg");
    if (F.size().empty()) {
        std::cout << "Unreadable file!" << std::endl;
    }
    cv::imshow("Sample", F); cv::waitKey();
    std::cout << robust_kl(&F) << std::endl;
}