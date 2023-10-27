#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


vector<Vec3f> my_hough_circle(Mat img, int minRadius, int maxRadius) {

    int  img_rows = img.rows;
    int img_cols = img.cols;

    int dMin = min(img_rows, img_cols);

    if (maxRadius == 0) {
        maxRadius = dMin / 2;
    }
    int bin_radius = maxRadius / minRadius;

    int range_radius = maxRadius - minRadius + 1;
    vector<vector<vector<int>>> houghSpace(img_rows, vector<vector<int>>(img_cols, vector<int>(range_radius, 0)));

    for (int i = 0; i < img_rows; i++) {
        for (int j = 0; j < img_cols; j++) {
            for (int r = 0; r < range_radius; r++) {
                houghSpace[i][j][r] = 0;
            }
        }
    }

    for (int i = 0; i < img_rows; i++) {
        for (int j = 0; j < img_cols; j++) {

            if (img.at<uchar>(i, j) == 255) {
                for (int r = 0; r < range_radius; r++) {

                    int current_radius = minRadius + r;

                    for (int theta = 0; theta < 180; theta += 4) {

                        double current_theta = theta * CV_PI / 180;

                        int x0 = j - cvRound(current_radius * cos(current_theta));
                        int y0 = i - cvRound(current_radius * sin(current_theta));

                        if (x0 >= 0 && x0 < img.cols && y0 >= 0 && y0 < img.rows) {
                            houghSpace[y0][x0][r] ++;
                        }

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
    vector<Vec3f> circles;
    for (int i = 0; i < img_rows; i++) {
        for (int j = 0; j < img_cols; j++) {
            for (int r = 0; r < range_radius; r++) {

                if (houghSpace[i][j][r] > 50) {

                    circles.push_back(Vec3f(i, j, r + minRadius));
                }
            }
        }
    }


    return circles;
}
int main() {
    //read
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

    vector<Vec3f> circles = my_hough_circle(canny_image, 20, 100);
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
    imshow("src", canny_image);
    imshow("dst", draw_image);
    waitKey(0); // Wait for any keystroke in the window

    return 0;
}



