#include "ErosionProcessor.h"

void ErosionProcessor :: process(cv::Mat &img, cv::Mat &out)
{
    int erosion_type = 0;	// Rect
    int erosion_size = 5;	// Size
    cv::Mat element = cv::getStructuringElement( erosion_type,
                                             cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                             cv::Point( erosion_size, erosion_size ) );
    /// Apply the erosion operation
    cv::erode( img, out, element );
}
