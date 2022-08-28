#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>


void show(cv::String str, const cv::Mat& src) {
	cv::namedWindow(str, cv::WINDOW_AUTOSIZE);
	cv::imshow(str, src);
}

int main() {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
	cv::Mat src, dst,gblur;
	src = cv::imread("新素材/1 (29).jpg");
	show("input_title", src);

	cv::blur(src, dst, cv::Size(11, 11), cv::Point(-1, -1));//cv::Size决定模糊的方式
	cv::GaussianBlur(src, gblur, cv::Size(11, 11), 11, 11);//高斯模糊

	show("output_title", dst);
	show("gaussian blur", gblur);

	cv::waitKey();
}