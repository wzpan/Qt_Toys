#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <QObject>
#include <QDateTime>
#include <vector>
#include "FrameProcessor.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dbg.h>

class VideoProcessor : public QObject {

    Q_OBJECT

public:

    explicit VideoProcessor(QObject *parent = 0);

    // Is the player stopped?
    bool isPlay();

    // Is the video modified?
    bool isModified();

    // Is the player opened?
    bool isOpened();

    // stop streaming at this frame number
    void stopAtFrameNo(long frame);

    // process callback to be called
    void callProcess();

    // do not call process callback
    void dontCallProcess();

    // set a delay between each frame
    // 0 means wait at each frame
    // negative means no delay
    void setDelay(int d);

    // a count is kept of the processed frames
    long getNumberOfProcessedFrames();

    // get the current playing progress
    long getNumberOfPlayedFrames();

    // return the size of the video frame
    cv::Size getFrameSize();

    // return the frame number of the next frame
    long getFrameNumber();

    // return the position in ms
    double getPositionMS();

    // return the frame rate
    double getFrameRate();

    // return the number of frames in video
    long getLength();

    // recaculate the number of frames in video
    // normally doesn't need it unless getLength()
    // can't return a valid value
    long caculateLength();

    // get the codec of input video
    int getCodec(char codec[4]);

    // get temp file lists
    void getTempFile(std::string &);

    // go to this position
    bool setPositionMS(double pos);

    // go to this position expressed in fraction of total film length
    bool setRelativePosition(double pos);

    // set the name of the video file
    bool setInput(const std::string &fileName);

    // set the output video file
    // by default the same parameters than input video will be used
    bool setOutput(const std::string &filename, int codec=0, double framerate=0.0, bool isColor=true);

    // set the output as a series of image files
    // extension must be ".jpg", ".bmp" ...
    bool setOutput(const std::string &filename, // filename prefix
                   const std::string &ext, // image file extension
                   int numberOfDigits=3,   // number of digits
                   int startIndex=0);       // start index

    // set the callback function that will be called for each frame
    void setFrameProcessor(void (*frameProcessingCallback)(cv::Mat&, cv::Mat&));

    // set the instance of the class that implements the FrameProcessor interface
    void setFrameProcessor(FrameProcessor* frameProcessorPtr);

    // go to this frame number
    bool setFrameNumber(long pos);

    // play the frames of the sequence
    void playIt();

    // pause the frames of the sequence
    void pauseIt();

    // Stop the processing
    void stopIt();

    // display the prev frame of the sequence
    void prevFrame();

    // display the next frame of the sequence
    void nextFrame();

    // Jump to a position
    void jumpTo(long index);

    // process the frames of the sequence
    void runProcess();

    // write the output
    void writeOutput();

private slots:
    void revertVideo();

signals:
    void showFrame(cv::Mat frame);
    void revert();
    void sleep(int msecs);
    void updateBtn();
    void updateProgressBar();
    void reload(const std::string &);

private:    

    // the OpenCV video capture object
    cv::VideoCapture capture;

    // the callback function to be called
    // for the processing of each frame
    void (*process)(cv::Mat&, cv::Mat&);
    // the pointer to the class implementing
    // the FrameProcessor interface
    FrameProcessor *frameProcessor;
    // a bool to determine if the
    // process callback will be called
    bool callIt;
    // delay between each frame processing
    int delay;
    // number of processed frames
    long fnumber;
    // total number of frames
    long length;
    // stop at this frame number
    long frameToStop;
    // to stop the player
    bool play;
    // is the video modified
    bool modify;

    // the OpenCV video writer object
    cv::VideoWriter writer;
    cv::VideoWriter tempWriter;

    // output filename
    std::string outputFile;
    // temp filename
    std::string tempFile;
    // all temp files queue
    std::vector<std::string> tempFileList;

    // current index for output images
    int currentIndex;
    // number of digits in output image filename
    int digits;
    // extension of output images
    std::string extension;

    // get the next frame if any
    bool getNextFrame(cv::Mat& frame);

    // to write the output frame
    void writeNextFrame(cv::Mat& frame);

    // set the temp video file
    // by default the same parameters than input video will be used
    bool setTemp(int codec=0, double framerate=0.0, bool isColor=true);

};

#endif // VIDEOPROCESSOR_H
