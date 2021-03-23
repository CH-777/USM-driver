/**
  ******************************************************************************
	*
	*利用高级定时器TIM1产生四路PWM波，频率和相位都可调，频率初始为43kHz，占空比设置为0.25
	*
  ******************************************************************************
  */
  
#include "./PWM/PWM.h"

__IO double  PWM1_FREQ= 46.1;//46.6;//45.7      //PWM波1的频率为PWM1_FREQ(kHz),分辨率为0.02
__IO double  PWM1_DPHS= 90;         //相位差(度)

__IO double  PWM2_FREQ= 45.7;//44.8;      //PWM波1的频率为PWM1_FREQ(kHz)
__IO double  PWM2_DPHS= 90;         //相位差(度)
/**
  * @brief  配置TIM复用输出PWM时用到的I/O
  * @param  无
  * @retval 无
  */
static void TIM1_GPIO_Config(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启定时器相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (PWM1_A_GPIO_CLK | PWM1_B_GPIO_CLK| PWM1_C_GPIO_CLK|
							PWM1_D_GPIO_CLK | BKIN1_GPIO_CLK, ENABLE); 
	/* 指定引脚复用功能 */
	GPIO_PinAFConfig(PWM1_A_GPIO,PWM1_A_PINSOURCE, PWM1_A_AF); 
	GPIO_PinAFConfig(PWM1_B_GPIO,PWM1_B_PINSOURCE, PWM1_B_AF); 
	GPIO_PinAFConfig(PWM1_C_GPIO,PWM1_C_PINSOURCE, PWM1_C_AF);
	GPIO_PinAFConfig(PWM1_D_GPIO,PWM1_D_PINSOURCE, PWM1_D_AF); 
	GPIO_PinAFConfig(BKIN1_GPIO,BKIN1_PINSOURCE, BKIN1_AF); 
	
	
	/* 定时器功能引脚初始化 */															   
	GPIO_InitStructure.GPIO_Pin = PWM1_A_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(PWM1_A_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PWM1_B_PIN;	
	GPIO_Init(PWM1_B_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PWM1_C_PIN;	
	GPIO_Init(PWM1_C_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PWM1_D_PIN;	
	GPIO_Init(PWM1_D_GPIO, &GPIO_InitStructure);
	
	
	
	GPIO_InitStructure.GPIO_Pin = BKIN1_PIN;	
	GPIO_Init(BKIN1_GPIO, &GPIO_InitStructure);
}



static void TIM1_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //定义时基结构体
	TIM_OCInitTypeDef  		 TIM_OCInitStructure;         //定义输出比较结构体
	TIM_BDTRInitTypeDef      TIM_BDTRInitStructure;       //定义断路和死区结构体
	
	// 开启TIM1的时钟 
	RCC_APB2PeriphClockCmd(TIM1_CLK, ENABLE);
	

	//预设PWM频率为42kHz，由于采用比较模式，PWM波的频率等于计数器频率的1/2，
	//因此计数器频率为84kHz(2*PWM1_FREQ)。设置预分频值为(1-1)，定时器周期为(2000-1)，因此频率分辨率为0.02KHz。
	TIM_TimeBaseStructure.TIM_Period = (84000/PWM1_FREQ)-1; 
	
	// 高级控制定时器时钟源TIMxCLK = HCLK=168MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=168MHz
	TIM_TimeBaseStructure.TIM_Prescaler = 1-1;	          
	// 采样时钟分频:4分频，用于死区设置，频率为42MHz
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV4;
	// 计数方式：向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// 重复计数器
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器TIM1
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	
	
	/*PWM通道1模式配置；输出互补的PWMA和PWMB*/
	//配置为输出比较模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;          //计数器CNT计数到CCR值时就翻转电平
	//使能比较输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	//使能互补比较输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	//脉冲宽度，调节占空比，设置占空比为0.5：值为TIM_Period的1/2
	TIM_OCInitStructure.TIM_Pulse = 42000/PWM1_FREQ;
	//输出极性为高电平有效
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//互补输出极性高电平有效
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//空闲状态下比较输出状态为高电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	//空闲状态下比较互补输出状态低电平
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	//使能通道1
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);	 
  	/* 使能通道1重载 */
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	
	
	
	/*PWM通道2模式配置；输出互补的PWMA和PWMB*/
	//配置为输出比较模式
	//使能通道2
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	/* 使能通道2重载 */
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
		
		
	/* 自动输出使能，断路、死区时间和锁定配置 */
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	//配置死区时间为250/42MHz=1/4 PWM周期
	TIM_BDTRInitStructure.TIM_DeadTime =189;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	//断路输入极性为低电平
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	// 使能定时器
	TIM_Cmd(TIM1, ENABLE);	
	
	/* 主动输出使能 */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

//以下两个函数可以放在主函数中实现PWM波频率和相位差的实时调节
	/*通过调用函数TIM_SetAutoreload可以调节PWM的频率*/
	//设置TIM1自动重载寄存器ARR的值，用于调节计数器的频率，其中计数器频率为PWM波频率的2倍
	TIM_SetAutoreload(TIM1,(84000/PWM1_FREQ)-1);
	
	
	/*通过调用TIM_SetCompare函数实现相位差的调节*/
	//设置TIM1 Capture Compare寄存器的值
	if(PWM1_DPHS>=0)
	{
		TIM_SetCompare1(TIM1, PWM1_DPHS*(466.7/PWM1_FREQ));  //第一组互补PWM波超前compare，由于计数器周期为PWM周期
		TIM_SetCompare2(TIM1, 0);                            //的一半，因此超前90度，只需除180度。84000/180=466.7
	}
	else
	{
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare2(TIM1, (-PWM1_DPHS)*(466.7/PWM1_FREQ)); //第二组互补PWM波超前compare
	}
	
}

/**
  * 配置断路源的GPIO：PA15
  */
static void BKIN1_SOURCE_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(BKIN1_SOURCE_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=BKIN1_SOURCE_PIN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init(BKIN1_SOURCE_GPIO, &GPIO_InitStructure);
}

/**
  * @brief  初始化高级控制定时器
  * @param  无
  * @retval 无
  *     默认为停止产生PWM状态，需要通过PWM1(ON)函数来打开PWM1
  */
void PWM1_TIM1_Config(void)
{  
	BKIN1_SOURCE_GPIO_Config();
	TIM1_GPIO_Config();
	TIM1_Mode_Config();
	PWM1(OFF);       //默认关闭PWM波
}
/**
 *   设置PWM1的频率
 *   FREQ：PWM1的频率，单位为kHz
 */
void PWM1_SetFREQ(double FREQ)
{
	PWM1_FREQ=FREQ;
	TIM_SetAutoreload(TIM1,(84000/PWM1_FREQ)-1);
}

/**
 *   设置PWM1的相位差
 *   
 */
void PWM1_SetDPHS(double DPHS)
{
	PWM1_DPHS=DPHS;
	if(PWM1_DPHS>=0)
	{
		TIM_SetCompare1(TIM1, PWM1_DPHS*(466.7/PWM1_FREQ));  //第一组互补PWM波超前compare，由于计数器周期为PWM周期
		TIM_SetCompare2(TIM1, 0);                            //的一半，因此超前90度，只需除180度。84000/180=466.7
	}
	else
	{
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare2(TIM1, (-PWM1_DPHS)*(466.7/PWM1_FREQ)); //第二组互补PWM波超前compare
	}
}
/**
  ******************************************************************************
	*
	*利用高级定时器TIM8产生四路PWM波，频率和相位都可调，频率初始为42kHz，占空比设置为0.25
	*
  ******************************************************************************
  */
  


/**
  * @brief  配置TIM复用输出PWM时用到的I/O
  * @param  无
  * @retval 无
  */
static void TIM8_GPIO_Config(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启定时器相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (PWM2_A_GPIO_CLK | PWM2_B_GPIO_CLK| PWM2_C_GPIO_CLK|
							PWM2_D_GPIO_CLK | BKIN2_GPIO_CLK, ENABLE); 
  /* 指定引脚复用功能 */
	GPIO_PinAFConfig(PWM2_A_GPIO,PWM2_A_PINSOURCE, PWM2_A_AF); 
	GPIO_PinAFConfig(PWM2_B_GPIO,PWM2_B_PINSOURCE, PWM2_B_AF); 
	GPIO_PinAFConfig(PWM2_C_GPIO,PWM2_C_PINSOURCE, PWM2_C_AF);
	GPIO_PinAFConfig(PWM2_D_GPIO,PWM2_D_PINSOURCE, PWM2_D_AF); 
	GPIO_PinAFConfig(BKIN2_GPIO,BKIN2_PINSOURCE, BKIN2_AF); 
	
	
	/* 定时器功能引脚初始化 */															   
	GPIO_InitStructure.GPIO_Pin = PWM2_A_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(PWM2_A_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PWM2_B_PIN;	
	GPIO_Init(PWM2_B_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PWM2_C_PIN;	
	GPIO_Init(PWM2_C_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PWM2_D_PIN;	
	GPIO_Init(PWM2_D_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = BKIN2_PIN;	
	GPIO_Init(BKIN2_GPIO, &GPIO_InitStructure);
}



static void TIM8_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //定义时基结构体
	TIM_OCInitTypeDef  		 TIM_OCInitStructure;         //定义输出比较结构体
	TIM_BDTRInitTypeDef      TIM_BDTRInitStructure;       //定义断路和死区结构体
	
	// 开启TIM1的时钟 
	RCC_APB2PeriphClockCmd(TIM8_CLK, ENABLE);
	

	//预计PWM频率为42kHz，由于采用比较模式，PWM波的频率等于计数器频率的1/2，
	//因此计数器频率为84kHz(2*PWM1_FREQ)。设置预分频值为(1-1)，定时器周期为(2000-1)
	TIM_TimeBaseStructure.TIM_Period = (84000/PWM2_FREQ)-1; 
	
	// 高级控制定时器时钟源TIMxCLK = HCLK=168MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=168MHz
	TIM_TimeBaseStructure.TIM_Prescaler = 1-1;	          
	// 采样时钟分频:4分频，用于死区设置，频率为42MHz
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV4;
	// 计数方式：向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// 重复计数器
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器TIM1
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	
	
	/*PWM通道1模式配置；输出互补的PWMA和PWMB*/
	//配置为输出比较模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;          //计数器CNT计数到CCR值时就翻转电平
	//使能比较输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	//使能互补比较输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	//脉冲宽度，调节占空比，设置占空比为0.5：值为TIM_Period的1/2
	TIM_OCInitStructure.TIM_Pulse = 42000/PWM2_FREQ;
	//输出极性为高电平有效
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//互补输出极性高电平有效
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//空闲状态下比较输出状态为高电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	//空闲状态下比较互补输出状态低电平
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	//使能通道1
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);	 
  	/* 使能通道1重载 */
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	
	
	
	/*PWM通道2模式配置；输出互补的PWMA和PWMB*/
	//配置为输出比较模式
	//使能通道2
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	/* 使能通道2重载 */
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
		
		
	/* 自动输出使能，断路、死区时间和锁定配置 */
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	//配置死区时间为250/42MHz=1/4 PWM周期
	TIM_BDTRInitStructure.TIM_DeadTime = 189;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	//断路输入极性为低电平
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);
	
	// 使能定时器
	TIM_Cmd(TIM8, ENABLE);	
	
	/* 主动输出使能 */
	TIM_CtrlPWMOutputs(TIM8, ENABLE);

//以下两个函数可以放在主函数中实现PWM波频率和相位差的实时调节
	/*通过调用函数TIM_SetAutoreload可以调节PWM的频率*/
	//设置TIM1自动重载寄存器ARR的值，用于调节计数器的频率，其中计数器频率为PWM波频率的2倍
	TIM_SetAutoreload(TIM8,(84000/PWM2_FREQ)-1);
	
	
	/*通过调用TIM_SetCompare函数实现相位差的调节*/
	//设置TIM1 Capture Compare寄存器的值
	if(PWM2_DPHS>=0)
	{
		TIM_SetCompare1(TIM8, PWM2_DPHS*(466.7/PWM2_FREQ));  //第一组互补PWM波超前compare，由于计数器周期为PWM周期
		TIM_SetCompare2(TIM8, 0);                            //的一半，因此超前90度，只需除180度。84000/180=466.7
	}
	else
	{
		TIM_SetCompare1(TIM8,0);
		TIM_SetCompare2(TIM8, (-PWM2_DPHS)*(466.7/PWM2_FREQ)); //第二组互补PWM波超前compare
	}
}

/**
  * 配置断路源的GPIO：PG11
  */
static void BKIN2_SOURCE_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(BKIN2_SOURCE_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=BKIN2_SOURCE_PIN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init(BKIN2_SOURCE_GPIO, &GPIO_InitStructure);
}

/**
  * @brief  初始化高级控制定时器
  * @param  无
  * @retval 无
  */
void PWM2_TIM8_Config(void)
{  
	BKIN2_SOURCE_GPIO_Config();    //PWM断路源GPIO配置
	TIM8_GPIO_Config();
	TIM8_Mode_Config();
	PWM2(OFF);                     //默认关闭PWM
}

/**
 *   设置PWM2的频率
 *   FREQ:PWM2d的频率，单位为KHz
 */
void PWM2_SetFREQ(double FREQ)
{
	PWM2_FREQ=FREQ;
	TIM_SetAutoreload(TIM8,(84000/PWM2_FREQ)-1);
}

/**
 *   设置PWM2的相位差，调节范围为-90--+90度
 *    
 */
void PWM2_SetDPHS(double DPHS)
{
	PWM2_DPHS=DPHS;
	if(PWM2_DPHS>=0)
	{
		TIM_SetCompare1(TIM8, PWM2_DPHS*(466.7/PWM2_FREQ));  //第一组互补PWM波超前compare，由于计数器周期为PWM周期
		TIM_SetCompare2(TIM8, 0);                            //的一半，因此超前90度，只需除180度。84000/180=466.7
	}
	else
	{
		TIM_SetCompare1(TIM8,0);
		TIM_SetCompare2(TIM8, (-PWM2_DPHS)*(466.7/PWM2_FREQ)); //第二组互补PWM波超前compare
	}
}


/*********************************************END OF FILE**********************/
