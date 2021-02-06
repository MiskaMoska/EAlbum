//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RCT6,正点原子MiniSTM32开发板,主频72MHZ，晶振12MHZ
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/08/09
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//此模块可以直接插入正点原子MiniSTM32开发板TFTLCD插槽，无需手动接线
//STM32连接引脚是指TFTLCD插槽引脚内部连接的STM32引脚
//=========================================电源接线================================================//
//     LCD模块             TFTLCD插槽引脚        STM32连接引脚
//      VDD       --->         5V/3.3              DC5V/3.3V          //电源
//      GND       --->          GND                  GND              //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为16位并口总线（8位模式：高8位数据引脚DB8~DB15接D8~D15） 
//     LCD模块             TFTLCD插槽引脚        STM32连接引脚
//     DB0~DB15   --->         D0~D15               PB0~PB15          //液晶屏16位并口数据信号
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 				     TFTLCD插槽引脚        STM32连接引脚 
//       WR       --->          WR                   PC7             //液晶屏写数据控制信号
//       RD       --->          RD                   PC6             //液晶屏读数据控制信号
//       RS       --->          RS                   PC8             //液晶屏数据/命令控制信号
//       RST      --->          RST                  PC4             //液晶屏复位控制信号
//       CS       --->          CS                   PC9             //液晶屏片选控制信号
//       BL       --->          BL                   PC10            //液晶屏背光控制信号
//=========================================触摸屏触接线=========================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块             TFTLCD插槽引脚        STM32连接引脚 
//      PEN       --->          PEN                  PC1             //触摸屏触摸中断信号
//      MISO      --->          MISO                 PC2             //触摸屏SPI总线读信号
//      MOSI      --->          MOSI                 PC3             //触摸屏SPI总线写信号
//      T_CS      --->          TCS                  PC13            //触摸屏片选控制信号
//      CLK       --->          CLK                  PC0             //触摸屏SPI总线时钟信号
**************************************************************************************************/		
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/				
#ifndef __MYFUNS_H_
#define __MYFUNS_H_

#include <stdio.h>
#include "lcd.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
#include "touch.h"
#include "key.h" 
#include "led.h"

//风采展示每个部分的照片数量
#define part1_num 13
#define part2_num 12
#define part3_num 8

extern u8 SD_Out_Buf[512];

extern u16 Go2ClassIntr[4]; //班级介绍
extern u16 Go2MembrIntr[4]; //成员介绍
extern u16 Go2FilmStrip[4]; //幻灯片
extern u16 Go2HandWrite[4]; //手写屏
extern u16 Go2Calbrtion[4]; //校准

extern u8 SysState;

void System(void);
void HomePage(void);
void ClassIntr(void);
void MembIntr(void);
void FilmStrip(void);
void HandWrite(void);
void Calibration(void);
void LeaveHP(void);
void ReturnHP(void);
void LeaveSHP(void);
void ReturnSHP(void);
void DrawHomePage(void);
void DrawClassIntr(void);
void LCD_Show_SD_Full_Img(u32 StartSector);
void LCD_Show_SD_Small_Img(u32 StartSector);
u8  Touch_Inside_Box(_m_tp_dev* p,u16* boxhd);
void Draw_Box(u16* boxhd,u16 color);
void ShowSquare(u8* p,u16 side_len,u16 fcolor,u16 bcolor,u16 sx,u16 sy);
void Appr(void);
void Disappr(void);
void Show_Memb_Info(u8 idx);

#endif
