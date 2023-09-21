// Khai báo các thư viện cần thiết
// Khai báo các thư viện cần thiết
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int lap()
{
    // Đọc ảnh nguồn từ đường dẫn
    Mat src = imread("sample.jpg");
    resize(src, src, Size(500, 400), 0, 0, INTER_LINEAR);
    // Kiểm tra xem ảnh có được đọc thành công không
    if (src.empty())
    {
        cout << "Không thể đọc ảnh" << endl;
        return -1;
    }

    Mat src_blur;
    GaussianBlur(src, src_blur, Size(5, 5), 0);
    Mat src_gray;
    cvtColor(src_blur, src_gray, COLOR_BGR2GRAY);

    Mat dst;
    // apply laplacian for src_gray 
    Laplacian(src_gray, dst, CV_64F, 3, 1, 0, BORDER_DEFAULT);
    // convert output to a 8bit unsigded image
    convertScaleAbs(dst, dst);

    // Hiển thị ảnh nguồn và ảnh đích trên cửa sổ
    imshow("Ảnh nguồn", src);
    imshow("Ảnh đích", dst);

    // Đợi phím bất kỳ để thoát chương trình
    waitKey(0);

    return 0;
}

