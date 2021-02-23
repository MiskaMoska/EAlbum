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
	SystemInit(); //��ʼ��RCC ����ϵͳ��ƵΪ72MHZ
	delay_init(72);	//��ʱ��ʼ��
	Test_Init(); //LED��ʼ��,������JTAG��SW

	LCD_Init();	   //Һ������ʼ��
	TP_Init();

	POINT_COLOR = GREEN;
	LCD_ShowString(30,60,16,"SD Card Initializing....",1);
	while(SD_Initialize())	//���SD��
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

