#include<opencv2/opencv.hpp>
#include<iostream>
#include <opencv2/imgproc/types_c.h>

int main() {
	cv::Mat src, dst;
	src = cv::imread("新素材/1 (1).jpg");
	if (!src.data) {
		std::cerr << "图片加载错误!\n";
		return -1;
	}
	cv::namedWindow("input image", cv::WINDOW_AUTOSIZE);
	cv::imshow("input image", src);
	
	

	cv::waitKey(0);
}