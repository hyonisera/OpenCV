#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void contrast();
void on_contrast(int pos, void* userdata);

int main() {
	contrast();
	return 0;
}

void contrast() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("contrast", "dst", 0, 10, on_contrast, (void*)&src);
	on_contrast(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}

void on_contrast(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;

	float a = (float)pos / 10.f;
	Mat dst = src + (src - 128) * a;

	String str = format("Alpha = %.1f", a);

	putText(dst, str, Point(0, 25), 0, 1, Scalar(0, 0, 0), 2);

	imshow("src", src);
	imshow("dst", dst);
}