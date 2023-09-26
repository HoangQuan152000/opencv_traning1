
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat dilate(Mat img, Mat struct_element);


int main() {
    // Đọc ảnh
    Mat img = imread("sample.jpg");
    if (img.empty()) {
        cout << "khong doc duoc anh!";
        return 0;
    }
    resize(img, img, Size(640, 460));
    // Khai báo ma trận cấu trúc cross
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

    Mat struct_element = getStructuringElement(MORPH_CROSS, Size(3, 3));


    // Thực hiện phép giãn nở
    Mat result = dilate(img, struct_element);

    // Hiển thị kết quả
    imshow("Result", result);
    waitKey(0);

    return 0;
}
Mat dilate(Mat img, Mat struct_element) {

    if (img.type() != CV_8UC1) {
        cvtColor(img, img, COLOR_BGR2GRAY);
        threshold(img, img, 128, 255, THRESH_BINARY);
    }
    else  threshold(img, img, 0, 255, THRESH_BINARY);



    // Kiểm tra kích thước ma trận cấu trúc
    if (struct_element.cols == 0 || struct_element.rows == 0) {
        return img;
    }


    // Lấy kích thước ảnh
    int h = img.rows;
    int w = img.cols;

    int x = struct_element.cols;
    int y = struct_element.rows;

    // Khởi tạo ma trận kết quả
    Mat result = img.clone();

    // Duyệt qua tất cả các pixel trong ảnh
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {

            for (int r = i - y / 2; r <= i + y / 2; r++) {
                for (int c = j - x / 2; c <= j + x / 2; c++) {
                    if (r >= 0 && r < h && c >= 0 && c < w && img.at<uchar>(r, c) == 255 &&
                        (r - i + y / 2) < y && (c - j + x / 2) < x &&
                        struct_element.at<uchar>((r - i + y / 2), (c - j + x / 2)) != 0)
                    {
                        result.at<uchar>(i, j) = 255;
                        break;
                    }
                }
            }

        }
    }

    return result;
}







