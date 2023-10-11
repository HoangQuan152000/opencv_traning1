#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int remapp() {

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

    // Create the destination image and the two mapping matrix (for x and y )
    Mat dst;
    Mat map_x(gray_image.size(), CV_32FC1);
    Mat map_y(gray_image.size(), CV_32FC1);

    //Go through each pixel and update the value for each mapping matrix 
    for (int i = 0; i < gray_image.rows; i++) {
        for (int j = 0; j < gray_image.cols; j++) {
            map_x.at<float>(i, j) = (float)(map_x.cols - j);
            map_y.at<float>(i, j) = (float)(map_y.rows - i);
        }
    }
    
    remap(gray_image,dst,map_x,map_y,INTER_LINEAR);

    imshow("dst", dst);

    waitKey(0); // Wait for any keystroke in the window

    return 0;
}
