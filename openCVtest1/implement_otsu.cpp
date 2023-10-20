#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
float otsu_implement(Mat image);


int imotsu() {

	// load image from file
	Mat src = imread("sample.jpg");
	resize(src, src, Size(640, 460), 0, 0, INTER_LINEAR);
	// Kiểm tra xem ảnh có được đọc thành công không
	if (src.empty())
	{
		cout << "Không thể đọc ảnh" << endl;
		return -1;
	}

	// Tạo một ma trận ảnh xám để lưu kết quả chuyển đổi từ ảnh màu
	Mat gray;

	// Chuyển đổi ảnh màu sang ảnh xám
	cvtColor(src, gray, COLOR_BGR2GRAY);

	int otsu_thres = otsu_implement(gray);

	Mat otsu_thresh;

	threshold(gray, otsu_thresh, otsu_thres, 255, THRESH_BINARY);

	Mat otsu_func;
	threshold(gray, otsu_func, 0, 255, THRESH_OTSU);

	imshow("otsu_thresh", otsu_thresh);
	imshow("otsu_func", otsu_func);
	imshow("src", gray);
	// Đợi phím bất kỳ để thoát chương trình
	waitKey(0);




	return 0;
}
float otsu_implement(Mat image) {

	// Get the histogram
	long double histogram[256];

	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
		histogram[i] = 0;

	// calculate the no of pixels for each intensity values
	for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
			histogram[(int)image.at<uchar>(y, x)]++;

	// Calculate the bin_edges
	long double bin_edges[256];
	bin_edges[0] = 0.0;
	// bin_edges[i] = i;
	for (int i = 1; i < 256; i++)
		bin_edges[i] = bin_edges[i - 1] + 1;

	// Calculate bin_mids
	long double bin_mids[256];
	// bin_mids[i] = i + 0.5;
	for (int i = 0; i < 256; i++)
		bin_mids[i] = (bin_edges[i] + bin_edges[i + 1]) / 2;

	// weight1, weight2
	long double weight1[256];
	weight1[0] = histogram[0];
	for (int i = 1; i < 256; i++)
		weight1[i] = histogram[i] + weight1[i - 1];

	int total_pixel = 0;
	for (int i = 0; i < 256; i++)
		total_pixel += histogram[i];

	long double weight2[256];
	weight2[0] = total_pixel;
	for (int i = 1; i < 256; i++)
		weight2[i] = weight2[i - 1] - histogram[i - 1];

	// Calculate the class means: mean1 and mean2
	long double histogram_bin_mids[256];
	for (int i = 0; i < 256; i++)
		histogram_bin_mids[i] = histogram[i] * bin_mids[i];

	long double cumsum_mean1[256];
	cumsum_mean1[0] = histogram_bin_mids[0];
	for (int i = 1; i < 256; i++)
		cumsum_mean1[i] = cumsum_mean1[i - 1] + histogram_bin_mids[i];

	long double cumsum_mean2[256];
	cumsum_mean2[0] = histogram_bin_mids[255];
	for (int i = 1, j = 254; i < 256 && j >= 0; i++, j--)
		cumsum_mean2[i] = cumsum_mean2[i - 1] + histogram_bin_mids[j];

	long double mean1[256];
	for (int i = 0; i < 256; i++)
		mean1[i] = cumsum_mean1[i] / weight1[i];

	long double mean2[256];
	for (int i = 0, j = 255; i < 256 && j >= 0; i++, j--)
		mean2[j] = cumsum_mean2[i] / weight2[j];

	// Calculate Inter_class_variance
	long double Inter_class_variance[255];
	long double dnum = 10000000000;
	for (int i = 0; i < 255; i++)
		Inter_class_variance[i] = ((weight1[i] * weight2[i] * (mean1[i] - mean2[i + 1])) / dnum) * (mean1[i] - mean2[i + 1]);

	// Maximize interclass variance
	long double maxi = 0;
	int getmax = 0;
	for (int i = 0; i < 255; i++) {
		if (maxi < Inter_class_variance[i]) {
			maxi = Inter_class_variance[i];
			getmax = i;
		}
	}

	return bin_mids[getmax];
}