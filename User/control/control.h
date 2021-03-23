#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f4xx.h"

#define USING_PI_SPEED    1      //�ٶȿ���ʹ�ñջ�PI������Ϊ1��������Ϊ0    
#define POSITON_CONTROL   1


//PI��������������
#define KP          0.003
#define KI          0.03


//�����״̬
#define CW          1            //��ת
#define CCW         0            //��ת


/*������Ʋ����ṹ��*/
typedef struct {
	volatile double SetSpeed;         //�ٶ��趨ֵ
	volatile double Speed_FBK;        //�ٶȷ���ֵ
	volatile double PreError;         //��һ�ٶ�ƫ��
	volatile double CurError;         //��ǰ�ٶ�ƫ��
	volatile double FREQ_Change;      //Ƶ�ʸı�ֵ
	volatile double FREQ_Sum;         //���Ƶ��
	
	volatile double FBKPosition;    //λ�÷���ֵ
	volatile double Pos_Change;      //λ�øı�ֵ
	volatile int16_t count1,count2;
	uint8_t Speed_Up_Flag;
	int32_t Angle_Pre;                 //��һ�仯������ֵ
	int32_t Angle_Cur;                 //��ǰ����������ֵ
	int32_t Angle_Change;              //�������ı�ֵ
}Motor_Ctrl;









#endif
