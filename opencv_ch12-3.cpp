//1번
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main(void)
{
    Mat src = imread("D:/Users/AIRLAB/source/repos/beta.png");
    Mat dst = src.clone(), tmp = src.clone();
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
    cvtColor(tmp, tmp, COLOR_BGR2GRAY);
    threshold(tmp, tmp, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    vector<vector<Point>> contours;
    findContours(tmp, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    Rect min_rect = boundingRect(contours[0]);
    RotatedRect ro_rect = minAreaRect(contours[0]);
    Point2f pts[4];
    ro_rect.points(pts);
    for (int i = 0; i < 4; i++) {
        line(dst, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 2);
    }
    Point2f center;
    float radius;
    minEnclosingCircle(contours[0], center, radius);
    rectangle(dst, min_rect, Scalar(0, 0, 255), 2);
    circle(dst, center, radius, Scalar(255, 0, 255), 2);

    imshow("src", src);
    imshow("dst", dst);
    imshow("tmp", tmp);
    waitKey();

    return 0;
}

//2번
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main(void)
{
    Mat src = imread("D:/Users/Admin/opencv/rotateda.bmp");
    Mat dst = src.clone(), tmp = src.clone();
    if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
    cvtColor(tmp, tmp, COLOR_BGR2GRAY);
    threshold(tmp, tmp, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    vector<vector<Point>> contours;
    findContours(tmp, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    RotatedRect ro_rect = minAreaRect(contours[0]);
    Mat M = getRotationMatrix2D(ro_rect.center, ro_rect.angle, 1);
    warpAffine(src, dst, M, Size(), 1, BORDER_REFLECT);

    imshow("src", src);
    imshow("dst", dst);
    imshow("tmp", tmp);
    waitKey();

    return 0;
}

//3번
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void)
{
    Mat img = imread("D:/Users/Admin/opencv/shapes.png", IMREAD_COLOR);
    if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }
    Mat gray;
    int three = 0, four = 0, five = 0, six = 0, cir = 0;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);
    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++) { // 하나의 외곽선 추출
        drawContours(img, contours, i, Scalar(0, 0, 255), 2);
        vector<Point> approx;
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);
        // 외곽선 근사화
        int vtc = (int)approx.size(); // 근사화된 점의 갯수
        if (vtc == 3) {
            three++;
        }
        else if (vtc == 4) {
            four++;
        }
        else if (vtc == 5) {
            five++;
        }
        else if (vtc == 6) {
            six++;
        }
        else {
            double len = arcLength(contours[i], true);
            double area = contourArea(contours[i]);
            double ratio = 4. * CV_PI * area / (len * len);
            if (ratio > 0.85) {
                cir++;
            }
        }
    }
    cout << "삼각형의 갯수 : " << three << endl;
    cout << "사각형의 갯수 : " << four << endl;
    cout << "오각형의 갯수 : " << five << endl;
    cout << "육각형의 갯수 : " << six << endl;
    cout << "원의 갯수 : " << cir << endl;
    imshow("img", img);
    waitKey(0);
    return 0;
}

//4번
#include <iostream>
#include "opencv2/opencv.hpp"
#include <cmath>
using namespace std;
using namespace cv;

double line_length(Point first, Point second) {
    return sqrt(pow((first.x - second.x), 2) + pow((first.y - second.y), 2));
}

int main(void)
{
    Mat img = imread("D:/Users/AIRLAB/source/repos/polygon2.bmp");
    if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }
    Mat gray;
    double length_t = 0, length_r = 0, length_c = 0;
    double three = 0, four = 0, cir = 0;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Mat bin;
    threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++) { // 하나의 외곽선 추출
        drawContours(img, contours, i, Scalar(0, 0, 255), 2);
        vector<Point> approx;
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);

        // 외곽선 근사화
        int vtc = (int)approx.size(); // 근사화된 점의 갯수

        if (vtc == 3) {
            for (int j = 0; j < 3; j++) {
                length_t += line_length(approx[j], approx[(j + 1) % 3]);
            }
            three = contourArea(contours[i]);
        }
        else if (vtc == 4) {
            for (int j = 0; j < 4; j++) {
                length_r += line_length(approx[j], approx[(j + 1) % 4]);
            }
            four = contourArea(contours[i]);
        }
        else {
            double len = arcLength(contours[i], true);
            double area = contourArea(contours[i]);
            double ratio = 4. * CV_PI * area / (len * len);
            if (ratio > 0.85) {
                for (int j = 0; j < vtc; j++) {
                    length_c += line_length(approx[j], approx[(j + 1) % vtc]);
                }
            }
            cir = contourArea(contours[i]);
        }
    }

    std::cout << "원의 둘레 길이 : " << length_c << endl;
    std::cout << "원의 면적 : " << cir << endl;
    std::cout << "삼각형의 둘레 길이 : " << length_t << endl;
    std::cout << "삼각형의 면적 : " << three << endl;
    std::cout << "사각형의 둘레 길이 : " << length_r << endl;
    std::cout << "사각형의 면적 : " << four << endl;
    cv::imshow("img", img);
    cv::waitKey();
    return 0;
}

//5번
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void) {
    Mat img = imread("D:/Users/AIRLAB/source/repos/ellipse.png");
    if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }

    Mat tmp, dst;
    cvtColor(img, tmp, COLOR_BGR2GRAY);
    threshold(tmp, tmp, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(tmp, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    double length_c = arcLength(contours[0], false);  // 외각선 길이
    double cir = contourArea(contours[0], false);      // 외각선 면적
    cout << "원의 둘레 길이 : " << length_c << endl;
    cout << "원의 면적 : " << cir << endl;

    drawContours(img, contours, 0, Scalar(0, 0, 255), 2);

    vector<Point> approx;
    approxPolyDP(contours[0], approx, arcLength(contours[0], false) * 0.02, true);

    dst = img.clone();
    for (int j = 0; j < approx.size(); j++) {
        line(dst, approx[j], approx[(j + 1) % approx.size()], Scalar(255, 0, 0), 2);
    }

    double close_c = arcLength(approx, false);          // 근사화된 외각선 길이
    double close_cir = contourArea(approx, false);      // 근사화된 외각선 면적

    cout << "근사화된 둘레 길이 : " << close_c << endl;
    cout << "근사화된 면적 : " << close_cir << endl;

    imshow("img", img);
    imshow("tmp", tmp);
    imshow("dst", dst);

    waitKey();
    return 0;
}
