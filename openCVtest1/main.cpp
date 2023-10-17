#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;

using namespace cv;

RNG rng(12345);
int main() {

	// Đọc ảnh gốc
	Mat image = imread("google.jpg");

	resize(image, image, Size(1000, 800));
	Mat gray_image;
	cvtColor(image, gray_image, COLOR_BGR2GRAY);

	Mat canny_image;
	Canny(gray_image, canny_image, 100 , 200);
	//Initialize array variable to store contour points
	// (Each parent array will have many child point arrays)
	vector<vector<Point>> contours;

	// Initialize the hierarchy variable and the relationship of the contours
	vector<Vec4i> hierarchy;

	// Use the function to find contours, the return value is the set of locations of the contours
	findContours(canny_image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	// Draw the contours you just found
	Mat image_draw = Mat::zeros(image.size(), CV_8UC3);

	//Initialize arrays containing the positions of rectangles and circles
	vector<Rect> boundRects(contours.size());
	vector<vector<Point>> contours_poly(contours.size());
	vector<Point2f> centers(contours.size());
	vector<float> radius(contours.size());

	for (size_t i = 0; i < contours.size(); i++) {
		
		// The approxPolyDP() function in the OpenCV library is used to approximate a complex contour to a simpler contour.
		//This function takes as input a contour and returns a simpler contour. (sum of points on the contour divided by the parameter)
		approxPolyDP(contours[i], contours_poly[i], 5, true);

		// Converts the values ​​in the contours array to an array containing the top left position and the length and width of the rectangle
		boundRects[i] = boundingRect(contours_poly[i]);

		//Converts the values ​​in the contours array into an array containing the center position and radius of the circle
		minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
		
	}

	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(image_draw, contours, i, color, 1);
		rectangle(image_draw, boundRects[i].tl(), boundRects[i].br(), Scalar(0, 255, 0), 1);
		circle(image_draw, centers[i], radius[i], Scalar(0, 0, 255), 1);
	}


	
	imshow("canny_image", canny_image);
	imshow("dts", image_draw);


	// Chờ người dùng nhấn phím bất kỳ để thoát
	waitKey(0);

	return 0;
}



