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
	cv::Mat src, dst;
	src = cv::imread("新素材/1 (17).jpg");

	cv::cvtColor(src, src, CV_BGR2GRAY);//可以看需求先将src转换为灰度图像

	char input_win[] = "input image";
	show(input_win, src);

	int height = src.rows;
	int width = src.cols;
	dst = cv::Mat::zeros(src.size(), src.type());
	float alpha = 1.2;//对比度
	float beta = +50;//亮度
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (src.channels() == 3) {
				float b = src.at<cv::Vec3b>(row, col)[0];
				float g = src.at<cv::Vec3b>(row, col)[1];
				float r = src.at<cv::Vec3b>(row, col)[2];

				dst.at<cv::Vec3b>(row, col)[0] = cv::saturate_cast<uchar>(b * alpha + beta);
				dst.at<cv::Vec3b>(row, col)[1] = cv::saturate_cast<uchar>(g * alpha + beta);
				dst.at<cv::Vec3b>(row, col)[2] = cv::saturate_cast<uchar>(r * alpha + beta);
			}
			else if (src.channels() == 1) {
				float v = src.at<uchar>(row, col);
				dst.at<uchar>(row, col) = cv::saturate_cast<uchar>(v * alpha + beta);
			}
		}
	}
	//我们上面用的都是cv::Vec3b，Mat它默认是这个类型，我们还能使用一些方法进行转换如下:
	cv::Mat m1;
	src.convertTo(m1, CV_32F);//m1就可以使用at<cv::Vec3f>了，我们这里不再示范

	char output_title[] = "contrast and brightness change demo";
	show(output_title, dst);

	cv::waitKey();
}