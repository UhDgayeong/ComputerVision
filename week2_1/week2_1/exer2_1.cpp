#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
	cv::Mat image;
	image = cv::imread("puppy.bmp");
	if (image.empty()) {
		cout << "Image unloaded" << endl;
		return 0;
	}
	cout << "Image Size = " << image.rows << " X " << image.cols << endl;
	namedWindow("Original");
	imshow("Original", image);

	Mat result;
	flip(image, result, 1);//ÁÂ¿ì°¡ µÚ¹Ù²î´Â
	imshow("Output", result);
	imwrite("output.bmp", result);
	vector<int> param_jpg = {cv::IMWRITE_JPEG_QUALITY, 20}
	imwrite("output.jpg", result, param_jpg);


	waitKey(0);

	return 0;
}