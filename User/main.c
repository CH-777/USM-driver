#include "stm32f4xx.h"

#include "./encoder/encoder.h"
#include "./usart/bsp_usart.h"
#include "./systick/bsp_SysTick.h"
#include "./PWM/PWM.h"
#include "./control/control.h"                 //电机控制模块
#include "./tim3/tim3.h"                        //定时器中断模块

/*******************************   全局变量    ********************************/

//extern uint8_t Motor1_St;             //电机1的正反转状态
//extern uint8_t Motor2_St;             //电机2的正反状状态

//extern __IO double PWM1_FREQ;        //PWM1的频率
//extern __IO double PWM1_DPHS;        //PWM1的两路互补PWM波的相位差
//extern __IO double PWM2_FREQ;        //PWM2的频率
//extern __IO double PWM2_DPHS;        //PWM2的两路互补PWM波的相位差

/*****************************************************************************/

//外设初始化函数
static void Model_Init(void)
{
	Encoder1_Init_TIM2();      //编码器1初始化
	Encoder2_Init_TIM4();      //编码器2初始化
	USARTx_Config();           //串口1初始化
	SysTick_Init();            //系统滴答初始化
	
	PWM1_TIM1_Config();        //PWM1初始化，默认PWM1为关闭状态
	
	PWM1(ON);                  //打开PWM1
	PWM2_TIM8_Config();        //PWM2初始化，默认PWM2位关闭状态
	PWM2(ON);                  //打开PWM2
	
	TIM3_Config();             //初始化定时器3
}

int main(void)
{
	Model_Init();
	PWM1_CCW();
//	PWM2_CCW();
//	printf("硬件初始化成功\n");
	while(1)
	{
	
	}
}

/*********************************************END OF FILE**********************/

