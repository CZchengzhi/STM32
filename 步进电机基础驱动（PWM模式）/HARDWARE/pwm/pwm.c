#include "pwm.h"
void Pin_Init(uint16_t arr, uint16_t  psc, uint16_t ccr)
{
	GPIO_InitTypeDef GPIO_InitStr;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
	TIM_OCInitTypeDef TIM_OCInitStr;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);//使能GPIOF的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);//使能GPIOB、端口复用时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器
	
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStr);
	
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, &GPIO_InitStr);
	
	TIM_TimeBaseInitStr.TIM_ClockDivision  = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStr.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStr.TIM_Period = arr;
	TIM_TimeBaseInitStr.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStr);
	
	TIM_OCStructInit(&TIM_OCInitStr);
	TIM_OCInitStr.TIM_OCMode = TIM_OCMode_PWM1;//PWM模式一
	TIM_OCInitStr.TIM_OCPolarity = TIM_OCPolarity_High;//极性高
	TIM_OCInitStr.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStr.TIM_Pulse = ccr;
	TIM_OC1Init(TIM4, &TIM_OCInitStr);
	
	//设置PF14、15引脚为高电平，此时DIR有效，顺时针，ENA有效，使能
	GPIO_SetBits(GPIOF, GPIO_Pin_14);
	GPIO_SetBits(GPIOF, GPIO_Pin_14);
	
	
}
void Start(void)
{
	TIM_Cmd(TIM4, ENABLE);
}
void Stop(void)
{
	TIM_Cmd(TIM4, DISABLE);
}

void Dir(u8 dir)
{
	if (dir==1)
		GPIO_SetBits(GPIOF, GPIO_Pin_14);
	else if (dir==0)
		GPIO_ResetBits(GPIOF, GPIO_Pin_14);
	
}

