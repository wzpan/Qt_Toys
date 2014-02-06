#include "DilationProcessor.h"

DilationProcessor::DilationProcessor()
{
    elem = 0;
    size = 3;
}

/**
 * process	-	Dilation processing method
 *
 * @param img	-	the input image
 * @param out	-	the output image
 */
void DilationProcessor :: process(cv::Mat &img, cv::Mat &out)
{
    cv::Mat element = cv::getStructuringElement( 0,
                                             cv::Size( 2*size + 1, 2*size+1 ),
                                             cv::Point( size, size ) );
    /// Apply the Dilation operation
    cv::dilate( img, out, element );
}

int DilationProcessor::getSize()
{
    return size;
}

int DilationProcessor::getElem()
{
    return elem;
}

void DilationProcessor::setSize(int s)
{
    size = s;
}

void DilationProcessor::setElem(int e)
{
    elem = e;
}

void DilationProcessor::setParam(int s, int e)
{
    setSize(s);
    setElem(e);
}
