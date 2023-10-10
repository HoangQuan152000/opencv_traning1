#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int hou() {

    Mat A = (Mat_<uchar>(16, 16) <<
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    threshold(A, A, 0, 255, THRESH_BINARY);
    Mat image = imread("sample.jpg");
    if (image.empty()) {
        cout << "cannot read file!";
        return -1;
    }
    resize(image, image, Size(640, 460));
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    Mat canny_image;
    Canny(gray_image, canny_image, 100, 200);

    //Initialize a 2-attribute structure array
    vector<Vec2f> lines_dectect;
    HoughLines(canny_image, lines_dectect, 1, CV_PI / 180, 100);

    // Initialize a 4-attribute structure array
    vector<Vec4f> linesP;
    HoughLinesP(canny_image, linesP, 1, CV_PI / 180, 100, 75, 10);
    for (int i = 0; i < linesP.size(); i++) {
        line(gray_image, Point(linesP[i][0], linesP[i][1]), Point(linesP[i][2], linesP[i][3]), Scalar(0, 0, 255), 2);

    }

    // detect circles
    vector<Vec3f> circles;
    HoughCircles(canny_image, circles, HOUGH_GRADIENT, 1, gray_image.rows / 16, 200, 10, 3, 8);

    // draw circle 
    for (size_t i = 0; i < circles.size(); i++) {
        // position center circles
        float x = circles[i][0];
        float y = circles[i][1];

        // initialize radius 
        float r = circles[i][2];


        circle(gray_image, Point(x, y), r, Scalar(0, 255, 0), 2);
    }

    // Hiển thị hình ảnh
    imshow("Hough Circles", canny_image);
    imshow("src", canny_image);
    imshow("dst", gray_image);
    waitKey(0); // Wait for any keystroke in the window

    return 0;
}
