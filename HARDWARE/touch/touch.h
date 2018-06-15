#ifndef __TOUCH_H
#define __TOUCH_H	
#include "sys.h"	
#include "delay.h"
/* touch panel interface define */
#define  CMD_RDX  0xD0	 //触摸IC读坐标积存器
#define  CMD_RDY  0x90

/*//IO连接
sbit DCLK	     =    P1^7;   
sbit CS        =    P1^4;
sbit DIN       =    P3^0;	
sbit DOUT      =    P3^1;																						   
sbit Penirq    =    P3^4;   //检测触摸屏响应信号
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
*PA4-5-6做输入需要测试
*PA3-7做输出需要测试 特别是PA3 PA4
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
extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //当前触控坐标的AD值,前触控坐标的像素值   
extern u16 vx,vy;  //比例因子，此值除以1000之后表示多少个AD值代表一个像素点
extern u16 chx,chy;//默认像素点坐标为0时的AD起始值
u8 tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //绘图函数
u16 ReadFromCharFrom7843(void);         //SPI 读数据
void touch_int(void);
u8 Convert_Pos(void);
#endif  
	 
	 



