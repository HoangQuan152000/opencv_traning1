#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int templ () {
	// Load the images
	cv::Mat image = cv::imread("example.jpg");
	resize(image, image, Size(640, 460));
	cv::Mat template_image = cv::imread("template.png");
	resize(template_image, template_image, Size(), 0.5, 0.5);

	// Create 6 images for each case
	Mat img[6];
	for (int i = 0; i < 6; i++) {
		img[i] = image.clone();
	}

	// initialize the result arrays
	vector<Mat> results;
	//Find matching objects
	for (int method = TM_SQDIFF; method <= TM_CCOEFF_NORMED; method++) {
		Mat result;
		matchTemplate(image, template_image, result, method);
		results.push_back(result);
	}
	// Get position values ​​and intensity values
	for (int i = 0; i < results.size(); i++) {
		double minVal, maxVal;
		Point minLoc, maxLoc;
		minMaxLoc(results[i], &minVal, &maxVal, &minLoc, &maxLoc);
		// Draw rectangles with matching positions on the image
		if (i < 2) {
			rectangle(img[i], minLoc, cv::Point(minLoc.x + template_image.cols, minLoc.y + template_image.rows), Scalar(i * 100, 255 / (i + 100), 0), 2 + i);
		}
		else
			rectangle(img[i], maxLoc, cv::Point(maxLoc.x + template_image.cols, maxLoc.y + template_image.rows), cv::Scalar(i * 50, 255 / i, i * 30), 2);

	}

	// Display the result

	imshow("src", image);
	imshow("template_image", template_image);
	cv::waitKey(0);

	return 0;
}