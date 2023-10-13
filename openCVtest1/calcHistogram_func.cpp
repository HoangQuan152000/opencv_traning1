
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int cacul(int argc, char** argv)
{
	Mat src = imread("sample.jpg");
	resize(src, src, Size(640, 460));
	if (src.empty())
	{
		return -1;
	}

	// Create an array containing single-channel color image matrices
	vector<Mat> bgr_planes;
	// Divide a color image into 3 single-channel color images
	split(src, bgr_planes);


	int histSize = 256;
	// Initialize the array containing 2 elements as the calculation range
	float range[] = { 0,256 };
	// initialize array pointer
	const float* histRange[] = { range };

	// Initialize objects corresponding to color channels
	Mat b_hist, g_hist, r_hist;
	// create arrays containing color histogram information
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange);

	// normalizes calculated arrays to the value range 0 to 400 
	normalize(b_hist, b_hist, 0, 400, NORM_MINMAX);
	normalize(g_hist, g_hist, 0, 400, NORM_MINMAX);
	normalize(r_hist, r_hist, 0, 400, NORM_MINMAX);

	// Initialize image size without histogram
	int hist_w = 640, hist_h = 460;

	// initialize the width of each bin
	int bin_w = cvRound((double)hist_w / histSize);

	//initialize the object containing the histogram
	Mat histImage(Size(640, 460), CV_8UC3, Scalar(0, 0, 0));
	//Draw value lines corresponding to color channels
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 1, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	imshow("Source image", src);
	imshow("b_hist", bgr_planes[0]);
	imshow("g_hist", bgr_planes[1]);
	imshow("r_histo", bgr_planes[2]);
	imshow("calcHist Demo", histImage);
	waitKey();
	return 0;
}