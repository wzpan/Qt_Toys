#ifndef DILATIONPROCESSOR_H
#define DILATIONPROCESSOR_H

#include "FrameProcessor.h"

class DilationProcessor : public FrameProcessor
{
    friend class DilationDialog;

public:
    DilationProcessor();

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

#endif // DILATIONPROCESSOR_H
