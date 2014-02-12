#ifndef COLORDETECTCONTROLLER_H
#define COLORDETECTCONTROLLER_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string.h>

class ColorDetectController {
  private:
    // pointer to the singleton
    static ColorDetectController *singleton;
    // the algorithm class
    ColorDetector *cdetect;
    // private constructor
    ColorDetectController() {
        // setting up the application
        cdetect = new ColorDetector();
    }
    cv::Mat image;	// The image to be processed
    cv::Mat result;	// The image result
  public:
    // Deletes processor objects created by the controller.
    ~ColorDetectController() {
        delete cdetect;
    }
    // Gets access to Singleton instance
    static ColorDetectController *getInstance() {
        // Creates the instance at first call
        if (singleton == 0)
            singleton = new ColorDetectController;
        return singleton;
    }
    // Release the singleton instance of this controller.
    static void destroy() {
        if (singleton != 0) {
            delete singleton;
            singleton = 0;
        }
    }
    // Sets the color distance threshold
    void setColorDistanceThreshold(int distance) {
        cdetect->setColorDistanceThreshold(distance);
    }
    // Gets the color distance threshold
    int getColorDistanceThreshold() const {
        return cdetect->getColorDistanceThreshold();
    }
    // Sets the color to be detected
    void setTargetColor(unsigned char red,
                        unsigned char green, unsigned char blue) {
        cdetect->setTargetColor(red,green,blue);
    }
    // Gets the color to be detected
    void getTargetColor(unsigned char &red,
                        unsigned char &green, unsigned char &blue) const {
        cv::Vec3b color= cdetect->getTargetColor();
        red= color[2];
        green= color[1];
        blue= color[0];
    }
    // Sets the input image. Reads it from file.
    bool setInputImage(std::string filename) {
        image = cv::imread(filename);
        if (!image.data)
            return false;
        else
            return true;
    }
    // Returns the current input image.
    const cv::Mat getInputImage() const {
        return image;
    }
    // Performs image processing.
    void process() {
        result = cdetect->process(image);
    }
    // Returns the image result from the latest processing
    const cv::Mat getLastResult() const {
        return result;
    }
};

#endif
