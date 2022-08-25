#include<opencv2/opencv.hpp>
#include<iostream>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>//用以引用管理日志输出的API

int main() {
	//关闭日志输出
	//cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
	//设置只打印error级别的日志信息
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

	cv::Mat src, dst;
	src = cv::imread("新素材/1 (1).jpg");
	if (!src.data) {
		std::cerr << "图片加载错误!\n";
		return -1;
	}
	//显示原图
	cv::namedWindow("input image", cv::WINDOW_AUTOSIZE);
	cv::imshow("input image", src);
	
	//int cols = (src.cols - 1) * src.channels();
	//int offsetx = src.channels();
	//int rows = src.rows;
	////参数:size是行，type是列;返回一个和src一样大小的的矩阵
	//dst = cv::Mat::zeros(src.size(), src.type());
	//for (int row = 1; row < (rows - 1); row++) {
	//	const uchar* previous = src.ptr(row);
	//	const uchar* current = src.ptr(row);
	//	const uchar* next = src.ptr(row+1);
	//	uchar* output = dst.ptr(row);
	//	for (int col = offsetx; col < cols; col++) {
	//		output[col] = cv::saturate_cast<uchar>(5 * current[col] - (current[col - offsetx] + current[col + offsetx] + previous[col] + next[col]));
	//	}
	//}
	auto start = cv::getTickCount();
	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	//定义掩膜，stc和dst是Mat类型变量，src.depth表示位图深度，有32,24,8等
	cv::filter2D(src, dst, src.depth(), kernel);
	//getTickFrequency()返回的是CPU在一秒钟内会发出的tick的次数
	auto end = (cv::getTickCount() - start) / cv::getTickFrequency();
	printf("%.2f\n", end);

	cv::namedWindow("input image demo", cv::WINDOW_AUTOSIZE);
	cv::imshow("input image demo", dst);

	cv::waitKey(0);
}