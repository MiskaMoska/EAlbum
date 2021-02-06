import os
import glob
import cv2
import time
import torch
import argparse
import numpy as np
import torch.nn.functional as F
from PIL import Image

#-------------------------------------------------------------
#     十进制转二进制函数
#-------------------------------------------------------------
def dec2bin(dec_num, bit_wide=16):    
    _, bin_num_abs = bin(dec_num).split('b')    
    if len(bin_num_abs) > bit_wide:        
        raise ValueError   # 数值超出bit_wide长度所能表示的范围    
    else:        
        if dec_num >= 0:            
            bin_num = bin_num_abs.rjust(bit_wide, '0')        
        else:            
            _, bin_num = bin(2**bit_wide + dec_num).split('b')    
    return bin_num 


folder = r"F:\ClassImage\jpg\classintro" #jpg文件夹
out_root_path = "F:/ClassImage/RGB565_txt/classintro" #输出txt根目录
target_width = 320
target_length = 240

os.chdir(folder)
filename = os.listdir('.')
filename.sort(key=lambda x:int(x[:2])) #! 按照文件名的前两位（必须是数字）排序
filename = glob.glob(str(filename)+'*.jpg') #获得文件名列表

# 获取根目录下所有jpg并导出320*240图片颜色信息
for i, file in enumerate(filename,1): #遍历所有（i，文件名） 
    h_file_path = os.path.join(out_root_path, str(i)+'.txt')
    
    target_shape = (target_width, target_length) #图片分辨率
    img = cv2.imread(file)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

    img_target_565 = np.random.random((target_length,target_width))
    image = cv2.resize(img, target_shape)
    img_target = image / 256
    for i in range(0,target_length):
        for j in range(0,target_width):
            for k in range(0,3):
                if k == 0: #Red
                    r = int(img_target[i,j,k] * 32)
                if k == 1: #Green
                    g = int(img_target[i,j,k] * 64)
                if k == 2: #Blue
                    b = int(img_target[i,j,k] * 32)

            img_target_565[i,j] = b + g * 32 + r * 2048

    img_target_565 = img_target_565.flatten()

    h_file = open(h_file_path,"w")
    for i in range(0,target_width*target_length):
        low_16bit = dec2bin(int(img_target_565[i]),bit_wide=17)
        low_16bit = str(low_16bit)
        hex_low_16bit = ""
        for j in range(0,4):
            temp = low_16bit[4*j+1:4*j+5]
            if temp=="0000" : hex_low_16bit = hex_low_16bit + "0"
            elif temp=="0001" : hex_low_16bit = hex_low_16bit + "1"
            elif temp=="0010" : hex_low_16bit = hex_low_16bit + "2"
            elif temp=="0011" : hex_low_16bit = hex_low_16bit + "3"
            elif temp=="0100" : hex_low_16bit = hex_low_16bit + "4"
            elif temp=="0101" : hex_low_16bit = hex_low_16bit + "5"
            elif temp=="0110" : hex_low_16bit = hex_low_16bit + "6"
            elif temp=="0111" : hex_low_16bit = hex_low_16bit + "7"
            elif temp=="1000" : hex_low_16bit = hex_low_16bit + "8"
            elif temp=="1001" : hex_low_16bit = hex_low_16bit + "9"
            elif temp=="1010" : hex_low_16bit = hex_low_16bit + "A"
            elif temp=="1011" : hex_low_16bit = hex_low_16bit + "B"
            elif temp=="1100" : hex_low_16bit = hex_low_16bit + "C"
            elif temp=="1101" : hex_low_16bit = hex_low_16bit + "D"
            elif temp=="1110" : hex_low_16bit = hex_low_16bit + "E"
            elif temp=="1111" : hex_low_16bit = hex_low_16bit + "F"
        h_file.write("{0}".format(hex_low_16bit))
        h_file.flush()
    print(file,"transferred completed")
