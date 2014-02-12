#include "SaltProcessor.h"

SaltProcessor::SaltProcessor()
{
    num = 100;
}

void SaltProcessor::process(cv::Mat &image, cv::Mat &result)
{
    result = image.clone();
    for (int k=0; k<num; k++) {
        // qrand is a Qt random number generator
        int i = rand() % result.cols;
        int j = rand() % result.rows;

        if (1 == result.channels()) {  // gray-level image
            result.at<uchar>(j,i) = 255;
        } else if (3 == result.channels()) {  // color image
            result.at<cv::Vec3b>(j,i)[0] = 255;
            result.at<cv::Vec3b>(j,i)[1] = 255;
            result.at<cv::Vec3b>(j,i)[2] = 255;
        }
    }
}

int SaltProcessor::getNum()
{
    return num;
}

void SaltProcessor::setNum(int n)
{
    num = n;
}
