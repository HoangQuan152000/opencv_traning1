#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;

using namespace cv;


int moment_ara() {
	RNG rng1(12345);
	
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

	// Initialize vectors to store the moments, areas, and arc lengths of the contours
	vector<Moments> arr_moments(contours.size());
	vector<double> arr_areas(contours.size());
	vector<double> arr_arcLengths(contours.size());

	// Iterate over the contours and calculate the moments, areas, and arc lengths
	for (int i = 0; i < contours.size(); i++) {

		// Calculate the moments of the contour
		arr_moments[i] = moments(contours[i]);

		// Calculate the area of the contour
		arr_areas[i] = contourArea(contours[i]);

		// Calculate the arc length of the contour
		arr_arcLengths[i] = arcLength(contours[i], true);

	}
	// Draw the contours you just found
	Mat image_draw = Mat::zeros(image.size(), CV_8UC3);
	// Find the contours that are circles
	vector<int> circleContours;
	// Find the contours that are rectangles
	vector<int> rectangleContours;
	// Find the contours that are triangles
	vector<int> triangleContours;
	for (int i = 0; i < contours.size(); i++) {

		// Calculate the circularity of the contour
		double circularity = 4 * CV_PI * arr_areas[i] / (arr_arcLengths[i] * arr_arcLengths[i]);

		// Circularity: The circularity of a contour is a characteristic that measures how close the contour is to a circle.
		// The closer the value of roundness is to 1, the closer the contour is to a circle.
		if (circularity > 0.5) {
			circleContours.push_back(i);
		}
		double aspectRatio = arr_moments[i].m10 / arr_moments[i].m00;

		//Aspect ratio: The aspect ratio of a border is a characteristic that measures how close the border is to a rectangle.
		//  The closer the value of the aspect ratio is to 1, the closer the border is to a rectangle.
		if (aspectRatio > 0.9 && aspectRatio <= 1) {
			rectangleContours.push_back(i);
		}
		// Number of corners: The number of corners of a border is a characteristic that measures the number of corners of the
		// border. The larger the value of the number of corners, the more corners the border has.
		int numCorners = arr_arcLengths[i] / 10;

		// If the number of corners is 3, then the contour is a triangle
		if (numCorners > 3) {
			triangleContours.push_back(i);
		}
		Scalar color = Scalar(rng1.uniform(0, 256), rng1.uniform(0, 256), rng1.uniform(0, 256));
		drawContours(image_draw, contours, i, color, 3);
	}




	imshow("image_draw", image_draw);



	// Chờ người dùng nhấn phím bất kỳ để thoát
	waitKey(0);

	return 0;
}



