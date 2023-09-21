#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int mor() {
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
    // morphology transformations closing
    Mat img_closing;
    morphologyEx(binary_image, img_closing, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));
    // types operators  
    //MORPH_BLACKHAT
    //MORPH_OPEN
    // ...
    // Show our images inside the created windows.
    imshow("src", binary_image);
    imshow("dts closing", img_closing);
    //imshow("dts dilated with 5 x 5 kernel", );

    waitKey(0); // Wait for any keystroke in the window

    return 0;
}