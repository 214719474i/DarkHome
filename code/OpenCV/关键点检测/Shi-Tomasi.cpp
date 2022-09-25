#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void main() {
	Mat src = imread("path");//路径请自定义哦~
	if (src.empty()) {
		cout << "could not load this file..." << endl;
		return;
	}
	Mat gray_src;
	vector<Point> corners;
	cvtColor(src, gray_src, COLOR_BGR2GRAY);
	goodFeaturesToTrack(gray_src, corners, 0, 0.01, 10);
	for (int i = 0; i < corners.size(); i++) {
		circle(src, corners[i], 2, Scalar(0, 0, 255));
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);
	waitKey(0);
	destroyAllWindows();
	return;
}
