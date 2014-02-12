#include "ColorDetector.h"

/** 
 * getDistance	-	 Computes the distance from target color.
 *
 * @param color		-	the color to be compared to
 * @param target	-	target color
 *
 * @return the Euclidean distance
 */
int ColorDetector::getDistance(const cv::Vec3b &color) const
{
    return abs(color[0] - target[0]) +
            abs(color[1] - target[1]) +
            abs(color[2] - target[2]);
}

/** 
 * setColorDistanceThreshold	-	Set the color distance threshold.
 *
 * Threshold must be positive.
 * otherwise distance threshold is set to 0.
 *
 * @param distance	-	threshold.
 */
void ColorDetector::setColorDistanceThreshold(int distance)
{    
    if (distance < 0)
        distance = 0;
    minDist = distance;
}

/** 
 * getColorDistanceThreshold	-	Get the color distance threshold.
 * 
 * @return the color distance
 */ 
int ColorDetector::getColorDistanceThreshold() const
{
    return minDist;
}

/** 
 * setTargetColor	-	Set the target color.
 *
 * @param red	-	value of red channel
 * @param green	-	value of green channel
 * @param blue	-	value of blue channel
 */
void ColorDetector::setTargetColor(unsigned char red,
                    unsigned char green,
                    unsigned char blue)
{
    // Temporary 1-pixel image
    cv::Mat tmp(1,1,CV_8UC3);
    tmp.at<cv::Vec3b>(0,0)[0]=blue;
    tmp.at<cv::Vec3b>(0,0)[1]=green;
    tmp.at<cv::Vec3b>(0,0)[2]=red;

    // Converting the target to Lab color space
    cv::cvtColor(tmp, tmp, CV_BGR2Lab);
    target = tmp.at<cv::Vec3b>(0,0);
}

/** 
 * getTargetColor	-	Get the target color.
 *
 * @return the target color
 */
const cv::Vec3b ColorDetector::getTargetColor()
{
    return target;    
}

/** 
 * process		-	Core process of color detect algorithm.
 *
 * @param image	-	image for detecting color
 *
 * @return		-	detect result
 */
cv::Mat ColorDetector::process(const cv::Mat &image) {
    // re-allocate binary map if neccessary
    // same size as input image, but 1-channel
    result.create(image.rows, image.cols, CV_8U);

    // re-allocate intermediate image if necessary
    converted.create(image.rows,image.cols,image.type());
    // Converting to Lab color space
    cv::cvtColor(image, converted, CV_BGR2Lab);
    
    // get the iterators
    cv::Mat_<cv::Vec3b>::const_iterator it =
            converted.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend =
            converted.end<cv::Vec3b>();
    cv::Mat_<uchar>::iterator itout =
            result.begin<uchar>();

    // for each pixel
    for ( ; it!=itend; ++it, ++itout) {
        // process each pixel
        // compute distance from target color
        if (getDistance(*it) < minDist) {
            *itout = 255;
        } else {
            *itout = 0;
        }
    } // end of pixel precessing
    return result;
}

