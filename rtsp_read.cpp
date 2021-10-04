//----------
//rtsp_read.cpp:
//----------
#include "rtsp_read.h"
#include <cmath>
#include <iostream>
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include <stdio.h>
using namespace std;

// 父类定义 WntimeCap
WntimeCap::WntimeCap()
{

}

WntimeCap::~WntimeCap()
{

}



//子类定义
class myCap : public WntimeCap {
public:
    myCap();
    ~myCap();
    void Init(char *uri);
    void getFrame(byte* bframe,unsigned long *);

    cv::Mat frame;
    cv::VideoCapture* reader;
};

myCap::myCap()
{
}

myCap::~myCap()
{
}


// 粘贴到参数区 bytes
void matToBytes(cv::Mat image,byte * arg_byte, unsigned long *lenpp)
{
    int size = image.total() * image.elemSize();
    *lenpp =  size * sizeof(byte);
    std::memcpy(arg_byte,image.data,*lenpp);
}

void show_str(char* gst,int lenth){
    for(int i=0;i<lenth;i++)
    {
        std::cout<<gst[i];
    }
    std::cout<<std::endl;
}
// 初始化
void myCap::Init(char* uri)
{
    std::cout<<"-----------init now----\n"<<std::endl;
    char* part1 = "rtspsrc location=";
    char* part2 = " latency=200 ! rtph264depay ! h264parse ! omxh264dec ! nvvidconv ! video/x-raw, width=(int)1920, height=(int)1080, format=(string)BGRx ! videoconvert ! appsink";
    char part3[strlen(part1)+strlen(part2)+strlen(uri)];
    sprintf(part3,"%s%s%s",part1,uri,part2);
    show_str(part3,strlen(part1)+strlen(part2)+strlen(uri));
    this->reader = new cv::VideoCapture(part3, cv::CAP_GSTREAMER);
    std::cout<<"-----------init success----"<<this->reader<<std::endl;
    *(this->reader) >> this->frame;
    std::cout<<"-----------init getFrame success----\n"<< this->frame.size()<<std::endl;

}
// 获取图片
void myCap::getFrame(byte* bframe,unsigned long *lenpp) {
    std::cout<<"-----------getFrame now----"<<std::endl;

    *(this->reader) >> this->frame;
    vector<uchar> buff;
    cv::imencode(".jpg",this->frame,buff);
    std::cout<<"-----------read img success----\n"<< this->frame.size()<<std::endl;
    matToBytes(cv::Mat(buff),bframe,lenpp);

}

// 封装C接口
extern "C"{
// 创建对象
myCap* MyCreate(){
    printf("------------create\n");
    return new myCap;
}


//初始化：创建链接
void init(myCap* t,char * gst){
    printf("-------------init-start\n");
    t->Init(gst);
    printf("-------------init-end\n");
}

//对象的方法:逐帧捕获
void my_get(myCap* t,byte* pp,unsigned long* lenpp){

/**************图片测试
    cv::Mat img = cv::imread("./xws.jpg");
    vector<uchar> buff;
    cv::imencode(".jpg",img,buff);
    std::cout<<"-----------read img success----\n"<< img.size()<<std::endl;
    matToBytes(cv::Mat(buff),pp,lenpp);
*/

    t->getFrame(pp,lenpp);

}

}
