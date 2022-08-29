#include <iostream>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/utils/logger.hpp>

int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    //打开视频文件
    cv::VideoCapture capture("./video/蕾姆海边.mp4");

    //isOpen判断视频是否打开成功
    if (!capture.isOpened()) {
        std::cerr << "Movie open Error\n";
        return -1;
    }
    //获取视频帧频
    double rate = capture.get(cv::CAP_PROP_FPS);
    std::cout << "帧率为:" << " " << rate << std::endl;
    std::cout << "总帧数为:" << " " << capture.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;//输出帧总数
    cv::Mat frame;
    cv::namedWindow("Movie Player");

    //设置从第多少帧开始播放
    capture.set(cv::CAP_PROP_POS_FRAMES, 0.0);
    while (true) {
        //读取视频帧
        if (!capture.read(frame))
            break;
        //显示读取到的视频帧同时设置一帧显示多少毫秒
        cv::imshow("Movie Player", frame);
        cv::waitKey(16.6);
    }
    capture.release();
    //对于视频需要手动关闭
    cv::destroyWindow("Movie Player");
}