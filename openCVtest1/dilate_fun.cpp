#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int dilate_func() {
    // Read the image file
    Mat image = imread("sample.jpg");
    resize(image, image, Size(640, 460));

    // Check for failure
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    Mat binary_image;
    threshold(gray_image, binary_image, 128, 255, THRESH_BINARY);
    //dilate the image with 3x3 kernel
    Mat image_dilated_with_3x3_kernel;
    dilate(binary_image, image_dilated_with_3x3_kernel, getStructuringElement(MORPH_RECT, Size(3, 3)));

    //dilate the image with 5x5 kernel
    Mat image_dilated_with_5x5_kernel;
    dilate(binary_image, image_dilated_with_5x5_kernel, getStructuringElement(MORPH_RECT, Size(5, 5)));

    // Create windows with above names
//namedWindow("src");
    //namedWindow("dts dilated with 3 x 3 kernel");
    //namedWindow("dts dilated with 5 x 5 kernel");

    // Show our images inside the created windows.
    imshow("src", binary_image);
    imshow("dts dilated with 3 x 3 kernel", image_dilated_with_3x3_kernel);
    imshow("dts dilated with 5 x 5 kernel", image_dilated_with_5x5_kernel);

    waitKey(0); // Wait for any keystroke in the window

    return 0;
}
