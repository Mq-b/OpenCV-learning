#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>
#include<format>
#include<vector>

void show(cv::String str, const cv::Mat& src) {
	cv::namedWindow(str, cv::WINDOW_AUTOSIZE);
	cv::imshow(str, src);
}

int main() {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
	cv::Mat src, src2,dst;
	src = cv::imread("新素材/1 (20).jpg");
	src2 = cv::imread("新素材/1 (21).jpg");
	if (src.empty() || src2.empty()) {
		std::cerr << "打开图片错误\n";
		return -1;
	}
	/*src- 第一个输入数组。
	src2- 第二个输入数组
	0.5- 第二 四个数组元素的权重
	gamma- 标量添加到每个总和。
	第二和第四个参数是他们图片占的权重，也就是越大那就越不透明，反之亦然*/
	cv::addWeighted(src, 0.5, src2, 0.5, 0.0, dst);
	//图像相乘
	//cv::multiply(src, src, dst, 1.0);
	show("src", src);
	show("src2", src2);
	show("src与src2两个图像相加后dst", dst);
	cv::waitKey(0);
}