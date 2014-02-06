#ifndef MORPHOPROCESSOR_H
#define MORPHOPROCESSOR_H

#include "ImageProcessor.h"

class MorphoProcessor : public ImageProcessor
{
    friend class MorphoDialog;

public:
    MorphoProcessor();

    void process(cv::Mat &img, cv::Mat &out);

    int getType();
    void setType(int);
    int getSize();
    int getElem();
    void setSize(int);
    void setElem(int);

private:
    int type;
    int elem;
    int size;
};

#endif // MORPHOPROCESSOR_H
