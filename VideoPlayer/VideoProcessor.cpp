#include "VideoProcessor.h"

VideoProcessor::VideoProcessor(QObject *parent) : QObject(parent)
{
    callIt = false;
    delay = -1;
    fnumber = 0;
    play = false;
    digits = 0;
    frameToStop = -1;
    process = 0;
    frameProcessor = 0;
    modify = false;
    length = 0;

    connect(this, SIGNAL(revert()), this, SLOT(revertVideo()));
}

void VideoProcessor::stopAtFrameNo(long frame)
{
    frameToStop = frame;
}

void VideoProcessor::callProcess()
{
    callIt = true;
}

void VideoProcessor::dontCallProcess()
{
    callIt = false;
}

void VideoProcessor::setDelay(int d)
{
    delay = d;
}

long VideoProcessor::getNumberOfProcessedFrames()
{
    return fnumber;
}

long VideoProcessor::getNumberOfPlayedFrames()
{
    return capture.get(CV_CAP_PROP_POS_FRAMES);
}

cv::Size VideoProcessor::getFrameSize()
{
    int w = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
    int h = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));

    return cv::Size(w,h);
}

long VideoProcessor::getFrameNumber()
{
    long f = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));

    return f;
}

double VideoProcessor::getPositionMS()
{
    double t = capture.get(CV_CAP_PROP_POS_MSEC);

    return t;
}

double VideoProcessor::getFrameRate()
{
    double r = capture.get(CV_CAP_PROP_FPS);

    return r;
}

long VideoProcessor::getLength()
{
    if (length <= 0)
        return caculateLength();
    else return length;
}

long VideoProcessor::caculateLength()
{
    long l;
    cv::Mat img;
    cv::VideoCapture lengthCapture;
    lengthCapture.open(tempFile);
    while(!lengthCapture.read(img)){
        ++l;
    }
    return l;
}

int VideoProcessor::getCodec(char codec[])
{
    union {
        int value;
        char code[4]; } returned;

    returned.value = static_cast<int>(capture.get(CV_CAP_PROP_FOURCC));

    codec[0] = returned.code[0];
    codec[1] = returned.code[1];
    codec[2] = returned.code[2];
    codec[3] = returned.code[3];

    return returned.value;
}

void VideoProcessor::getTempFile(std::string &str)
{
    if (!tempFileList.empty()){
        str = tempFileList.back();
        tempFileList.pop_back();
    } else {
        str = "";
    }
}


bool VideoProcessor::setInput(const std::string &fileName)
{
    fnumber = 0;

    // In case a resource was already
    // associated with the VideoCapture instance
    if (isOpened()){
        capture.release();
    }

    // Open the video file
    if(capture.open(fileName)){
        length = capture.get(CV_CAP_PROP_FRAME_COUNT);
        cv::Mat input;
        getNextFrame(input);
        emit showFrame(input);
        emit updateBtn();
        return true;
    } else {
        return false;
    }
}

bool VideoProcessor::setOutput(const std::string &filename, int codec, double framerate, bool isColor)
{
    outputFile = filename;
    extension.clear();

    if (framerate==0.0)
        framerate = getFrameRate(); // same as input

    char c[4];
    // use same codec as input
    if (codec==0) {
        codec = getCodec(c);
    }

    // Open output video
    return writer.open(outputFile, // filename
                       codec, // codec to be used
                       framerate,      // frame rate of the video
                       getFrameSize(), // frame size
                       isColor);       // color video?
}

bool VideoProcessor::setOutput(const std::string &filename, const std::string &ext, int numberOfDigits, int startIndex)
{
    // number of digits must be positive
    if (numberOfDigits<0)
        return false;

    // filenames and their common extension
    outputFile = filename;
    extension = ext;

    // number of digits in the file numbering scheme
    digits = numberOfDigits;
    // start numbering at this index
    currentIndex = startIndex;

    return true;
}

bool VideoProcessor::setTemp(int codec, double framerate, bool isColor)
{
    std::stringstream ss;
    ss << "temp_" << QDateTime::currentDateTime().toTime_t() << ".avi";
    tempFile = ss.str();

    tempFileList.push_back(tempFile);

    if (framerate==0.0)
        framerate = getFrameRate(); // same as input

    char c[4];
    // use same codec as input
    if (codec==0) {
        codec = getCodec(c);
    }

    // Open output video
    return tempWriter.open(tempFile, // filename
                       codec, // codec to be used
                       framerate,      // frame rate of the video
                       getFrameSize(), // frame size
                       isColor);       // color video?
}

void VideoProcessor::setFrameProcessor(void (*frameProcessingCallback)(cv::Mat&, cv::Mat&))
{
    // invalidate frame processor class instance
    frameProcessor = 0;
    // this is the frame processor function that will be called
    process = frameProcessingCallback;
    callProcess();
}

void VideoProcessor::setFrameProcessor(FrameProcessor *frameProcessorPtr)
{
    // invalidate callback function
    process = 0;
    // this is the frame processor instance that will be called
    frameProcessor = frameProcessorPtr;
    callProcess();
}

bool VideoProcessor::setFrameNumber(long pos)
{
    return capture.set(CV_CAP_PROP_POS_FRAMES, pos);
}

bool VideoProcessor::setPositionMS(double pos)
{
    return capture.set(CV_CAP_PROP_POS_MSEC, pos);
}

void VideoProcessor::stopIt()
{
    play = false;
    emit revert();
}

void VideoProcessor::prevFrame()
{

}

void VideoProcessor::nextFrame()
{

}

void VideoProcessor::jumpTo(long index)
{
    cv::Mat frame;
    capture.set(CV_CAP_PROP_POS_FRAMES, index);

    if (!isPlay()){
        capture.read(frame);
        emit showFrame(frame);
    }

    emit updateProgressBar();
}

bool VideoProcessor::isPlay()
{
    return play;
}

bool VideoProcessor::isModified()
{
    return modify;
}

bool VideoProcessor::isOpened()
{
    return capture.isOpened();
}

bool VideoProcessor::getNextFrame(cv::Mat &frame)
{
    return capture.read(frame);
}

void VideoProcessor::writeNextFrame(cv::Mat &frame)
{
    if (extension.length()) { // then we write images

        std::stringstream ss;
        ss << outputFile << std::setfill('0') << std::setw(digits) << currentIndex++ << extension;
        cv::imwrite(ss.str(),frame);

    } else { // then write video file

        writer.write(frame);
    }
}

void VideoProcessor::playIt()
{
    // current frame
    cv::Mat input;

    // if no capture device has been set
    if (!isOpened())
        return;

    play = true;
    emit updateBtn();

    while (isPlay()) {

        // read next frame if any
        if (!getNextFrame(input))
            break;

        // display input frame
        emit showFrame(input);

        emit updateProgressBar();

        // introduce a delay
        emit sleep(delay);

        // check if we should stop
        if (frameToStop>=0 && getFrameNumber()==frameToStop)
            stopIt();
    }
    if (isPlay())
        emit revert();
}

void VideoProcessor::pauseIt()
{
    play = false;
    emit updateBtn();
}

void VideoProcessor::runProcess()
{
    setTemp();

    // current frame
    cv::Mat input;
    // output frame
    cv::Mat output;

    // if no capture device has been set
    if (!isOpened())
        return;

    modify = true;

    while (getNextFrame(input)) {

        // process the frame
        if (process)
            process(input, output);
        else if (frameProcessor)
            frameProcessor->process(input, output);

        fnumber++;

        tempWriter.write(output);
    }

    setInput(tempFile);

    //emit revert();
}

void VideoProcessor::writeOutput()
{
    cv::Mat output;

    // if no capture device has been set
    if (!isOpened())
        return;

    while (!getNextFrame(output)) {

        // write output sequence
        if (outputFile.length()!=0)
            writeNextFrame(output);
    }

    modify = false;
}

void VideoProcessor::revertVideo()
{
    jumpTo(0);
    emit updateBtn();
}
