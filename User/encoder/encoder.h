#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f4xx.h"

#define TIM2_CLK           RCC_APB1Periph_TIM2
#define TIM4_CLK           RCC_APB1Periph_TIM4


#define ENCODER_PERIOD     2500

/*编码器A、B相IO口PA5,PB3定义*/
#define ENCODER1_A_CLK     RCC_AHB1Periph_GPIOA
#define ENCODER1_A_GPIO    GPIOA
#define ENCODER1_A_PIN     GPIO_Pin_5
#define ENCODER1_A_SOURCE  GPIO_PinSource5

#define ENCODER1_B_CLK     RCC_AHB1Periph_GPIOB
#define ENCODER1_B_GPIO    GPIOB
#define ENCODER1_B_PIN     GPIO_Pin_3
#define ENCODER1_B_SOURCE  GPIO_PinSource3

/*编码器2的A、B相IO口PD12,PD13定义*/
#define ENCODER2_A_CLK     RCC_AHB1Periph_GPIOD
#define ENCODER2_A_GPIO    GPIOD
#define ENCODER2_A_PIN     GPIO_Pin_12
#define ENCODER2_A_SOURCE  GPIO_PinSource12

#define ENCODER2_B_CLK     RCC_AHB1Periph_GPIOD
#define ENCODER2_B_GPIO    GPIOD
#define ENCODER2_B_PIN     GPIO_Pin_13
#define ENCODER2_B_SOURCE  GPIO_PinSource13

void Encoder1_Init_TIM2(void);
uint16_t Read_Encoder1(void);

void Encoder2_Init_TIM4(void);
uint16_t Read_Encoder2(void);

#endif
