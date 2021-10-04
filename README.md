# GPU 硬解码动态链接库
本程序使用gsteamer解码rtsp流
返回二进制片，或者自己改合适的输出
rtsp_gpu_decode.aarch64-linux-gnu.so文件可以直接使用,没法用的自己编译
参考demo程序（python）调用，也可以是其他语言

## 方法介绍
```cpp

// 创建对象
myCap* MyCreate()
//返回值 对象指针


//初始化：创建链接
void init(myCap* t,char * gst)
//参数：t：对象地址 ;gst:视频流地址


//对象的方法:逐帧捕获
void my_get(myCap* t,byte* pp,unsigned long* lenpp)
//参数：t：对象地址 ;pp: 图片指针 ；lenpp:图片长度
```
## 开始使用
##### step1 修改CMakelist.txt文件
查找opencv库，并相应的修改opencv库路径
```shell
sudo find / -name opencv2
```
粘贴到此处
```shell
set(OPENCV /usr/include/opencv4)
```
##### step2 生成so文件
```shell
mkdir build
cd build
cmake ..
make
```
此时就可以看到.so文件

##### step3 解码视频

修改demo文件：demo_python_loader.py
将自己的rtsp地址粘贴进去

```shell
python3 demo_python_loader.py
```
