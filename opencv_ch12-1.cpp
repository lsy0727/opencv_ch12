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

	double x, y;	//객체의 무게중심 x, y좌표를 임시로 저장할 변수
	//max_x, max_y = 면적이 가장 큰 객체의 무게중심 x, y좌표 / min_x, min_y = 면적이 가장 작은 객체의 무게중심 x, y좌표
	double max_x = centroids.at<double>(1, 0), max_y = centroids.at<double>(1, 1), min_x = centroids.at<double>(1, 0), min_y = centroids.at<double>(1, 1);
	int area;	//객체의 면적을 임시로 저장할 변수
	//max_area = 면적이 가장 큰 객체의 면적, max = 면적이 가장 큰 객체의 레이블 값 / min_area = 면적이 가장 작은 객체의 면적, min = 면적이 가장 작은 객체의 레이블 값
	int max_area = 0, max = 1, min_area = 0, min = 1;
	for (int i = 2; i < stats.rows; i++) {
		x = centroids.at<double>(i, 0);	//무게중심 x좌표
		y = centroids.at<double>(i, 1);	//무게중심 y좌표
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
	cout << "면적이 최대인 객체의 레이블:" << max << endl;
	cout << "무게중심:(x,y): " << max_x << "\t" << max_y << endl;
	cout << "면적이 최소인 객체의 레이블:" << min << endl;
	cout << "무게중심:(x,y): " << min_x << "\t" << min_y << endl;

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

	cout << "갯수 " << cnt << endl;
	cout << "label\tx\ty\twidth\theight\tarea\tcolor[B,G,R]" << endl;

	for (int i = 1; i < cnt; i++) {
		double x = centroids.at<double>(i, 0);	//무게중심 x좌표
		double y = centroids.at<double>(i, 1);	//무게중심 y좌표
		rectangle(src, Rect(stats.at<int>(i, 0), stats.at<int>(i, 1), stats.at<int>(i, 2), stats.at<int>(i, 3)), Scalar(0, 255, 255));
		putText(src, to_string(i), Point(x, y),	//to_string(i) : int형 변수인 i의 값을 string으로 변환
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
		xcount = 0;	//x좌표 합 초기화
		ycount = 0;	//y좌표 합 초기화
		count = 0;	//총 픽셀 수 초기화
		for (int n = stats.at<int>(i, 1); n < stats.at<int>(i, 1) + stats.at<int>(i, 3); n++) {
			for (int m = stats.at<int>(i, 0); m < stats.at<int>(i, 0) + stats.at<int>(i, 2); m++) {
				xcount += m;
				ycount += n;
				count++;
			}
		}
		cout << i << "번 객체의 무게중심(  직접 계산  ):(" << xcount/(double)count << ", " << ycount/(double)count << ")" << endl;
		cout << i << "번 객체의 무게중심(레이블링 함수):(" << centroids.at<double>(i, 0) << "," << centroids.at<double>(i, 1) << ")" << endl << endl;
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

	namedWindow("이진화 영상");
	int pos = 0;	//이진화 영상의 임계값
	createTrackbar("threshold", "이진화 영상", &pos, 255);

	while (true) {
		imshow("src", src);
		src = src_clone.clone();

		Mat gray, blurring, dx;
		cvtColor(src, gray, COLOR_BGR2GRAY);	//그레이 변환
		blur(gray, blurring, Size(5, 5));	//5x5 블러링
		Sobel(blurring, dx, CV_32FC1, 1, 0);	//x축 방향 편미분
		dx.convertTo(dx, CV_8UC1);	//8비트 1채널 영상으로 변환
		imshow("x축 방향 소벨", dx);

		Mat bin;
		threshold(dx, bin, pos, 255, THRESH_BINARY);	//이진화
		imshow("이진화 영상", bin);

		Mat close;
		Mat rect = getStructuringElement(MORPH_RECT, Size(30, 5));	//5행 50열의 사각형 구조 요소
		morphologyEx(bin, close, MORPH_CLOSE, rect, Point(-1,-1));	//닫힘 연산
		imshow("닫힘 연산", close);

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
