#include "./encoder/encoder.h"

/**
 * ��ʱ��2����GPIO��ʼ������ 
 * ��TIM2����Ϊ������ģʽ����������CNT����ת���Ĺ�դ�̶�����4������תʱ�������������ӣ���תʱ���������µݼ�
 * PA0��PA1���ӱ�������A��B��ӿ�
 */
void Encoder1_Init_TIM2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	/*��A��B��IO��ʱ���Լ���ʱ��2��ʱ��*/
	RCC_AHB1PeriphClockCmd(ENCODER1_A_CLK|ENCODER1_B_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(TIM2_CLK,ENABLE);
		
	/*����A��B��IO*/
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

	/*����ʱ��2�ļĴ�����Ϊ��ʼֵ*/
	TIM_DeInit(TIM2);
	//����Ԥ��ƵΪ1��Ƶ
	TIM_TimeBaseStructure.TIM_Prescaler=0;     //0
	//����ֵΪ	
	TIM_TimeBaseStructure.TIM_Period=65535; 
	//���ϼ���	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/*������ģʽ*/
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	
	
//	/*�Ƚ��˲���*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	
	TIM_ICInitStructure.TIM_ICFilter = 7;    //7 
	/*��ʼ����ʱ��2*/
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	
	/*�Ƚ��˲���*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	
	TIM_ICInitStructure.TIM_ICFilter = 7;     //
//	/*��ʼ����ʱ��2*/
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	
	//���TIM�ĸ��±�־λ
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);      
//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	/*��������ʼ��*/
	TIM_SetCounter(TIM2,0);     
	TIM_Cmd(TIM2, ENABLE); 
}
/**
 * ��ʱ��4����GPIO��ʼ������ 
 * ��TIM4����Ϊ������ģʽ����������CNT����ת���Ĺ�դ�̶�����4������תʱ�������������ӣ���תʱ���������µݼ�
 * PD12��PD13���ӱ�����1��A��B��ӿ�
 */
void Encoder2_Init_TIM4(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	/*��A��B��IO��ʱ���Լ���ʱ��2��ʱ��*/
	RCC_AHB1PeriphClockCmd(ENCODER2_A_CLK|ENCODER2_B_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(TIM4_CLK,ENABLE);
		
	/*����A��B��IO*/
	GPIO_DeInit(ENCODER2_A_GPIO);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;   
	GPIO_InitStructure.GPIO_Pin=ENCODER2_A_PIN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  
	GPIO_Init(ENCODER2_A_GPIO,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(ENCODER2_A_GPIO,ENCODER2_A_SOURCE,GPIO_AF_TIM4);  
	GPIO_PinAFConfig(ENCODER2_B_GPIO,ENCODER2_B_SOURCE,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin=ENCODER2_B_PIN;
	GPIO_Init(ENCODER2_B_GPIO,&GPIO_InitStructure);

	/*����ʱ��4�ļĴ�����Ϊ��ʼֵ*/
	TIM_DeInit(TIM4);
	//����Ԥ��ƵΪ1��Ƶ
	TIM_TimeBaseStructure.TIM_Prescaler=1-1;    
	//����ֵ
	TIM_TimeBaseStructure.TIM_Period=65535;  
	//���ϼ���	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/*������ģʽ*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	/*�Ƚ��˲���*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	
	TIM_ICInitStructure.TIM_ICFilter = 7; 
	/*��ʼ����ʱ��4*/
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	
	TIM_ICInitStructure.TIM_ICFilter = 7; 
	/*��ʼ����ʱ��4*/
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	
	//���TIM�ĸ��±�־λ
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);      
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	/*��������ʼ��*/
	TIM_SetCounter(TIM4,0);     
	TIM_Cmd(TIM4, ENABLE); 
}




/**************************************************************************
�������ܣ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
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




