#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;

using namespace cv;

int mfdfain() {

	// Đọc ảnh gốc
	Mat image = imread("sample.jpg");

	resize(image, image, Size(640, 460));
	Mat gray_image;
	cvtColor(image, gray_image, COLOR_BGR2GRAY);
	Mat bin_image;
	threshold(gray_image, bin_image, 128, 255, THRESH_BINARY);
	//Canny(bin_image , bin_image , 100 , 200);
	//Initialize array variable to store contour points
	// (Each parent array will have many child point arrays)
	vector<vector<Point>> contours;

	// Initialize the hierarchy variable and the relationship of the contours
	vector<Vec4i> hierarchy;

	// Use the function to find contours, the return value is the set of locations of the contours
	findContours(bin_image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// Draw the contours you just found
	Mat image_draw = Mat::zeros(image.size(), CV_8UC3);

	vector<Rect> boundRects;
	vector<vector<Point>> contours_poly(contours.size());
	vector<Point2f> centers(contours.size());
	vector<float> radius(contours.size());

	for (size_t i = 0; i < contours.size(); i++) {
		boundRects.push_back(boundingRect(contours[i]));
		rectangle(image_draw, boundRects[i], Scalar(0, 255, 0), 2);
		approxPolyDP(contours[i], contours_poly[i], 5, true);
		minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
		circle(image_draw, centers[i], radius[i], Scalar(0, 0, 255), 2);
		drawContours(image_draw, contours, i, Scalar(i * 10, 255, i + 20), 2);
	}



	imshow("bin_image", bin_image);
	imshow("Image", image_draw);


	// Chờ người dùng nhấn phím bất kỳ để thoát
	waitKey(0);

	return 0;
}



