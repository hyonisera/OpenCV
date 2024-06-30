#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main() {
	Point pt1;
	pt1.x = 5; pt1.y = 10;
	Point pt2(10, 30);

	Point pt3 = pt1 + pt2;
	Point pt4 = pt1 * 2;

	int d1 = pt1.dot(pt2);


	cout << d1 << endl << pt4 << endl;
}