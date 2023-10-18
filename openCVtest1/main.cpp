#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(void)
{
	// Đọc ảnh gốc
	Mat image = imread("google.jpg");

	resize(image, image, Size(600, 600));
	Mat gray_image;
	cvtColor(image, gray_image, COLOR_BGR2GRAY);

	Mat canny_image;
	Canny(gray_image, canny_image, 100, 200);
	vector<vector<Point> > contours;
	findContours(canny_image, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	Mat raw_dist(canny_image.size(), CV_32F);
	for (int i = 0; i < canny_image.rows; i++)
	{
		for (int j = 0; j < canny_image.cols; j++)
		{
			raw_dist.at<float>(i, j) = (float)pointPolygonTest(contours[12], Point2f((float)j, (float)i), false);
			if (raw_dist.at<float>(i, j) < 0) {
				raw_dist.at<float>(i, j) = 0;
			}
			else raw_dist.at<float>(i, j) = 255;
		}
	}
	Mat draw_img = Mat::zeros(image.size() , CV_8UC3);
	drawContours(draw_img, contours, 12, Scalar(0,255,0), 1);

	
	imshow("Source", canny_image);
	imshow("Distance and inscribed circle", image);
	waitKey();
	return 0;
}