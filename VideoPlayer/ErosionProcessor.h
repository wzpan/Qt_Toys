#ifndef EROSIONPROCESSOR_H
#define EROSIONPROCESSOR_H

#include "FrameProcessor.h"

// The canny processor class
class ErosionProcessor : public FrameProcessor
{
public:
    void process(cv::Mat &img, cv::Mat &out);
};

#endif // EROSIONPROCESSOR_H
