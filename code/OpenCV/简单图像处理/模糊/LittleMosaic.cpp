#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//һ����������Ч��
void main() {
	Mat src = imread("path");//�Զ���·���������þ���·��
	if (src.empty()) {
		cout << "cloud not load this file..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);
	int k = 10;//�����Ŵ����С�ĳߴ�
	int nums = 10;//ѭ������
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