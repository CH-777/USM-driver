#include "stm32f4xx.h"

#include "./encoder/encoder.h"
#include "./usart/bsp_usart.h"
#include "./systick/bsp_SysTick.h"
#include "./PWM/PWM.h"
#include "./control/control.h"                 //�������ģ��
#include "./tim3/tim3.h"                        //��ʱ���ж�ģ��

/*******************************   ȫ�ֱ���    ********************************/

//extern uint8_t Motor1_St;             //���1������ת״̬
//extern uint8_t Motor2_St;             //���2������״״̬

//extern __IO double PWM1_FREQ;        //PWM1��Ƶ��
//extern __IO double PWM1_DPHS;        //PWM1����·����PWM������λ��
//extern __IO double PWM2_FREQ;        //PWM2��Ƶ��
//extern __IO double PWM2_DPHS;        //PWM2����·����PWM������λ��

/*****************************************************************************/

//�����ʼ������
static void Model_Init(void)
{
	Encoder1_Init_TIM2();      //������1��ʼ��
	Encoder2_Init_TIM4();      //������2��ʼ��
	USARTx_Config();           //����1��ʼ��
	SysTick_Init();            //ϵͳ�δ��ʼ��
	
	PWM1_TIM1_Config();        //PWM1��ʼ����Ĭ��PWM1Ϊ�ر�״̬
	
	PWM1(ON);                  //��PWM1
	PWM2_TIM8_Config();        //PWM2��ʼ����Ĭ��PWM2λ�ر�״̬
	PWM2(ON);                  //��PWM2
	
	TIM3_Config();             //��ʼ����ʱ��3
}

int main(void)
{
	Model_Init();
	PWM1_CCW();
//	PWM2_CCW();
//	printf("Ӳ����ʼ���ɹ�\n");
	while(1)
	{
	
	}
}

/*********************************************END OF FILE**********************/

