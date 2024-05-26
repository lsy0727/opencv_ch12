//1번
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("polygon.bmp");

	Mat gray, bin, rev;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	rev = ~bin;
	vector<vector<Point>> polygon;
	findContours(rev, polygon, RETR_LIST, CHAIN_APPROX_NONE);

	for (int i = 0; i < polygon.size(); i++) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(src, polygon, i, c, 2);
	}

	imshow("src", src);
	waitKey();
	return 0;
}
*/

//2번
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	uchar data[] = {
		0,0,1,1,0,0,0,0,
		1,1,1,1,0,0,1,0,
		1,1,1,1,0,0,0,0,
		0,0,0,0,0,1,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,1,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0
	};
	Mat src = Mat(8, 8, CV_8UC1, data) * 255;
	vector<vector<Point>> contours;
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
	cout << "외곽선의 갯수:" << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++) {
		cout << i << "번째 외곽선의 점의 좌표:" << endl;
		for (int j = 0; j < contours[i].size(); j++) cout << contours[i][j] << ',';
		cout << endl;
	}
	return 0;
}
*/

//3번
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("labelex.png", IMREAD_GRAYSCALE);
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);	//이진화
	Mat rev = ~bin;	//영상 반전 (영상 자체를 객체로 인식하지 못하게 함)
	vector<vector<Point>> contours;
	findContours(rev, contours, RETR_LIST, CHAIN_APPROX_NONE);

	cvtColor(src, src, COLOR_GRAY2BGR);

	for (int i = 0; i < contours.size(); i++) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255);	//외곽선 색
		for (int j = 0; j < contours[i].size() - 1; j++) {
			line(src, contours[i][j], contours[i][j + 1], c, 2);
		}
		line(src, contours[i][0], contours[i][contours[i].size() - 1], c, 2);
	}
	imshow("src", src);
	waitKey();
	return 0;
}
*/

//4번
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("labelex.png");

	Mat gray, bin, rev;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	rev = ~bin;
	vector<vector<Point>> contours;
	findContours(rev, contours, RETR_LIST, CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		cout << i << "번째 외곽선 길이:" << contours[i].size() << endl;	//외곽선 길이 = 외곽선 점의 개수
	}
	int line_num = 0;	//가장 긴 외곽선 번호 (0번째로 초기화)
	int long_det = contours[0].size();	//가장 긴 외곽선의 길이(0번째 외곽선의 길이로 초기화)
	for (int i = 1; i < contours.size(); i++) {	//1번째 외곽선부터 비교
		if (contours[i].size() > long_det) {
			line_num = i;
			long_det = contours[i].size();
		}
	}
	drawContours(src, contours, line_num, Scalar(0, 0, 255), 2);
	cout << "길이가 최대인 외곽선:" << line_num << "번째, 길이는 " << long_det << endl;
	imshow("src", src);
	waitKey();
	return 0;
}
*/

//5번
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("char_c.png");

	Mat gray, bin, rev;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	rev = ~bin;

	vector<vector<Point>> contours;
	findContours(rev, contours, RETR_LIST, CHAIN_APPROX_NONE);

	vector<int> pt_x;
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(rev, labels, stats, centroids);
	for (int i = 0; i < cnt; i++) {
		pt_x.push_back(centroids.at<double>(i, 0));	//무게중심 x좌표
	}

	for (int i = 0; i < contours.size(); i++) {
		if (pt_x[i] > (stats.at<int>(i, 0) + stats.at<int>(i, 2)) / 2)	//무게중심 x좌표 위치가 객체의 오른쪽에 있다면
		{
			drawContours(src, contours, i, Scalar(255, 0, 0), 2);
			cout << i << "번째 문자(파란색):왼쪽으로 열림" << endl;
		}
		else if (pt_x[i] < (stats.at<int>(i, 0) + stats.at<int>(i, 2)) / 2)	//무게중심 x좌표 위치가 객체의 왼쪽에 있다면
		{
			drawContours(src, contours, i, Scalar(0, 0, 255), 2);
			cout << i << "번째 문자(빨간색):오른쪽으로 열림" << endl;
		}
	}

	imshow("src", src);
	waitKey();
	return 0;
}
*/