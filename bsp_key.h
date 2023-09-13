#ifndef BSP_KEY_H
#define BSP_KEY_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_KEY_RCU RCU_GPIOA
#define BSP_KEY_PORT GPIOA
#define BSP_KEY_PIN GPIO_PIN_0




#endif



void key_config(void);
FlagStatus key_scanf(void);

