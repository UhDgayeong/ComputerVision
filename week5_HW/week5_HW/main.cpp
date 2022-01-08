#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main() {
	/*
	-(y, x) = (30, 40)에서 dy, dx, 에지 강도, 에지 방향을 구하여라
	힌트 : cartToPolar() 사용.에지강도와 그래디언트 방향은 magnitude와 angle 행렬에서 동일한 위치임.
	– sobel 에지를 구하여라.*/
	Mat image = imread("food.jpg");
	imshow("Original", image);

	Mat norm, dir;
	Mat sobelX, sobelY;
	Sobel(image, sobelX, CV_32F, 1, 0);
	Sobel(image, sobelY, CV_32F, 0, 1);
	cartToPolar(sobelX, sobelY, norm, dir);
	cout << "sobelX(2,2) = " << sobelX.at<float>(30, 40) << "  sobelY(2,2) = " << sobelY.at<float>(30, 40) << endl;
	cout << "norm(2,2) = " << norm.at<float>(30, 40) << " dir(2,2) = " << dir.at<float>(30, 40) << endl;
	waitKey();

	return 0;
}
