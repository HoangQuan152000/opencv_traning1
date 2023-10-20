#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int wat(void)
{
	RNG rng = rng(12435);
	// Đọc ảnh gốc
	Mat image = imread("poker.jpg");

	resize(image, image, Size(640, 460));
	Mat gray_image;
	cvtColor(image, gray_image, COLOR_BGR2GRAY);

	Mat bin_img;
	threshold(gray_image, bin_img, 128, 255, THRESH_BINARY);

	Mat dist;
	distanceTransform(bin_img, dist, DIST_L2, 3);

	normalize(dist, dist, 0, 1, NORM_MINMAX);

	threshold(dist, dist, 0.03, 1, THRESH_BINARY);

	Mat dist_8U;
	dist.convertTo(dist_8U, CV_8U);

	vector<vector<Point>> contours;
	findContours(dist_8U, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	Mat markers = Mat::zeros(dist.size(), CV_32SC1);
	for (int i = 0; i < contours.size(); i++) {

		drawContours(markers, contours, i, Scalar(i + 1), -1);
	}

	circle(markers, Point(5, 5), 3, Scalar(255, 255, 255), -1);
	watershed(image, markers);

	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++) {
		int b = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		int r = rng.uniform(0, 256);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	Mat dst = Mat::zeros(markers.size(), CV_8UC3);
	for (int i = 0; i < markers.rows; i++) {
		for (int j = 0; j < markers.cols; j++) {
			int index = markers.at<int>(i, j);
			if (index > 0 && index <= contours.size()) {
				dst.at<Vec3b>(i, j) = colors[index - 1];
			}
			else
				dst.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
		}
	}


	imshow("src", image);
	//imshow("distance", dist);
	imshow("dts", dst);
	waitKey();
	return 0;
}