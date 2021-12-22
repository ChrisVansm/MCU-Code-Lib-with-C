/*
**#############################################################################
**      SVN Information
**
**      Checked In          : 2016-6-15
**
**      Revision            : 0.01
**
**      Release Information : Key cheak function
**   
**#############################################################################
*/
#include "Janus_Reg.h"
#include "App.h"
#define KEY1		PT1DAT_D0			//按下一次地址递增一个，长按持续递增
#define KEY2		PT1DAT_D1			//按下一次地址递减一个，长按持续递减
#define KEY3		PT1DAT_D2			//按下后地址复位为0

/*
**#############################################################################
** Function prototype
**#############################################################################
*/
extern void Delay(uint32 howlong);
uint8 KeyScanf(void);

/*
**#############################################################################
** Variable declaration
**#############################################################################
*/
extern uint32 addresstemp;
static uint8 KeyScanfState = 1;		//按键状态机
static uint8 keydata = 0;
static uint32 longkeycount = 0;
static uint8 keyresult = 0;
static uint32 keydelaycount = 0;
enum
{
	KEY_FREE = 0x01,
	KEY_ONCE_DOWN,
	KEY_PRESS_DOWN,
	KEY_ONCE_LEAVE,
};

/*
**#############################################################################
** KeyCheak function
**#############################################################################
*/
void Key_Proc(void)
{
	keyresult = KeyScanf();
	switch(keyresult)
	{
		case 1:
			addresstemp++;
		break;
		case 2:
			addresstemp--;
		break;
		case 3:
			addresstemp = 0;
		break;
		case 4:
			if(TimerOutChkMsLong_pultus(&keydelaycount,150) == 1)		//当长按KEY1时，每隔150ms地址递增一次
			{
				addresstemp++;
			}
		break;
		case 5:
			if(TimerOutChkMsLong_pultus(&keydelaycount,150) == 1)		//当长按KEY2时，每隔150ms地址递减一次
			{
				addresstemp--;
			}
		break;
		case 6:
			#ifdef USE_SPI_GET_REG
				Plutus_Reset_SPI();
			#endif
		
			#ifdef USE_UART_GET_REG
				Plutus_Reset_UART();
			#endif
		
			#ifdef USE_MCH_GET_REG
		
			#endif
		break;
	}
}


/*
**#############################################################################
** KeyScanf function
**#############################################################################
*/
uint8 KeyScanf(void)
{

	switch(KeyScanfState)
	{
		case KEY_FREE:
		if((KEY1&KEY2&KEY3) == 0)
			{
				KeyScanfState = KEY_ONCE_DOWN;				//状态机转换为按键检测到一次按下
				if(KEY1 == 0)													//保存按键按下信息
					keydata = 1;
				else if(KEY2 == 0)
					keydata = 2;
				else if(KEY3 == 0)
					keydata = 3;
			}
		break;
			
		case KEY_ONCE_DOWN:
			if(TimerOutChkMsLong_pultus(&keydelaycount,15) == 1)
			{
				if((KEY1&KEY2&KEY3) == 0)							//如果跳过了抖动时间 检测到按键依然按下，状态机切换到按键确定被按下状态
				{
					KeyScanfState = KEY_PRESS_DOWN;
					return keydata;											//返回按键信息
				}
				else
				{
					KeyScanfState = KEY_FREE;						//如果按键已经被抬起，则状态机切换会按键空闲状态
				}
			}
		break;
			
		case KEY_PRESS_DOWN:						
			if((KEY1&KEY2&KEY3) == 1)								//如果检测到按键全部离开，状态机切换到按键离开一次状态
			{
				KeyScanfState = KEY_ONCE_LEAVE;
			}
			else
			{
				longkeycount++;
				if(longkeycount >= 40000)
				{
					if(KEY1 == 0)
						return 4;
					else if(KEY2 == 0)
						return 5;
					else if(KEY3 == 0)
						return 6;
				}
			}
		break;
			
		case KEY_ONCE_LEAVE:											//如果经过按键防抖动时间还是检测到按键全部离开，状态机切换到按键离开状态
			if(TimerOutChkMsLong_pultus(&keydelaycount,15) == 1)
			{
				if((KEY1&KEY2&KEY3) == 1)
				{
					KeyScanfState = KEY_FREE;
					longkeycount = 0;
					keydata = 0;
				}
			}
	}
	return 0;

}
