#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


void main() {
	Mat src = imread("path");//加载图像，路径自定义
	if (src.empty()) {//检查读取的图像文件是否成功
		cout << "文件打开失败..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);//创建一个窗体
	imshow("src", src);//在窗体上展示图像
	//创建一个用来检测特征的检测器，读取的xml文件是opencv自带的人脸文件
	CascadeClassifier face_detector = CascadeClassifier("/etc/haarcascade_frontalface_default.xml");
	vector<Rect> face;//创建一个矩形容器来接受检测到的参数
	face_detector.detectMultiScale(src, face);//开始检测，结果参数存于face中
	for (int i = 0; i < face.size(); i++) {//遍历容器
		rectangle(src, face[i], Scalar(0, 0, 255), 2);//框出人脸
	}
	namedWindow("detectResult", WINDOW_AUTOSIZE);//创建窗体
	imshow("detectResult", src);//展示人脸在窗体上

	waitKey(0);
	destroyAllWindows();
	return;
}