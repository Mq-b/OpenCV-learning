#include <iostream>​
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>//在OpenCV4后需要引入此头文件，其实还有是因为将c风格的改为枚举，看情况吧

int main(int argc, char** argv)
{
	/*cv::imread是加载一个文件成为Mat对象，可以传入2个参数，第二个参数表示图形的类型
	* <0加载原图，0把原图作为灰度图图像加载，>0把原图作为RGB图像格式加载。默认参数是1，也就是第三种
	*/
	cv::Mat scr = cv::imread("D:/素材！！！！！！！！！！！！/1 (67).jpg",1);

	/*cv::namedWindow创建OpenCV窗口, 由OpenCV自动创建与释放 第一个参数是窗口名称，第二个参数0表示窗口大小可以修改(1则不能修改)
	* 它的窗口名称如果和imshow的设置的一样就是说显示的图片的窗口可以修改大小，如果不是，那么namedWindow就会单独创建一个窗口
	*/
	cv::namedWindow("img", 0);

	//创建窗口显示图片，第一个参数是窗口名称，第二个参数是Mat对象
	cv::imshow("img", scr);

	cv::Mat output_image;
	//设置图片属性，第一个参数是传入，第二个参数是传出，第三个参数是改变什么，这里是调整饱和度
	cv::cvtColor(scr, output_image, CV_BGR2HLS);
	cv::imshow("img2", output_image);

	cv::imwrite("D:/素材！！！！！！！！！！！！/testOpenCV.png", output_image);

	//在一个给定的时间内(单位ms)等待用户按键触发; 如果用户没有按下 键, 则接续等待(循环)，如果设置为0则会无限等待
	cv::waitKey(0);
	//可以调用destroyWindow（）或destroyAllWindows（）来关闭窗口并取消分配任何相关的内存使用。对于一个简单的程序，实际上不必调用这些函数，因为退出时操作系统会自动关闭应用程序的所有资源和窗口
	cv::destroyAllWindows();
}