#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void camera_in();
void video_in();
void camera_in_video_out();

int main(void)
{
	camera_in();
	video_in();
	camera_in_video_out();

	return 0;
}

void camera_in()
{
	VideoCapture cap(0); //VideoCapture : 영상을 읽어들이는 클래스, 장치번호를 쓰면 웹캠에서, 파일이름을 쓰면 파일에서 읽어들임, cap 변수, 장치 하나면 기본적으로 0번(안되면 1번)

	if (!cap.isOpened()) { //true가 되면 연결되지 않은 것
		cerr << "Camera open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl; //영상의 가로 사이즈를 얻음
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl; //세로 사이즈, cvRound : 실수를 정수로 바꿈, cap.get : 영상의 정보를 얻음

	Mat frame, inversed; //Mat : 2차원에 대한 클래스, 영상을 다루는
	while (true) { //영상은 무한루프를 돌음
		cap >> frame; //cap 에서의 정지영상(한 프레임)을 읽어서 frame에 보냄, cap.read() 해도 됨
		//cap.read(frame);
		if (frame.empty()) //캡쳐한 화면을 읽었는데 비었으면 영상을 못 얻어온 것
			break;

		inversed = ~frame; //영상을 반전시켜서 inversed 객체에 넣어줌

		imshow("frame", frame); //읽어들인 이미지를 띄워줌, namedwindow 안 써도 됨, 창이 두 개
		imshow("inversed", inversed);

		if (waitKey(10) == 27) // 27 = ESC key //딜레이가 있는 키보드 입력 받음 //10미리세크 단위로 -> 움직이는 것처럼 보임 //100 -> 1초에 10프레임
			break;
	}

	destroyAllWindows(); //떠있는 윈도우를 다 종료시킴
}

void video_in()
{
	VideoCapture cap("stopwatch.avi"); //파일이 있는지 확인

	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl; 
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

	double fps = cap.get(CAP_PROP_FPS); //초당 몇 프레임으로 데이터가 들어오는지
	cout << "FPS: " << fps << endl;

	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}

void camera_in_video_out()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS); //초당 프레임 수

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X'); //fourcc : 코덱을 결정하는 글자
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened()) { 
		cout << "File open failed!" << endl;
		return;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame; 
		if (frame.empty())
			break;

		inversed = ~frame;
		outputVideo << inversed; //.write() 해도 됨

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}

	destroyAllWindows();
}
