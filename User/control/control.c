#include "./control/control.h"
#include "./PWM/PWM.h"
#include "./encoder/encoder.h"
#include "./usart/bsp_usart.h"
#include <math.h>
/**
 *    超声电机速度控制采用增量式PI控制，采样周期为5ms
 *
 */
 
//PI控制器初始化

//double SetSpeed1=3,SetSpeed2=3;             //预设定的速度值40r/min              //   !!!!

double Speed_Opt[21]={4,4.03693,4.14683,4.32698,4.57295,4.87868,5.23664,5.63803,6.07295,6.5307,7,
                       7.4693,7.92705,8.36197,8.76336,9.12132,9.42705,9.67302,9.85317,9.96307,10};  // !!!


//double Speed_Opt1[21]={9,8.96307,8.85317,8.67302,8.42705,8.12132,7.76336,7.36197,6.92705,6.4693,6,
//                       5.5307,5.07295,4.63803,4.23664,3.87868,3.57295,3.32698,3.14683,3.03693,3};
					   
double SetPosition1=-5;    //设定的电机1、2转角，单位为度，基准位置为竖直方向，顺时针为正，逆时针为负
					   
double SetPosition2=0;    //设定的电机1、2转角，单位为度，基准位置为竖直方向，顺时针为正，逆时针为负


//uint8_t Motor1_St=CW;      //默认打开PWM1时，电机为正转状态
//uint8_t Motor2_St=CW;      //默认打开PWM2时，电机为正转状态
////电机的状态
////#define CW    1          //正转
////#define CCW   0          //反转


static void Speed_Ctrl(Motor_Ctrl *Motor);
static void Positon_Ctrl(Motor_Ctrl *Motor,double SetPosition);
/*
 * 定时器3中断处理函数，每5ms产生一次中断
 *
 */
void  TIM3_IRQHandler (void)
{
	static volatile int16_t i=0;
	static Motor_Ctrl Motor1={
		.SetSpeed=4,
		.Speed_FBK=0,
		.PreError=0,
		.CurError=0,
		.FREQ_Change=0,
		.FREQ_Sum=46.1,
		.FBKPosition=0,
		.Pos_Change=0,
		.count1=0,
		.count2=19,
		.Speed_Up_Flag=0,
		.Angle_Pre=0,
		.Angle_Cur=0,
		.Angle_Change=0,
	};
	static Motor_Ctrl Motor2={
		.SetSpeed=4,
		.Speed_FBK=0,
		.PreError=0,
		.CurError=0,
		.FREQ_Change=0,
		.FREQ_Sum=45.7,
		.FBKPosition=0,
		.Pos_Change=0,
		.count1=0,
		.count2=19,
		.Speed_Up_Flag=0,
		.Angle_Pre=0,
		.Angle_Cur=0,
		.Angle_Change=0,
	};
		
		
		
		
	if ( TIM_GetITStatus( TIM3, TIM_IT_Update) != RESET ) 
	{	
		
		/*****************  PI控制器主体函数  ******************/	
		/*获取当前转速并更新上次转速*/
		Motor1.Angle_Cur=Read_Encoder1();                 //获取当前编码器1测得的值

		Motor1.Angle_Change = Motor1.Angle_Cur - Motor1.Angle_Pre;
		
		if(Motor1.Angle_Change < 0)                       //当电机正转时，<0,则TIM2计数器溢出,
			Motor1.Angle_Change = Motor1.Angle_Change +65536;      //编码器计数值最大为65535
		
		if(Motor1.Angle_Change >30000)                     //当电机反转时，>30000，则TIM2计数器溢出
			Motor1.Angle_Change =65536-Motor1.Angle_Change;
		
		Motor1.Speed_FBK = Motor1.Angle_Change*3;//1.2;               //f=Angel_Change1*60/分辨率(10000)*Sampling_Period  单位r/min
		
		Motor1.Angle_Pre = Motor1.Angle_Cur;                       //更新上次编码器1测得的值

		Motor2.Angle_Cur = Read_Encoder2();                 //获取当前编码器1测得的值

		Motor2.Angle_Change = Motor2.Angle_Cur - Motor2.Angle_Pre;
		
		if(Motor2.Angle_Change < 0)                       //当电机正转时，<0,则TIM2计数器溢出,
			Motor2.Angle_Change = Motor2.Angle_Change+65536;      //编码器计数值最大为65535
		
		if(Motor2.Angle_Change >30000)                     //当电机反转时，>30000，则TIM2计数器溢出
			Motor2.Angle_Change =65536-Motor2.Angle_Change;
		
		Motor2.Speed_FBK =Motor2.Angle_Change*3;//1.2;               //f=Angel_Change1*60/分辨率*Sampling_Period  单位r/min
		
		Motor2.Angle_Pre = Motor2.Angle_Cur;  

		/*对速度进行PI控制*/
		#if(USING_PI_SPEED) 
		{		
			if(Motor1.Angle_Change !=0){
				Speed_Ctrl(&Motor1);
				PWM1_SetFREQ(Motor1.FREQ_Sum);                 //改变电机1的PWM频率
			}
			/*电机2速度控制*/
			if(Motor2.Angle_Change!=0){
				Speed_Ctrl(&Motor2);
				PWM2_SetFREQ(Motor2.FREQ_Sum);                 //改变电机1的PWM频率
			}
		}
		#endif
		#if(POSITON_CONTROL)
		{	
			Positon_Ctrl(&Motor1,SetPosition1);
			Positon_Ctrl(&Motor2,SetPosition2);
		}
		#endif

//		if(i<200 && i%2==0)                //1s
//		{
//			printf("%.3f\t",Motor1.FBKPosition);
//			printf("%.3f\n",Motor2.FBKPosition);
//		}
//		++i;
	}	
	TIM_ClearITPendingBit(TIM3 , TIM_IT_Update);	
}


static void Speed_Ctrl(Motor_Ctrl *Motor)
{
	Motor->CurError = Motor->Speed_FBK - Motor->SetSpeed;           //当前速度偏差
	
	Motor->FREQ_Change =KP*(Motor->CurError - Motor->PreError)+KI*Motor->CurError;//KP*[e(k)-e(k-1)]+KI*T*e(k)=输出增量
	
	Motor->PreError=Motor->CurError;                     //更新上次偏差值
	
	Motor->FREQ_Sum=Motor->FREQ_Sum+Motor->FREQ_Change;        //获得PI控制器的输出频率值
	
	if(Motor->FREQ_Sum>=50)                        //频率限幅
		Motor->FREQ_Sum=50;
	if(Motor->FREQ_Sum<=42)
		Motor->FREQ_Sum=42;
}
static void Positon_Ctrl(Motor_Ctrl *Motor,double SetPosition)
{
	if(SetPosition>90)                   //限制转动角度
		SetPosition=90;
	if(SetPosition<-90)
		SetPosition=-90;
	
	if(Motor->Angle_Cur>30000)                  //设定角度小于0时，Angel_Cur1会大于60000
		Motor->Angle_Cur=Motor->Angle_Cur-65536;      //此时角度为负
	
	
	Motor->FBKPosition=(double)Motor->Angle_Cur*0.09;//Angel_Cur1*360/4000;
	
	Motor->Pos_Change=fabs(fabs(SetPosition)-fabs(Motor->FBKPosition));
	
	if(Motor->Pos_Change>2)
	{							
		if(Motor->Pos_Change < 10 && Motor->Speed_Up_Flag==0)
		{
			Motor->SetSpeed=4;
		}
		
		if(Motor->Pos_Change >= 10 || Motor->Speed_Up_Flag==1) 
		{
			if(Motor->count1==0)
				Motor->Speed_Up_Flag=1;
			if(Motor->count1<20)
				Motor->SetSpeed=Speed_Opt[++Motor->count1];
		}
		
		if(Motor->Pos_Change<=8 && Motor->Speed_Up_Flag==1)
		{
			if(Motor->count2>0)
				Motor->SetSpeed=Speed_Opt[--Motor->count2];
			if(Motor->count2==0)
				Motor->Speed_Up_Flag=0;
		}

	}
	else if(Motor->Pos_Change>0.15)
	{
		Motor->SetSpeed=4;
	}
	else
	{
		if(SetPosition==SetPosition1) {
			PWM1(OFF);
		}
		if(SetPosition==SetPosition2) {
			PWM2(OFF);
		}
	}
}


/**********************************    END OF FILE    ******************************/
