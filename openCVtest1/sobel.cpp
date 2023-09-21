#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int test() {
    // load an imgage
    Mat img = imread("sample.jpg");
    // check if image empty
    if (img.empty())
    {
        std::cout << "Không tìm thấy ảnh" << std::endl;
        return -1;
    }
    // Thay đổi kích thước ảnh gốc với kích thước mới là (300,200) và phương pháp nội suy là tuyến tính
    resize(img, img, Size(500, 400), 0, 0, INTER_LINEAR);

    // Convert image to grayscale
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    // Apply the Sobel function in the x direction with a filter size of 3x3
    Mat sobel_x;
    Sobel(img_gray, sobel_x, CV_64F, 1, 0, 3);
    // Apply the Sobel function in the y direction with a filter size of 3x3
    Mat sobel_y;
    Sobel(img_gray, sobel_y, CV_64F, 0, 1, 3);
    Mat sobel_xy;
    Sobel(img_gray, sobel_xy, CV_64F, 1, 1, 3);

    // Tính độ dốc theo chuẩn L2

    Mat gradient;
    magnitude(sobel_x, sobel_y, gradient);
    // Normalize gradient to the interval [0.255]
    normalize(gradient, gradient, 0, 255, NORM_MINMAX, CV_8U);
    // Normalize gradient to x_derection
    normalize(sobel_x, sobel_x, 0, 255, NORM_MINMAX, CV_8U);
    // Normalize gradient to y_derection
    normalize(sobel_y, sobel_y, 0, 255, NORM_MINMAX, CV_8U);
    // display images
    imshow("Source ", img);
    imshow("sobel X", sobel_x);
    imshow("Sobel Y", sobel_y);
    imshow("Sobel XY", gradient);


    // Đợi người dùng nhấn phím để thoát
    waitKey(0);
}