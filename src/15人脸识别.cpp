#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdio>
using namespace std;
using namespace cv;
int main()
{
	// 【1】加载分类器
	CascadeClassifier cascade;
	auto i=cascade.load("haarcascade_frontalface_alt.xml");
	
	Mat srcImage, grayImage, dstImage;
	// 【2】读取图片
	srcImage = imread("新素材\\images2.png");
	dstImage = srcImage.clone();
	imshow("【原图】", srcImage);

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY); // 生成灰度图，提高检测效率

	// 定义7种颜色，用于标记人脸
	Scalar colors[] =
	{
		// 红橙黄绿青蓝紫
		CV_RGB(255, 0, 0),
		CV_RGB(255, 97, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(0, 255, 0),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 0, 255),
		CV_RGB(160, 32, 240)
	};

	// 【3】检测
	vector<Rect> rect;
	
	cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // 分类器对象调用

	printf("检测到人脸个数：%zd\n", rect.size()); // 将识别的人脸的数量显示在控制台中
	// 【4】标记--在脸部画圆
	for (int i = 0; i < rect.size(); i++)
	{
		Point  center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));
		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(dstImage, center, radius, colors[i % 7], 2);

		// 【5】显示
		imshow("【人脸识别detectMultiScale】", dstImage);
	}
	waitKey();
}
//这里遇到一个很诡异的问题，vs2022不管是使用相对路径还是那种绝对路径都无法找到xml文件，只能将它放到项目文件同级目录下，不能放到文件夹中