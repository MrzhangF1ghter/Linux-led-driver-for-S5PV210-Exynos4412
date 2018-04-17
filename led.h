#ifndef __BTN_H
#define __BTN_H
#include <linux/ioctl.h>
#define LED_TYPE 'l'

#define LED_IORESET _IO(LED_TYPE,0)
#define LED_OPERATION _IOW(LED_TYPE,3,char)
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define ALL_LED 0
#define LED_ON 1
#define LED_OFF 0
#define LED_MAXNUM 4

#endif
