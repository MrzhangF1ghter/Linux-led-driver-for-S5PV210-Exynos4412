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
	int val;
	int fd = open("/dev/led_f1ghter",O_RDWR);
	if(fd<0)
	{
		perror("open error!");
		exit(-1);
	}
	printf("usage:./leds <led_no> <1/0>");
	if(argv[1]<1||argv[1]>4)
	{
		printf("led val should between 1~4.led值应为1到4之间");
		return -1;	
	}
	if(argv[2]!=0||argv[2]!=1)
	{
		printf("led on input 1,to turn off,input 0.打开led输入1,关闭输入0");
		return -1;	
	}
		
	led_ops1.leds=argv[1];
	led_ops1.operation=argv[2];

	ioctl(fd,LED_OPERATION,&led_ops1);
	printf("app:led%d on!\n",led_ops1.leds);
	sleep(5);
	printf("app:leds flow!\n",led_ops1.leds);
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

