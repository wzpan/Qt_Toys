#include <stdio.h>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ColorDetector.h"

int main()
{
    cv::Mat img = cv::imread("./lena.png");

    if (!img.data) {
        perror("Open file failed!");
        return 1;
    }

    cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
    cv::imshow("image", img);

    ColorDetector *processor = new ColorDetector();
    processor->setTargetColor(190, 80, 80);
    cv::Mat result = processor->process(img);

    cv::namedWindow("result", CV_WINDOW_AUTOSIZE);
    cv::imshow("result", result);

    char k;

    while(1){
        k = cv::waitKey(0);
        if (k == 27)
            break;
    }
    return 0;
}
