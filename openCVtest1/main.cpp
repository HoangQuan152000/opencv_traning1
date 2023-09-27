
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat dilate_im(Mat img, Mat struct_element);


int main() {
    // load image from file
    Mat img = imread("sample.jpg");
    if (img.empty()) {
        cout << "khong doc duoc anh!";
        return 0;
    }
    resize(img, img, Size(640, 460));

    // initialize the source matrix
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

    // initialize the struct element matrix
    Mat struct_element = getStructuringElement(MORPH_CROSS, Size(1, 3));


    // call dilate function 
    Mat result = dilate_im(img, struct_element);


    imshow("Result", result);
    waitKey(0);

    return 0;
}
Mat dilate_im(Mat img, Mat struct_element) {


    // check type data , convert to gray image 
    if (img.type() != CV_8UC1) {
        cvtColor(img, img, COLOR_BGR2GRAY);
    }


    // check size kernel 
    if (struct_element.cols == 0 || struct_element.rows == 0) {
        return img;
    }


    // initial variable size image , kernel
    int h = img.rows;
    int w = img.cols;

    int x = struct_element.cols;
    int y = struct_element.rows;

    // initial img dst
    Mat result = img.clone();

    // scan each pixel 
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {

            // initial varible position pixel start and end for caculator 
            int start_number_row = i - y / 2;
            int end_number_row = i + y / 2;
            int start_number_col = j - x / 2;
            int end_number_col = j + x / 2;

            // scan each pixel within kernel 
            for (int r = start_number_row; r <= end_number_row; r++) {
                for (int c = start_number_col; c <= end_number_col; c++) {

                    // initial varible position belong to kernel
                    int point_x = c - j + x / 2;
                    int point_y = r - i + y / 2;

                    // check access out of range size image 
                    if (r >= 0 && r < h && c >= 0 && c < w &&                       
                        //check access out of range size kernel
                        point_y < y && point_x < x &&
                        // remove kernel 0 value position
                        struct_element.at<uchar>(point_y, point_x) != 0)
                    {
                        // Find the maximum value of neighboring pixels
                        if (result.at<uchar>(i, j) < img.at<uchar>(r, c)) {
                            result.at<uchar>(i, j) = img.at<uchar>(r, c);
                        }
                    }
                }
            }

        }
    }

    return result;
}







