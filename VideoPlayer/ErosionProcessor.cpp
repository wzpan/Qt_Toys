#include "ErosionProcessor.h"

ErosionProcessor::ErosionProcessor()
{
    size = 0;
    elem = 0;
}

/** 
 * process	-	erosion processing method
 *
 * @param img	-	the input image
 * @param out	-	the output image
 */
void ErosionProcessor :: process(cv::Mat &img, cv::Mat &out)
{
    cv::Mat element = cv::getStructuringElement( 0,
                                             cv::Size( 2*size + 1, 2*size+1 ),
                                             cv::Point( size, size ) );
    /// Apply the erosion operation
    cv::erode( img, out, element );
}

int ErosionProcessor::getSize()
{
    return size;
}

int ErosionProcessor::getElem()
{
    return elem;
}

void ErosionProcessor::setSize(int s)
{
    size = s;
}

void ErosionProcessor::setElem(int e)
{
    elem = e;
}

void ErosionProcessor::setParam(int s, int e)
{
    setSize(s);
    setElem(e);
}

