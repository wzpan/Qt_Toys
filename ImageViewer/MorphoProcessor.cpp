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
 * @param image	-	the input image
 * @param result	-	the output image
 */
void MorphoProcessor :: process(cv::Mat &image, cv::Mat &result)
{
    // allocate if neccessary
    result.create(image.size(), image.type());
    cv::Mat element = cv::getStructuringElement( 0,
                                             cv::Size( 2*size + 1, 2*size+1 ),
                                             cv::Point( size, size ) );
    // Apply the Morphology operation
    if (0 == type)
        cv::erode( image, result, element );
    else
        cv::dilate( image, result, element);
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
