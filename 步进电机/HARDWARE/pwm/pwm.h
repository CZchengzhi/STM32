#ifndef __BSP_STEPMOTOR_H
#define __BSP_STEPMOTOR_H

#include "stm32f10x.h"

//�������ӷ�
//���ߣ�PF14--->DIR PF15--->ENA PB6--->PUL

//��ʼ����ʱ��������
void Pin_Init(uint16_t arr, uint16_t  psc, uint16_t ccr);

//ʹ��TIM4�Ӷ�ʹ�õ��ת��
void Start(void);

//ʧ��TIM4�Ӷ�ʹ�õ��ת��
void Stop(void);

//�ı�dir���ŴӶ��ı���ת����
void Dir(u8 dir);

#endif


