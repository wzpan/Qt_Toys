#ifndef SALTPROCESSOR_H
#define SALTPROCESSOR_H

#include "ImageProcessor.h"

class SaltProcessor : public ImageProcessor
{
    friend class SaltDialog;
public:
    SaltProcessor();

    void process(cv::Mat &, cv::Mat &);

    int getNum();
    void setNum(int);

private:
    int num;
};

#endif // SALTPROCESSOR_H
