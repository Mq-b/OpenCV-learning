#include <opencv2/opencv.hpp>
#include <iostream>
#include<filesystem>

int main(int argc, char** argv) {
	std::string writePath = "拍摄的照片/";
	std::filesystem::create_directory("拍摄的照片");

	cv::VideoCapture capture(0);//打开0号摄像头
	std::string name;
	cv::namedWindow("hello", cv::WINDOW_AUTOSIZE);
	int i = 0;
	while (true) {
		cv::Mat frame;
		capture >> frame;//将拍摄到的图片写入到frame
		if (32 == cv::waitKey(10)) {			//空格拍照
			name = writePath + std::to_string(i) + ".jpg";
			cv::imwrite(name, frame);
			std::cout << name << std::endl;
			i++;
		}
		if (97 == cv::waitKey(10)) {			//长按'a'退出
			break;
		}
		cv::imshow("hello", frame);//不停的实时显示摄像头拍摄的画面
	}
}