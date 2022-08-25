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
	cv::Mat src, gray_src;
	src = cv::imread("新素材/1 (120).jpg");
	if (src.empty()) {
		std::cerr << "打开图片错误\n";
		return -1;
	}
	show("input", src);

	cv::cvtColor(src, gray_src, CV_BGR2GRAY);//变成灰度图像
	show("output", gray_src);

	//单通道反差
	int height = gray_src.rows;
	int width = gray_src.cols;
	for (int row = 0; row < width; row++) {
		for (int col = 0; col < row; col++) {
			int gray = gray_src.at<uchar>(row, col);
			gray_src.at<uchar>(row, col) = 255 - gray;
		}
	}
	show("gray inver",gray_src);//反差之后的图像(单通道)

	cv::Mat dst;
	dst.create(src.size(), src.type());
	height = src.rows;
	width = src.cols;
	int nc = src.channels();//获取通道数
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (nc == 1) {
				int gray = gray_src.at<uchar>(row, col);
				gray_src.at<uchar>(row, col) = 255 - gray;
			}
			else if (nc == 3) {
				int b = src.at<cv::Vec3b>(row, col)[0];
				int g = src.at<cv::Vec3b>(row, col)[1];
				int r = src.at<cv::Vec3b>(row, col)[2];
				/*dst.at<cv::Vec3b>(row, col)[0] = 255 - b;
				dst.at<cv::Vec3b>(row, col)[1] = 255 - g;
				dst.at<cv::Vec3b>(row, col)[2] = 255 - r;*/
				/*除了直接取反，其实我们还可以做很多事情，比如去掉某个GRB(RGB是红绿蓝)色*/
				dst.at<cv::Vec3b>(row, col)[0] = b;
				dst.at<cv::Vec3b>(row, col)[1] = g;
				dst.at<cv::Vec3b>(row, col)[2] = 0;
			}
		}
	}
	//cv::bitwise_not(src, dst);//除了像上面一样手写修改像素，还可以调用方法取反
	show("output", dst);//显示三通道反差图
	
	cv::waitKey(0);
}