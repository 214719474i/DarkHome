#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


void main() {
	Mat insertImage = imread("path of stickers");
	VideoCapture cap(0);
	Mat frame;
	namedWindow("video", WINDOW_AUTOSIZE);
	CascadeClassifier face_detector = CascadeClassifier("/etc/haarcascade_frontalface_default.xml");
	vector<Rect> face;
	while (cap.read(frame)) {
		face_detector.detectMultiScale(frame, face, 1.1, 10);

		for (int i = 0; i < face.size(); i++) {
			resize(insertImage, insertImage, Size(face[i].width, face[i].height));
			insertImage.copyTo(frame(face[i]));
			//rectangle(frame, face[i], Scalar(0, 0, 255));
		}
		imshow("video", frame);
		char c = waitKey(1000 / 24);
		if (c == 'q') {
			return;
		}
	}
	waitKey(0);
	destroyAllWindows();
	return;
}