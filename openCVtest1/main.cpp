
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;



vector<Vec2f> my_hough(Mat img, double rho , double theta , int threshold) {

   // Calculate the width and height of the image
    int img_height = img.rows;
    int img_width = img.cols;

    // calculate the diagonal length
    int diagonal_length = int(sqrt(img_height * img_height + img_width * img_width));
    // maximum number of cases of rho and theta
    int max_num_rho = int(diagonal_length / rho);
    int num_theta = int(CV_PI / theta);

    // Find pixels that are edges
    vector<Point> point_pixel_edges;
    findNonZero(img, point_pixel_edges);
    int num_points_edges = point_pixel_edges.size();

    //Change the row and col positions of Point to each other
    vector<vector<int>> arr_point_edges(num_points_edges, vector<int>(2));
    for (int i = 0; i < num_points_edges; i++) {

        arr_point_edges[i][0] = point_pixel_edges[i].x;
        arr_point_edges[i][1] = point_pixel_edges[i].y;
    }
    // Create a 2 X 180 matrix containing theta cases
    vector<vector<float>> theta_matrix(2, vector<float>(num_theta));
    float current_theta = 0;
    for (int i = 0; i < num_theta; i++) {
        theta_matrix[0][i] = cos(current_theta);
        theta_matrix[1][i] = sin(current_theta);
        current_theta += theta;
    }

    // Create a voting matrix as the dot product of 2 matrices
    vector<vector<float>> vote_matrix(num_points_edges, vector<float>(num_theta));
    for (int i = 0; i < num_points_edges; i++) {
        for (int j = 0; j < num_theta; j++) {
            for (int k = 0; k < 2; k++) {
                vote_matrix[i][j] += arr_point_edges[i][k] * theta_matrix[k][j];
            }
        }
    }

    // create a matrix that counts the number of repetitions of rho and theta pairs
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
    // create an index matrix containing pairs of rho and theta greater than the threshold
    vector<Vec2i> line_idx;
    for (int i = 0; i < edge_matrix.size(); i++) {
        for (int j = 0; j < edge_matrix[i].size(); j++) {
            if (edge_matrix[i][j] > threshold) {
                line_idx.push_back({ i, j });
            }
        }
    }
     // Create a vector containing rho values
    vector<int> rho_values;

    for (int i = 0; i < line_idx.size(); i++) {
        rho_values.push_back(line_idx[i][0] - max_num_rho);
    }
     // Create a vector containing theta values
    vector<float> theta_values;
    for (int i = 0; i < line_idx.size(); i++) {
        theta_values.push_back(line_idx[i][1] * CV_PI / 180.0);
    }
     // add the pairs rho and theta and the returned array
    vector<Vec2f> lines;
    lines.resize(line_idx.size());
    for (int i = 0; i < line_idx.size(); i++) {
        lines[i] = Vec2f(rho_values[i], theta_values[i]);
    }
    return lines;
}

int main() {

    
    Mat img = imread("sample.jpg");
    resize(img, img, Size(640, 460));
    if (img.empty())
    {
        return -1;
    }
    
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(5, 5), 0);
    
    Mat edges;
    Canny(gray, edges, 100, 200);

    
    vector<Vec2f> lines = my_hough(edges, 1, CV_PI/180 , 100);
    

    // Vẽ các đường thẳng được phát hiện lên ảnh
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        // Stretch the start and end positions out of the image range
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


