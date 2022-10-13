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
	float theta = PI / 12; //30°除以二，默认真正的θ=30°
	float r = w / (2 * tan(theta));//焦距
	int ix, iy;
	float fx, fy;
	for (int y = 0; y < h; y++) {//行
		for (int x = 0; x < w; x++) {//列
			float k = sqrt(float(r * r + (x - w / 2) * (x - w / 2)));//公式
			fx = r * sin(theta) + r * sin(atan((x - w / 2) / r));//x轴变换
			fy = h / 2 + r * (y - h / 2) / k;//y轴变换
			ix = int(fx);
			iy = int(fy);

			if (ix < w && iy < h) {//确保投影之后的宽高不要超出设定的界限
				result.at<Vec3b>(iy, ix)[0] = src.at<Vec3b>(y, x)[0];//赋值
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