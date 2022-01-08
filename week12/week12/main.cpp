#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	// Read input images
	cv::Mat image1 = cv::imread("a1.jpg");
	cv::Mat image2 = cv::imread("a2.jpg");
	cv::Mat image3 = cv::imread("a3.jpg");

	resize(image1, image1, cv::Size(), 1. / 4., 1. / 4.);
	resize(image2, image2, cv::Size(), 1. / 4., 1. / 4.);
	resize(image3, image3, cv::Size(), 1. / 4., 1. / 4.);

	if (!image1.data || !image2.data || !image3.data) return 0;
	cv::imshow("Image 1", image1);
	cv::imshow("Image 2", image2);
	cv::imshow("Image 3", image3);
	cv::waitKey(0);

	// Read input images
	std::vector<cv::Mat> images;
	images.push_back(image1);
	images.push_back(image2);
	images.push_back(image3);

	cout << "image size : " << images.size() << endl;
	cv::Mat panorama; // output panorama

	Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(Stitcher::PANORAMA);
	// stitch the images
	cv::Stitcher::Status status = stitcher->stitch(images, panorama);
	if (status == cv::Stitcher::OK)
	{
		cout << "success..." << endl;
		cv::imwrite("result_stitch.jpg", panorama);
		cv::imshow("Panorama", panorama);
	}
	else
		cout << "failed..." << endl;
	cv::waitKey(0);

	return 0;
}