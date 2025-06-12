#include <REGX52.H>
#include "Delay.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password,Password1,Count,Count1,flag,Password_Data,Change_flag,i;
sbit red = P2^0;
sbit green = P2^1;
sbit keyled = P2^4;

void main()
{
	red = 0;
	green = 0;
	keyled = 0;
	i = 0;
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)
		{
			if(flag == 0)
			{
				if(KeyNum<=10)								//如果S1~S10按键按下，输入密码
				{
					keyled = 1;
					Delay(100);
					keyled = 0;
					if(Count<4)								//如果输入次数小于4
					{
						Password*=10;						//密码左移一位
						Password+=KeyNum%10;				//获取一位密码
						Count++;	//计次加一
						Password_Data++;
					}
				}
				if(KeyNum==11)								//如果S11按键按下，确认
				{
					keyled = 1;
					Delay(100);
					keyled = 0;
					if( Change_flag == 0) 					//没修改密码之前此标志位一直为0 修改密码之后此标志位为1 进入另外一个判断
					{
						if(Password==1234)					//如果密码等于正确密码
						{
							Password=0;						//密码清零
							Count=0;						//计次清零
							red = 0;
							green = 1;
							Delay(2000);					//延时
							Password_Data=0;
						}
						else								//否则
						{
							Password=0;						//密码清零
							Count=0;						//计次清零
							Password_Data=0;
							i++;
						}
					}
					if( Change_flag == 1 ) 					//修改密码之后为1 进入此判断
					{
						if(Password==Password1)				//如果密码等于正确密码
						{
							green = 1;
							Password=0;						//密码清零
							Count=0;						//计次清零
							Password_Data=0;
						}
						else								//否则
						{
							green = 0;
							Password=0;						//密码清零
							Count=0;						//计次清零
							Password_Data=0;
							i++;
						}
					}
				}
				if(KeyNum==12)								//如果S12按键按下，取消
				{
					keyled = 1;
					Delay(100);
					keyled = 0;
					Password=0;								//密码清零
					Count=0;								//计次清零
					Password_Data=0;
				}
				if(KeyNum==14) 								//修改密码按键
				{
					Password1=0;							//新密码清除
					flag = 2; 								//修改密码标志位
				}
			}
			if(flag == 2) 									//修改密码标志位判断
			{
				if(KeyNum<=10)								//如果S1~S10按键按下，输入密码
				{
					if(Count1<4)							//如果输入次数小于4
					{
						Password1*=10;						//密码左移一位
						Password1+=KeyNum%10;				//获取一位密码
						Count1++;							//计次加1
						Password_Data++;					//清除*号显示位置
					}
				}
				if(KeyNum==11)								//如果S11按键按下，确认
				{
					keyled = 1;
					Delay(100);
					keyled = 0;
					Count1 = 0; 							//输入密码位数清除
					flag = 0; 								//输入密码标志位
					Password_Data = 0; 						//清除*号显示位置
					Change_flag = 1; 						//更新密码判断标志位
				}
				if(KeyNum==12)								//如果S12按键按下，取消
				{
					Password1=0;							//密码清零
					Count1=0;								//计次清零
					Password_Data=0;						//清除*号显示位置
				}
			}
			if(KeyNum==13) 									//上锁解锁
			{
				keyled = 1;
				Delay(100);
				keyled = 0;
				flag = !flag; 								//上锁解锁标志位
				if(flag==1)
				{
					red = 1;
					green = 0;
				}
				else
				{
					red = 0;
				}
			}
		}
	}
}
