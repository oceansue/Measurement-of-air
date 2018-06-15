#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "rtc.h"
#include "wkup.h"
#include "adc.h"
#include "dac.h"
#include "stmflash.h"
#include "string.h"
#include "includes.h"
#include "lcd.h"
#include "touch.h"

/////////////////////////UCOSII任务设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO 10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE 128
//任务堆栈
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);

//LED任务
//设置任务优先级
#define LED_TASK_PRIO 7
//设置任务堆栈大小
#define LED_STK_SIZE 128
//任务堆栈
OS_STK LED_TASK_STK[LED_STK_SIZE];
//任务函数
void led_task(void *pdata);

//触摸屏任务
//设置任务优先级
#define TOUCH_TASK_PRIO 6
//设置任务堆栈大小
#define TOUCH_STK_SIZE 128
//任务堆栈
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//任务函数
void touch_task(void *pdata);

//队列消息显示任务
//设置任务优先级
#define QMSGSHOW_TASK_PRIO 5
//设置任务堆栈大小
#define QMSGSHOW_STK_SIZE 128
//任务堆栈
OS_STK QMSGSHOW_TASK_STK[QMSGSHOW_STK_SIZE];
//任务函数
void qmsgshow_task(void *pdata);

//主任务
//设置任务优先级
#define MAIN_TASK_PRIO 4
//设置任务堆栈大小
#define MAIN_STK_SIZE 512
//任务堆栈
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//任务函数
void main_task(void *pdata);

//信号量集任务
//设置任务优先级
#define FLAGS_TASK_PRIO 3
//设置任务堆栈大小
#define FLAGS_STK_SIZE 128
//任务堆栈
OS_STK FLAGS_TASK_STK[FLAGS_STK_SIZE];
//任务函数
void flags_task(void *pdata);

//按键扫描任务
//设置任务优先级
#define KEY_TASK_PRIO 2
//设置任务堆栈大小
#define KEY_STK_SIZE 128
//任务堆栈
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//任务函数
void key_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////

OS_EVENT *msg_key;		//按键邮箱事件块
OS_EVENT *q_msg;		//消息队列
OS_TMR *tmr1;			//软件定时器1
OS_TMR *tmr2;			//软件定时器2
OS_TMR *tmr3;			//软件定时器3
OS_FLAG_GRP *flags_key; //按键信号量集
void *MsgGrp[256];		//消息队列存储地址,最大支持256个消息
u8 moo;
u8 sleep_time, work_time;

void show_quality(u8 i, u8 x, u8 y)
{
	u16 temp;
	temp = USART_RX_BUF[i * 2 + 4] & 0x00ff;
	temp = temp << 8;
	temp = temp | USART_RX_BUF[i * 2 + 5];
	LCD_Show2Num(y - 48, x * 16, temp, 5);
}
void load_time_ui()
{

}
//加载菜单界面
void ucos_load_menu_ui(void)
{
	BACK_COLOR = 0xffff;
	POINT_COLOR = BLUE;
	showhanzi(32, 0, 13);  //LOGO
	showhanzi(64, 0, 14);  //
	showhanzi(96, 0, 15);  //
	showhanzi(128, 0, 16); //
	showhanzi(160, 0, 17); //

	showhanzi_16(0, 40, 11);   //休眠时间
	showhanzi_16(24, 40, 12);  //
	showhanzi_16(48, 40, 13);  //
	showhanzi_16(72, 40, 14);  //
	showhanzi_16(96, 40, 15);  //
	showhanzi_16(174, 40, 24); //

	showhanzi_16(0, 80, 16);   //测量时间
	showhanzi_16(24, 80, 17);  //
	showhanzi_16(48, 80, 18);  //
	showhanzi_16(72, 80, 19);  //
	showhanzi_16(96, 80, 15);  //
	showhanzi_16(174, 80, 24); //

	showhanzi_16(0, 120, 26);  //时间设置
	showhanzi_16(24, 120, 27); //
	showhanzi_16(48, 120, 28); //
	showhanzi_16(72, 120, 29); //
	showhanzi_16(96, 120, 15); //

	showhanzi_16(80, 150, 20);  //年月日
	showhanzi_16(150, 150, 21); //
	showhanzi_16(210, 150, 22); //

	showhanzi_16(80, 180, 23);  //时分秒
	showhanzi_16(150, 180, 24); //
	showhanzi_16(210, 180, 25); //

	//刷按键
	LCD_DrawLine_big(0, 300, 35, 315);
	LCD_DrawLine_big(0, 300, 35, 285);
	LCD_DrawLine_big(35, 285, 35, 315);

	LCD_DrawLine_big(204, 285, 239, 300);
	LCD_DrawLine_big(204, 285, 204, 315);
	LCD_DrawLine_big(204, 315, 239, 300);

	LCD_DrawLine_big(65, 285, 95, 285);
	LCD_DrawLine_big(65, 285, 80, 315);
	LCD_DrawLine_big(80, 315, 95, 285);

	LCD_DrawLine_big(155, 285, 140, 315);
	LCD_DrawLine_big(155, 285, 170, 315);
	LCD_DrawLine_big(140, 315, 170, 315);
	
	//保存 退出
	showhanzi_16(0, 220, 32);  //时间设置
	showhanzi_16(24, 220, 33); //
	
	showhanzi_16(190, 220, 34); //
	showhanzi_16(210, 220, 35); //
}
//加载主界面
void ucos_load_main_ui(void)
{
	BACK_COLOR = 0xffff;
	POINT_COLOR = BLUE;
	showhanzi(32, 0, 13);  //
	showhanzi(64, 0, 14);  //
	showhanzi(96, 0, 15);  //
	showhanzi(128, 0, 16); //
	showhanzi(160, 0, 17); //

	showhanzi_16(0, 40, 0);  //
	showhanzi_16(18, 40, 1); //
	showhanzi_16(38, 40, 2); //
	showhanzi_16(54, 40, 3); //
	showhanzi_16(60, 40, 4); //

	showshu_24(170, 40, 18);
	showshu_24(194, 40, 19);

	showhanzi_16(10, 80, 5); //
	showhanzi_16(40, 80, 6); //
	showshu_24(170, 80, 20);
	showshu_24(194, 80, 21);

	showhanzi_16(10, 120, 7); //
	showhanzi_16(40, 120, 8); //

	showhanzi_16(10, 160, 9);  //
	showhanzi_16(40, 160, 10); //
	//画线 组成坐标。
	LCD_DrawLine_big(5, 315, 235, 315);
	LCD_DrawLine_big(230, 310, 235, 315);
	LCD_DrawLine_big(230, 320, 235, 315);
	LCD_DrawLine_big(5, 315, 5, 200);
	LCD_DrawLine_big(0, 205, 5, 200);
	LCD_DrawLine_big(10, 205, 5, 200);
	//% ℃
	showshu_24(180, 120, 16);
	showshu_24(180, 160, 15);
}
int main(void)
{
	u32 rtccnt;
	Stm32_Clock_Init(9); //系统时钟设置
	uart_init(72, 9600); //串口初始化为9600
	delay_init(72);		 //延时初始化
	LED_Init();			 //初始化与LED连接的硬件接口
	Lcd_Init();
	touch_int();
	while (RTC_Init())
		;
	//读取flash里面的数据。work_time and sleep_time
	work_time = 5;
	sleep_time = 10;
	rtccnt = RTC->CNTH; //得到闹钟值
	rtccnt <<= 16;
	rtccnt |= RTC->CNTL;
	ALARM_CNT_Set(rtccnt + work_time + sleep_time); //设置5秒钟后，闹钟唤醒,唤醒时间等于worktime+sleep time
	LCD_Clear(0xffff);
	ucos_load_main_ui();
	OSInit();																							 //初始化UCOSII
	OSTaskCreate(start_task, (void *)0, (OS_STK *)&START_TASK_STK[START_STK_SIZE - 1], START_TASK_PRIO); //创建起始任务
	OSStart();
}

//开始任务
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr = 0;
	u8 err;
	pdata = pdata;
	msg_key = OSMboxCreate((void *)0);  //创建消息邮箱
	q_msg = OSQCreate(&MsgGrp[0], 256); //创建消息队列
	flags_key = OSFlagCreate(0, &err);  //创建信号量集
	Touch_Adjust();
	OSStatInit();		 //初始化统计任务.这里会延时1秒钟左右
	OS_ENTER_CRITICAL(); //进入临界区(无法被中断打断)
	OSTaskCreate(led_task, (void *)0, (OS_STK *)&LED_TASK_STK[LED_STK_SIZE - 1], LED_TASK_PRIO);
	OSTaskCreate(touch_task, (void *)0, (OS_STK *)&TOUCH_TASK_STK[TOUCH_STK_SIZE - 1], TOUCH_TASK_PRIO);
	OSTaskCreate(qmsgshow_task, (void *)0, (OS_STK *)&QMSGSHOW_TASK_STK[QMSGSHOW_STK_SIZE - 1], QMSGSHOW_TASK_PRIO);
	OSTaskCreate(main_task, (void *)0, (OS_STK *)&MAIN_TASK_STK[MAIN_STK_SIZE - 1], MAIN_TASK_PRIO);
	OSTaskCreate(flags_task, (void *)0, (OS_STK *)&FLAGS_TASK_STK[FLAGS_STK_SIZE - 1], FLAGS_TASK_PRIO);
	OSTaskCreate(key_task, (void *)0, (OS_STK *)&KEY_TASK_STK[KEY_STK_SIZE - 1], KEY_TASK_PRIO);
	OSTaskSuspend(START_TASK_PRIO); //挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}
//LED任务
void led_task(void *pdata)
{
	while (1)
	{
		//point();
		delay_ms(100);
	}
}
//触摸屏任务
void touch_task(void *pdata)
{
	u8 count,i;
	_calendar_obj temp_calendar;//时钟结构体 	
	moo = 0;
	count = 0;
	temp_calendar=calendar;
	while (1)
	{
		i++;
		if(i>6)
		{
			i=0;
		}
		if (Penirq == 0) //按键按下了
		{
			Convert_Pos();
			/*showshu_24(0, 0, tp_pixlcd.x / 100);
			showshu_24(20, 0, tp_pixlcd.x % 100/10);
			showshu_24(40, 0, tp_pixlcd.x % 10);

			showshu_24(80, 0, tp_pixlcd.y / 100);
			showshu_24(100, 0, tp_pixlcd.y % 100/10);
			showshu_24(120, 0, tp_pixlcd.y % 10);*/
		}
		switch (moo)
		{
		case 0x00:
		{
			if (tp_pixlcd.x > 10 & tp_pixlcd.y > 100)
			{
				tp_pixlcd.x = 0;
				tp_pixlcd.y = 0;
				moo = 1;
				LCD_Clear(0xffff);
				ucos_load_menu_ui();
				showshu_24(116, 40, sleep_time / 1000);
				showshu_24(134, 40, sleep_time % 100 / 10);
				showshu_24(152, 40, sleep_time % 10);
				showshu_24(116, 80, work_time / 1000);
				showshu_24(134, 80, work_time % 100 / 10);
				showshu_24(152, 80, work_time % 10);
				showshu_24(0, 150, temp_calendar.w_year / 1000);
				showshu_24(18, 150, temp_calendar.w_year % 1000 / 100);
				showshu_24(36, 150, temp_calendar.w_year % 100 / 10);
				showshu_24(54, 150, temp_calendar.w_year % 10);
				showshu_24(112, 150, temp_calendar.w_month / 10);
				showshu_24(130, 150, temp_calendar.w_month % 10);
				showshu_24(170, 150, temp_calendar.w_date / 10);
				showshu_24(188, 150, temp_calendar.w_date % 10);
				showshu_24(36, 180, temp_calendar.hour / 10);
				showshu_24(54, 180, temp_calendar.hour % 10);
				showshu_24(112, 180, temp_calendar.min / 10);
				showshu_24(130, 180, temp_calendar.min % 10);
				showshu_24(170, 180, temp_calendar.sec / 10);
				showshu_24(188, 180, temp_calendar.sec % 10);
			}
		}
		break;
		case 0x01:
		{
			switch (count)
			{
			case 0:
			{
				if(i<5)
				{
					showshu_24(116, 40, sleep_time / 1000);
					showshu_24(134, 40, sleep_time % 100 / 10);
					showshu_24(152, 40, sleep_time % 10);
				}
				else
				{
					showshu_24(116, 40, 22);
					showshu_24(134, 40, 22);
					showshu_24(152, 40, 22);
				
				}
			}
			break;
			case 1:
			{
				if(i<5)
				{
					showshu_24(116, 80, work_time / 1000);
					showshu_24(134, 80, work_time % 100 / 10);
					showshu_24(152, 80, work_time % 10);
				}
				else
				{
					showshu_24(116, 80, 22);
					showshu_24(134, 80, 22);
					showshu_24(152, 80, 22);
				}
			}
			break;
			case 2:
			{
				//2018-06-01
				if(i<5)
				{
					showshu_24(0, 150, temp_calendar.w_year / 1000);
					showshu_24(18, 150, temp_calendar.w_year % 1000 / 100);
					showshu_24(36, 150, temp_calendar.w_year % 100 / 10);
					showshu_24(54, 150, temp_calendar.w_year % 10);
				}
				else
				{
					showshu_24(0, 150, 22);
					showshu_24(18, 150, 22);
					showshu_24(36, 150, 22);
					showshu_24(54, 150, 22);
				}
			}
			break;
			case 3:
			{
				if(i<5)
				{
					showshu_24(112, 150, temp_calendar.w_month / 10);
					showshu_24(130, 150, temp_calendar.w_month % 10);
				}
				else
				{
					showshu_24(112, 150, 22);
					showshu_24(130, 150, 22);
				}
			}
			break;
			case 4:
			{
				if(i<5)
				{
					showshu_24(170, 150, temp_calendar.w_date / 10);
					showshu_24(188, 150, temp_calendar.w_date % 10);
				}
				else
				{
					showshu_24(170, 150, 22);
					showshu_24(188, 150, 22);
				}
			}
			break;
			case 5:
			{
				if(i<5)
				{
					showshu_24(36, 180, temp_calendar.hour / 10);
					showshu_24(54, 180, temp_calendar.hour % 10);
				}
				else
				{
					showshu_24(36, 180, 22);
					showshu_24(54, 180, 22);
				}
			}
			break;
			case 6:
			{
				if(i<5)
				{
					showshu_24(112, 180, temp_calendar.min / 10);
					showshu_24(130, 180, temp_calendar.min % 10);
				}
				else
				{
					showshu_24(112, 180, 22);
					showshu_24(130, 180, 22);
				}
			}
			break;
			case 7:
			{
				if(i<5)
				{
					showshu_24(170, 180, temp_calendar.sec / 10);
					showshu_24(188, 180, temp_calendar.sec % 10);
				}
				else
				{
					showshu_24(170, 180, 22);
					showshu_24(188, 180, 22);				
				}
			}
			break;
			case 8:
			{
			}
			break;
			}
			if (tp_pixlcd.y > 220&tp_pixlcd.y<240)
			{
				if (tp_pixlcd.x > 0&tp_pixlcd.x<50)
				{
					RTC_Set(temp_calendar.w_year,temp_calendar.w_month,temp_calendar.w_date,temp_calendar.hour,temp_calendar.min,temp_calendar.sec);
					tp_pixlcd.x = 0;
					tp_pixlcd.y = 0;
					delay_ms(500);
				}
				if (tp_pixlcd.x > 190&tp_pixlcd.x<240)
				{
					moo=0;
					tp_pixlcd.x = 0;
					tp_pixlcd.y = 0;
					LCD_Clear(0xffff);
					ucos_load_main_ui();
					delay_ms(500);
				}
			}
			if (tp_pixlcd.y > 285)
			{
				if (tp_pixlcd.x > 0 & tp_pixlcd.x < 35)
				{
					switch (count)
					{
					case 0:
					{
						if(sleep_time >0)
						sleep_time--;
					}
					break;
					case 1:
					{
						if(work_time >0)
						work_time--;
					}
					break;
					case 2:
					{
						if(calendar.w_year>0)
						temp_calendar.w_year--;
					}
					break;
					case 3:
					{
						if(calendar.w_month>0)
						temp_calendar.w_month--;
					}
					break;
					case 4:
					{
						if(calendar .w_date >0)
						temp_calendar.w_date--;
					}
					break;
					case 5:
					{
						if(calendar .hour>0)
						temp_calendar.hour--;
					}
					break;
					case 6:
					{
						if(calendar .min>0)
						temp_calendar.min--;
					}
					break;
					case 7:
					{
						if(calendar .sec>0)
						temp_calendar.sec--;
					}
					break;
					case 8:
					{
					}
					break;
					}
				}
				else if (tp_pixlcd.x > 65 & tp_pixlcd.x < 95)
				{
					if(count<7)
					count++;
					showshu_24(116, 40, sleep_time / 1000);
					showshu_24(134, 40, sleep_time % 100 / 10);
					showshu_24(152, 40, sleep_time % 10);
					showshu_24(116, 80, work_time / 1000);
					showshu_24(134, 80, work_time % 100 / 10);
					showshu_24(152, 80, work_time % 10);
					showshu_24(0, 150, temp_calendar.w_year / 1000);
					showshu_24(18, 150, temp_calendar.w_year % 1000 / 100);
					showshu_24(36, 150, temp_calendar.w_year % 100 / 10);
					showshu_24(54, 150, temp_calendar.w_year % 10);
					showshu_24(112, 150, temp_calendar.w_month / 10);
					showshu_24(130, 150, temp_calendar.w_month % 10);
					showshu_24(170, 150, temp_calendar.w_date / 10);
					showshu_24(188, 150, temp_calendar.w_date % 10);
					showshu_24(36, 180, temp_calendar.hour / 10);
					showshu_24(54, 180, temp_calendar.hour % 10);
					showshu_24(112, 180, temp_calendar.min / 10);
					showshu_24(130, 180, temp_calendar.min % 10);
					showshu_24(170, 180, temp_calendar.sec / 10);
					showshu_24(188, 180, temp_calendar.sec % 10);
				}
				else if (tp_pixlcd.x > 140 & tp_pixlcd.x < 170)
				{
					if(count>0)
					count--;
					showshu_24(116, 40, sleep_time / 1000);
					showshu_24(134, 40, sleep_time % 100 / 10);
					showshu_24(152, 40, sleep_time % 10);
					showshu_24(116, 80, work_time / 1000);
					showshu_24(134, 80, work_time % 100 / 10);
					showshu_24(152, 80, work_time % 10);
					showshu_24(0, 150, temp_calendar.w_year / 1000);
					showshu_24(18, 150, temp_calendar.w_year % 1000 / 100);
					showshu_24(36, 150, temp_calendar.w_year % 100 / 10);
					showshu_24(54, 150, temp_calendar.w_year % 10);
					showshu_24(112, 150, temp_calendar.w_month / 10);
					showshu_24(130, 150, temp_calendar.w_month % 10);
					showshu_24(170, 150, temp_calendar.w_date / 10);
					showshu_24(188, 150, temp_calendar.w_date % 10);
					showshu_24(36, 180, temp_calendar.hour / 10);
					showshu_24(54, 180, temp_calendar.hour % 10);
					showshu_24(112, 180, temp_calendar.min / 10);
					showshu_24(130, 180, temp_calendar.min % 10);
					showshu_24(170, 180, temp_calendar.sec / 10);
					showshu_24(188, 180, temp_calendar.sec % 10);
				}
				else if (tp_pixlcd.x > 204 & tp_pixlcd.x < 239)
				{
					switch(count)
					{
					case 0:
					{
						if(sleep_time <250)
						sleep_time++;
					}
					break;
					case 1:
					{
						if(work_time<250)
						work_time++;
					}
					break;
					case 2:
					{
						if(calendar.w_year<2099)
						temp_calendar.w_year++;
					}
					break;
					case 3:
					{
						if(calendar.w_month<12)
						temp_calendar.w_month++;
					}
					break;
					case 4:
					{
						if(calendar.w_date<31)//此处不谨慎，需要读取当前月是否为31/30天 然后在写限制。
						temp_calendar.w_date++;
					}
					break;
					case 5:
					{
						if(calendar.hour<24)
						temp_calendar.hour++;
					}
					break;
					case 6:
					{
						if(calendar.min<60)
						temp_calendar.min++;
					}
					break;
					case 7:
					{
						if(calendar.sec<60)
						temp_calendar.sec++;
					}
					break;
					case 8:
					{
					}
					break;
					}
				}
				tp_pixlcd.x = 0;
				tp_pixlcd.y = 0;
				delay_ms(500);
			}
		}
		break;
		case 0x02:
		{
			//时间显示
			/*showshu_24(10,185,calendar.w_year%100/10);
				showshu_24(30,185,calendar.w_year%10);
				showshu_24(50,185,calendar.w_month/10);
				showshu_24(70,185,calendar.w_month%10);
				showshu_24(90,185,calendar.w_date/10);
				showshu_24(110,185,calendar.w_date%10);

				showshu_24(10,205,calendar.hour/10);
				showshu_24(30,205,calendar.hour%10);
				showshu_24(50,205,calendar.min/10);
				showshu_24(70,205,calendar.min%10);
				showshu_24(90,205,calendar.sec/10);
				showshu_24(110,205,calendar.sec%10);*/
		}
		break;
		}
		delay_ms(100);
	}
}
//队列消息显示任务
void qmsgshow_task(void *pdata)
{
	u8 flg_min, Count_min;

	Count_min = 0;
	while (1)
	{
		if (flg_min != calendar.min)
		{
			flg_min = calendar.min;
			Count_min++;
		}
		if (Count_min > 20)
		{
			Count_min = 0;
			Sys_Enter_Standby();
		}
		delay_ms(1000);
	}
}
//主任务
void main_task(void *pdata)
{
	u8 flg_sec = 0;
	u16 temp;
	u16 PM25[120];
	u16 methanal[120];
	u16 temper[120];
	u16 humidity[120];
	u16 count;
	count = 0;
	AIR_RESET = 1;
	while (1)
	{
		if ((flg_sec != calendar.sec) && moo == 0)
		{
			temp = USART_RX_BUF[6] & 0x00ff;
			temp = temp << 8;
			temp = temp | USART_RX_BUF[7];
			PM25[count] = temp;
			if (temp > 250)
			{
				POINT_COLOR = ConvertRGB32To16(0x800000); //棕色
			}
			else if (temp > 150)
			{
				POINT_COLOR = ConvertRGB32To16(0x800080); //紫色
			}
			else if (temp > 115)
			{
				POINT_COLOR = ConvertRGB32To16(0xff0000); //红色
			}
			else if (temp > 75)
			{
				POINT_COLOR = ConvertRGB32To16(0xff9900); //橘黄色
			}
			else if (temp > 35)
			{
				POINT_COLOR = ConvertRGB32To16(0xffff00); //黄色
			}
			else
			{
				POINT_COLOR = ConvertRGB32To16(0x00ff00); //优秀绿色
			}
			if (count >= 3)
			{
				LCD_DrawLine(count * 2, 315 - PM25[count - 1] / 10, count * 2 + 2, 315 - PM25[count] / 10);
			}
			showshu_24(85, 40, temp / 1000);
			showshu_24(102, 40, temp / 100 % 10);
			showshu_24(119, 40, temp % 100 / 10);
			showshu_24(138, 40, temp % 10);

			temp = USART_RX_BUF[28] & 0x00ff;
			temp = temp << 8;
			temp = temp | USART_RX_BUF[29];
			methanal[count] = temp;
			if (temp > 1700)
			{
				POINT_COLOR = ConvertRGB32To16(0x524d73); //棕色
			}
			else if (temp > 1500)
			{
				POINT_COLOR = ConvertRGB32To16(0x639dc7); //紫色
			}
			else if (temp > 1200)
			{
				POINT_COLOR = ConvertRGB32To16(0x6fd1a1); //红色
			}
			else if (temp > 900)
			{
				POINT_COLOR = ConvertRGB32To16(0x89ccd2); //橘黄色
			}
			else if (temp > 500)
			{
				POINT_COLOR = ConvertRGB32To16(0x6fd1a1); //黄色
			}
			else
			{
				POINT_COLOR = ConvertRGB32To16(0x00ff00); //优秀绿色
			}
			if (count >= 3)
			{
				LCD_DrawLine(count * 2, 312 - methanal[count - 1], count * 2 + 2, 312 - methanal[count]);
			}
			showshu_24(85, 80, temp / 1000);
			showshu_24(102, 80, 17);
			showshu_24(110, 80, temp / 100 % 10);
			showshu_24(128, 80, temp % 100 / 10);
			showshu_24(145, 80, temp % 10);

			temp = USART_RX_BUF[30] & 0x00ff;
			temp = temp << 8;
			temp = temp | USART_RX_BUF[31];
			temper[count] = temp;
			if (temp > 400)
			{
				POINT_COLOR = ConvertRGB32To16(0x980000); //棕色
			}
			else if (temp > 350)
			{
				POINT_COLOR = ConvertRGB32To16(0xff0000); //紫色
			}
			else if (temp > 300)
			{
				POINT_COLOR = ConvertRGB32To16(0xff9900); //红色
			}
			else if (temp > 200)
			{
				POINT_COLOR = ConvertRGB32To16(0x3c78d8); //橘黄色
			}
			else if (temp > 100)
			{
				POINT_COLOR = ConvertRGB32To16(0xf321c2); //黄色
			}
			else
			{
				POINT_COLOR = ConvertRGB32To16(0x3d85c6); //优秀绿色
			}
			if (count >= 3)
			{
				LCD_DrawLine(count * 2, 400 - temper[count - 1] / 2, count * 2 + 2, 400 - temper[count] / 2);
			}
			showshu_24(102, 120, temp / 100 % 10);
			showshu_24(119, 120, temp % 100 / 10);
			showshu_24(138, 120, 17);
			showshu_24(150, 120, temp % 10);

			temp = USART_RX_BUF[32] & 0x00ff;
			temp = temp << 8;
			temp = temp | USART_RX_BUF[33];
			humidity[count] = temp;
			if (temp > 900)
			{
				POINT_COLOR = ConvertRGB32To16(0x980000); //棕色
			}
			else if (temp > 800)
			{
				POINT_COLOR = ConvertRGB32To16(0xff0000); //紫色
			}
			else if (temp > 700)
			{
				POINT_COLOR = ConvertRGB32To16(0xff9900); //红色
			}
			else if (temp > 500)
			{
				POINT_COLOR = ConvertRGB32To16(0x3c78d8); //橘黄色
			}
			else if (temp > 300)
			{
				POINT_COLOR = ConvertRGB32To16(0xf321c2); //黄色
			}
			else
			{
				POINT_COLOR = ConvertRGB32To16(0x3d85c6); //优秀绿色
			}
			if (count >= 3)
			{
				LCD_DrawLine(count * 2, 300 - humidity[count - 1] / 10, count * 2 + 2, 300 - humidity[count] / 10);
			}
			showshu_24(102, 160, temp / 100 % 10);
			showshu_24(119, 160, temp % 100 / 10);
			showshu_24(138, 160, 17);
			showshu_24(150, 160, temp % 10);

			count++;
			if (count > 110)
			{
				count = 0;
				LCD_Fill(10, 200, 225, 313, 0xffff);
			}
		}
		delay_ms(500); //系统延时
	}
}
//信号量集处理任务
void flags_task(void *pdata)
{
	while (1)
	{
		delay_ms(800);
	}
}

//按键扫描任务
void key_task(void *pdata)
{
	while (1)
	{
		delay_ms(1000);
	}
}
