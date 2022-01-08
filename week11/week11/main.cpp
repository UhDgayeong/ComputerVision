#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	cv::Mat image = cv::imread("binaryGroup.bmp", 0);
	imshow("BinaryImage", image);
	waitKey(0);

	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hieararchy;
	cv::findContours(image, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	cout << "�ܰ��� ���� : " << contours.size() << endl;
	for (unsigned int i = 0; i < contours.size(); i++)
		cout << i+1 << "��° �ܰ����� ���� : " << contours[i].size() << endl;

	// �ܰ��� �׷�����
	cv::Mat result(image.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(result, contours, -1, 0, 2);
	imshow("Contours", result);
	waitKey(0);

	// �ʹ� �۰ų� ū �ܰ��� ����
	int cmin = 50, cmax = 1000;
	vector<vector<cv::Point>>::iterator itc = contours.begin();
	while (itc != contours.end()) {
		if (itc->size() <= cmin || itc->size() >= cmax)
			itc = contours.erase(itc);
		else
			++itc;
	}
	cout << "���ŵǰ� ���� �ܰ��� ���� : " << contours.size() << endl;

	// �ʹ� �۰ų� ū �ܰ������� ���ŵ� ��� Ȯ��
	cv::Mat result1(image.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(result1, contours, -1, 0, 2);
	imshow("Contour_after remove", result1);
	waitKey(0);


	// ������ ��� �����
	cv::Rect r0 = cv::boundingRect(contours[0]);
	cv::rectangle(result1, r0, 0, 2);

	float radius;
	cv::Point2f center;
	cv::minEnclosingCircle(contours[1], center, radius);
	cv::circle(result1, center, static_cast<int>(radius), cv::Scalar(0), 2);

	vector<cv::Point> poly;
	cv::approxPolyDP(contours[2], poly, 5, true);
	cv::polylines(result1, poly, true, 0, 2);
	cout << "Polygon size : " << poly.size() << endl;

	vector<cv::Point> hull;
	cv::convexHull(contours[3], hull);
	cv::polylines(result1, hull, true, 0, 2);

	// �߽��� �׸���
	itc = contours.begin();
	while (itc != contours.end()) {
		cv::Moments mom = cv::moments(cv::Mat(*itc++));
		cv::circle(result1, cv::Point(mom.m10 / mom.m00, mom.m01 / mom.m00),
			2, cv::Scalar(0), 2);
		cout << "�߽��� ��ġ : ( " << mom.m10 / mom.m00 << ", " << mom.m01 / mom.m00 << " )" << endl;
	}
	imshow("Shape Descriptor", result1);
	
	for (unsigned int i = 0; i < contours.size(); i++)
		cout << i+1 << "��° �ܰ����� ���� : " << contours[i].size() << endl;
	waitKey(0);


	return 0;
}