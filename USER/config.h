/////////////////////////UCOSII��������///////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO 10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE 128
//�����ջ
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);

//LED����
//�����������ȼ�
#define LED_TASK_PRIO 7
//���������ջ��С
#define LED_STK_SIZE 128
//�����ջ
OS_STK LED_TASK_STK[LED_STK_SIZE];
//������
void led_task(void *pdata);

//����������
//�����������ȼ�
#define TOUCH_TASK_PRIO 6
//���������ջ��С
#define TOUCH_STK_SIZE 128
//�����ջ
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//������
void touch_task(void *pdata);

//������Ϣ��ʾ����
//�����������ȼ�
#define QMSGSHOW_TASK_PRIO 5
//���������ջ��С
#define QMSGSHOW_STK_SIZE 128
//�����ջ
OS_STK QMSGSHOW_TASK_STK[QMSGSHOW_STK_SIZE];
//������
void qmsgshow_task(void *pdata);

//������
//�����������ȼ�
#define MAIN_TASK_PRIO 4
//���������ջ��С
#define MAIN_STK_SIZE 512
//�����ջ
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//������
void main_task(void *pdata);

//�ź���������
//�����������ȼ�
#define FLAGS_TASK_PRIO 3
//���������ջ��С
#define FLAGS_STK_SIZE 128
//�����ջ
OS_STK FLAGS_TASK_STK[FLAGS_STK_SIZE];
//������
void flags_task(void *pdata);

//����ɨ������
//�����������ȼ�
#define KEY_TASK_PRIO 2
//���������ջ��С
#define KEY_STK_SIZE 128
//�����ջ
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//������
void key_task(void *pdata);
//////////////////////////////////////////////////////////////////////////////

OS_EVENT *msg_key;		//���������¼���
OS_EVENT *q_msg;		//��Ϣ����
OS_TMR *tmr1;			//�����ʱ��1
OS_TMR *tmr2;			//�����ʱ��2
OS_TMR *tmr3;			//�����ʱ��3
OS_FLAG_GRP *flags_key; //�����ź�����
void *MsgGrp[256];		//��Ϣ���д洢��ַ,���֧��256����Ϣ
u8 moo;