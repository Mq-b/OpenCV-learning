#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>

cv::Mat bgImage;
const char* drawdemo = "draw shapes and text demo";
void show(cv::String str, const cv::Mat& src) {
	cv::namedWindow(str, 0);
	cv::imshow(str, src);
}

void MyLine() {
	cv::Point p1(20, 30);
	cv::Point p2;
	p2.x = 600;
	p2.y = 600;
	cv::Scalar color = cv::Scalar(0, 0, 255);
	//给bgImage画一根线，第五个参数是线条粗细,第六个参数决定了线条的连接，越大越好看
	cv::line(bgImage, p1, p2, color, 2, cv::LINE_AA);
}

void MyRectangle() {
	cv::Rect rect{ 200,100,300,300 };
	cv::Scalar color(255, 0, 0);
	//它的参数类似于上面的line类似，只是这里使用LINE_AA抗锯齿
	cv::rectangle(bgImage, rect, color, 2, cv::LINE_AA);
}

void MyEllipse() {
	//cv::Point设置圆的圆心位置，这里设置的是整个图片的中心，cv::Size设置的是圆的大小，90设置的是圆倾斜的角度，0和360设置的是这个圆是0-360，我们还可以写成0-180，cv::Scalar设置颜色，2设置的是线条粗细
	cv::ellipse(bgImage, cv::Point(bgImage.cols / 2, bgImage.rows / 2), cv::Size(300, 500), 90, 0, 360, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
}

void MyCircle() {
	cv::Scalar color(0, 255, 255);
	cv::Point center(bgImage.cols / 2, bgImage.rows / 2);
	cv::circle(bgImage, center, 150, color, 2, cv::LINE_8);
}

void MyPolygon() {
	cv::Point pts[1][5];
	pts[0][0] = cv::Point(100, 100);
	pts[0][1] = cv::Point(100, 200);
	pts[0][2] = cv::Point(200, 200);
	pts[0][3] = cv::Point(200, 100);
	pts[0][4] = cv::Point(100, 100);

	const cv::Point* ppts[]{ pts[0] };
	int npt[]{ 5 };
	cv::Scalar color(255, 12, 255);
	cv::fillPoly(bgImage, ppts, npt, 1, color, 8);
}

void RandomLineDemo() {
	cv::RNG rng(NULL);//OpenCV的随机数类
	cv::Point pt1;
	cv::Point pt2;
	cv::Mat bg = cv::Mat::zeros(bgImage.size(), bgImage.type());
	for (size_t i = 0; i < 1000; i++)
	{
		pt1.x = rng.uniform(0, bgImage.cols);
		pt2.x = rng.uniform(0, bgImage.cols);
		pt1.y = rng.uniform(0, bgImage.rows);
		pt2.y = rng.uniform(0, bgImage.rows);
		cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

		if (cv::waitKey(50) > 0)//为了随时停止
			break;

		cv::line(bg, pt1, pt2, color, 1, 8);//不停的随机画线
		show("random line demo", bg);
	}
}

int main() {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

	bgImage = cv::imread("新素材/1 (23).jpg");
	//MyLine();//画线
	//MyRectangle();//画矩形
	//MyEllipse();//画椭圆
	//MyCircle();//画圆
	//MyPolygon();//画填充

	/*cv::putTest参数 ： 
	Img ：要绘制的图像
	文本：要写在图像上的字符串
	来源：文本框的左上角
	fontFace : 字体（例如 cv::FONT_HERSHEY_PLAIN）
	fontScale : 大小（乘数，而不是“点”！）
	颜色：RGB 形式（标量）
	粗细：线的粗细
	lintType ：连通性，4 或 8*/
	//cv::putText(bgImage, "Hello OpenCV", cv::Point(300, 300), cv::FONT_HERSHEY_COMPLEX,2.0,cv::Scalar(12,255,200),2,8);//画文字

	RandomLineDemo();
	
	show(drawdemo, bgImage);
	
	cv::waitKey();
}