#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void detectHScolor(const Mat& image, double minHue, double maxHue, double minSat, double maxSat, Mat& mask) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);

	vector<Mat> channels;
	split(hsv, channels); //HSV 채널 분리

	Mat mask1;
	threshold(channels[0], mask1, maxHue, 255, THRESH_BINARY_INV);
	Mat mask2;
	threshold(channels[0], mask2, minHue, 255, THRESH_BINARY);
	Mat hueMask;
	if (minHue < maxHue) hueMask = mask1 & mask2;
	else hueMask = mask1 | mask2;

	threshold(channels[1], mask1, maxSat, 255, THRESH_BINARY_INV);
	threshold(channels[1], mask2, minSat, 255, THRESH_BINARY);
	Mat satMask;
	satMask = mask1 & mask2;

	mask = hueMask & satMask;
}

int main() {
	Mat image = imread("BALLOON.bmp");
	imshow("original", image);
	Mat mask;
	detectHScolor(image, 100, 130, 0, 255, mask);
	//imshow("Mask", mask);
	//waitKey(0);

	Mat detected(image.size(), CV_8UC3, Scalar(255, 255, 255));
	image.copyTo(detected, mask);
	imshow("Dectected", detected);
	waitKey(0);
	return 0;
}