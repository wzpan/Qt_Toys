#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageProcessor
{
public:
    // processing method
    virtual void process(cv:: Mat &input, cv:: Mat &output)= 0;
};

#endif // IMAGEPROCESSOR_H
