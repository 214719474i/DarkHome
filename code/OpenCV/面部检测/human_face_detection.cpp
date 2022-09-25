#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


void main() {
	Mat src = imread("path");//����ͼ��·���Զ���
	if (src.empty()) {//����ȡ��ͼ���ļ��Ƿ�ɹ�
		cout << "�ļ���ʧ��..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);//����һ������
	imshow("src", src);//�ڴ�����չʾͼ��
	//����һ��������������ļ��������ȡ��xml�ļ���opencv�Դ��������ļ�
	CascadeClassifier face_detector = CascadeClassifier("/etc/haarcascade_frontalface_default.xml");
	vector<Rect> face;//����һ���������������ܼ�⵽�Ĳ���
	face_detector.detectMultiScale(src, face);//��ʼ��⣬�����������face��
	for (int i = 0; i < face.size(); i++) {//��������
		rectangle(src, face[i], Scalar(0, 0, 255), 2);//�������
	}
	namedWindow("detectResult", WINDOW_AUTOSIZE);//��������
	imshow("detectResult", src);//չʾ�����ڴ�����

	waitKey(0);
	destroyAllWindows();
	return;
}