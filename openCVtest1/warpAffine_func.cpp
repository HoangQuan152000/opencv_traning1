#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int maifdfn() {

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

    //create the center point of the image for rotation
    Point2f center((gray_image.cols - 1) / 2 , (gray_image.rows - 1) / 2);
    //Create a rotation matrix with arbitrary points and rotation angles
    Mat matrix_rota = getRotationMatrix2D(center,70,1);
    //initialize the rotating image and call the function warpAffine
    Mat rota_image;
    warpAffine(gray_image,rota_image,matrix_rota,gray_image.size());
    // Initialize image movement size
    int tran_x = gray_image.cols / 4;
    int tran_y = gray_image.rows / 3;
    // initialize the move matrix
    Mat matrix_tran = (Mat_<float>(2,3) << 1, 0, tran_x,
        0, 1, tran_y);
    //initialize the moving image and call the function warpAffine
    Mat tran_image;
    warpAffine(gray_image,tran_image,matrix_tran, tran_image.size());
    

    imshow("dst", rota_image);
    imshow("tran", tran_image);
    waitKey(0); // Wait for any keystroke in the window

    return 0;
}
