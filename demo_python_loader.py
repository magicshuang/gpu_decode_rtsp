import ctypes
import cv2 as cv
import numpy as np

so = ctypes.CDLL('librtsp_gpu_decode.so')  # 动态库加载
obj = so.MyCreate()  # 创建对象

# 交互数据：
buffout = ctypes.create_string_buffer(b'',65535*100)
arg = ctypes.c_char_p(b"rtsp://.......")
bufferout_len = ctypes.c_ulong(12)
bufferout_len_p = ctypes.pointer(bufferout_len)

# 对象初始化
so.init(obj,arg)


# 循环读取图片
while True:
    so.my_get(obj,buffout,bufferout_len_p)  # 参数：对象id ,图像buffer,图像长度
    print("[python] 图像数据长度：",bufferout_len.value)
    # 图像还原
    nparr = np.frombuffer(buffout[:bufferout_len.value], dtype=np.uint8)
    segment_data = cv.imdecode(nparr, cv.IMREAD_COLOR)
    print("[python] ",segment_data.shape)

    break

