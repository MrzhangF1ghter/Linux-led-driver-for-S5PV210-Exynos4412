#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "led.h"

struct led_ops{
	int leds;
	int operation;
};
struct led_ops led_ops1;

int main(int argc, char ** argv)
{
	int fd = open("/dev/led",O_RDWR);
	if(fd<0)
	{
		perror("open error!");
		exit(-1);
	}

	while(1)
	{
		for(val=1;val<=4;val++)
		{
			led_ops1.leds=val;
			led_ops1.operation=LED_ON;
			ioctl(fd,LED_OPERATION,&led_ops1);
			printf("app:led%d on!\n",led_ops1.leds);
			sleep(1);
		}
	}
	return 0;
}
