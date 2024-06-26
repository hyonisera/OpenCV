#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
#define COLSIZE	50
int colsel = 0, sel = 0;
vector <Scalar> colpal;
void on_mouse(int event, int x, int y, int flags, void*);
void resetPaint(Mat&);
int main(void) {
	Mat pal = Mat::zeros(600, 600, CV_8UC3);
	namedWindow("MyPaint");
	setMouseCallback("MyPaint", on_mouse, (Mat*)&pal);
	colpal.push_back(Scalar(127, 127, 127));
	colpal.push_back(Scalar(0, 0, 255));
	colpal.push_back(Scalar(0, 255, 0));
	colpal.push_back(Scalar(255, 0, 0));
	colpal.push_back(Scalar(255, 0, 255));
	colpal.push_back(Scalar(255, 255, 0));
	colpal.push_back(Scalar(0, 255, 255));
	colpal.push_back(Scalar(255, 255, 255));
	resetPaint(pal);
	waitKey();
	return 0;
}
void resetPaint(Mat& mat)
{
	mat = Mat::zeros(600, 600, CV_8UC3);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			Rect rect(j * COLSIZE, i * COLSIZE, COLSIZE, COLSIZE);
			rectangle(mat, rect, colpal[i * 2 + j], -1);
		}
	}
	rectangle(mat, Rect(0, COLSIZE * 5, COLSIZE, COLSIZE), colpal[7], 2);
	rectangle(mat, Rect(8, COLSIZE * 5 + 8, COLSIZE - 16, COLSIZE - 16), colpal[colsel], -1);
	rectangle(mat, Rect(COLSIZE, COLSIZE * 5, COLSIZE, COLSIZE), colpal[7], 2);
	circle(mat, Point(COLSIZE + (COLSIZE / 2), COLSIZE * 5 + (COLSIZE / 2)), (COLSIZE - 14) / 2, colpal[colsel], -1);
	if (sel == 0) {
		rectangle(mat, Rect(6, COLSIZE * 5 + 6, COLSIZE - 12, COLSIZE - 12), colpal[7], 1);
		circle(mat, Point(COLSIZE + (COLSIZE / 2), COLSIZE * 5 + (COLSIZE / 2)), (COLSIZE - 12) / 2, Scalar(0, 0, 0), 1);
	}
	else {
		rectangle(mat, Rect(6, COLSIZE * 5 + 6, COLSIZE - 12, COLSIZE - 12), Scalar(0, 0, 0), 1);
		circle(mat, Point(COLSIZE + (COLSIZE / 2), COLSIZE * 5 + (COLSIZE / 2)), (COLSIZE - 12) / 2, colpal[7], 1);
	}
	imshow("MyPaint", mat);
}
void on_mouse(int event, int x, int y, int flags, void* user)
{
	Mat pal = *(Mat*)user;
	int cx, cy;
	Point oldPt;

	if (event == EVENT_LBUTTONDOWN) {
		if ((x > 0 && x < COLSIZE * 2) && (y > 0 && y < COLSIZE * 4)) {
			cx = (int)(x / COLSIZE);
			cy = (int)(y / COLSIZE);

			colsel = cx + cy * 2;
			rectangle(pal, Rect(8, COLSIZE * 5 + 8, COLSIZE - 16, COLSIZE - 16), colpal[colsel], -1);
			circle(pal, Point(COLSIZE + (COLSIZE / 2), COLSIZE * 5 + (COLSIZE / 2)), (COLSIZE - 14) / 2, colpal[colsel], -1);
		}
		else if ((x > 0 && x < COLSIZE * 2) && (y > COLSIZE * 5 && y < COLSIZE * 5 + COLSIZE)) {
			if (x < COLSIZE) {
				sel = 0;
				rectangle(pal, Rect(6, COLSIZE * 5 + 6, COLSIZE - 12, COLSIZE - 12), colpal[7], 1);
				circle(pal, Point(COLSIZE + (COLSIZE / 2), COLSIZE * 5 + (COLSIZE / 2)), (COLSIZE - 12) / 2, Scalar(0, 0, 0), 1);
			}
			else {
				sel = 1;
				rectangle(pal, Rect(6, COLSIZE * 5 + 6, COLSIZE - 12, COLSIZE - 12), Scalar(0, 0, 0), 1);
				circle(pal, Point(COLSIZE + (COLSIZE / 2), COLSIZE * 5 + (COLSIZE / 2)), (COLSIZE - 12) / 2, colpal[7], 1);
			}
		}
		else {
			if (x > COLSIZE * 2) {
				if (sel == 0)
					rectangle(pal, Rect(x - 8, y - 8, 16, 16), colpal[colsel], -1);
				else
					circle(pal, Point(x, y), 8, colpal[colsel], 2);
			}
		}
		imshow("MyPaint", pal);
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (flags & EVENT_FLAG_LBUTTON) {
			if (x > COLSIZE * 2) {
				if (sel == 0)
					rectangle(pal, Rect(x - 8, y - 8, 16, 16), colpal[colsel], -1);
				else
					circle(pal, Point(x, y), 8, colpal[colsel], 2);
				imshow("MyPaint", pal);
			}
		}
	}
	else if (event == EVENT_RBUTTONDOWN) {
		resetPaint(pal);
	}
}