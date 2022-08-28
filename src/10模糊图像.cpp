#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>


void show(cv::String str, const cv::Mat& src) {
	cv::namedWindow(str, 0);
	cv::imshow(str, src);
}

int main() {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
	cv::Mat src, dst,gblur,dst2;
	src = cv::imread("新素材/1 (29).jpg");
	show("input_title", src);
	//cv::Size决定模糊的方式
	cv::blur(src, dst, cv::Size(11, 11), cv::Point(-1, -1));//普通模糊
	cv::GaussianBlur(src, gblur, cv::Size(11, 11), 11, 11);//高斯模糊

	/*该函数对输入图像应用双边过滤，双边过滤器可以很好地减少不需要的噪声，同时保持边缘相当清晰
	Sigma 值：为简单起见，您可以将 2 个 sigma 值设置为相同。如果它们很小（< 10），则滤镜不会有太大的效果，而如果它们很大（> 150），它们会产生非常强烈的效果，使图像看起来“卡通”​​。
	过滤器大小：大过滤器（d > 5）非常慢，因此建议在实时应用中使用 d=5，对于需要大量噪声过滤的离线应用，建议使用 d=9
	*/
	cv::bilateralFilter(src, dst2, 9, 100, 100);

	show("output_title", dst);
	show("gaussian blur", gblur);
	show("bilateral Filter", dst2);

	cv::waitKey();
}