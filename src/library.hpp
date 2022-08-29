#include<opencv2/opencv.hpp>

void faceRecognition(cv::Mat& srcImage) {//图片人脸识别
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
}