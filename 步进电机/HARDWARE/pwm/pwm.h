#ifndef __BSP_STEPMOTOR_H
#define __BSP_STEPMOTOR_H

#include "stm32f10x.h"

//共阴极接法
//接线：PF14--->DIR PF15--->ENA PB6--->PUL

//初始化定时器、引脚
void Pin_Init(uint16_t arr, uint16_t  psc, uint16_t ccr);

//使能TIM4从而使得电机转动
void Start(void);

//失能TIM4从而使得电机转动
void Stop(void);

//改变dir引脚从而改变旋转方向
void Dir(u8 dir);

#endif


