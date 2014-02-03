#ifndef EROSIONPROCESSOR_H
#define EROSIONPROCESSOR_H

#include "FrameProcessor.h"

// The canny processor class
class ErosionProcessor : public FrameProcessor
{
public:
    ErosionProcessor();
    // erosion processing method
    void process(cv::Mat &img, cv::Mat &out);
    int getSize();
    int getElem();
    void setSize(int);
    void setElem(int);
    void setParam(int, int);

private:
    int elem;
    int size;
};

#endif // EROSIONPROCESSOR_H
