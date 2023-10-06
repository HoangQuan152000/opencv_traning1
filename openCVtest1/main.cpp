#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {

    Mat A = (Mat_<uchar>(16, 16) <<
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    threshold(A,A,0,255,THRESH_BINARY);
    Mat image = imread("sample.jpg");
    if (image.empty()) {
        cout << "cannot read file!";
        return -1;
   }
    resize(image,image ,Size(640,460));
    Mat gray_image;
    cvtColor(image, gray_image,COLOR_BGR2GRAY);
    Mat canny_image;
    Canny(gray_image,canny_image,100,200);


    vector<Vec2f> lines_dectect;
    HoughLines(canny_image,lines_dectect,1,CV_PI/180,100);
    

    vector<Vec4f> linesP;
    HoughLinesP(canny_image,linesP,1,CV_PI/180,100,75,10);
    for (int i = 0; i < linesP.size();  i ++) {
        line(gray_image,Point(linesP[i][0] , linesP[i][1]), Point(linesP[i][2], linesP[i][3]) , Scalar(0,0,255),2);

    }

    // Tìm các đường tròn bằng HoughCircles
    vector<Vec3f> circles;
    HoughCircles(canny_image, circles, HOUGH_GRADIENT, 1, gray_image.rows / 64, 200, 10, 5, 30);

    // Vẽ các đường tròn
    for (size_t i = 0; i < circles.size(); i++) {
        // Lấy tọa độ tâm của đường tròn
        float x = circles[i][0];
        float y = circles[i][1];

        // Lấy bán kính của đường tròn
        float r = circles[i][2];

        // Vẽ đường tròn
        circle(gray_image, Point(x, y), r, Scalar(0, 255, 0), 2);
    }

    // Hiển thị hình ảnh
    imshow("Hough Circles", canny_image);
    imshow("src", canny_image);
    imshow("dst", gray_image);
    waitKey(0); // Wait for any keystroke in the window

    return 0;
}
