#include "MorphoProcessor.h"

MorphoProcessor::MorphoProcessor()
{
    type = 0;
    elem = 0;
    size = 3;
}

/**
 * process	-	Morphology processing method
 *
 * @param img	-	the input image
 * @param out	-	the output image
 */
void MorphoProcessor :: process(cv::Mat &img, cv::Mat &out)
{
    cv::Mat element = cv::getStructuringElement( 0,
                                             cv::Size( 2*size + 1, 2*size+1 ),
                                             cv::Point( size, size ) );
    // Apply the Morphology operation
    if (0 == type)
        cv::erode( img, out, element );
    else
        cv::dilate( img, out, element);
}

int MorphoProcessor::getType()
{
    return type;
}

void MorphoProcessor::setType(int t)
{
    type = t;
}

int MorphoProcessor::getSize()
{
    return size;
}

int MorphoProcessor::getElem()
{
    return elem;
}

void MorphoProcessor::setSize(int s)
{
    size = s;
}

void MorphoProcessor::setElem(int e)
{
    elem = e;
}
