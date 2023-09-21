#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int acc() {

    Mat img = imread("sample.jpg");
    Vec3b color_img = img.at<Vec3b>(100, 100);
    uchar blue_color = color_img[0];
    uchar green_color = color_img[1];
    uchar red_color = color_img[2];
    cout << "red color of pixel: " << red_color;
    cout << "blue color of pixel: " << blue_color;
    cout << "green color of pixel: " << green_color;


    //waitKey();
    return 0;
}