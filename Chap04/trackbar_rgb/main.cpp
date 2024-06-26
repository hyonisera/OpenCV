#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
void on_level_changeR(int pos, void* userdata);
void on_level_changeG(int pos, void* userdata);
void on_level_changeB(int pos, void* userdata);
uchar red = 0, green = 0, blue = 0;
int main(void)
{
	Mat img = Mat::zeros(500, 500, CV_8UC3);
	int value = 128;
	namedWindow("image");
	createTrackbar("Red", "image", 0, 255, on_level_changeR, (void*)&img);
	createTrackbar("Green", "image", 0, 255, on_level_changeG, (void*)&img);
	createTrackbar("Blue", "image", 0, 255, on_level_changeB, (void*)&img);

	imshow("image", img);
	waitKey();
	return 0;
}
void on_level_changeR(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;
	red = pos;
	img.setTo(Scalar(blue, green, red));
	imshow("image", img);
}
void on_level_changeG(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;
	green = pos;
	img.setTo(Scalar(blue, green, red));
	imshow("image", img);
}
void on_level_changeB(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;
	blue = pos;
	img.setTo(Scalar(blue, green, red));
	imshow("image", img);
}