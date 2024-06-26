#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_level_change(int pos, void* userdata);

int main(void)
{
	Mat img = Mat::zeros(500, 500, CV_8UC1); //400x400을 0으로 채움
	int value = 128;

	namedWindow("image");
	createTrackbar("level", "image", &value, 255, on_level_change, (void*)&img);

	imshow("image", img);
	waitKey();

	return 0;
}

void on_level_change(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;

	img.setTo(pos); //0부터 16까지면 img.setTo(pos * 16);
	imshow("image", img);
}