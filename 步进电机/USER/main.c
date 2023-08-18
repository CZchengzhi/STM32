#include "stm32f10x.h"
#include "key.h"
#include "pwm.h"
#include "delay.h"


int main(void)
{
	u8 key = 0, dir=0;
	
	KEY_Init();
	delay_init();
	Pin_Init(100-1, 720-1, 50);
	while(1)
	{
		key = KEY_Scan(0);
		if (key  == KEY0_PRES)
			Start();
		else if (key == KEY1_PRES)
			Stop();
		else if (key == WKUP_PRES)
		{
			dir =! dir;
			Dir(dir);
			
		}
		delay_ms(10);
		
		
	}
}
