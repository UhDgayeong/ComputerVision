#pragma once
#include <opencv2/opencv.hpp>

class WatershedSegmenter {
private:
	cv::Mat markers;
public:
	void  setMarkers(const cv::Mat& markerImage) {
		markerImage.convertTo(markers, CV_32S);
	}
	//convertTo(OutputArray m, int rtype, double alpha=1, double beta=0 ) const
	//m(x,y) = saturate_cast<rType>( alpha x (*this)(x,y) + beta )
	cv::Mat  process(const cv::Mat& image) {
		cv::watershed(image, markers);
		return markers;    //-1, 128, 250 
	}
	cv::Mat  getSegmentation() {
		cv::Mat  tmp;
		markers.convertTo(tmp, CV_8U);    return  tmp;
	}
	cv::Mat  getWatersheds() {
		cv::Mat tmp;
		markers.convertTo(tmp, CV_8U, 255, 255);    return  tmp;
	}
};

int main() {

	cv::Mat  image = cv::imread("hand_sample2.jpg");
	cv::imshow("Original Image", image);

	cv::Mat  image1 = cv::imread("hand_sample2.jpg", 0);
	cv::imshow("Original Image in gray level", image1);

	cv::Mat  binary;
	cv::adaptiveThreshold(image1, binary, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 31, 10);
	cv::imshow("Binary Image", binary);
	//cv::waitKey(0);

	cv::Mat  fg;
	cv::erode(binary, fg, cv::Mat(), cv::Point(-1, -1), 2);
	cv::imshow("Foreground", fg);
	//cv::waitKey(0);

	cv::Mat  bg;
	cv::dilate(binary, bg, cv::Mat(), cv::Point(-1, -1), 6);
	cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);//πË∞Ê¿ª 128, ∞¥√º 0
	cv::imshow("Background", bg);
	//cv::waitKey(0);

	cv::Mat  markers(binary.size(), CV_8U, cv::Scalar(0));
	markers = fg + bg;
	cv::imshow("Marker", markers);
	//cv::waitKey(0);

	WatershedSegmenter  segmenter;
	segmenter.setMarkers(markers);
	segmenter.process(image);
	cv::imshow("Segmentation", segmenter.getSegmentation());
	//cv::waitKey(0);

	cv::imshow("Watershed", segmenter.getWatersheds());
	cv::waitKey(0);

	return 0;
}
