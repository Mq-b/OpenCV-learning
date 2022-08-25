#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>
#include<vector>
#include<string>
#include<filesystem>

void show(const char* str, const cv::Mat& src) {
	cv::namedWindow(str, 1);
	cv::imshow(str, src);
}

int main() {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
	std::vector<std::string>imagePath;
	std::vector<std::string>imageName;
	std::vector<cv::Mat>Mats;
	cv::Mat src, dst;
	std::filesystem::path p = "D:/自用/vs的c++/OpenCVTest1/新素材/";
	for (auto e : std::filesystem::directory_iterator{ p }) {//如果p是目录，那么std::filesystem::directory_iterator方法就会获取当前目录下所有的文件path
		imagePath.push_back(std::filesystem::path{ e }.string());//e实际上是std::wstring的对象，我们使用path进行临时构造然后转换为string
		std::cout << e << '\n';
	}
	//将目录字符串切割只剩下图片名称
	for (const auto& i : imagePath) {
		imageName.push_back(i.substr(41));
	}
	for (auto i : imagePath) {
		src = cv::imread(i);
		cv::cvtColor(src, dst, CV_BGR2GRAY);
		show("test", dst);
		cv::waitKey(1);
		Mats.push_back(dst.clone());
	}

	std::filesystem::create_directory("灰度图像");
	for (int i = 0; i < Mats.size(); i++) {
		cv::imwrite("灰度图像/" + imageName[i], Mats[i]);
	}
}