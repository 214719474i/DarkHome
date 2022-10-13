#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


void main() {
	Mat src = imread("path");//����ͼ��·���Զ���
	if (src.empty()) {//����ȡ��ͼ���ļ��Ƿ�ɹ�
		cout << "could not load this file..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);//����һ������
	imshow("src", src);//�ڴ�����չʾͼ��
	//����һ��������������ļ��������ȡ��xml�ļ���opencv�Դ��������ļ�
	CascadeClassifier face_detector = CascadeClassifier("/etc/haarcascade_frontalface_default.xml");
	vector<Rect> face;//����һ���������������ܼ�⵽�Ĳ���
	face_detector.detectMultiScale(src, face, 1.001, 100, 0, Size(70, 70), Size(100, 100));//��ʼ��⣬�����������face��
	//����˵����
	//����1��image--�����ͼƬ��һ��Ϊ�Ҷ�ͼ��ӿ����ٶȣ�
	//����2��objects--���������ľ��ο������飻
	//����3��scaleFactor--��ʾ��ǰ��������̵�ɨ���У��������ڵı���ϵ����Ĭ��Ϊ1.1��ÿ������������������10%;
	//����4��minNeighbors--��ʾ���ɼ��Ŀ������ھ��ε���С����(Ĭ��Ϊ3��)��
	//����5��flags--ʹ��Ĭ��ֵ
	//����6��7��minSize��maxSize�������Ƶõ���Ŀ������ķ�Χ��
	for (int i = 0; i < face.size(); i++) {//��������
		rectangle(src, face[i], Scalar(0, 0, 255), 2);//�������
	}
	namedWindow("detectResult", WINDOW_AUTOSIZE);//��������
	imshow("detectResult", src);//չʾ�����ڴ�����

	waitKey(0);
	destroyAllWindows();
	return;
}