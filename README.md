
# 1  Introduction
The software code of a little electronic album (EAlbum), which is designed based on STM32F103C8T6 MCU. Some pictures are provided to show the outlook of EAlbum.

**Click [here](https://pan.baidu.com/s/1BRxl9arHRHqPtyCifSQCGA) to get more information about EAlbum, extraction code `8nyz`** 

**Click [here](https://www.bilibili.com/video/BV1of4y1e7pQ) to see a brief video of EAlbum** 

![img1](https://github.com/MiskaMoska/EAlbum/blob/main/img1.png)

![img2](https://github.com/MiskaMoska/EAlbum/blob/main/img2.png)

# 2 Functions
- **Show Stuffs：** EAlbum is equipped with a TFT LCD to show anything (text, logos, pictures, videos, etc.) you like as long as you program it to do so. 
- **Touchable：** The TFT LCD is touch-sensitive, and the PCB of EAlbum is equipped with a touch controller chip, so users are permitted to control EAlbum by touching the screen.
- **Rechargeable：** EAlbum is equipped with a lithium battery, users can charge it through a micro-USB port, which makes EAlbum more mobile and convenient.

# 3 Solution
This chapter provides the design and control method of EAlbum, I recommend you to read it carefully if you're going to **reproduce**, even more, **modify**  my project.

EAlbum is equipped with a SD card slot, and you may think naturally that it works by reading the pictures in SD card which is managed by PC, but things are totally different.   

To achieve SD card management on PC, a FAT file system is necessary to be established onto MCU to provide users with APIs to access SD card on the file system level. Unfortunately, this is not practical for STM32F103C8T6 due to its extremely tiny On Chip Flash, it is too small to keep the whole FAT. 

So I adopted another method: save pictures into the physical sectors of SD card and use `Read_Sector()`functions to extract the data out to display. By this way, user can access the SD card without a FAT file system. However, the data that is saved in SD card must be **the RGB565 values of every pixel in a picture** and I must find another proper way to write data into the SD card.

I use a **python script** to achieve it, in which I **transferred the pictures to .txt docs one by one in RGB565 format**. After that I use my **development board** which is equipped with a STM32F4 to transmit the data from these .txt docs to the SD card through a **UART port**. 

However, the aforementioned sector access functions support accesses by sector only, which means I cannot transmit data with size larger than a sector (512B) to SD card. So I have to set a 512B buffer to buffer the data received from my PC, but the buffer is too large and it disturbs the UART transmission when I read out the data from the buffer. So I devide the whole transmission into two steps:
- First transmit data from .txt docs to the LCD controller to display.
- Second read the data on screen and transmit it to the corresponding sectors of the SD card.

# 4 File Structure
### 4.1 Main
This folder keeps the main project. The application-related functions are defined in `myfuns.c` and declared in `myfuns.h`. A Chinese character database is declared in `FONT.H`.
### 4.2 Auxiliary
This folder keeps two auxiliary projects which is designed to transmit data from .txt docs on PC to SD card physical sectors. The variable `base_sector` in `main.c` is the start sector to read or write, the real time sector in access is displayed on LCD. User is permitted to use keys to change the storage sector and to launch a receive (from PC) or a write (to SD card) action.
- **WR_SIMG_2_SD：** Write a small (128*240) image to SD card
- **WR_FIMG_2_SD：** Write a full (320*240) image to SD card

### 4.3 Script
Python script to transfer pictures to RGB565 data.
