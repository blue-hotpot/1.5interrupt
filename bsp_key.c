#include "bsp_key.h"
#include <stdio.h>
#include "bsp_usart.h"


void key_config(void)
{
	rcu_periph_clock_enable(BSP_KEY_RCU);
	rcu_periph_clock_enable(RCU_SYSCFG);//系统开启
	gpio_mode_set(BSP_KEY_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN,BSP_KEY_PIN);
	nvic_irq_enable(EXTI0_IRQn,3U,3U);//设置中断位
	syscfg_exti_line_config(EXTI_SOURCE_GPIOA,EXTI_SOURCE_PIN0);//系统与中断口相连
	
	exti_init(EXTI_0,EXTI_INTERRUPT,EXTI_TRIG_BOTH);//中断初始化
	exti_interrupt_enable(EXTI_0);//中断开启
	exti_interrupt_flag_clear(EXTI_0);
}

void EXTI0_IRQHandler(void)
{
	if(exti_interrupt_flag_get(EXTI_0)==SET)
	{
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN)==SET)
		{
			printf("key press\r\t");
			gpio_bit_toggle(GPIOG,GPIO_PIN_3);
		}
		else
		{
			printf("key release\r\n");
		}
		exti_interrupt_flag_clear(EXTI_0);
	}
}


FlagStatus key_scanf(void)
{
	if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN)==SET)
	{
		delay_1ms(20);
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN)==SET)
		{
			return SET;
		}
	}
	return RESET;
	
}




