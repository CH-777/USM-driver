#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f4xx.h"

#define USING_PI_SPEED    1      //速度控制使用闭环PI控制设为1，开环设为0    
#define POSITON_CONTROL   1


//PI控制器参数定义
#define KP          0.003
#define KI          0.03


//电机的状态
#define CW          1            //正转
#define CCW         0            //反转


/*电机控制参数结构体*/
typedef struct {
	volatile double SetSpeed;         //速度设定值
	volatile double Speed_FBK;        //速度反馈值
	volatile double PreError;         //上一速度偏差
	volatile double CurError;         //当前速度偏差
	volatile double FREQ_Change;      //频率改变值
	volatile double FREQ_Sum;         //输出频率
	
	volatile double FBKPosition;    //位置反馈值
	volatile double Pos_Change;      //位置改变值
	volatile int16_t count1,count2;
	uint8_t Speed_Up_Flag;
	int32_t Angle_Pre;                 //上一变化器测量值
	int32_t Angle_Cur;                 //当前编码器测量值
	int32_t Angle_Change;              //编码器改变值
}Motor_Ctrl;









#endif
