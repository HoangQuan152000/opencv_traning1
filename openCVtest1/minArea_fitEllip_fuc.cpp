#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;

using namespace cv;


int area_el() {
	RNG rng1(12345);
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
	// Đọc ảnh gốc
	Mat image = imread("google.jpg");

	resize(image, image, Size(800, 800));
	Mat gray_image;
	cvtColor(image, gray_image, COLOR_BGR2GRAY);

	Mat canny_image;
	Canny(gray_image, canny_image, 100, 200);
	//Initialize array variable to store contour points
	// (Each parent array will have many child point arrays)
	vector<vector<Point>> contours;

	// Use the function to find contours, the return value is the set of locations of the contours
	findContours(canny_image, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	// Initialize array of rotated rectangular objects
	vector<RotatedRect> min_rect(contours.size());
	vector<RotatedRect> min_ellip(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		// This function will convert the positions in the border to an array containing the 
		// rectangle's center position, width and height, and rotation angle of the rectangle.
			//This function will return the center, size and rotation values ​​of the ellipse
		min_rect[i] = minAreaRect(contours[i]);


		if (contours[i].size() > 50) {
			//This function will return the center, size and rotation values ​​of the ellipse
			min_ellip[i] = fitEllipse(contours[i]);
		}
	}


	// Draw the contours you just found
	Mat image_draw = Mat::zeros(image.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng1.uniform(0, 256), rng1.uniform(0, 256), rng1.uniform(0, 256));
		drawContours(image_draw, contours, (int)i, color, 1);

		ellipse(image_draw, min_ellip[i], color, 2);

		Point2f rect_points[4];
		//returns the minimal up-right integer rectangle containing the rotated rectangle 
		//(This function will return the 4 vertices of the rectangle)
		min_rect[i].points(rect_points);
		for (int j = 0; j < 4; j++) {
			//line(image_draw, rect_points[j], rect_points[(j + 1) % 4], Scalar(0, 0, 255), 2);
		}
	}


	imshow("canny_image", canny_image);
	imshow("dts", image_draw);


	// Chờ người dùng nhấn phím bất kỳ để thoát
	waitKey(0);

	return 0;
}



