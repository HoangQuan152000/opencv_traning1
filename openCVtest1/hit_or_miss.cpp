#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
int hit_miss() {

    // create input matrix;
    Mat input_image = (Mat_<uchar>(8, 8) << 0, 0, 0, 0, 0, 0, 0, 0,
        0, 255, 255, 255, 0, 0, 0, 255,
        0, 0, 255, 255, 0, 0, 0, 0,
        0, 0, 255, 255, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 255, 255, 0, 0, 255, 255, 255,
        0, 255, 0, 0, 0, 0, 255, 0,
        0, 255, 0, 0, 0, 0, 255, 0);

    // create custom matrix kernel
    Mat cus_kernel = (Mat_<int>(3, 3) << 1, 1, 1,
        0, 1, -1,
        0, 1, -1);

    // create output matrix;
    Mat output_image;
    // hit or miss;
    morphologyEx(input_image, output_image, MORPH_HITMISS, cus_kernel);

    // convert type of data matrix kernel to unsigded char
    cus_kernel.convertTo(cus_kernel, CV_8UC1);

    //resize
    resize(input_image, input_image, Size(), 50, 50);
    resize(cus_kernel, cus_kernel, Size(400, 400), 50, 50);
    resize(output_image, output_image, Size(), 50, 50);
    imshow("src", input_image);
    // move window display to position we want
    moveWindow("src", 500, 500);
    imshow("dts hit or miss", output_image);
    imshow("kernel", cus_kernel);
    waitKey(0);

    return 0;
}