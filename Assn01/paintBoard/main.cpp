#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat board(500, 500, CV_8UC3, Scalar(0, 0, 0));
Point ptOld;
Scalar color(255, 255, 255);

bool drawRec = false;
bool drawCir = false;
void palette();
void on_mouse(int event, int x, int y, int flags, void*);
void selectBorder();

int main() {
	palette();
	namedWindow("paintBoard");
	setMouseCallback("paintBoard", on_mouse);
	imshow("paintBoard", board);
	waitKey();

	return 0;
}

void palette() {
	rectangle(board, Rect(0, 0, 50, 50), Scalar(0, 0, 255), -1);
	rectangle(board, Rect(50, 0, 50, 50), Scalar(0, 125, 255), -1);
	rectangle(board, Rect(0, 50, 50, 50), Scalar(0, 255, 255), -1);
	rectangle(board, Rect(50, 50, 50, 50), Scalar(0, 255, 0), -1);
	rectangle(board, Rect(0, 100, 50, 50), Scalar(255, 0, 0), -1);
	rectangle(board, Rect(50, 100, 50, 50), Scalar(255, 0, 125), -1);
	rectangle(board, Rect(0, 150, 50, 50), Scalar(255, 0, 255), -1);
	rectangle(board, Rect(50, 150, 50, 50), Scalar(255, 255, 255), -1);

	rectangle(board, Rect(0, 250, 50, 50), Scalar(255, 255, 255), 2);
	rectangle(board, Rect(50, 250, 50, 50), Scalar(255, 255, 255), 2);

	rectangle(board, Rect(10, 260, 30, 30), Scalar(255, 255, 255), -1);
	circle(board, Point(75, 275), 15, Scalar(255, 255, 255), -1);
}

void on_mouse(int event, int x, int y, int flags, void*) {
	int cx = x / 50;
	int cy = y / 50;

	if (event == EVENT_LBUTTONDOWN) {
		ptOld = Point(x, y);

		if (cx == 0 && cy == 0) color = Scalar(0, 0, 255);
		else if (cx == 1 && cy == 0) color = Scalar(0, 125, 255);
		else if (cx == 0 && cy == 1) color = Scalar(0, 255, 255);
		else if (cx == 1 && cy == 1) color = Scalar(0, 255, 0);
		else if (cx == 0 && cy == 2) color = Scalar(255, 0, 0);
		else if (cx == 1 && cy == 2) color = Scalar(255, 0, 125);
		else if (cx == 0 && cy == 3) color = Scalar(255, 0, 255);
		else if (cx == 1 && cy == 3) color = Scalar(255, 255, 255);

		else if (cx == 0 && cy == 5) {
			drawRec = true, drawCir = false;
			selectBorder();
		}
		else if (cx == 1 && cy == 5) {
			drawCir = true, drawRec = false;
			selectBorder();
		}
	}
	else if (event == EVENT_LBUTTONUP) {
		rectangle(board, Rect(10, 260, 30, 30), color, -1);
		circle(board, Point(75, 275), 16, color, -1);
		
		if (drawRec) {
			rectangle(board, Rect(x, y, 20, 20), color, -1);
		}
		else if (drawCir) {
			circle(board, Point(x, y), 10, color, -1);
		}
		imshow("paintBoard", board);
	}
	else if ((event == EVENT_MOUSEMOVE) && (flags & EVENT_FLAG_LBUTTON)) {
		if (drawRec) {
			rectangle(board, Rect(x, y, 20, 20), color, -1);
		}
		else if (drawCir) {
			circle(board, Point(x, y), 10, color, -1);
		}
		else {
			line(board, ptOld, Point(x, y), color, 2);
			ptOld = Point(x, y);
		}
		imshow("paintBoard", board);
	}
	else if (event == EVENT_RBUTTONDOWN) {
		palette();
		imshow("paintBoard", board);
	}
}

void selectBorder() {
	palette();

	if (drawRec) {
		rectangle(board, Rect(8, 258, 34, 34), Scalar(255, 255, 255), 2);
	}
	else if (drawCir) {
		circle(board, Point(75, 275), 18, Scalar(255, 255, 255), 2);
	}
	imshow("paintBoard", board);
}