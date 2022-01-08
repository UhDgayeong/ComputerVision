#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

String face_cascade = "C:/Program Files/OpenCV4.4.0/build/etc/haarcascades/haarcascade_frontalface_alt.xml";
String eye_cascade = "C:/Program Files/OpenCV4.4.0/build/etc/haarcascades/haarcascade_eye.xml";
CascadeClassifier face;
CascadeClassifier eye;

void FaceAndEyeDetect(Mat);

int main()
{
	VideoCapture v(0); //0번 카메라를 열어 변수 v에 저장
	assert(v.isOpened());

	bool b1 = face.load(face_cascade);
	bool b2 = eye.load(eye_cascade);
	assert(b1 && b2);

	Mat frame;
	while (true) {
		v.read(frame);
		FaceAndEyeDetect(frame);
		if ((char)waitKey(20) == 27) break;
	}
	return 0;
}

void FaceAndEyeDetect(Mat img)
{
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	vector<Rect> face_pos;	// 얼굴 검출 결과를 표시하는 직사각형
	face.detectMultiScale(gray, face_pos, 1.1, 2, 0, Size(10, 10));

	for (int i = 0; i < face_pos.size(); i++)
		rectangle(img, face_pos[i], Scalar(255, 0, 0), 2);

	for (int i = 0; i < face_pos.size(); i++) { 	// 눈 검출
		vector<Rect> eye_pos;
		Mat roi = gray(face_pos[i]);

		eye.detectMultiScale(roi, eye_pos, 1.1, 2, 0, Size(10, 10));

		for (int j = 0; j < eye_pos.size(); j++) {
			Point center(face_pos[i].x + eye_pos[j].x + eye_pos[j].width * 0.5,
				face_pos[i].y + eye_pos[j].y + eye_pos[j].height * 0.5);
			int radius = cvRound((eye_pos[j].width + eye_pos[j].height) * 0.25);
			circle(img, center, radius, Scalar(0, 0, 255), 2, 8, 0);
		}
	}
	imshow("얼굴 검출", img);
}

