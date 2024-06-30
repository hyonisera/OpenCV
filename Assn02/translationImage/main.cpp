#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat img;
Point ptOld;
void on_mouse(int event, int x, int y, int flags, void*);

int main() {
	img = imread("tekapo.bmp");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("img");
	setMouseCallback("img", on_mouse);
	

	imshow("img", img);
	waitKey();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);
		Mat M = Mat_<double>({ 2, 3 }, { 1, 0, x, 0, 1, y });
		break;
	case EVENT_LBUTTONUP:
		warpAffine(src, dst, M, Size());
		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			
			imshow("img", img);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}