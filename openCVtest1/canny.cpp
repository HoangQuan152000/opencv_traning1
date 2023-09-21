// Khai báo các thư viện cần thiết
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int can()
{
    // Đọc ảnh nguồn từ đường dẫn
    Mat src = imread("sample.jpg");
    resize(src, src, Size(640, 460), 0, 0, INTER_LINEAR);
    // Kiểm tra xem ảnh có được đọc thành công không
    if (src.empty())
    {
        cout << "Không thể đọc ảnh" << endl;
        return -1;
    }

    // Tạo một ma trận ảnh xám để lưu kết quả chuyển đổi từ ảnh màu
    Mat gray;

    // Chuyển đổi ảnh màu sang ảnh xám
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // Tạo một ma trận ảnh lọc để lưu kết quả lọc bằng ma trận kernel
    Mat filter;

    // Tạo một ma trận kernel có kích thước 3x3 và các giá trị bằng 1/9
    Mat kernel = Mat::ones(3, 3, CV_32F) / (float)(9);

    // Áp dụng nhân chập với ma trận kernel cho ảnh xám
    //filter2D(gray, filter, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);

    // filter out any noise
    GaussianBlur(gray, filter, Size(5, 5), 0);

    // Tạo một ma trận ảnh cạnh để lưu kết quả phát hiện cạnh bằng hàm canny

    Mat edge;
    // apply canny function
    Canny(filter, edge, 100, 200);

    // Hiển thị ảnh nguồn, ảnh xám, ảnh lọc và ảnh cạnh trên cửa sổ
    imshow("source", src);
    imshow("gray", gray);
    imshow("blur", filter);
    imshow("canny", edge);

    // Đợi phím bất kỳ để thoát chương trình
    waitKey(0);
}
