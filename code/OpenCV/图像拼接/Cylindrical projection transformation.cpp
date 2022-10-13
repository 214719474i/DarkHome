#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;


void main() {
	Mat src = imread("path");
	if (src.empty()) {
		cout << "could not load this file..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	int w = src.cols;
	int h = src.rows;
	Mat result = Mat::zeros(src.size(), src.type());
	float theta = PI / 12; //30����Զ���Ĭ�������Ħ�=30��
	float r = w / (2 * tan(theta));//����
	int ix, iy;
	float fx, fy;
	for (int y = 0; y < h; y++) {//��
		for (int x = 0; x < w; x++) {//��
			float k = sqrt(float(r * r + (x - w / 2) * (x - w / 2)));//��ʽ
			fx = r * sin(theta) + r * sin(atan((x - w / 2) / r));//x��任
			fy = h / 2 + r * (y - h / 2) / k;//y��任
			ix = int(fx);
			iy = int(fy);

			if (ix < w && iy < h) {//ȷ��ͶӰ֮��Ŀ�߲�Ҫ�����趨�Ľ���
				result.at<Vec3b>(iy, ix)[0] = src.at<Vec3b>(y, x)[0];//��ֵ
				result.at<Vec3b>(iy, ix)[1] = src.at<Vec3b>(y, x)[1];
				result.at<Vec3b>(iy, ix)[2] = src.at<Vec3b>(y, x)[2];
			}

		}
	}
	namedWindow("transform", WINDOW_AUTOSIZE);
	imshow("transform", result);

	waitKey(0);
	destroyAllWindows();
	return;
}