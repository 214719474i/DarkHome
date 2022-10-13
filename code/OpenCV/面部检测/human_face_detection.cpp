#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


void main() {
	Mat src = imread("path");//加载图像，路径自定义
	if (src.empty()) {//检查读取的图像文件是否成功
		cout << "could not load this file..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);//创建一个窗体
	imshow("src", src);//在窗体上展示图像
	//创建一个用来检测特征的检测器，读取的xml文件是opencv自带的人脸文件
	CascadeClassifier face_detector = CascadeClassifier("/etc/haarcascade_frontalface_default.xml");
	vector<Rect> face;//创建一个矩形容器来接受检测到的参数
	face_detector.detectMultiScale(src, face, 1.001, 100, 0, Size(70, 70), Size(100, 100));//开始检测，结果参数存于face中
	//参数说明：
	//参数1：image--待检测图片，一般为灰度图像加快检测速度；
	//参数2：objects--被检测物体的矩形框向量组；
	//参数3：scaleFactor--表示在前后两次相继的扫描中，搜索窗口的比例系数。默认为1.1即每次搜索窗口依次扩大10%;
	//参数4：minNeighbors--表示构成检测目标的相邻矩形的最小个数(默认为3个)。
	//参数5：flags--使用默认值
	//参数6、7：minSize和maxSize用来限制得到的目标区域的范围。
	for (int i = 0; i < face.size(); i++) {//遍历容器
		rectangle(src, face[i], Scalar(0, 0, 255), 2);//框出人脸
	}
	namedWindow("detectResult", WINDOW_AUTOSIZE);//创建窗体
	imshow("detectResult", src);//展示人脸在窗体上

	waitKey(0);
	destroyAllWindows();
	return;
}