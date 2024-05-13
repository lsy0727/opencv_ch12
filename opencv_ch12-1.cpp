//1
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main() {
	Mat src = imread("labelex.png", IMREAD_GRAYSCALE);

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	double x, y;
	double max_x = centroids.at<double>(1, 0), max_y = centroids.at<double>(1, 1), min_x = centroids.at<double>(1, 0), min_y = centroids.at<double>(1, 1);
	int area;
	int max_area = 0, max = 1, min_area = 0, min = 1;
	for (int i = 2; i < stats.rows; i++) {
		x = centroids.at<double>(i, 0);
		y = centroids.at<double>(i, 1);
		area = stats.at<int>(i, 4);
		if (area > max_area) {
			max_area = area;
			max = i;
			max_x = x;
			max_y = y;
		}
		if (area < min_area) {
			min_area = area;
			min = i;
			min_x = x;
			min_y = y;
		}
	}

	cvtColor(src, src, COLOR_GRAY2BGR);
	rectangle(src, Rect(stats.at<int>(min, 0), stats.at<int>(min, 1), stats.at<int>(min, 2), stats.at<int>(min, 3)), Scalar(255, 0, 0));
	rectangle(src, Rect(stats.at<int>(max, 0), stats.at<int>(max, 1), stats.at<int>(max, 2), stats.at<int>(max, 3)), Scalar(0, 0, 255));
	cout << "������ �ִ��� ��ü�� ���̺�:" << max << endl;
	cout << "�����߽�:(x,y): " << max_x << "\t" << max_y << endl;
	cout << "������ �ּ��� ��ü�� ���̺�:" << min << endl;
	cout << "�����߽�:(x,y): " << min_x << "\t" << min_y << endl;

	imshow("src", src);
	waitKey();
	destroyAllWindows();
	return 0;
}
*/

//2
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("polygon.bmp");

	Mat gray, bin;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 150, 255, THRESH_BINARY_INV);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	cout << "���� " << cnt << endl;
	cout << "label\tx\ty\twidth\theight\tarea\tcolor[B,G,R]" << endl;

	for (int i = 1; i < cnt; i++) {
		double x = centroids.at<double>(i, 0);	//�����߽� x��ǥ
		double y = centroids.at<double>(i, 1);	//�����߽� y��ǥ
		rectangle(src, Rect(stats.at<int>(i, 0), stats.at<int>(i, 1), stats.at<int>(i, 2), stats.at<int>(i, 3)), Scalar(0, 255, 255));
		putText(src, to_string(i), Point(x, y),	//to_string(i) : int�� ������ i�� ���� string���� ��ȯ
			FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
		cout << i << "\t" << stats.at<int>(i, 0) << "\t" << stats.at<int>(i, 1) << "\t" << stats.at<int>(i, 2) << "\t" << stats.at<int>(i, 3) << "\t" << stats.at<int>(i, 4)
			<< "\t" << src.at<Vec3b>(y, x) << endl;
	}
	imshow("src", src);
	imshow("gray", gray);
	imshow("bin", bin);
	waitKey();
	return 0;
}
*/

//3
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("polygon.bmp");

	Mat gray, bin;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 150, 255, THRESH_BINARY_INV);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	int xcount, ycount, count;
	for (int i = 1; i < cnt; i++) {
		xcount = 0;	//x��ǥ �� �ʱ�ȭ
		ycount = 0;	//y��ǥ �� �ʱ�ȭ
		count = 0;	//�� �ȼ� �� �ʱ�ȭ
		for (int n = stats.at<int>(i, 1); n < stats.at<int>(i, 1) + stats.at<int>(i, 3); n++) {
			for (int m = stats.at<int>(i, 0); m < stats.at<int>(i, 0) + stats.at<int>(i, 2); m++) {
				xcount += m;
				ycount += n;
				count++;
			}
		}
		cout << i << "�� ��ü�� �����߽�:(" << xcount/(double)count << ", " << ycount/(double)count << ")" << endl;
	}
}
*/

//4
/*
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	Mat src = imread("car.jpg");
	Mat src_clone = src.clone();
	Mat labels, stats, centroids;

	namedWindow("����ȭ ����");
	int pos = 0;	//����ȭ ������ �Ӱ谪
	createTrackbar("threshold", "����ȭ ����", &pos, 255);

	while (true) {
		imshow("src", src);
		src = src_clone.clone();

		Mat gray, blurring, dx;
		cvtColor(src, gray, COLOR_BGR2GRAY);	//�׷��� ��ȯ
		blur(gray, blurring, Size(5, 5));	//5x5 ����
		Sobel(blurring, dx, CV_32FC1, 1, 0);	//x�� ���� ��̺�
		dx.convertTo(dx, CV_8UC1);	//8��Ʈ 1ä�� �������� ��ȯ
		imshow("x�� ���� �Һ�", dx);

		Mat bin;
		threshold(dx, bin, pos, 255, THRESH_BINARY);	//����ȭ
		imshow("����ȭ ����", bin);

		Mat close;
		Mat rect = getStructuringElement(MORPH_RECT, Size(30, 5));	//5�� 50���� �簢�� ���� ���
		morphologyEx(bin, close, MORPH_CLOSE, rect, Point(-1,-1));	//���� ����
		imshow("���� ����", close);

		int cnt = connectedComponentsWithStats(close, labels, stats, centroids);
		int max = stats.at<int>(1, 4);
		int max_cnt = 1;
		for (int i = 2; i < cnt; i++) {
			if (stats.at<int>(i, 4) > max) {
				max = stats.at<int>(i, 4);
				max_cnt = i;
			}
		}
		rectangle(src, Rect(stats.at<int>(max_cnt, 0), stats.at<int>(max_cnt, 1), stats.at<int>(max_cnt, 2), stats.at<int>(max_cnt, 3)), Scalar(0, 0, 255), 2);

		waitKey(1);
	}

	return 0;
}
*/