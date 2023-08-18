#include "pwm.h"
void Pin_Init(uint16_t arr, uint16_t  psc, uint16_t ccr)
{
	GPIO_InitTypeDef GPIO_InitStr;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
	TIM_OCInitTypeDef TIM_OCInitStr;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);//ʹ��GPIOF��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIOB���˿ڸ���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��
	
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStr);
	
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_AF_PP;//��������
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, &GPIO_InitStr);
	
	TIM_TimeBaseInitStr.TIM_ClockDivision  = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseInitStr.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStr.TIM_Period = arr;
	TIM_TimeBaseInitStr.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStr);
	
	TIM_OCStructInit(&TIM_OCInitStr);
	TIM_OCInitStr.TIM_OCMode = TIM_OCMode_PWM1;//PWMģʽһ
	TIM_OCInitStr.TIM_OCPolarity = TIM_OCPolarity_High;//���Ը�
	TIM_OCInitStr.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStr.TIM_Pulse = ccr;
	TIM_OC1Init(TIM4, &TIM_OCInitStr);
	
	//����PF14��15����Ϊ�ߵ�ƽ����ʱDIR��Ч��˳ʱ�룬ENA��Ч��ʹ��
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

