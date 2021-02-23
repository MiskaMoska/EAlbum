#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"

//LED端口定义
#define Test_LED PAout(0)// PA0


void LED_Init(void);//初始化
void Test_Init(void);//测试初始化

		 				    
#endif
