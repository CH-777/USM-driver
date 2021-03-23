#ifndef __PWM_H
#define __PWM_H

#include "stm32f4xx.h"

/*************************PWM1********************************/
/* ��ʱ�� */
#define TIM1_CLK       		    RCC_APB2Periph_TIM1

/* TIM1ͨ��1���PWMA����:PE9 */
#define PWM1_A_PIN        	    GPIO_Pin_9              
#define PWM1_A_GPIO		    	GPIOE                      
#define PWM1_A_GPIO_CLK        RCC_AHB1Periph_GPIOE
#define PWM1_A_PINSOURCE		GPIO_PinSource9
#define PWM1_A_AF			    GPIO_AF_TIM1

/* TIM1ͨ��1�������PWMB����:PE8 */
#define PWM1_B_PIN             GPIO_Pin_8              
#define PWM1_B_GPIO		      	GPIOE
#define PWM1_B_GPIO_CLK       	RCC_AHB1Periph_GPIOE
#define PWM1_B_PINSOURCE		GPIO_PinSource8
#define PWM1_B_AF				GPIO_AF_TIM1

/* TIM1ͨ��2���PWMC����:PE11 */
#define PWM1_C_PIN        	    GPIO_Pin_11              
#define PWM1_C_GPIO		    	GPIOE                      
#define PWM1_C_GPIO_CLK        RCC_AHB1Periph_GPIOE
#define PWM1_C_PINSOURCE	    GPIO_PinSource11
#define PWM1_C_AF			    GPIO_AF_TIM1

/* TIM1ͨ��2�������PWMD����:PE10 */
#define PWM1_D_PIN        	    GPIO_Pin_10              
#define PWM1_D_GPIO		    	GPIOE                      
#define PWM1_D_GPIO_CLK        RCC_AHB1Periph_GPIOE
#define PWM1_D_PINSOURCE	    GPIO_PinSource10
#define PWM1_D_AF			    GPIO_AF_TIM1

/* TIM1��·��������:PB12(�͵�ƽ��Ч) */
#define BKIN1_PIN              GPIO_Pin_12
#define BKIN1_GPIO		        GPIOB
#define BKIN1_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define BKIN1_PINSOURCE	  		GPIO_PinSource12
#define BKIN1_AF				GPIO_AF_TIM1


/*��·Դ����һ��IO(PA15)��Ϊ��·Դ����ʼʱ����ߵ�ƽ��Ҫ��·ʱ����͵�ƽ*/
#define BKIN1_SOURCE_PIN        GPIO_Pin_15
#define BKIN1_SOURCE_GPIO       GPIOA
#define BKIN1_SOURCE_GPIO_CLK   RCC_AHB1Periph_GPIOA
#define BKIN1_SOURCE_PINSOURCE  GPIO_PinSource15

/**********************************  PWM2   **********************************/
					/* ��ʱ�� */
#define TIM8_CLK       		    RCC_APB2Periph_TIM8

/* TIM8ͨ��1���PWMA����:PC6 */
#define PWM2_A_PIN        	    GPIO_Pin_6              
#define PWM2_A_GPIO		    	GPIOC                      
#define PWM2_A_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define PWM2_A_PINSOURCE	    GPIO_PinSource6
#define PWM2_A_AF		        GPIO_AF_TIM8

/* TIM8ͨ��1�������PWMB����:PA7 */
#define PWM2_B_PIN             GPIO_Pin_7
#define PWM2_B_GPIO		      	GPIOA
#define PWM2_B_GPIO_CLK       	RCC_AHB1Periph_GPIOA
#define PWM2_B_PINSOURCE		GPIO_PinSource7
#define PWM2_B_AF				GPIO_AF_TIM8

/* TIM8ͨ��2���PWMC����:PC7 */
#define PWM2_C_PIN        	    GPIO_Pin_7              
#define PWM2_C_GPIO		    	GPIOC                      
#define PWM2_C_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define PWM2_C_PINSOURCE	    GPIO_PinSource7
#define PWM2_C_AF	            GPIO_AF_TIM8

/* TIM8ͨ��2�������PWMD����:PB14 */
#define PWM2_D_PIN        	    GPIO_Pin_14              
#define PWM2_D_GPIO		    	GPIOB                
#define PWM2_D_GPIO_CLK        RCC_AHB1Periph_GPIOB
#define PWM2_D_PINSOURCE	    GPIO_PinSource14
#define PWM2_D_AF		        GPIO_AF_TIM8

/* TIM8��·��������:PA6 */
#define BKIN2_PIN              GPIO_Pin_6              
#define BKIN2_GPIO		        GPIOA                      
#define BKIN2_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define BKIN2_PINSOURCE	  		GPIO_PinSource6
#define BKIN2_AF				GPIO_AF_TIM8

/*��·Դ����һ��IO(PG11)��Ϊ��·Դ����ʼʱ����ߵ�ƽ��Ҫ��·ʱ����͵�ƽ*/
#define BKIN2_SOURCE_PIN        GPIO_Pin_11
#define BKIN2_SOURCE_GPIO       GPIOG
#define BKIN2_SOURCE_GPIO_CLK   RCC_AHB1Periph_GPIOG
#define BKIN2_SOURCE_PINSOURCE  GPIO_PinSource11



/*
 *  ����PWM�ķ�����ͨ����·���ſ��ƣ�Ĭ��Ϊ�ߵ�ƽΪͨ
 *  �͵�ƽʱֹͣ����PWM��
 *
 */
#define ON  1
#define OFF 0

//Ĭ�ϴ�PWMʱ�����Ϊ��ת״̬
#define PWM1(a)  if(a) \
						GPIO_SetBits(BKIN1_SOURCE_GPIO,BKIN1_SOURCE_PIN);\
					else  \
						GPIO_ResetBits(BKIN1_SOURCE_GPIO,BKIN1_SOURCE_PIN)

#define PWM2(a)  if(a) \
						GPIO_SetBits(BKIN2_SOURCE_GPIO,BKIN2_SOURCE_PIN);\
					else  \
						GPIO_ResetBits(BKIN2_SOURCE_GPIO,BKIN2_SOURCE_PIN)
					
/*��ת*/
#define PWM1_CW()   PWM1_SetDPHS(90)
/*��ת*/
#define PWM1_CCW()   PWM1_SetDPHS(-90)
/*��������״̬*/
#define PWM1_Xuanfu()    PWM1_SetDPHS(0)


/*��ת*/
#define PWM2_CW()  PWM2_SetDPHS(90)     
/*��ת*/
#define PWM2_CCW()  PWM2_SetDPHS(-90)
/*��������״̬*/
#define PWM2_Xuanfu()   PWM2_SetDPHS(0)					
					
					
void PWM1_TIM1_Config(void);
void PWM2_TIM8_Config(void);     //PWM2��ʼ������ʼ����Ƶ��Ϊ42kHz����λ��Ϊ90�ȣ�Ĭ��ֹͣPWM��
void PWM1_SetFREQ(double FREQ);  //����PWM1��Ƶ�ʣ���λΪkHz
void PWM2_SetFREQ(double FREQ);  //����PWM2��Ƶ�ʣ���λΪkHz
void PWM1_SetDPHS(double DPHS);
void PWM2_SetDPHS(double DPHS);  //����PWM2����λ��


#endif

