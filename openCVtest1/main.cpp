#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


void my_hough_circle(Mat img, vector<Vec3f>& circles, int minRadius, int maxRadius, double resolution_theta, int threshold) {
    double min_dist = 40;
    // Calculate the width and height of the image
    int  img_rows = img.rows;
    int img_cols = img.cols;
    // find the smallest dimension
    int dMin = min(img_rows, img_cols);

    const double degree2radians = CV_PI / 180;

    if (maxRadius == 0) {
        maxRadius = dMin / 2;
    }

    // create radius range variable
    int range_radius = maxRadius - minRadius + 1;

    // Initialize 3D storage space ( number of rows X number of columns X radius range )
    vector<vector<vector<int>>> houghSpace(img_rows, vector<vector<int>>(img_cols, vector<int>(range_radius, 0)));

    for (int i = 0; i < img_rows; i++) {
        for (int j = 0; j < img_cols; j++) {
            for (int r = 0; r < range_radius; r++) {
                houghSpace[i][j][r] = 0;
            }
        }
    }

    // Go through each pixel in the image
    for (int i = 0; i < img_rows; i++) {
        for (int j = 0; j < img_cols; j++) {
            // check edge pixels
            if (img.at<uchar>(i, j) == 255) {
                // That 3rd dimensional loop is the radius within the range
                for (int r = 0; r < range_radius; r++) {

                    //The current radius value is equal to MIN value plus the index
                    int current_radius = minRadius + r;
                    // rotation loop from 0 to 180
                    for (int theta = 0; theta < 180; theta += int(resolution_theta / degree2radians)) {
                        // convert rotation angle from degrees to radians
                        double current_theta = theta * degree2radians;

                        // Calculate the position of each pixel on the circle
                        int x0 = j - cvRound(current_radius * cos(current_theta));
                        int y0 = i - cvRound(current_radius * sin(current_theta));

                        if (x0 >= 0 && x0 < img.cols && y0 >= 0 && y0 < img.rows) {
                            // voting into the array
                            houghSpace[y0][x0][r] ++;
                        }
                        // position of the opposite pixel
                        x0 = j + cvRound(current_radius * cos(current_theta));
                        y0 = i + cvRound(current_radius * sin(current_theta));

                        if (x0 >= 0 && x0 < img.cols && y0 >= 0 && y0 < img.rows) {
                            houghSpace[y0][x0][r] ++;
                        }

                    }

                }
            }
        }
    }
    // Browse elements in accmulator
    for (int i = 0; i < img_rows; i++) {
        for (int j = 0; j < img_cols; j++) {
            for (int r = 0; r < range_radius; r++) {

                // get the elements larger than the threshold and add to the circles array the position and radius
                if (houghSpace[i][j][r] > 50) {

                    circles.push_back(Vec3f(i, j, r + minRadius));

                }
            }
        }
    }

}
int main() {


    Mat image = imread("circle.jpg");
    if (image.empty()) {
        cout << "cannot read file!";
        return -1;
    }
    resize(image, image, Size(640, 640));
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    Mat canny_image;
    Canny(gray_image, canny_image, 50, 150);

    // detect circles

    vector<Vec3f> circles;
    my_hough_circle(canny_image, circles, 20, 100, CV_PI / 45, 50);
    //HoughCircles(canny_image, circles, HOUGH_GRADIENT, 1, gray_image.rows / 16, 100, 50, 20, 100);

    // draw circle
    Mat draw_image = image.clone();
    for (size_t i = 0; i < circles.size(); i++) {
        // position center circles
        float x = circles[i][1];
        float y = circles[i][0];

        // initialize radius 
        float r = circles[i][2];


        circle(draw_image, Point(x, y), r, Scalar(0, 255, 0), 2);
    }

    // Hiển thị hình ảnh
    imshow("Hough Circles", image);
    imshow("src", canny_image);
    imshow("dst", draw_image);
    waitKey(0); // Wait for any keystroke in the window

    return 0;
}



