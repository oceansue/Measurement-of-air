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