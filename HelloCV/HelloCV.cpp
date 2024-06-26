#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main() {
	cout << "Hello OpenCV" << CV_VERSION << endl;

	Mat img;
	img = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("image");
	imshow("image", img);

	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(95);
	imwrite("lenna.jpg", img, params);

	waitKey(0);
	return 0;
}