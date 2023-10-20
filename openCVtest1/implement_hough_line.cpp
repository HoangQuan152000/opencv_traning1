
/*#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// Hàm phát hiện đường thẳng bằng thuật toán Hough
vector<Vec2i> my_hough(Mat img, float rho, float theta, int threshold) {

    // Tính chiều dài đường chéo của ảnh
    int img_height, img_width;
    img_height = img.rows;
    img_width = img.cols;
    float diagonal_length = sqrt(img_height * img_height + img_width * img_width);

    // Tạo ma trận cạnh
    int num_rho = int(diagonal_length / rho);
    int num_theta = int(CV_PI / theta);
    Mat edge_matrix(2 * num_rho + 1, num_theta, CV_32SC1);

    float cos_sin[2][180];
    float current_theta = 0;
    for (int i = 0; i < 180; i++) {

        cos_sin[0][i] = cos(theta);
        cos_sin[1][i] = sin(theta);
        theta += theta;
    }

    // Duyệt qua tất cả các điểm ảnh có cạnh trong ảnh
    for (int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            if (img.at<uchar>(i, j) > 0) {


            }
        }
    }

    // Tìm các đường thẳng có số lượng phiếu bầu lớn hơn hoặc bằng ngưỡng
    vector<Vec2i> lines;
    for (int i = 0; i < edge_matrix.rows; i++) {
        for (int j = 0; j < edge_matrix.cols; j++) {
            if (edge_matrix.at<int>(i, j) >= threshold) {
                lines.push_back(Vec2i(i - num_rho, j));
            }
        }
    }

    // Trả về danh sách các đường thẳng được phát hiện
    return lines;
}

// Chương trình chính
int main() {

    // Đọc ảnh
    Mat img = imread("sample.jpg");

    // Chuyển ảnh sang ảnh xám
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Áp dụng thuật toán Canny để phát hiện cạnh
    Mat edges;
    Canny(gray, edges, 100, 200);

    // Phát hiện đường thẳng bằng hàm my_hough
    vector<Vec2i> lines = my_hough(edges, 1, CV_PI / 180, 100);

    // Vẽ các đường thẳng được phát hiện lên ảnh
    for (Vec2i line : lines) {

        // Tính các tham số của đường thẳng
        float rho = line[0];
        float theta = line[1];
        float a = cos(theta);
        float b = sin(theta);

        // Tính các tọa độ của hai điểm cuối của đường thẳng
        int x0 = a * rho;
        int y0 = b * rho;
        int x1 = x0 + 1000 * (-b);
        int y1 = y0 + 1000 * (a);

        // Vẽ đường thẳng
        line(img, Point(x0, y0), Point(x1, y1), Scalar(0, 0, 255), 2);
    }

    // Hiển thị ảnh
    imshow("Image", img);
    waitKey(0);

    return 0;
}
*/


