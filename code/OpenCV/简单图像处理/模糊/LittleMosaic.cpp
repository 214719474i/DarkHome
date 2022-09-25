#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//一点点的马赛克效果
void main() {
	Mat src = imread("path");//自定义路径，建议用绝对路径
	if (src.empty()) {
		cout << "cloud not load this file..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);
	int k = 10;//调整放大和缩小的尺寸
	int nums = 10;//循环轮数
	for (int i = 0; i < nums; i++) {
		resize(src, src, Size(src.cols / k, src.rows / k));
		resize(src, src, Size(src.cols * k, src.rows * k));
	}
	namedWindow("Mosaic", WINDOW_AUTOSIZE);
	imshow("Mosaic", src);
	waitKey(0);
	destroyAllWindows();
	return;
}