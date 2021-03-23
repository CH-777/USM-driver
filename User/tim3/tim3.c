#include "./tim3/tim3.h"

/*
 *  ͨ�ö�ʱ��3ÿ5ms����һ���ж�
 *  
 */

static void TIM3_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ4
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);		
	// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 	
	// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
	// ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIM3_CLK,
	RCC_APB1PeriphClockCmd(TIM3_CLK, ENABLE); 

	/* �ۼ� TIM_Period�������һ�����»����жϣ�*/		
	//5ms����һ���жϣ���TIM_Period=5*10-1
	TIM_TimeBaseStructure.TIM_Period = 50-1;       
	
	// ͨ�ÿ��ƶ�ʱ��ʱ��ԴTIM3CLK = HCLK/2=84MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIM3CLK/(TIM_Prescaler+1)=10000Hz��0.1ms����һ��
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;	
	// ����ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// ������ʽ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIM3
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	// �����ʱ�������жϱ�־λ
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	
	// ������ʱ�������ж�
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3, ENABLE);	
}

/**
  * @brief  ��ʼ���߼����ƶ�ʱ����ʱ��5ms����һ���ж�
  * @param  tim3�жϿ��ƺ�����controlģ����
  * @retval 
  */
void TIM3_Config(void)
{
	TIM3_NVIC_Configuration();     //�жϳ�ʼ��	
  
	TIM_Mode_Config();             //ģʽ����

}
