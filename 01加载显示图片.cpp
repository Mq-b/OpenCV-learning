#include <iostream>​
#include <opencv2/opencv.hpp>

int main(int argc, char** argv)
{
	cv::Mat scr = cv::imread("D:/素材！！！！！！！！！！！！/1 (67).jpg");
	cv::namedWindow("img", 0);
	cv::imshow("img", scr);
	cv::waitKey(0);
	cv::destroyAllWindows();
}