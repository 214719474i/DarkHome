#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


void main() {
	Mat src = imread("path");
	Mat insertImage = imread("stickers_path");
	if (src.empty()) {
		cout << "could not load this file..." << endl;
		return;
	}
	pyrDown(src, src);//如果待检测图像太大，可以降采样
	CascadeClassifier face_detector = CascadeClassifier("/etc/haarcascade_frontalface_default.xml");
	vector<Rect> face;
	face_detector.detectMultiScale(src, face, 1.001, 100, 0, Size(70, 70), Size(100, 100));//, 1.001, 100, 0, Size(70, 70), Size(100,100)
	Mat imageROI;
	for (int i = 0; i < face.size(); i++) {
		resize(insertImage, insertImage, Size(face[i].width / 4, face[i].height / 4));
		//将贴纸设置到合适的位置上，如检测区域的正上方
		insertImage.copyTo(src(Rect(face[i].tl().x + face[i].width / 2 - face[i].width / 8, face[i].tl().y,
			face[i].width / 4, face[i].height / 4)));
	}
	namedWindow("detectresult", WINDOW_AUTOSIZE);
	imshow("detectresult", src);
	waitKey(0);
	destroyAllWindows();
	return;
}