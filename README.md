# 1  Introduction
The software code of a little electronic album(EAlbum),which is designed based on STM32F103C8T6 MCU. Some pictures are provided to show the outlook of EAlbum.

**Click [here](https://pan.baidu.com/s/1BRxl9arHRHqPtyCifSQCGA) to get more information about EAlbum,extraction code `8nyz`** 

**Click [here](https://www.bilibili.com/video/BV1of4y1e7pQ)to see a brief video of EAlbum** 

# 2 Functions
- **Show Stuffs：** EAlbum is equipped with a TFT LCD,so it is able to show not only photos but anything(text,logos,pictures,videos,etc.) you like as long as you program it to do so. 
- **Touchable：** The TFT LCD is manufactured touch-sensitive,and the PCB of EAlbum is equipped with a touch controller chip,so users are permitted to control EAlbum by touching the screen.
- **Rechargeable：** EAlbum is equipped with a lithium battery, users can charge it through a micro-USB port,which makes EAlbum more mobile and convenient.

# 3 Solution
This chapter states the design and control method of EAlbum,I recommend you to read it carefully if you're going to **reproduce** my project,even more,**modify** it.

 EAlbum is equipped with a SD card slot,and you may think naturally that it works by reading the pictures in SD card which user has coppied into it on PC beforehand,but things are totally different.   

To achieve what I said above,a FAT file system is necessary to be established on MCU, so that users are permitted to apply some API functions to read and write SD card.Unfortunately,this is not practical for STM32F103C8T6 due to its extremely tiny On Chip Flash. 

So I adopted another method:to save pictures into the physical sectors of SD card and use `Read_Sector()`functions to extract the data out for displaying. By this way,user can access the SD card without a FAT file system.However,the data that is saved in SD card must be **the raw color values of every pixel in a picture** and I must find another proper way to write data into the SD card.

But how can I get the raw color data of the pictures? I use a **python script** to achieve it, in which I **transferred the pictures to .txt docs one by one**.After that I use my **development board** which is equipped with a STM32F4 core to transport the data from these .txt docs into the SD card through a **UART port**. 

However, the sector access functions which I just said support accesses by sector only, that means I cannot transport data whose size is smaller than a sector(512B)to SD card. So I have to set a 512B buffer to buff the data received from my PC,but the buffer is too large and it interrupt my UART transportation when I read out the data from the buffer. So I devide the whole transportation into two steps:
- First transport data from .txt docs into the LCD controller to display.
- Second read the data on screen and transport it into corresponding sectors of the SD card.

Yeah I know it is an awful way,it makes my project far more complicated and far less extensible, but I enjoy the process of dealing with data.
