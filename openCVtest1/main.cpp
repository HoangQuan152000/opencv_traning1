#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void imp_dilate(Mat A, Size size, int shape);
enum shape_kernel {
    CROSS_XXX,
    RECTANGLE_XXX
};

int main() {

    Mat A = imread("sample.jpg");
    Scalar();
    if (A.empty()) {
        cout << "can not read image";
        return 1;
    }
    resize(A, A, Size(640, 460));


    // chọn loại ma trận
    shape_kernel kernel_choice;
    int input_shape;

    // Lặp lại cho đến khi người dùng nhập vào một giá trị hợp lệ
    while (1) {
        // Hiển thị danh sách các loại kernel
        cout << "Chon loai kernel: " << endl;
        cout << "1. CROSS" << endl;
        cout << "2. RECTANGLE" << endl;

        // Đọc đầu vào của người dùng
        cin >> input_shape;

        // Kiểm tra xem đầu vào có hợp lệ hay không
        if (input_shape == 1) {
            kernel_choice = CROSS_XXX;
            break;
        }
        else if (input_shape == 2) {
            kernel_choice = RECTANGLE_XXX;
            break;
        }
        else {
            cout << "Nhap lai." << endl;
        }
    }
    // create size object and input width , height

    Size size;
    double w;
    double h;

tryAgain:
    cout << "nhap chieu rong kernel: ";
    cin >> w;
    size.width = (int)w;
    cout << "nhap chieu cao kernel: ";
    cin >> h;
    size.height = (int)h;

    if (size.width <= 0 || size.height <= 0) {
        cout << "chieu rong va chieu cao phai la so duong!" << endl;
        goto tryAgain;
    }

    imp_dilate(A, size, input_shape);



    waitKey(0);

    return 0;
}


void imp_dilate(Mat A, Size size, int shape) {

    // create height and width for kernel
    int h = size.height;
    int w = size.width;

    // check type data A
    if (A.type() != CV_8UC1) {
        cvtColor(A, A, COLOR_BGR2GRAY);
    }
    else threshold(A, A, 0, 255, THRESH_BINARY);


    Mat dst = Mat(A.rows, A.cols, CV_8UC1);
    resize(dst, dst, Size(640, 460));


    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {

            dst.at<uchar>(i, j) = 0;
            // matrix rectangle kernel
            if (shape == 2) {
                // scan with a non - square matrix
                if (h != w) {
                    for (int r = 0; r < h; r++) {
                        for (int c = 0; c < w; c++) {
                            // Check pixels are within matrix A
                            if (i + r >= 0 && i + r < A.rows && j + c >= 0 && j + c < A.cols) {
                                if (dst.at<uchar>(i, j) < A.at<uchar>(i + r, j + c)) {
                                    dst.at<uchar>(i, j) = A.at<uchar>(i + r, j + c);
                                }
                            }
                        }
                    }
                }
                // scan with even matrix
                else if (h % 2 == 0 && w % 2 == 0) {
                    for (int r = -(h - 1) / 2; r <= h / 2; r++) {
                        for (int c = -(w - 1); c <= w / 2; c++) {
                            // Check pixels are within matrix A
                            if (i + r >= 0 && i + r < A.rows && j + c >= 0 && j + c < A.cols) {
                                if (dst.at<uchar>(i, j) < A.at<uchar>(i + r, j + c)) {
                                    dst.at<uchar>(i, j) = A.at<uchar>(i + r, j + c);
                                }
                            }
                        }
                    }
                }
                // scan with odd matrix
                else for (int r = -h / 2; r <= h / 2; r++) {
                    for (int c = -w / 2; c <= w / 2; c++) {

                        // Check pixels are within matrix A
                        if (i + r >= 0 && i + r < A.rows && j + c >= 0 && j + c < A.cols) {
                            if (dst.at<uchar>(i, j) < A.at<uchar>(i + r, j + c)) {
                                dst.at<uchar>(i, j) = A.at<uchar>(i + r, j + c);
                            }
                        }
                    }
                }
            }
            // matrix cross kernel
            if (shape == 1) {
                // matrix 1 x n or n x 1
                if (h == 1 || w == 1) {
                    if (h == 1) {
                        for (int c = -(w - 1) / 2; c <= w / 2; c++) {
                            if (j + c >= 0 && j + c < A.cols) {
                                if (dst.at<uchar>(i, j) < A.at<uchar>(i, j + c)) {
                                    dst.at<uchar>(i, j) = A.at<uchar>(i, j + c);
                                }
                            }
                        }
                    }
                    else for (int r = -(h - 1) / 2; r <= h / 2; r++) {
                        if (i + r >= 0 && i + r < A.rows) {
                            if (dst.at<uchar>(i, j) < A.at<uchar>(i + r, j)) {
                                dst.at<uchar>(i, j) = A.at<uchar>(i + r, j);
                            }
                        }
                    }
                } // 1 or 2 canh la chan
                else if (h % 2 == 0 || w % 2 == 0) {
                    // h chan w le
                    if (h % 2 == 0 && w % 2 != 0) {
                        for (int r = -(h + 1) / 2; r < h / 2; r++) {
                            for (int c = -w / 2; c <= w / 2; c++) {
                                if (i + r >= 0 && i + r < A.rows && j + c >= 0 && j + c < A.cols) {
                                    // tim max theo từng ma tran 1 x n va n x 1
                                    if (dst.at<uchar>(i, j) < A.at<uchar>(i + r, j)) {
                                        dst.at<uchar>(i, j) = A.at<uchar>(i + r, j);
                                    }
                                    if (dst.at<uchar>(i, j) < A.at<uchar>(i, j + c)) {
                                        dst.at<uchar>(i, j) = A.at<uchar>(i, j + c);
                                    }
                                }
                            }

                        }
                    }
                    // h le w chan
                    else if (h % 2 != 0 && w % 2 == 0) {
                        for (int c = -(w + 1) / 2; c < w / 2; c++) {
                            for (int r = -h / 2; r <= h / 2; r++) {
                                if (i + r >= 0 && i + r < A.rows && j + c >= 0 && j + c < A.cols) {
                                    // tim max theo từng ma tran 1 x n va n x 1
                                    if (dst.at<uchar>(i, j) < A.at<uchar>(i + r, j)) {
                                        dst.at<uchar>(i, j) = A.at<uchar>(i + r, j);
                                    }
                                    if (dst.at<uchar>(i, j) < A.at<uchar>(i, j + c)) {
                                        dst.at<uchar>(i, j) = A.at<uchar>(i, j + c);
                                    }
                                }
                            }

                        }
                    }
                    // ca h va w deu chan
                    else for (int c = -(w + 1) / 2; c < w / 2; c++) {
                        for (int r = -(h + 1) / 2; r < h / 2; r++) {
                            if (i + r >= 0 && i + r < A.rows && j + c >= 0 && j + c < A.cols) {
                                // tim max theo từng ma tran 1 x n va n x 1
                                if (dst.at<uchar>(i, j) < A.at<uchar>(i + r, j)) {
                                    dst.at<uchar>(i, j) = A.at<uchar>(i + r, j);
                                }
                                if (dst.at<uchar>(i, j) < A.at<uchar>(i, j + c)) {
                                    dst.at<uchar>(i, j) = A.at<uchar>(i, j + c);
                                }
                            }
                        }

                    }
                }
                // ca h va w deu le
                else for (int c = -w / 2; c <= w / 2; c++) {
                    for (int r = -h / 2; r <= h / 2; r++) {
                        if (i + r >= 0 && i + r < A.rows && j + c >= 0 && j + c < A.cols) {
                            // tim max theo từng ma tran 1 x n va n x 1
                            if (dst.at<uchar>(i, j) < A.at<uchar>(i + r, j)) {
                                dst.at<uchar>(i, j) = A.at<uchar>(i + r, j);
                            }
                            if (dst.at<uchar>(i, j) < A.at<uchar>(i, j + c)) {
                                dst.at<uchar>(i, j) = A.at<uchar>(i, j + c);
                            }
                        }
                    }

                }
            }


        }
    }
    imshow("dst", dst);
}