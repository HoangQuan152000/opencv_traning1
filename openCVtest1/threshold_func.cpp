#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int thres() {

    Mat img = imread("sample.jpg");
    if (img.empty()) {
        cout << "khong doc duoc anh!";
        return 0;
    }
    resize(img, img, Size(640, 460));

    cvtColor(img, img, COLOR_BGR2GRAY);

    // threshold with binary
    Mat img_bin;
    threshold(img, img_bin, 128, 255, THRESH_BINARY);
    // threshold with binary inverted
    Mat img_bin_inv;
    threshold(img, img_bin_inv, 128, 255, THRESH_BINARY_INV);
    // threshold with truncate
    Mat img_trun;
    threshold(img, img_trun, 128, 255, THRESH_TRUNC);
    // threshold with to zero
    Mat img_2zero;
    threshold(img, img_2zero, 128, 1, THRESH_TOZERO);
    // threshold with to zero inverted
    Mat img_2zero_inv;
    threshold(img, img_2zero_inv, 128, 2, THRESH_TOZERO_INV);


    imshow("src", img);
    imshow("binary", img_bin);
    imshow("binary inverted", img_bin_inv);
    imshow("truncate", img_trun);
    imshow("zero", img_2zero);
    imshow("zero inverted", img_2zero_inv);

    // Đợi phím bất kỳ để thoát chương trình
    waitKey(0);
    return 0;
}