
//time.c
#include "timer.h"
#include "usart.h"
#include "sys.h"
 
 
//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM4_PWM_Init(u16 arr,u16 psc)
{
 GPIO_InitTypeDef GPIO_InitStrue;
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 TIM_OCInitTypeDef TIM_OCInitStructure;
 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   //使能定时器4时钟
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
 //GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);//=Timer4部分重映射  TIM4_CH3->PB9 
 //设置该引脚为复用输出功能,输出TIM4 CH3的PWM脉冲波形    GPIOB.9
 GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;   //复用推挽输出
 GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;  //TIM_CH3
 GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
 GPIO_Init(GPIOB,&GPIO_InitStrue);   //初始化该该端口 
 
    //初始化TIM4
 TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
 TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
 TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
 TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
    //初始化TIM4 Channel2 PWM模式
 TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low; //High --> Low //输出极性:TIM输出比较极性低
 TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //比较输出使能
 TIM_OC4Init(TIM4,&TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC4
 
 TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能TIM在CH3上CCR4上的预装载寄存器
 TIM_Cmd(TIM4,ENABLE);  //使能TIM4
}
