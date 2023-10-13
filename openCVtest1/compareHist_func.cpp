
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int comp(int argc, char** argv)
{
	Mat src1 = imread("sample.jpg");
	Mat src2 = imread("example.jpg");
	resize(src1, src1, Size(640, 460));
	resize(src2, src2, Size(640, 460));

	if (src1.empty() || src2.empty())
	{
		return -1;
		cout << "can not read file !";
	}

	// convert bgr to hue , saturation , value
	Mat hsv_img1, hsv_img2;
	cvtColor(src1, hsv_img1, COLOR_BGR2HSV);
	cvtColor(src2, hsv_img2, COLOR_BGR2HSV);

	// initialize the number of bins for each color channel
	int hue_bins = 256;
	int satu_bins = 256;
	int hist_size[] = { hue_bins , satu_bins };

	// initialize the range for each color channel
	float hue_range[] = { 0 , 256 };
	float satu_range[] = { 0 , 256 };
	const float* hist_range[] = { hue_range , satu_range };

	// Calculate with HUE and SATURATION channels
	int channels[] = { 0 , 1 };
	Mat hist_img1, hist_img2;

	calcHist(&hsv_img1, 1, channels, Mat(), hist_img1, 2, hist_size, hist_range);
	normalize(hist_img1, hist_img1, 0, 1, NORM_MINMAX);
	calcHist(&hsv_img2, 1, channels, Mat(), hist_img2, 2, hist_size, hist_range);
	normalize(hist_img2, hist_img2, 0, 1, NORM_MINMAX);

	double  compare_correl = compareHist(hist_img1, hist_img2, HISTCMP_CORREL);
	double compare_chisqr = compareHist(hist_img1, hist_img2, HISTCMP_CHISQR);
	double compare_bhata = compareHist(hist_img1, hist_img2, HISTCMP_BHATTACHARYYA);
	double compare_inter = compareHist(hist_img1, hist_img2, HISTCMP_INTERSECT);

	cout << "compare_correl" << compare_correl << endl << "compare_chisqr" << compare_chisqr << endl << "compare_bhata" << compare_bhata << endl << "compare_inter" << compare_inter;


	return 0;
}