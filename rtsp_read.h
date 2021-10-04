//----------
//rtsp_read.h:
//----------
#ifndef RTSPREAD_H
#define RTSPREAD_H
#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv_modules.hpp"

using namespace cv;
class WntimeCap {


public:
    WntimeCap();
    virtual ~WntimeCap();

    void Init(char* uri);
    void getFrame();
    cv::Mat frame;
    cv::VideoCapture* reader;
};

typedef unsigned char byte;

#endif
