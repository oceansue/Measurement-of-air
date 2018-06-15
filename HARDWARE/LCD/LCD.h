/*************************************************
Copyright (C), 1988-1999, Ruiru Tech. Co., Ltd.
File name: touch.c
Author: Version: Date: Ocean sue ; 2018/4/20.
Description: ����2.4TFT������ʾ���ơ�
Others: 
���Žӿڡ�����оƬΪSTM32F103ZEXX
#define DATAOUT(x) GPIOB->ODR=x//���
#define LCD_RS   PCout(1)   	//PC1
#define LCD_WR   PCout(2)   	//PC2
#define LCD_RD   PCout(5)   	//PC5
#define LCD_CS   PCout(6)   	//PC6
#define LCD_REST PCout(7)   	//PC7
ע�⣺PC3 PC4 ������������ܲ��������д����!!!
Function List: 
1. void Lcd_Init(void); 
2. void LCD_Clear(u16 Color);
3. void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
4. void LCD_WR_DATA8(int temp); //��������-8λ����
5. void LCD_WR_DATA(int da);
6. void LCD_WR_REG(int da);

7. void LCD_DrawPoint(u16 x,u16 y);//����
8. void LCD_DrawPoint_big(u16 x,u16 y);//��һ�����
9. u16  LCD_ReadPoint(u16 x,u16 y); //����
10. void Draw_Circle(u16 x0,u16 y0,u8 r);
11. void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
12. void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
13. void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
14. void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);//��ʾһ���ַ�
15. void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//��ʾ����
16. void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//��ʾ2������
17. void LCD_ShowString(u16 x,u16 y,const u8 *p);		 //��ʾһ���ַ���,16����
 
18. void showhanzi(unsigned int x,unsigned int y,unsigned char index);

History: 
*************************************************/

#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"
//����LCD�ĳߴ�	
#define LCD_W 240
#define LCD_H 320
//IO����
//#define  LCD_DataPortH  (GPIOB_IDR_Addr>>8)     //��8λ���ݿ�,
//#define  LCD_DataPortL  (GPIOB_IDR_Addr&&0X00FF)     //��8λ���ݿ�	,��ȷ��P0���Ѿ�����10K����,����̫С����С4.7K,�Ƽ�10K.

#define DATAOUT(x) GPIOB->ODR=x//���
#define LCD_RS   PCout(1)   	//PC1 
#define LCD_WR   PCout(2)   	//PC2
#define LCD_RD   PCout(5)   	//PC5
#define LCD_CS   PCout(6)   	//PC6
#define LCD_REST PCout(7)   	//PC7

extern  u16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ
void Lcd_Init(void); 
void LCD_Clear(u16 Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_WR_DATA8(int temp); //��������-8λ����
void LCD_WR_DATA(int da);
void LCD_WR_REG(int da);

void LCD_DrawPoint(u16 x,u16 y);//����
void LCD_DrawPoint_big(u16 x,u16 y);//��һ�����
u16  LCD_ReadPoint(u16 x,u16 y); //����
void Draw_Circle(u16 x0,u16 y0,u8 r);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);//��ʾ����
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len);//��ʾ2������
void LCD_ShowString(u16 x,u16 y,const u8 *p);		 //��ʾһ���ַ���,16����
void LCD_DrawLine_big(u16 x1, u16 y1, u16 x2, u16 y2);
u16 ConvertRGB32To16(u32 nSrcRGB);
 
void showhanzi(unsigned int x,unsigned int y,unsigned char index);
void showhanzi_16(unsigned int x,unsigned int y,unsigned char index);
void showshu_24(unsigned int x,unsigned int y,unsigned char index);



//������ɫ
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
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


					  		 
#endif  
	 
	 



