#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;


// Hàm phát hiện đường thẳng trong ảnh bằng thuật toán Hough với các tham số rho và theta cố định
vector<Vec2d> my_hough( Mat img, int threshold) {
    float theta = CV_PI / 180;
    // Tính toán chiều cao và chiều rộng của ảnh
    int img_height = img.rows;
    int img_width = img.cols;

    // Tính toán độ dài và độ dốc của đường thẳng dài nhất có thể được phát hiện
    int num_rho = int(sqrt(img_height * img_height + img_width * img_width));
    int num_theta = int(CV_PI / theta);

    // Tạo ma trận kích thước (2 * num_rho + 1, num_theta)
    //Mat edge_matrix =Mat::zeros(2 * num_rho + 1, num_theta, CV_32S);
    vector<vector<float>> edge_matrix(2 * num_rho + 1,vector<float>(num_theta));

    // Tìm các điểm biên trong ảnh
    vector<Point> point_pixel_edges;
    findNonZero(img, point_pixel_edges);
    int num_points = point_pixel_edges.size();
    vector<vector<int>> two_d_array(num_points, vector<int>(2));
    for (int i = 0; i < num_points; i++) {
        // Lưu trữ vị trí của điểm biên thứ i
        two_d_array[i][0] = point_pixel_edges[i].x;
        two_d_array[i][1] = point_pixel_edges[i].y;
    }
    float theta_matrix[2][180];
    
    for (int i = 0; i < 180; i++) {

        theta_matrix[0][i] = cos(theta);
        theta_matrix[1][i] = sin(theta);
        theta += theta;
    }

    vector<vector<int>> vote_matrix(num_points, vector<int>(num_theta));
    for (int i = 0; i < num_points; i ++) {
        for (int  j = 0; j < num_theta; j ++ ) {
            for (int k = 0; k < 2; k++ ) {
                vote_matrix[i][j] += two_d_array[i][k] * theta_matrix[k][j];
            }
            
        }
    }

    for (int i = 0; i < num_points ; i++) {
        for (int j = 0; j < num_theta; j++) {
            int rho_post = int(cvRound(vote_matrix[i][j])) + num_rho;
            edge_matrix[rho_post][j] += 1;
        }
    }



    // Tính toán ma trận vote_matrix
    Mat vote_matrix(point_pixel_edges.size(), num_theta, CV_32S);
    for (int i = 0; i < point_pixel_edges.size(); i++) {
        for (int i = 1; i <= 180; i++) {
            vote_matrix.at<int>(i, 0)
        }
        vote_matrix.at<int>(i, 0) = idx[i].x * cos(theta) + idx[i].y * sin(theta);
    }

    // Tính toán ma trận edge_matrix
    int rho_pos;
    for (int vr = 0; vr < vote_matrix.rows; vr++) {
        for (int vc = 0; vc < vote_matrix.cols; vc++) {
            rho_pos = round(vote_matrix.at<int>(vr, vc)) + num_rho;
            edge_matrix.at<int>(rho_pos, vc)++;
        }
    }

    // Tìm các đường thẳng được phát hiện
    std::vector<Vec2d> lines;
    for (int i = 0; i < edge_matrix.rows; i++) {
        for (int j = 0; j < edge_matrix.cols; j++) {
            if (edge_matrix.at<int>(i, j) > threshold) {
                lines.push_back(Vec2d( i - num_rho, j * theta / CV_PI ));
            }
        }
    }

    // Cố định tham số rho và theta
    for (auto& line : lines) {
        line[0] = line[0] - 1;
        line[1] = line[1] * theta / CV_PI;
    }

    return lines;
}
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
    vector<Vec2i> lines = my_hough(edges, 100);

    // Vẽ các đường thẳng được phát hiện lên ảnh
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
    }

    // Hiển thị ảnh
    imshow("Image", img);
    waitKey(0);

    return 0;
}