//1��
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

//2��
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
	cout << "�ܰ����� ����:" << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++) {
		cout << i << "��° �ܰ����� ���� ��ǥ:" << endl;
		for (int j = 0; j < contours[i].size(); j++) cout << contours[i][j] << ',';
		cout << endl;
	}
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
	Mat src = imread("labelex.png", IMREAD_GRAYSCALE);
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);	//����ȭ
	Mat rev = ~bin;	//���� ���� (���� ��ü�� ��ü�� �ν����� ���ϰ� ��)
	vector<vector<Point>> contours;
	findContours(rev, contours, RETR_LIST, CHAIN_APPROX_NONE);

	cvtColor(src, src, COLOR_GRAY2BGR);

	for (int i = 0; i < contours.size(); i++) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255);	//�ܰ��� ��
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

//4��
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
		cout << i << "��° �ܰ��� ����:" << contours[i].size() << endl;	//�ܰ��� ���� = �ܰ��� ���� ����
	}
	int line_num = 0;	//���� �� �ܰ��� ��ȣ (0��°�� �ʱ�ȭ)
	int long_det = contours[0].size();	//���� �� �ܰ����� ����(0��° �ܰ����� ���̷� �ʱ�ȭ)
	for (int i = 1; i < contours.size(); i++) {	//1��° �ܰ������� ��
		if (contours[i].size() > long_det) {
			line_num = i;
			long_det = contours[i].size();
		}
	}
	drawContours(src, contours, line_num, Scalar(0, 0, 255), 2);
	cout << "���̰� �ִ��� �ܰ���:" << line_num << "��°, ���̴� " << long_det << endl;
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
		pt_x.push_back(centroids.at<double>(i, 0));	//�����߽� x��ǥ
	}

	for (int i = 0; i < contours.size(); i++) {
		if (pt_x[i] > (stats.at<int>(i, 0) + stats.at<int>(i, 2)) / 2)	//�����߽� x��ǥ ��ġ�� ��ü�� �����ʿ� �ִٸ�
		{
			drawContours(src, contours, i, Scalar(255, 0, 0), 2);
			cout << i << "��° ����(�Ķ���):�������� ����" << endl;
		}
		else if (pt_x[i] < (stats.at<int>(i, 0) + stats.at<int>(i, 2)) / 2)	//�����߽� x��ǥ ��ġ�� ��ü�� ���ʿ� �ִٸ�
		{
			drawContours(src, contours, i, Scalar(0, 0, 255), 2);
			cout << i << "��° ����(������):���������� ����" << endl;
		}
	}

	imshow("src", src);
	waitKey();
	return 0;
}
*/