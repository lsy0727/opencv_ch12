//1번
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("beta.png");

	Mat gray, bin;
	src = ~src;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);	//바깥쪽 외곽선 검출
	//바운딩 박스 그리기
	Rect boundingBox = boundingRect(contours[0]);
	rectangle(src, boundingBox, Scalar(0, 0, 255), 1);

	RotatedRect minR = minAreaRect(contours[0]);	//0번 객체에 대한 사각형의 정보
	Point2f pts[4];	//꼭짓점 4개 좌표
	minR.points(pts);	//정보입력
	//최소면적사각형
	for (int i = 0; i < 4; i++) {
		line(src, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 1);
	}

	Point2f center;
	float radius;
	//최소면적 원
	minEnclosingCircle(contours[0], center, radius);	//0번 객체에 대한 원의 중심 좌표, 반지름을 구함
	circle(src, center, radius, Scalar(0, 255, 255), 1);

	imshow("result", src);
	imshow("bin", bin);
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
	Mat src = imread("rotateda.bmp");
	Mat gray, bin, rev;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	rev = ~bin;

	vector<vector<Point>> contours;
	findContours(rev, contours, RETR_LIST, CHAIN_APPROX_NONE);

	RotatedRect minR = minAreaRect(contours[1]);
	float angle = minR.angle;

	Point2f center;
	float radius;
	minEnclosingCircle(contours[1], center, radius);
	Mat M = getRotationMatrix2D(center, angle, 1);

	Mat dst;
	warpAffine(src, dst, M, Size(), INTER_LINEAR, BORDER_REPLICATE);

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
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
	Mat img = imread("shapes.png");

	Mat gray, bin, rev;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	rev = ~bin;

	vector<vector<Point>> contours;
	findContours(rev, contours, RETR_LIST, CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		drawContours(img, contours, i, Scalar(0, 0, 255), 2);
	}

	int triangle = 0, rectangle = 0, pentagon = 0, hexagon = 0, circle = 0;
	for (vector<Point> pts : contours) {	//contours 요소의 수만큼 반복함, 외곽선을 pts에 복사
		if (contourArea(pts) < 400)continue;	//면적이 400미만이면 무시

		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);	//외곽선을 근사화(점의 개수를 줄임)

		int vtc = (int)approx.size();	//근사화된 외곽선의 꼭짓점 개수
		if (vtc == 3) { triangle++; }
		else if (vtc == 4) { rectangle++; }
		else if (vtc == 5) { pentagon++; }
		else if (vtc == 6) { hexagon++; }
		else {
			double len = arcLength(pts, true);	//외곽선 둘레 길이
			double area = contourArea(pts);	//외곽선의 면적
			double ratio = 4. * CV_PI * area / (len * len);	//이상적인 원일수록 1에 가까움
			if (ratio > 0.85) { circle++; }	//0.85보다 크면 원으로 간주
		}
	}
	cout << "삼각형의 갯수:" << triangle << endl;
	cout << "사각형의 갯수:" << rectangle << endl;
	cout << "오각형의 갯수:" << pentagon << endl;
	cout << "육각형의 갯수:" << hexagon << endl;
	cout << "원의 갯수:" << circle << endl;
	imshow("img", img);
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
	Mat src = imread("polygon2.bmp");
	Mat gray, bin, rev;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	rev = ~bin;

	vector<vector<Point>> contours;
	findContours(rev, contours, RETR_LIST, CHAIN_APPROX_NONE);

	double trilen = 0, rectlen = 0, cirlen = 0;
	double triarea = 0, rectarea = 0, cirarea = 0;
	for (vector<Point> pts : contours) {	//contours 요소의 수만큼 반복함, 외곽선을 pts에 복사
		static int count = 0;
		drawContours(src, contours, count++, Scalar(0, 0, 255), 2);	//외곽선 그리기

		if (contourArea(pts) < 400)continue;	//면적이 400미만이면 무시

		vector<Point> approx;	//근사화된 다각형의 꼭짓점 저장
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);	//외곽선을 근사화(점의 개수를 줄임)

		int vtc = (int)approx.size();	//근사화된 외곽선의 꼭짓점 개수
		if (vtc == 3) {
			trilen = arcLength(pts, true);	//ture : 폐곡선, 첫번째 점과 마지막 점을 연결함
			triarea = contourArea(pts);
		}
		else if (vtc == 4) {
			rectlen = arcLength(pts, true);
			rectarea = contourArea(pts);
		}
		else {
			double len = arcLength(pts, true);	//외곽선 둘레 길이
			double area = contourArea(pts);	//외곽선의 면적
			double ratio = 4. * CV_PI * area / (len * len);	//이상적인 원일수록 1에 가까움
			if (ratio > 0.85) {	//0.85보다 크면 원으로 간주
				cirlen = len;
				cirarea = area;
			}
		}

	}
	cout << "원의 둘레 길이:" << cirlen << endl;
	cout << "원의 면적:" << cirarea << endl;
	cout << "삼각형의 둘레 길이:" << trilen << endl;
	cout << "삼각형의 면적:" << triarea << endl;
	cout << "사각형의 둘레 길이:" << rectlen << endl;
	cout << "사각형의 면적:" << rectarea << endl;

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
	Mat src = imread("ellipse.png");
	Mat copy_src = src.clone();
	Mat gray, bin, rev;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	rev = ~bin;

	vector<vector<Point>> contours;
	findContours(rev, contours, RETR_LIST, CHAIN_APPROX_NONE);
	drawContours(copy_src, contours, 0, Scalar(0, 0, 255), 2);	//외곽선 - 빨간색
	Mat dst1 = copy_src.clone();	//근사화 오차 0.02일때 외곽선을 그릴 영상
	Mat dst2 = copy_src.clone();	//근사화 오차 0.002일때 외곽선을 그릴 영상


	vector<vector<Point>> approx(2);	//근사화된 다각형의 꼭짓점 저장
	Mat approx_src = dst1;
	float mag = 0.02;	//근사화 오차 초기값 0.02
	for (int i = 0; i < 2; i++) {
		approxPolyDP(contours[0], approx[i], arcLength(contours[0], true) * mag, true);	//외곽선을 근사화(점의 개수를 줄임), 오차가 작아질수록 기존 외곽선에 가까워짐
		for (int j = 0; j < approx[i].size(); j++) {
			line(approx_src, approx[i][j], approx[i][(j + 1) % approx[i].size()], Scalar(255, 0, 0), 2);	//근사화된 외곽선 - 파란색
		}
		approx_src = dst2;
		mag = 0.002;	//근사화 오차 0.002로 설정
	}

	cout << "외곽선길이:" << arcLength(contours[0], true) << endl;
	cout << "외곽선 면적:" << contourArea(contours[0]) << endl;
	cout << "근사화된 외곽선의 길이:" << arcLength(approx[0], true) << endl;
	cout << "근사화된 외곽선 면적:" << contourArea(approx[0]) << endl;

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	return 0;
}
*/