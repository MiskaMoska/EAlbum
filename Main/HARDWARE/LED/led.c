#include "stm32f10x.h"
#include "led.h"

/*****************************************************************************
 * @name       :void LED_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialize LED GPIO
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 
void LED_Init(void)
{ 
 GPIO_InitTypeDef  GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				  //PA8
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);   //使能GPIOD时钟 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //PD2
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 GPIO_Init(GPIOD, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 
}

void Test_Init(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	// GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE); //PB3,PB4,PA15,PA13,PA14全部用作IO口

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
