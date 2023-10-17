#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int maifdgfgffn() {
	RNG rng(12345);
	// Đọc ảnh gốc
	Mat image = imread("google.jpg");

	resize(image, image, Size(640, 460));
	Mat gray_image;
	cvtColor(image, gray_image, COLOR_BGR2GRAY);
	Mat canny_img;
	Canny(gray_image, canny_img, 100, 200);
	//Initialize array variable to store contour points
	// (Each parent array will have many child point arrays)
	vector<vector<Point>> contours;

	// Initialize the hierarchy variable and the relationship of the contours
	vector<Vec4i> hierarchy;

	// Use the function to find contours, the return value is the set of locations of the contours
	findContours(canny_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	// Draw the contours you just found
	Mat image_draw = Mat::zeros(image.size(), CV_8UC3);


	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(image_draw, contours, i, color, 2);
	}


	imshow("image_src", image);
	imshow("image_canny", canny_img);
	imshow("dts", image_draw);


	// Chờ người dùng nhấn phím bất kỳ để thoát
	waitKey(0);

	return 0;
}



