#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "malloc.h" 
#include "sdio_sdcard.h"    

//按0键将当前LCD的图片存到SD卡的startsector扇区
//按1键显示SD卡当前起始扇区的图像
//按2键减小startsector
//按wakeup键增大startsector
//!自我介绍基地址0
//!成长基地址3000
//!实践基地址12000
//!娱乐基地址21000

u16 StartSector = 0;
u8 a[512];
u8 LCD_Out_Buf[512];
u8 SD_Out_Buf[512];

extern u8 RawDataBuff[1024];

//通过串口打印SD卡相关信息
void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
  	printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//制造商ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//卡相对地址
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//显示容量
 	printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//显示块大小
}

void set_window(u16 sx,u16 sy,u16 width,u16 height)
{
		LCD->LCD_REG = (lcddev.setxcmd); 
		LCD->LCD_RAM = (sx>>8); 
		LCD->LCD_RAM = (sx&0XFF);	 
		LCD->LCD_RAM = ((width-1)>>8); 
		LCD->LCD_RAM = ((width-1)&0XFF);  
		LCD->LCD_REG = (lcddev.setycmd); 
		LCD->LCD_RAM = (sy>>8); 
		LCD->LCD_RAM = (sy&0XFF); 
		LCD->LCD_RAM = ((height-1)>>8); 
		LCD->LCD_RAM = ((height-1)&0XFF); 
		LCD->LCD_REG = (lcddev.wramcmd); 
}

int main(void)
{        
	u8 key;		 
	u16 x,y;
	u32 idx_buf = 0;
	u32 idx_sector = 0;
	// u8  SD_Out_Buf_u8[512] = {0};

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	LED_Init();					//初始化LED  
 	LCD_Init();					//LCD初始化  
 	KEY_Init();					//按键初始化  
	
	my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMCCM);		//初始化CCM内存池
 	while(SD_Init())//检测不到SD卡
	{
		LCD_ShowString(30,150,200,16,16,"SD Card Error!");
		delay_ms(500);					
		LCD_ShowString(30,150,200,16,16,"Please Check! ");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}

//!---------------------------------------
//!      设置方向和窗口大小

	LCD_Display_Dir(1);
	set_window(0,0,128,200);
//!---------------------------------------

	while(1)
	{	

		LED0 = 1;
		key = KEY_Scan(0);
		
		if(key == KEY0_PRES) //!按键0读屏幕信息到SD卡
		{	
			LED0= 0;
			idx_buf = 0;
			idx_sector = 0;

			for(y=0; y<200; y++)
			{
				for(x=0; x<128; x++)
				{	
					*(LCD_Out_Buf + 2*idx_buf) = LCD_ReadPoint(x,y)>>8;
					*(LCD_Out_Buf + 2*idx_buf + 1) = LCD_ReadPoint(x,y)&0xFF;
					idx_buf++;

					if(idx_buf==256)
					{	
						SD_WriteDisk(LCD_Out_Buf,StartSector + idx_sector,1);
						idx_buf = 0;
						idx_sector++;
					}
				}
			}
		}

		else if(key == KEY2_PRES) //!按键2显示当前SD扇区里的信息到LCD
		{	
			LED0 = 0;
			set_window(0,0,128,200);

			for(idx_sector = 0; idx_sector<100; idx_sector++)
			{	
				SD_ReadDisk(SD_Out_Buf, StartSector+idx_sector, 1);
				for(idx_buf = 0; idx_buf<256; idx_buf++)
					LCD->LCD_RAM = ((u16)(*(SD_Out_Buf + 2*idx_buf))<<8) | ((u16)(*(SD_Out_Buf + 2*idx_buf + 1)));
			}
		}
		
		else if(key == KEY1_PRES) //!按键1图片索引--
		{	
			if(StartSector>0)
				StartSector -= 100;
			LCD_Clear(WHITE);
			set_window(0,0,319,239);
			LCD_ShowString(20,100,200,16,16,"Present Image:");
			LCD_ShowNum(200,100,(StartSector/100)+1,8,16);
			set_window(0,0,128,200);
		}
		
		else if(key == WKUP_PRES) //!按键WKUP图片索引++
		{	
			if(StartSector<3000)
				StartSector += 100;
			LCD_Clear(WHITE);
			set_window(0,0,319,239);
			LCD_ShowString(20,100,200,16,16,"Present Image:");
			LCD_ShowNum(200,100,(StartSector/100)+1,8,16);
			set_window(0,0,128,200);
		}
	} 
}





