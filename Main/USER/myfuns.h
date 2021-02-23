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

//���չʾÿ�����ֵ���Ƭ����
#define part1_num 13
#define part2_num 12
#define part3_num 8

extern u8 SD_Out_Buf[512];

extern u16 Go2ClassIntr[4]; //�༶����
extern u16 Go2MembrIntr[4]; //��Ա����
extern u16 Go2FilmStrip[4]; //�õ�Ƭ
extern u16 Go2HandWrite[4]; //��д��
extern u16 Go2Calbrtion[4]; //У׼

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
