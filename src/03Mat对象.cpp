#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>//用以引用管理日志输出的API
#include<format>

void show(const char*str,const cv::Mat& src) {
	cv::namedWindow(str, 1);
	cv::imshow(str, src);
}

int main() {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
	cv::Mat src, dst;
	src = cv::imread("新素材/1 (12).jpg");
	if (src.empty()) {
		std::cerr << "打开图片错误\n";
		return -1;
	}
	show("input", src);

	//调用copyTo方法将src拷贝给dst，拷贝构造函数只会复制头和指针部分，所以如果想要完全复制就调用copyTo或clone方法
	//src.copyTo(dst);
	//show("output", dst);

	cv::cvtColor(src, dst, CV_BGR2GRAY);//将dst设置为src图片的灰色的样子
	show("output", dst);
	//打印2个Mat对象分别有几个通道
	std::cout << std::format("input 通道: {}\noutput 通道: {}\n", src.channels(), dst.channels());
	//通过指针访问像素打印第一个像素的值
	auto fistRow = dst.ptr(0);
	std::cout << std::format("fist pixel value:{}\n", *fistRow);
	//打印Max对象的行和列数
	auto cols = dst.cols;
	auto rows = dst.rows;
	std::cout << std::format("row:{} cols:{}\n", rows, cols);
	/*调用Mat的构造函数，一个3 * 3的像素集合, CV_8UC3中的8表示每个通道占8位，U表示无符号，C表示char类型，3表示通道数目是3
	最后一个参数是表示初始化每个像素的值是多少，向量长度对应通道数目一致*/
	cv::Mat M(3, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	//cv::Mat M(100, 100, CV_8UC1, cv::Scalar(127));//灰度，只有一个颜色
	std::cout << "M = \n" << M << std::endl;

	show("M", M);

	cv::Mat m1;
	m1.create(src.size(), src.type());
	m1 = cv::Scalar(0, 0, 25);
	show("m1", m1);

	cv::Mat csrc;
	cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(src, csrc, -1, kernel);//增加对比度
	show("output", csrc);

	cv::Mat m2 = cv::Mat::zeros(2, 2, CV_8UC1);//初始化一个全0的Mat对象
	std::cout << "m2 = \n" << m2 << std::endl;

	cv::waitKey(0);
}