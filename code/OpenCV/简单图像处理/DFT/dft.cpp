#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void main() {
	Mat src = imread("path");
	if (src.empty()) {
		cout << "�ļ���ʧ��..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);
	cvtColor(src, src, COLOR_BGR2GRAY);//תΪ�Ҷ�ͼ��
	int row = getOptimalDFTSize(src.rows);//�������DFT�������ֵ������ԭͼ�����
	int col = getOptimalDFTSize(src.cols);//�������DFT�������ֵ������ԭͼ�����
	copyMakeBorder(src, src, 0, (row - src.rows), 0, (col - src.cols), BORDER_CONSTANT, Scalar::all(0));//���߽�ʹ��ͼ������DFT

	Mat planes[] = { Mat_<float>(src), Mat::zeros(src.size(), CV_32F) };
	Mat complex, dst;
	merge(planes, 2, complex);//�ϲ�Ϊ˫ͨ����ͼ�񡣷ֱ����ڴ洢ʵ�����鲿
	dft(complex, complex);//DFT�任
	split(complex, planes);//��ʵ�����鲿�ֱ�洢
	magnitude(planes[0], planes[1], planes[0]);//��ʵ�����鲿�ϲ�Ϊ����
	planes[0] += Scalar::all(1);//��һ��ֹ�е���Ϊ0
	log(planes[0], planes[0]);//�Է���ȡ����
	normalize(planes[0], dst, 0, 1, NORM_MINMAX);//��һ��
	//��x���y�ᣬ�����״�ͼ�й۲⵽DFT��ֱ�����
	line(dst, Point(0, dst.cols / 2), Point(dst.rows, dst.cols / 2), Scalar(0, 0, 255));
	line(dst, Point(dst.rows / 2, dst.cols), Point(dst.rows / 2, 0), Scalar(0, 0, 255));
	putText(dst, "x", Point(dst.rows - 40, dst.cols / 2 - 40), CV_FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255));
	putText(dst, "y", Point(dst.rows / 2 + 40, 40), CV_FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255));

	namedWindow("dst", WINDOW_AUTOSIZE);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
	return;
}