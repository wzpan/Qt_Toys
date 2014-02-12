/*------------------------------------------------------------------------------------------*\
   This file contains material supporting chapter 4 of the cookbook:  
   Computer Vision Programming using the OpenCV Library. 
   by Robert Laganiere, Packt Publishing, 2011.

   This program is free software; permission is hereby granted to use, copy, modify, 
   and distribute this source code, or portions thereof, for any purpose, without fee, 
   subject to the restriction that the copyright notice may not be removed 
   or altered from any source or altered source distribution. 
   The software is released on an as-is basis and without any warranties of any kind. 
   In particular, the software is not guaranteed to be fault-tolerant or free from failure. 
   The author disclaims all warranties with regard to this software, any use, 
   and any consequent failure, is purely the responsibility of the user.
 
   Copyright (C) 2010-2011 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/


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
