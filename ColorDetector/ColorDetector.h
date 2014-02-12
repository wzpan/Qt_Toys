#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class ColorDetector
{
  public:

    // empty constructor
    ColorDetector() : minDist(100) {
      // default parameter initialization here
      target[0] = target[1] = target[2] = 0;
    }
    // Set the color distance threshold.
    void setColorDistanceThreshold(int distance);
    // Get the color distance threshold.
    int getColorDistanceThreshold() const;
    // Set the target color.
    void setTargetColor(unsigned char red,
                        unsigned char green,
                        unsigned char blue);
    // Get the target color.
    const cv::Vec3b getTargetColor();
    // Core process of color detect algorithm.
    cv::Mat process(const cv::Mat &image);    
   
  private:
    // minimum acceptable distance
    int minDist;
    // target color
    cv::Vec3b target;
    // image containing resulting binary map
    cv::Mat result;
    // image containing color converted image
    cv::Mat converted;
    // Computes the distance from target color
    int getDistance(const cv::Vec3b &color) const;

};

#endif
