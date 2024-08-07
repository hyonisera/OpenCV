#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
Point ptOld;
uchar red, green, blue;
Scalar color(0, 255, 255);

void on_mouse(int event, int x, int y, int flags, void*);

int main(void)
{
	img = imread("lenna.bmp");
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	srand(time(NULL));

	namedWindow("img");
	setMouseCallback("img", on_mouse);
	imshow("img", img);
	waitKey();
	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:
		blue = (rand() % 256);
		green = (rand() % 256);
		red = (rand() % 256);
		color = Scalar(blue, green, red);
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << ", Color : " << color << endl;
		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			line(img, ptOld, Point(x, y), color, 2);
			imshow("img", img);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}