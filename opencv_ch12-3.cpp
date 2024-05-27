//1��
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
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);	//�ٱ��� �ܰ��� ����
	//�ٿ�� �ڽ� �׸���
	Rect boundingBox = boundingRect(contours[0]);
	rectangle(src, boundingBox, Scalar(0, 0, 255), 1);

	RotatedRect minR = minAreaRect(contours[0]);	//0�� ��ü�� ���� �簢���� ����
	Point2f pts[4];	//������ 4�� ��ǥ
	minR.points(pts);	//�����Է�
	//�ּҸ����簢��
	for (int i = 0; i < 4; i++) {
		line(src, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 1);
	}

	Point2f center;
	float radius;
	//�ּҸ��� ��
	minEnclosingCircle(contours[0], center, radius);	//0�� ��ü�� ���� ���� �߽� ��ǥ, �������� ����
	circle(src, center, radius, Scalar(0, 255, 255), 1);

	imshow("result", src);
	imshow("bin", bin);
	waitKey();
	return 0;
}
*/

//2��
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

//3��
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
	for (vector<Point> pts : contours) {	//contours ����� ����ŭ �ݺ���, �ܰ����� pts�� ����
		if (contourArea(pts) < 400)continue;	//������ 400�̸��̸� ����

		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);	//�ܰ����� �ٻ�ȭ(���� ������ ����)

		int vtc = (int)approx.size();	//�ٻ�ȭ�� �ܰ����� ������ ����
		if (vtc == 3) { triangle++; }
		else if (vtc == 4) { rectangle++; }
		else if (vtc == 5) { pentagon++; }
		else if (vtc == 6) { hexagon++; }
		else {
			double len = arcLength(pts, true);	//�ܰ��� �ѷ� ����
			double area = contourArea(pts);	//�ܰ����� ����
			double ratio = 4. * CV_PI * area / (len * len);	//�̻����� ���ϼ��� 1�� �����
			if (ratio > 0.85) { circle++; }	//0.85���� ũ�� ������ ����
		}
	}
	cout << "�ﰢ���� ����:" << triangle << endl;
	cout << "�簢���� ����:" << rectangle << endl;
	cout << "�������� ����:" << pentagon << endl;
	cout << "�������� ����:" << hexagon << endl;
	cout << "���� ����:" << circle << endl;
	imshow("img", img);
	waitKey();
	return 0;
}
*/

//4��
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
	for (vector<Point> pts : contours) {	//contours ����� ����ŭ �ݺ���, �ܰ����� pts�� ����
		static int count = 0;
		drawContours(src, contours, count++, Scalar(0, 0, 255), 2);	//�ܰ��� �׸���

		if (contourArea(pts) < 400)continue;	//������ 400�̸��̸� ����

		vector<Point> approx;	//�ٻ�ȭ�� �ٰ����� ������ ����
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);	//�ܰ����� �ٻ�ȭ(���� ������ ����)

		int vtc = (int)approx.size();	//�ٻ�ȭ�� �ܰ����� ������ ����
		if (vtc == 3) {
			trilen = arcLength(pts, true);	//ture : ��, ù��° ���� ������ ���� ������
			triarea = contourArea(pts);
		}
		else if (vtc == 4) {
			rectlen = arcLength(pts, true);
			rectarea = contourArea(pts);
		}
		else {
			double len = arcLength(pts, true);	//�ܰ��� �ѷ� ����
			double area = contourArea(pts);	//�ܰ����� ����
			double ratio = 4. * CV_PI * area / (len * len);	//�̻����� ���ϼ��� 1�� �����
			if (ratio > 0.85) {	//0.85���� ũ�� ������ ����
				cirlen = len;
				cirarea = area;
			}
		}

	}
	cout << "���� �ѷ� ����:" << cirlen << endl;
	cout << "���� ����:" << cirarea << endl;
	cout << "�ﰢ���� �ѷ� ����:" << trilen << endl;
	cout << "�ﰢ���� ����:" << triarea << endl;
	cout << "�簢���� �ѷ� ����:" << rectlen << endl;
	cout << "�簢���� ����:" << rectarea << endl;

	imshow("src", src);
	waitKey();
	return 0;
}
*/

//5��
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
	drawContours(copy_src, contours, 0, Scalar(0, 0, 255), 2);	//�ܰ��� - ������
	Mat dst1 = copy_src.clone();	//�ٻ�ȭ ���� 0.02�϶� �ܰ����� �׸� ����
	Mat dst2 = copy_src.clone();	//�ٻ�ȭ ���� 0.002�϶� �ܰ����� �׸� ����


	vector<vector<Point>> approx(2);	//�ٻ�ȭ�� �ٰ����� ������ ����
	Mat approx_src = dst1;
	float mag = 0.02;	//�ٻ�ȭ ���� �ʱⰪ 0.02
	for (int i = 0; i < 2; i++) {
		approxPolyDP(contours[0], approx[i], arcLength(contours[0], true) * mag, true);	//�ܰ����� �ٻ�ȭ(���� ������ ����), ������ �۾������� ���� �ܰ����� �������
		for (int j = 0; j < approx[i].size(); j++) {
			line(approx_src, approx[i][j], approx[i][(j + 1) % approx[i].size()], Scalar(255, 0, 0), 2);	//�ٻ�ȭ�� �ܰ��� - �Ķ���
		}
		approx_src = dst2;
		mag = 0.002;	//�ٻ�ȭ ���� 0.002�� ����
	}

	cout << "�ܰ�������:" << arcLength(contours[0], true) << endl;
	cout << "�ܰ��� ����:" << contourArea(contours[0]) << endl;
	cout << "�ٻ�ȭ�� �ܰ����� ����:" << arcLength(approx[0], true) << endl;
	cout << "�ٻ�ȭ�� �ܰ��� ����:" << contourArea(approx[0]) << endl;

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	return 0;
}
*/