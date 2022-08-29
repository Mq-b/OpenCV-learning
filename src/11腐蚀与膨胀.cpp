#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>

cv::Mat src, dst;
int element_size = 1;
int max_size = 10;

void show(cv::String str, const cv::Mat& src) {
	cv::namedWindow(str, 0);
	cv::imshow(str, src);
}

void CallBack_Demo(int , void* ) {
	int s = max_size * 2 + 1;
	cv::Mat structElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(s,s),cv::Point(-1,-1));
	cv::dilate(src, dst, structElement, cv::Point(-1, -1), 1);
	//cv::erode(src, dst, structElement);

	cv::imshow("output image", dst);
}

int main() {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

	src = cv::imread("新素材/1 (32).jpg");
	show("input image", src);

	cv::namedWindow("output image",0);
	cv::createTrackbar("Element Size :", "output image", &element_size, max_size, CallBack_Demo);
	CallBack_Demo(0, 0);

	cv::waitKey();
}