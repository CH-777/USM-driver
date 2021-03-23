#include "./tim3/tim3.h"

/*
 *  通用定时器3每5ms产生一次中断
 *  
 */

static void TIM3_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为4
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);		
	// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 	
	// 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
	// 设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// 开启TIM3_CLK,
	RCC_APB1PeriphClockCmd(TIM3_CLK, ENABLE); 

	/* 累计 TIM_Period个后产生一个更新或者中断，*/		
	//5ms产生一次中断，即TIM_Period=5*10-1
	TIM_TimeBaseStructure.TIM_Period = 50-1;       
	
	// 通用控制定时器时钟源TIM3CLK = HCLK/2=84MHz 
	// 设定定时器频率为=TIM3CLK/(TIM_Prescaler+1)=10000Hz，0.1ms计数一次
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;	
	// 采样时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// 计数方式
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// 初始化定时器TIM3
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	// 清除定时器更新中断标志位
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	
	// 开启定时器更新中断
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	// 使能定时器
	TIM_Cmd(TIM3, ENABLE);	
}

/**
  * @brief  初始化高级控制定时器定时，5ms产生一次中断
  * @param  tim3中断控制函数在control模块中
  * @retval 
  */
void TIM3_Config(void)
{
	TIM3_NVIC_Configuration();     //中断初始化	
  
	TIM_Mode_Config();             //模式配置

}
