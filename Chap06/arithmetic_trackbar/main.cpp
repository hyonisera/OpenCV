#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src2;
Mat dst;
void onChange(int pos, void* userdata);
int main(void)
{
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	src2 = imread("square.bmp", IMREAD_GRAYSCALE);
	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	addWeighted(src1, 0, src2, 1, 0, dst);
	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);
	createTrackbar("weight", "dst", 0, 10, onChange, (void*)&src1);

	waitKey();
	return 0;
}
void onChange(int pos, void* userdata)
{
	Mat src1 = *(Mat*)userdata;
	float alpha = pos * 0.1;

	addWeighted(src1, alpha, src2, 1 - alpha, 0, dst);
	imshow("dst", dst);
}