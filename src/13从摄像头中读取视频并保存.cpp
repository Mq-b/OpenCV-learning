#include <opencv2/opencv.hpp>
#include <iostream>
#include<filesystem>

int main() {

    //视频保存位置(不支持avi格式)
    std::string outputVideoPath = "video/test.mp4";

    //打开摄像头
    cv::VideoCapture capture0(0);

    cv::VideoWriter outputVideo;
    //获取当前摄像头的视频信息
    cv::Size S = cv::Size((int)capture0.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)capture0.get(cv::CAP_PROP_FRAME_HEIGHT));
    //打开视频路劲，设置基本信息 open函数中你参数跟上面给出的VideoWriter函数是一样的
    outputVideo.open(outputVideoPath, -1, 60.0, S, true);

    if (!outputVideo.isOpened()) {
        std::cout << "fail to open!" << std::endl;
        return -1;
    }

    cv::Mat frameImage;
    int count = 0;

    while (true) {
        //读取当前帧
        capture0 >> frameImage;

        if (frameImage.empty()) break;

        ++count;
        //输出当前帧
        cv::imshow("output", frameImage);
        //保存当前帧，不停的写入到(test.mp4)文件
        outputVideo << frameImage;

        if (char(cv::waitKey(1)) == 'q') break;
    }

    std::cout << "TotalFrame: " << count << std::endl;
}