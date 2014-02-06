#include "SaltProcessor.h"

SaltProcessor::SaltProcessor()
{
    num = 100;
}

void SaltProcessor::process(cv::Mat &img, cv::Mat &out)
{
    out = img.clone();
    for (int k=0; k<num; k++) {
        // qrand is a Qt random number generator
        int i = rand() % out.cols;
        int j = rand() % out.rows;

        if (1 == out.channels()) {  // gray-level image
            out.at<uchar>(j,i) = 255;
        } else if (3 == out.channels()) {  // color image
            out.at<cv::Vec3b>(j,i)[0] = 255;
            out.at<cv::Vec3b>(j,i)[1] = 255;
            out.at<cv::Vec3b>(j,i)[2] = 255;
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
