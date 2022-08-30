#include <opencv2/opencv.hpp>
#include <iostream>
#include<filesystem>
#include<thread>

bool faceRecognition(cv::Mat& srcImage) {//单独封装一个精简的函数(使用的15)
    // 加载分类器
    cv::CascadeClassifier cascade;
    auto i = cascade.load("haarcascade_frontalface_alt.xml");

    cv::Mat grayImage, dstImage;

    dstImage = srcImage.clone();
    //imshow("【原图】", srcImage);

    cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY); // 生成灰度图，提高检测效率

    std::vector<cv::Rect> rect;

    cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // 分类器对象调用
    for (int i = 0; i < rect.size(); i++)
    {
        cv::Point  center;
        center.x = cvRound((rect[i].x + rect[i].width * 0.5));
        center.y = cvRound((rect[i].y + rect[i].height * 0.5));
        rectangle(dstImage, cv::Rect(center.x - rect[i].width * 0.5, center.y - rect[i].height * 0.5, rect[i].width, rect[i].height), cv::Scalar(30, 144, 255), 2);//(方框)
    }
    srcImage = dstImage;
    return rect.size() != 0;
}

int main() {
    std::vector<cv::Mat>mat;
    //视频保存位置(不支持avi格式)
    std::string outputVideoPath = "video/人脸识别.mp4";
    //打开摄像头
    cv::VideoCapture capture0(0);

    cv::VideoWriter outputVideo;
    //获取当前摄像头的视频信息
    cv::Size S = cv::Size((int)capture0.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)capture0.get(cv::CAP_PROP_FRAME_HEIGHT));
    //打开视频路劲，设置基本信息 open函数中你参数跟上面给出的VideoWriter函数是一样的
    outputVideo.open(outputVideoPath, -1, 24, S, true);

    cv::Mat frameImage;
    int  n = 1;
    while (true) {
        //读取当前帧
        capture0 >> frameImage;
       /* if (frameImage.empty()) break;*/
        //输出当前帧
        faceRecognition(frameImage);
        cv::imshow("output", frameImage);
        //保存当前帧，不停的写入到(test.mp4)文件
        outputVideo << frameImage;
        if (char(cv::waitKey(1)) == 'q') break;
    }
}