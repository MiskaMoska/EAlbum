#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "led.h" 
#include "MMC_SD.h"  
#include "myfuns.h"
#include "timer.h"

int main(void)
{	
	SystemInit(); //初始化RCC 设置系统主频为72MHZ
	delay_init(72);	//延时初始化
	Test_Init(); //LED初始化,禁用了JTAG和SW

	LCD_Init();	   //液晶屏初始化
	TP_Init();

	POINT_COLOR = GREEN;
	LCD_ShowString(30,60,16,"SD Card Initializing....",1);
	while(SD_Initialize())	//检测SD卡
	{	
		Test_LED = 0;
		delay_ms(150);
		Test_LED = 1;
		delay_ms(150);
	}
	TIM3_Int_Init(720-1,100-1);
	LCD_ShowString(280,60,16,"Done",1);
	delay_ms(500);
	LCD_Clear(BLACK);
	
	while(1)
	{	
		System();
	}
}

