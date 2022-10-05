#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;


//与人脸检测的方式是一样的
void main() {
	Mat src = imread("path of the license plate");
	if (src.empty()) {
		cout << "could not load this file..." << endl;
		return;
	}
	vector<Rect> card;
	CascadeClassifier carCardDet = CascadeClassifier("etc\\haarcascade_russian_plate_number.xml");
	carCardDet.detectMultiScale(src, card);
	for (int i = 0; i < card.size(); i++) {
		rectangle(src, card[i], Scalar(0, 0, 255));
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);
	waitKey(0);
	destroyAllWindows();
	return;
}