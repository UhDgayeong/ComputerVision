#include <iostream>
#include <opencv2/opencv.hpp>
//#include<opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;


int main() {
	cv::Mat image = cv::imread("church01.jpg"); //원본 이미지(칼라)
	cv::Mat image1 = cv::imread("church01.jpg", 0); //1.영상입력
	cv::imshow("Church01 in grayLevel", image1);
	//waitKey(0);

	std::vector<cv::KeyPoint> keypoints1;  // 2. keypoints
	//cv::Ptr<cv::Feature2D> ptrFeature2D = cv::xfeatures2d::SURF::create(2500);
	cv::Ptr<cv::Feature2D> ptrFeature2D = cv::SIFT::create(500);

	ptrFeature2D->detect(image1, keypoints1);
	cout << "Number of keyPoints(SIFT) 1: " << keypoints1.size() << endl;
	
	float maxSize = keypoints1[0].size;
	int n = 0;
	for (int i = 0; i < keypoints1.size(); i++) {
		if (keypoints1[i].size > maxSize) {
			maxSize = keypoints1[i].size;
			n = i;
		}
	}
	printf("keypoint size값들 중 가장 큰 값 : %f\n", maxSize);

	cv::circle(image1, keypoints1[n].pt, 10, cv::Scalar(255, 255, 255), 2);
	cv::circle(image, keypoints1[n].pt, 10, cv::Scalar(255, 255, 255), 2);
	//cv::imshow("Show circle", image1);
	cv::imshow("Show circle in image", image);

	cv::Mat featureImage1;
	cv::drawKeypoints(image1, keypoints1, featureImage1, cv::Scalar(255, 255, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	cv::imshow("SIFT1", featureImage1);
	//waitKey(0);

	//Extract the descriptor
	cv::Mat descriptors1;
	ptrFeature2D->compute(image1, keypoints1, descriptors1);
	cout << descriptors1.rows << "x" << descriptors1.cols << endl;
	cout << descriptors1.row(0) << endl;


	waitKey(0);
	return 0;
}