#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

int main() {


    Mat img = imread("example.jpg");
    Scalar();
    if (img.empty()) {
        cout << "can not read image";
        return 1;
    }
    resize(img, img, Size(640, 460));

    Mat gray_img;
    cvtColor(img, gray_img, COLOR_BGR2GRAY);


    Mat bin_img;
    adaptiveThreshold(gray_img, bin_img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, -2);


    // 460 / 115 = 4
    int vertical_size = bin_img.rows / 115;
    // vertical_kernel (1,4);
    Mat vertical_kernel = getStructuringElement(MORPH_RECT, Size(1, vertical_size));

    Mat erode_img;
    erode(bin_img, erode_img, vertical_kernel);

    Mat dilate_img;
    dilate(erode_img, dilate_img, vertical_kernel);


    // 640 / 30 = 21
    int horizontal_size = bin_img.cols / 30;
    // horizontal_kernel (21,1)
    Mat horizontal_kernel = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));

    Mat erode_img_1;
    erode(bin_img, erode_img_1, horizontal_kernel);
    Mat dilate_img_1;
    dilate(erode_img_1, dilate_img_1, horizontal_kernel);


    imshow("src", bin_img);
    imshow("img", img);

    imshow("extract vertical", dilate_img);
    imshow("extract horizontal", dilate_img_1);
    waitKey(0);

    return 0;
}