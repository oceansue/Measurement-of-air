#ifndef __TOUCH_H
#define __TOUCH_H	
#include "sys.h"	
#include "delay.h"
/* touch panel interface define */
#define  CMD_RDX  0xD0	 //����IC�����������
#define  CMD_RDY  0x90

/*//IO����
sbit DCLK	     =    P1^7;   
sbit CS        =    P1^4;
sbit DIN       =    P3^0;	
sbit DOUT      =    P3^1;																						   
sbit Penirq    =    P3^4;   //��ⴥ������Ӧ�ź�
*/
#define DCLK   PAout(4)   	//PA4 
#define CS  	 PAout(5)   	//PA5 
#define DIN 	 PAout(6)   	//PA6 
#define DOUT 	 PAin(3)   	  //PA3
#define Penirq PAin(7)   		//PA7
/**********************************
*IRQ=PA3(int)
*CS =PA4(out)
*CLK=PA5(out)
*OUT=PA6(int)
*DIN=PA7(out)
*PA4-5-6��������Ҫ����
*PA3-7�������Ҫ���� �ر���PA3 PA4
************************************/
struct tp_pix_
{
	u16 x;
	u16 y;
};
struct tp_pixu32_
{
	u32 x;
	u32 y;
};
extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //��ǰ���������ADֵ,ǰ�������������ֵ   
extern u16 vx,vy;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
extern u16 chx,chy;//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ
u8 tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //��ͼ����
u16 ReadFromCharFrom7843(void);         //SPI ������
void touch_int(void);
u8 Convert_Pos(void);
#endif  
	 
	 



