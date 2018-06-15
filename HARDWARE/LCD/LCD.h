/*************************************************
Copyright (C), 1988-1999, Ruiru Tech. Co., Ltd.
File name: touch.c
Author: Version: Date: Ocean sue ; 2018/4/20.
Description: 用于2.4TFT彩屏显示控制。
Others: 
引脚接口。主控芯片为STM32F103ZEXX
#define DATAOUT(x) GPIOB->ODR=x//输出
#define LCD_RS   PCout(1)   	//PC1
#define LCD_WR   PCout(2)   	//PC2
#define LCD_RD   PCout(5)   	//PC5
#define LCD_CS   PCout(6)   	//PC6
#define LCD_REST PCout(7)   	//PC7
注意：PC3 PC4 做输入输出功能不正常，有待解决!!!
Function List: 
1. void Lcd_Init(void); 
2. void LCD_Clear(u16 Color);
3. void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
4. void LCD_WR_DATA8(int temp); //发送数据-8位参数
5. void LCD_WR_DATA(int da);
6. void LCD_WR_REG(int da);

7. void LCD_DrawPoint(u16 x,u16 y);//画点
8. void LCD_DrawPoint_big(u16 x,u16 y);//画一个大点
9. u16  LCD_ReadPoint(u16 x,u16 y); //读点
10. void Draw_Circle(u16 x0,u16 y0,u8 r);
11. void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
12. void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
13. void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
14. void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);//显示一个字符
15. void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//显示数字
16. void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//显示2个数字
17. void LCD_ShowString(u16 x,u16 y,const u8 *p);		 //显示一个字符串,16字体
 
18. void showhanzi(unsigned int x,unsigned int y,unsigned char index);

History: 
*************************************************/

#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"
//定义LCD的尺寸	
#define LCD_W 240
#define LCD_H 320
//IO连接
//#define  LCD_DataPortH  (GPIOB_IDR_Addr>>8)     //高8位数据口,
//#define  LCD_DataPortL  (GPIOB_IDR_Addr&&0X00FF)     //低8位数据口	,请确认P0口已经上拉10K电阻,不宜太小，最小4.7K,推荐10K.

#define DATAOUT(x) GPIOB->ODR=x//输出
#define LCD_RS   PCout(1)   	//PC1 
#define LCD_WR   PCout(2)   	//PC2
#define LCD_RD   PCout(5)   	//PC5
#define LCD_CS   PCout(6)   	//PC6
#define LCD_REST PCout(7)   	//PC7

extern  u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色
void Lcd_Init(void); 
void LCD_Clear(u16 Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_WR_DATA8(int temp); //发送数据-8位参数
void LCD_WR_DATA(int da);
void LCD_WR_REG(int da);

void LCD_DrawPoint(u16 x,u16 y);//画点
void LCD_DrawPoint_big(u16 x,u16 y);//画一个大点
u16  LCD_ReadPoint(u16 x,u16 y); //读点
void Draw_Circle(u16 x0,u16 y0,u8 r);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//显示数字
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//显示2个数字
void LCD_ShowString(u16 x,u16 y,const u8 *p);		 //显示一个字符串,16字体
void LCD_DrawLine_big(u16 x1, u16 y1, u16 x2, u16 y2);
u16 ConvertRGB32To16(u32 nSrcRGB);
 
void showhanzi(unsigned int x,unsigned int y,unsigned char index);
void showhanzi_16(unsigned int x,unsigned int y,unsigned char index);
void showshu_24(unsigned int x,unsigned int y,unsigned char index);



//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


					  		 
#endif  
	 
	 



