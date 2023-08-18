
//time.c
#include "timer.h"
#include "usart.h"
#include "sys.h"
 
 
//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_PWM_Init(u16 arr,u16 psc)
{
 GPIO_InitTypeDef GPIO_InitStrue;
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 TIM_OCInitTypeDef TIM_OCInitStructure;
 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   //ʹ�ܶ�ʱ��4ʱ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
 //GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);//=Timer4������ӳ��  TIM4_CH3->PB9 
 //���ø�����Ϊ�����������,���TIM4 CH3��PWM���岨��    GPIOB.9
 GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;   //�����������
 GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;  //TIM_CH3
 GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
 GPIO_Init(GPIOB,&GPIO_InitStrue);   //��ʼ���øö˿� 
 
    //��ʼ��TIM4
 TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
 TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
 TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
 TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
    //��ʼ��TIM4 Channel2 PWMģʽ
 TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low; //High --> Low //�������:TIM����Ƚϼ��Ե�
 TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //�Ƚ����ʹ��
 TIM_OC4Init(TIM4,&TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC4
 
 TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIM��CH3��CCR4�ϵ�Ԥװ�ؼĴ���
 TIM_Cmd(TIM4,ENABLE);  //ʹ��TIM4
}
