#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void main() {
	Mat src = imread("path");
	if (src.empty()) {
		cout << "文件打开失败..." << endl;
		return;
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);
	cvtColor(src, src, COLOR_BGR2GRAY);//转为灰度图像
	int row = getOptimalDFTSize(src.rows);//获得行做DFT的最佳数值，基于原图像的行
	int col = getOptimalDFTSize(src.cols);//获得列做DFT的最佳数值，基于原图像的列
	copyMakeBorder(src, src, 0, (row - src.rows), 0, (col - src.cols), BORDER_CONSTANT, Scalar::all(0));//填充边界使得图像易做DFT

	Mat planes[] = { Mat_<float>(src), Mat::zeros(src.size(), CV_32F) };
	Mat complex, dst;
	merge(planes, 2, complex);//合并为双通道的图像。分别用于存储实部和虚部
	dft(complex, complex);//DFT变换
	split(complex, planes);//将实部和虚部分别存储
	magnitude(planes[0], planes[1], planes[0]);//将实部和虚部合并为幅度
	planes[0] += Scalar::all(1);//加一防止有的数为0
	log(planes[0], planes[0]);//对幅度取对数
	normalize(planes[0], dst, 0, 1, NORM_MINMAX);//归一化
	//画x轴和y轴，便容易从图中观测到DFT的直观情况
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