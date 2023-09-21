
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void imp_dilate(Mat A ,Size size);

int main() {

    // custom matrix A
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
    // create size object and input width , height
    Size size;
    cout << "nhap chieu rong kernel: ";
    cin >> size.width;
    cout << "nhap chieu cao kernel: ";
    cin >> size.height;

    imp_dilate(A , size);
    
    imshow("A", A);
    
    waitKey(0);

    return 0;
}

void imp_dilate(Mat A,Size size) {
    Mat dst = Mat(A.rows, A.cols, CV_8UC1);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {

            dst.at<uchar>(i, j) = 0;
            // scan pixels within the kernel
            for (int r = -size.height/2; r <= size.height/2; r++) {
                for (int c = -size.width/2; c <= size.width/2; c++) {

                  // Check pixels are within matrix A
                    if (i + r >= 0 && i + r < A.rows && j + c >= 0 && j + c < A.cols && A.at<uchar>(r + i, c + j) == 1) {
                        dst.at<uchar>(i, j) = 1;
                        break;
                    }
                }
                // dont need check value 1 again, continue next pixel 
                if (dst.at<uchar>(i, j) == 1) {
                    break;
                }
            }

        }
    }
    threshold(dst, dst, 0, 255, THRESH_BINARY);
    imshow("dst", dst);
}