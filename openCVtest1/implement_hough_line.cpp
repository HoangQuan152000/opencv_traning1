/*
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;


// Hàm phát hiện đường thẳng trong ảnh bằng thuật toán Hough với các tham số rho và theta cố định
vector<Vec2f> my_hough(Mat img, double rho, double theta, int threshold) {

    // Tính toán chiều cao và chiều rộng của ảnh
    int img_height = img.rows;
    int img_width = img.cols;

    // Tính toán độ dài và độ dốc của đường thẳng dài nhất có thể được phát hiện
    int diagonal_length = int(sqrt(img_height * img_height + img_width * img_width));
    int max_num_rho = int(diagonal_length / rho);
    int num_theta = int(CV_PI / theta);

    // Find pixels that are edges
    vector<Point> point_pixel_edges;
    findNonZero(img, point_pixel_edges);
    int num_points_edges = point_pixel_edges.size();

    vector<vector<int>> arr_point_edges(num_points_edges, vector<int>(2));
    for (int i = 0; i < num_points_edges; i++) {

        arr_point_edges[i][0] = point_pixel_edges[i].x;
        arr_point_edges[i][1] = point_pixel_edges[i].y;
    }
    // Tạo ma trận theta
    vector<vector<float>> theta_matrix(2, vector<float>(num_theta));
    float current_theta = 0;
    for (int i = 0; i < num_theta; i++) {
        theta_matrix[0][i] = cos(current_theta);
        theta_matrix[1][i] = sin(current_theta);
        current_theta += theta;
    }

    vector<vector<float>> vote_matrix(num_points_edges, vector<float>(num_theta));
    for (int i = 0; i < num_points_edges; i++) {
        for (int j = 0; j < num_theta; j++) {
            for (int k = 0; k < 2; k++) {
                vote_matrix[i][j] += arr_point_edges[i][k] * theta_matrix[k][j];
            }
        }
    }

    // Tạo ma trận kích thước (2 * num_rho + 1, num_theta)
    vector<vector<float>> edge_matrix(2 * max_num_rho + 1, vector<float>(num_theta));

    for (int i = 0; i < edge_matrix.size(); i++) {
        for (int j = 0; j < edge_matrix[i].size(); j++) {
            edge_matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < num_points_edges; i++) {
        for (int j = 0; j < num_theta; j++) {

            int rho_post = int(cvRound(vote_matrix[i][j])) + max_num_rho;

            edge_matrix[rho_post][j] += 1;

        }
    }

    vector<Vec2i> line_idx;
    for (int i = 0; i < edge_matrix.size(); i++) {
        for (int j = 0; j < edge_matrix[i].size(); j++) {
            if (edge_matrix[i][j] > threshold) {
                line_idx.push_back({ i, j });
            }
        }
    }

    vector<int> rho_values;

    for (int i = 0; i < line_idx.size(); i++) {
        rho_values.push_back(line_idx[i][0] - max_num_rho);
    }
    // Chuyển đổi giá trị theta về radian
    vector<float> theta_values;
    for (int i = 0; i < line_idx.size(); i++) {
        theta_values.push_back(line_idx[i][1] * CV_PI / 180.0);
    }
    // Tạo vector chứa các đường thẳng
    vector<Vec2f> lines(line_idx.size());

    // Chuyển đổi giá trị rho và theta cho các phần tử của vector lines
    for (int i = 0; i < line_idx.size(); i++) {
        lines.emplace_back(rho_values[i], theta_values[i]);
    }
    return lines;
}

int main() {

    // Đọc ảnh
    Mat img = imread("sample.jpg");
    resize(img, img, Size(640, 460));
    if (img.empty())
    {
        return -1;
    }
    // Chuyển ảnh sang ảnh xám
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(5, 5), 0);
    // Áp dụng thuật toán Canny để phát hiện cạnh
    Mat edges;
    Canny(gray, edges, 100, 200);

    // Phát hiện đường thẳng bằng hàm my_hough
    vector<Vec2f> lines = my_hough(edges, 1, CV_PI / 180, 100);
    //vector<Vec2f> lines;
    //HoughLines(edges , lines , 1 , CV_PI / 180 , 100);

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
        line(gray, pt1, pt2, Scalar(0, 0, 255), 2);
    }
    vector<Vec2f> hough_lines;
    HoughLines(edges, hough_lines, 1, CV_PI / 180, 100);
    for (size_t i = 0; i < hough_lines.size(); i++)
    {
        float rho = hough_lines[i][0], theta = hough_lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(img, pt1, pt2, Scalar(0, 0, 255), 2);
    }
    // Hiển thị ảnh
    imshow("Image", img);
    imshow("gray", gray);
    waitKey(0);

    return 0;
}
*/

