#ifndef __PWM_H
#define __PWM_H

#include "stm32f4xx.h"

/*************************PWM1********************************/
/* 定时器 */
#define TIM1_CLK       		    RCC_APB2Periph_TIM1

/* TIM1通道1输出PWMA引脚:PE9 */
#define PWM1_A_PIN        	    GPIO_Pin_9              
#define PWM1_A_GPIO		    	GPIOE                      
#define PWM1_A_GPIO_CLK        RCC_AHB1Periph_GPIOE
#define PWM1_A_PINSOURCE		GPIO_PinSource9
#define PWM1_A_AF			    GPIO_AF_TIM1

/* TIM1通道1互补输出PWMB引脚:PE8 */
#define PWM1_B_PIN             GPIO_Pin_8              
#define PWM1_B_GPIO		      	GPIOE
#define PWM1_B_GPIO_CLK       	RCC_AHB1Periph_GPIOE
#define PWM1_B_PINSOURCE		GPIO_PinSource8
#define PWM1_B_AF				GPIO_AF_TIM1

/* TIM1通道2输出PWMC引脚:PE11 */
#define PWM1_C_PIN        	    GPIO_Pin_11              
#define PWM1_C_GPIO		    	GPIOE                      
#define PWM1_C_GPIO_CLK        RCC_AHB1Periph_GPIOE
#define PWM1_C_PINSOURCE	    GPIO_PinSource11
#define PWM1_C_AF			    GPIO_AF_TIM1

/* TIM1通道2互补输出PWMD引脚:PE10 */
#define PWM1_D_PIN        	    GPIO_Pin_10              
#define PWM1_D_GPIO		    	GPIOE                      
#define PWM1_D_GPIO_CLK        RCC_AHB1Periph_GPIOE
#define PWM1_D_PINSOURCE	    GPIO_PinSource10
#define PWM1_D_AF			    GPIO_AF_TIM1

/* TIM1断路输入引脚:PB12(低电平有效) */
#define BKIN1_PIN              GPIO_Pin_12
#define BKIN1_GPIO		        GPIOB
#define BKIN1_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define BKIN1_PINSOURCE	  		GPIO_PinSource12
#define BKIN1_AF				GPIO_AF_TIM1


/*断路源：将一个IO(PA15)作为断路源，初始时输出高电平，要断路时输出低电平*/
#define BKIN1_SOURCE_PIN        GPIO_Pin_15
#define BKIN1_SOURCE_GPIO       GPIOA
#define BKIN1_SOURCE_GPIO_CLK   RCC_AHB1Periph_GPIOA
#define BKIN1_SOURCE_PINSOURCE  GPIO_PinSource15

/**********************************  PWM2   **********************************/
					/* 定时器 */
#define TIM8_CLK       		    RCC_APB2Periph_TIM8

/* TIM8通道1输出PWMA引脚:PC6 */
#define PWM2_A_PIN        	    GPIO_Pin_6              
#define PWM2_A_GPIO		    	GPIOC                      
#define PWM2_A_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define PWM2_A_PINSOURCE	    GPIO_PinSource6
#define PWM2_A_AF		        GPIO_AF_TIM8

/* TIM8通道1互补输出PWMB引脚:PA7 */
#define PWM2_B_PIN             GPIO_Pin_7
#define PWM2_B_GPIO		      	GPIOA
#define PWM2_B_GPIO_CLK       	RCC_AHB1Periph_GPIOA
#define PWM2_B_PINSOURCE		GPIO_PinSource7
#define PWM2_B_AF				GPIO_AF_TIM8

/* TIM8通道2输出PWMC引脚:PC7 */
#define PWM2_C_PIN        	    GPIO_Pin_7              
#define PWM2_C_GPIO		    	GPIOC                      
#define PWM2_C_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define PWM2_C_PINSOURCE	    GPIO_PinSource7
#define PWM2_C_AF	            GPIO_AF_TIM8

/* TIM8通道2互补输出PWMD引脚:PB14 */
#define PWM2_D_PIN        	    GPIO_Pin_14              
#define PWM2_D_GPIO		    	GPIOB                
#define PWM2_D_GPIO_CLK        RCC_AHB1Periph_GPIOB
#define PWM2_D_PINSOURCE	    GPIO_PinSource14
#define PWM2_D_AF		        GPIO_AF_TIM8

/* TIM8断路输入引脚:PA6 */
#define BKIN2_PIN              GPIO_Pin_6              
#define BKIN2_GPIO		        GPIOA                      
#define BKIN2_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define BKIN2_PINSOURCE	  		GPIO_PinSource6
#define BKIN2_AF				GPIO_AF_TIM8

/*断路源：将一个IO(PG11)作为断路源，初始时输出高电平，要断路时输出低电平*/
#define BKIN2_SOURCE_PIN        GPIO_Pin_11
#define BKIN2_SOURCE_GPIO       GPIOG
#define BKIN2_SOURCE_GPIO_CLK   RCC_AHB1Periph_GPIOG
#define BKIN2_SOURCE_PINSOURCE  GPIO_PinSource11



/*
 *  控制PWM的发生，通过短路引脚控制，默认为高电平为通
 *  低电平时停止产生PWM波
 *
 */
#define ON  1
#define OFF 0

//默认打开PWM时，电机为正转状态
#define PWM1(a)  if(a) \
						GPIO_SetBits(BKIN1_SOURCE_GPIO,BKIN1_SOURCE_PIN);\
					else  \
						GPIO_ResetBits(BKIN1_SOURCE_GPIO,BKIN1_SOURCE_PIN)

#define PWM2(a)  if(a) \
						GPIO_SetBits(BKIN2_SOURCE_GPIO,BKIN2_SOURCE_PIN);\
					else  \
						GPIO_ResetBits(BKIN2_SOURCE_GPIO,BKIN2_SOURCE_PIN)
					
/*正转*/
#define PWM1_CW()   PWM1_SetDPHS(90)
/*反转*/
#define PWM1_CCW()   PWM1_SetDPHS(-90)
/*超声悬浮状态*/
#define PWM1_Xuanfu()    PWM1_SetDPHS(0)


/*正转*/
#define PWM2_CW()  PWM2_SetDPHS(90)     
/*反转*/
#define PWM2_CCW()  PWM2_SetDPHS(-90)
/*超声悬浮状态*/
#define PWM2_Xuanfu()   PWM2_SetDPHS(0)					
					
					
void PWM1_TIM1_Config(void);
void PWM2_TIM8_Config(void);     //PWM2初始化，初始设置频率为42kHz，相位差为90度，默认停止PWM波
void PWM1_SetFREQ(double FREQ);  //设置PWM1的频率，单位为kHz
void PWM2_SetFREQ(double FREQ);  //设置PWM2的频率，单位为kHz
void PWM1_SetDPHS(double DPHS);
void PWM2_SetDPHS(double DPHS);  //设置PWM2的相位差


#endif

