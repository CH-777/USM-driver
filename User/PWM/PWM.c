/**
  ******************************************************************************
	*
	*���ø߼���ʱ��TIM1������·PWM����Ƶ�ʺ���λ���ɵ���Ƶ�ʳ�ʼΪ43kHz��ռ�ձ�����Ϊ0.25
	*
  ******************************************************************************
  */
  
#include "./PWM/PWM.h"

__IO double  PWM1_FREQ= 46.1;//46.6;//45.7      //PWM��1��Ƶ��ΪPWM1_FREQ(kHz),�ֱ���Ϊ0.02
__IO double  PWM1_DPHS= 90;         //��λ��(��)

__IO double  PWM2_FREQ= 45.7;//44.8;      //PWM��1��Ƶ��ΪPWM1_FREQ(kHz)
__IO double  PWM2_DPHS= 90;         //��λ��(��)
/**
  * @brief  ����TIM�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
static void TIM1_GPIO_Config(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*������ʱ����ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (PWM1_A_GPIO_CLK | PWM1_B_GPIO_CLK| PWM1_C_GPIO_CLK|
							PWM1_D_GPIO_CLK | BKIN1_GPIO_CLK, ENABLE); 
	/* ָ�����Ÿ��ù��� */
	GPIO_PinAFConfig(PWM1_A_GPIO,PWM1_A_PINSOURCE, PWM1_A_AF); 
	GPIO_PinAFConfig(PWM1_B_GPIO,PWM1_B_PINSOURCE, PWM1_B_AF); 
	GPIO_PinAFConfig(PWM1_C_GPIO,PWM1_C_PINSOURCE, PWM1_C_AF);
	GPIO_PinAFConfig(PWM1_D_GPIO,PWM1_D_PINSOURCE, PWM1_D_AF); 
	GPIO_PinAFConfig(BKIN1_GPIO,BKIN1_PINSOURCE, BKIN1_AF); 
	
	
	/* ��ʱ���������ų�ʼ�� */															   
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
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //����ʱ���ṹ��
	TIM_OCInitTypeDef  		 TIM_OCInitStructure;         //��������ȽϽṹ��
	TIM_BDTRInitTypeDef      TIM_BDTRInitStructure;       //�����·�������ṹ��
	
	// ����TIM1��ʱ�� 
	RCC_APB2PeriphClockCmd(TIM1_CLK, ENABLE);
	

	//Ԥ��PWMƵ��Ϊ42kHz�����ڲ��ñȽ�ģʽ��PWM����Ƶ�ʵ��ڼ�����Ƶ�ʵ�1/2��
	//��˼�����Ƶ��Ϊ84kHz(2*PWM1_FREQ)������Ԥ��ƵֵΪ(1-1)����ʱ������Ϊ(2000-1)�����Ƶ�ʷֱ���Ϊ0.02KHz��
	TIM_TimeBaseStructure.TIM_Period = (84000/PWM1_FREQ)-1; 
	
	// �߼����ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK=168MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=168MHz
	TIM_TimeBaseStructure.TIM_Prescaler = 1-1;	          
	// ����ʱ�ӷ�Ƶ:4��Ƶ�������������ã�Ƶ��Ϊ42MHz
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV4;
	// ������ʽ�����ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// �ظ�������
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��TIM1
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	
	
	/*PWMͨ��1ģʽ���ã����������PWMA��PWMB*/
	//����Ϊ����Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;          //������CNT������CCRֵʱ�ͷ�ת��ƽ
	//ʹ�ܱȽ����
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	//ʹ�ܻ����Ƚ����
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	//�����ȣ�����ռ�ձȣ�����ռ�ձ�Ϊ0.5��ֵΪTIM_Period��1/2
	TIM_OCInitStructure.TIM_Pulse = 42000/PWM1_FREQ;
	//�������Ϊ�ߵ�ƽ��Ч
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//����������Ըߵ�ƽ��Ч
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//����״̬�±Ƚ����״̬Ϊ�ߵ�ƽ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	//����״̬�±Ƚϻ������״̬�͵�ƽ
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	//ʹ��ͨ��1
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);	 
  	/* ʹ��ͨ��1���� */
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	
	
	
	/*PWMͨ��2ģʽ���ã����������PWMA��PWMB*/
	//����Ϊ����Ƚ�ģʽ
	//ʹ��ͨ��2
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	/* ʹ��ͨ��2���� */
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
		
		
	/* �Զ����ʹ�ܣ���·������ʱ����������� */
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	//��������ʱ��Ϊ250/42MHz=1/4 PWM����
	TIM_BDTRInitStructure.TIM_DeadTime =189;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	//��·���뼫��Ϊ�͵�ƽ
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TIM1, ENABLE);	
	
	/* �������ʹ�� */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

//���������������Է�����������ʵ��PWM��Ƶ�ʺ���λ���ʵʱ����
	/*ͨ�����ú���TIM_SetAutoreload���Ե���PWM��Ƶ��*/
	//����TIM1�Զ����ؼĴ���ARR��ֵ�����ڵ��ڼ�������Ƶ�ʣ����м�����Ƶ��ΪPWM��Ƶ�ʵ�2��
	TIM_SetAutoreload(TIM1,(84000/PWM1_FREQ)-1);
	
	
	/*ͨ������TIM_SetCompare����ʵ����λ��ĵ���*/
	//����TIM1 Capture Compare�Ĵ�����ֵ
	if(PWM1_DPHS>=0)
	{
		TIM_SetCompare1(TIM1, PWM1_DPHS*(466.7/PWM1_FREQ));  //��һ�黥��PWM����ǰcompare�����ڼ���������ΪPWM����
		TIM_SetCompare2(TIM1, 0);                            //��һ�룬��˳�ǰ90�ȣ�ֻ���180�ȡ�84000/180=466.7
	}
	else
	{
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare2(TIM1, (-PWM1_DPHS)*(466.7/PWM1_FREQ)); //�ڶ��黥��PWM����ǰcompare
	}
	
}

/**
  * ���ö�·Դ��GPIO��PA15
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
  * @brief  ��ʼ���߼����ƶ�ʱ��
  * @param  ��
  * @retval ��
  *     Ĭ��Ϊֹͣ����PWM״̬����Ҫͨ��PWM1(ON)��������PWM1
  */
void PWM1_TIM1_Config(void)
{  
	BKIN1_SOURCE_GPIO_Config();
	TIM1_GPIO_Config();
	TIM1_Mode_Config();
	PWM1(OFF);       //Ĭ�Ϲر�PWM��
}
/**
 *   ����PWM1��Ƶ��
 *   FREQ��PWM1��Ƶ�ʣ���λΪkHz
 */
void PWM1_SetFREQ(double FREQ)
{
	PWM1_FREQ=FREQ;
	TIM_SetAutoreload(TIM1,(84000/PWM1_FREQ)-1);
}

/**
 *   ����PWM1����λ��
 *   
 */
void PWM1_SetDPHS(double DPHS)
{
	PWM1_DPHS=DPHS;
	if(PWM1_DPHS>=0)
	{
		TIM_SetCompare1(TIM1, PWM1_DPHS*(466.7/PWM1_FREQ));  //��һ�黥��PWM����ǰcompare�����ڼ���������ΪPWM����
		TIM_SetCompare2(TIM1, 0);                            //��һ�룬��˳�ǰ90�ȣ�ֻ���180�ȡ�84000/180=466.7
	}
	else
	{
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare2(TIM1, (-PWM1_DPHS)*(466.7/PWM1_FREQ)); //�ڶ��黥��PWM����ǰcompare
	}
}
/**
  ******************************************************************************
	*
	*���ø߼���ʱ��TIM8������·PWM����Ƶ�ʺ���λ���ɵ���Ƶ�ʳ�ʼΪ42kHz��ռ�ձ�����Ϊ0.25
	*
  ******************************************************************************
  */
  


/**
  * @brief  ����TIM�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
static void TIM8_GPIO_Config(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*������ʱ����ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (PWM2_A_GPIO_CLK | PWM2_B_GPIO_CLK| PWM2_C_GPIO_CLK|
							PWM2_D_GPIO_CLK | BKIN2_GPIO_CLK, ENABLE); 
  /* ָ�����Ÿ��ù��� */
	GPIO_PinAFConfig(PWM2_A_GPIO,PWM2_A_PINSOURCE, PWM2_A_AF); 
	GPIO_PinAFConfig(PWM2_B_GPIO,PWM2_B_PINSOURCE, PWM2_B_AF); 
	GPIO_PinAFConfig(PWM2_C_GPIO,PWM2_C_PINSOURCE, PWM2_C_AF);
	GPIO_PinAFConfig(PWM2_D_GPIO,PWM2_D_PINSOURCE, PWM2_D_AF); 
	GPIO_PinAFConfig(BKIN2_GPIO,BKIN2_PINSOURCE, BKIN2_AF); 
	
	
	/* ��ʱ���������ų�ʼ�� */															   
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
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       //����ʱ���ṹ��
	TIM_OCInitTypeDef  		 TIM_OCInitStructure;         //��������ȽϽṹ��
	TIM_BDTRInitTypeDef      TIM_BDTRInitStructure;       //�����·�������ṹ��
	
	// ����TIM1��ʱ�� 
	RCC_APB2PeriphClockCmd(TIM8_CLK, ENABLE);
	

	//Ԥ��PWMƵ��Ϊ42kHz�����ڲ��ñȽ�ģʽ��PWM����Ƶ�ʵ��ڼ�����Ƶ�ʵ�1/2��
	//��˼�����Ƶ��Ϊ84kHz(2*PWM1_FREQ)������Ԥ��ƵֵΪ(1-1)����ʱ������Ϊ(2000-1)
	TIM_TimeBaseStructure.TIM_Period = (84000/PWM2_FREQ)-1; 
	
	// �߼����ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK=168MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=168MHz
	TIM_TimeBaseStructure.TIM_Prescaler = 1-1;	          
	// ����ʱ�ӷ�Ƶ:4��Ƶ�������������ã�Ƶ��Ϊ42MHz
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV4;
	// ������ʽ�����ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// �ظ�������
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��TIM1
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	
	
	/*PWMͨ��1ģʽ���ã����������PWMA��PWMB*/
	//����Ϊ����Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;          //������CNT������CCRֵʱ�ͷ�ת��ƽ
	//ʹ�ܱȽ����
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	//ʹ�ܻ����Ƚ����
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	//�����ȣ�����ռ�ձȣ�����ռ�ձ�Ϊ0.5��ֵΪTIM_Period��1/2
	TIM_OCInitStructure.TIM_Pulse = 42000/PWM2_FREQ;
	//�������Ϊ�ߵ�ƽ��Ч
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//����������Ըߵ�ƽ��Ч
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//����״̬�±Ƚ����״̬Ϊ�ߵ�ƽ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	//����״̬�±Ƚϻ������״̬�͵�ƽ
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	//ʹ��ͨ��1
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);	 
  	/* ʹ��ͨ��1���� */
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	
	
	
	/*PWMͨ��2ģʽ���ã����������PWMA��PWMB*/
	//����Ϊ����Ƚ�ģʽ
	//ʹ��ͨ��2
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	/* ʹ��ͨ��2���� */
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
		
		
	/* �Զ����ʹ�ܣ���·������ʱ����������� */
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	//��������ʱ��Ϊ250/42MHz=1/4 PWM����
	TIM_BDTRInitStructure.TIM_DeadTime = 189;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	//��·���뼫��Ϊ�͵�ƽ
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);
	
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TIM8, ENABLE);	
	
	/* �������ʹ�� */
	TIM_CtrlPWMOutputs(TIM8, ENABLE);

//���������������Է�����������ʵ��PWM��Ƶ�ʺ���λ���ʵʱ����
	/*ͨ�����ú���TIM_SetAutoreload���Ե���PWM��Ƶ��*/
	//����TIM1�Զ����ؼĴ���ARR��ֵ�����ڵ��ڼ�������Ƶ�ʣ����м�����Ƶ��ΪPWM��Ƶ�ʵ�2��
	TIM_SetAutoreload(TIM8,(84000/PWM2_FREQ)-1);
	
	
	/*ͨ������TIM_SetCompare����ʵ����λ��ĵ���*/
	//����TIM1 Capture Compare�Ĵ�����ֵ
	if(PWM2_DPHS>=0)
	{
		TIM_SetCompare1(TIM8, PWM2_DPHS*(466.7/PWM2_FREQ));  //��һ�黥��PWM����ǰcompare�����ڼ���������ΪPWM����
		TIM_SetCompare2(TIM8, 0);                            //��һ�룬��˳�ǰ90�ȣ�ֻ���180�ȡ�84000/180=466.7
	}
	else
	{
		TIM_SetCompare1(TIM8,0);
		TIM_SetCompare2(TIM8, (-PWM2_DPHS)*(466.7/PWM2_FREQ)); //�ڶ��黥��PWM����ǰcompare
	}
}

/**
  * ���ö�·Դ��GPIO��PG11
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
  * @brief  ��ʼ���߼����ƶ�ʱ��
  * @param  ��
  * @retval ��
  */
void PWM2_TIM8_Config(void)
{  
	BKIN2_SOURCE_GPIO_Config();    //PWM��·ԴGPIO����
	TIM8_GPIO_Config();
	TIM8_Mode_Config();
	PWM2(OFF);                     //Ĭ�Ϲر�PWM
}

/**
 *   ����PWM2��Ƶ��
 *   FREQ:PWM2d��Ƶ�ʣ���λΪKHz
 */
void PWM2_SetFREQ(double FREQ)
{
	PWM2_FREQ=FREQ;
	TIM_SetAutoreload(TIM8,(84000/PWM2_FREQ)-1);
}

/**
 *   ����PWM2����λ����ڷ�ΧΪ-90--+90��
 *    
 */
void PWM2_SetDPHS(double DPHS)
{
	PWM2_DPHS=DPHS;
	if(PWM2_DPHS>=0)
	{
		TIM_SetCompare1(TIM8, PWM2_DPHS*(466.7/PWM2_FREQ));  //��һ�黥��PWM����ǰcompare�����ڼ���������ΪPWM����
		TIM_SetCompare2(TIM8, 0);                            //��һ�룬��˳�ǰ90�ȣ�ֻ���180�ȡ�84000/180=466.7
	}
	else
	{
		TIM_SetCompare1(TIM8,0);
		TIM_SetCompare2(TIM8, (-PWM2_DPHS)*(466.7/PWM2_FREQ)); //�ڶ��黥��PWM����ǰcompare
	}
}


/*********************************************END OF FILE**********************/
