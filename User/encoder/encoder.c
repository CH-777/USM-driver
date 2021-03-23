#include "./encoder/encoder.h"

/**
 * 定时器2及其GPIO初始化函数 
 * 将TIM2配置为编码器模式，计数器的CNT就是转过的光栅刻度数的4倍，正转时计数器向上增加，反转时计数器向下递减
 * PA0和PA1连接编码器的A、B相接口
 */
void Encoder1_Init_TIM2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	/*打开A、B相IO的时钟以及定时器2的时钟*/
	RCC_AHB1PeriphClockCmd(ENCODER1_A_CLK|ENCODER1_B_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(TIM2_CLK,ENABLE);
		
	/*配置A、B相IO*/
	GPIO_DeInit(ENCODER1_A_GPIO);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;   
	GPIO_InitStructure.GPIO_Pin=ENCODER1_A_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  
	GPIO_Init(ENCODER1_A_GPIO,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(ENCODER1_A_GPIO,ENCODER1_A_SOURCE,GPIO_AF_TIM2);
	GPIO_PinAFConfig(ENCODER1_B_GPIO,ENCODER1_B_SOURCE,GPIO_AF_TIM2);
	
	GPIO_InitStructure.GPIO_Pin=ENCODER1_B_PIN;
	GPIO_Init(ENCODER1_B_GPIO,&GPIO_InitStructure);

	/*将定时器2的寄存器设为初始值*/
	TIM_DeInit(TIM2);
	//设置预分频为1分频
	TIM_TimeBaseStructure.TIM_Prescaler=0;     //0
	//计数值为	
	TIM_TimeBaseStructure.TIM_Period=65535; 
	//向上计数	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/*编码器模式*/
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	
	
//	/*比较滤波器*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	
	TIM_ICInitStructure.TIM_ICFilter = 7;    //7 
	/*初始化定时器2*/
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	
	/*比较滤波器*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	
	TIM_ICInitStructure.TIM_ICFilter = 7;     //
//	/*初始化定时器2*/
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	
	//清除TIM的更新标志位
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);      
//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	/*计数器初始化*/
	TIM_SetCounter(TIM2,0);     
	TIM_Cmd(TIM2, ENABLE); 
}
/**
 * 定时器4及其GPIO初始化函数 
 * 将TIM4配置为编码器模式，计数器的CNT就是转过的光栅刻度数的4倍，正转时计数器向上增加，反转时计数器向下递减
 * PD12和PD13连接编码器1的A、B相接口
 */
void Encoder2_Init_TIM4(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	/*打开A、B相IO的时钟以及定时器2的时钟*/
	RCC_AHB1PeriphClockCmd(ENCODER2_A_CLK|ENCODER2_B_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(TIM4_CLK,ENABLE);
		
	/*配置A、B相IO*/
	GPIO_DeInit(ENCODER2_A_GPIO);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;   
	GPIO_InitStructure.GPIO_Pin=ENCODER2_A_PIN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  
	GPIO_Init(ENCODER2_A_GPIO,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(ENCODER2_A_GPIO,ENCODER2_A_SOURCE,GPIO_AF_TIM4);  
	GPIO_PinAFConfig(ENCODER2_B_GPIO,ENCODER2_B_SOURCE,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin=ENCODER2_B_PIN;
	GPIO_Init(ENCODER2_B_GPIO,&GPIO_InitStructure);

	/*将定时器4的寄存器设为初始值*/
	TIM_DeInit(TIM4);
	//设置预分频为1分频
	TIM_TimeBaseStructure.TIM_Prescaler=1-1;    
	//计数值
	TIM_TimeBaseStructure.TIM_Period=65535;  
	//向上计数	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/*编码器模式*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	/*比较滤波器*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	
	TIM_ICInitStructure.TIM_ICFilter = 7; 
	/*初始化定时器4*/
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	
	TIM_ICInitStructure.TIM_ICFilter = 7; 
	/*初始化定时器4*/
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	
	//清除TIM的更新标志位
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);      
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	/*计数器初始化*/
	TIM_SetCounter(TIM4,0);     
	TIM_Cmd(TIM4, ENABLE); 
}




/**************************************************************************
函数功能：读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/

uint16_t Read_Encoder1(void)
{
    uint16_t Encoder_TIM;    
    Encoder_TIM= TIM2 -> CNT; 
		
	return Encoder_TIM;
}


uint16_t Read_Encoder2(void)
{
    uint16_t Encoder2_TIM;    
    Encoder2_TIM= TIM4 -> CNT; 
		
	return Encoder2_TIM;
}




