#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "led.h"

struct led_ops{
	int leds;
	int operation;
};
struct led_ops led_ops1,led_ops2;

int main(int argc, char * argv[])
{
	int val,leds,ops;
	int fd = open("/dev/led_f1ghter",O_RDWR);
	if(fd<0)
	{
		perror("open error!");
		exit(-1);
	}
	if(argc<3)
	{
		printf("command wrong! usage:./leds <led_no> <1/0>\n");
		exit(-1);
	}
	leds = atoi(argv[1]);
	ops =atoi(argv[2]);
	if(leds<1||leds>4)
	{
		printf("led val should between 1~4.\n");
		exit(-1);
	}else if(ops!=0&&ops!=1)
	{
		printf("led on input 1,to turn off,input 0.\n");
		exit(-1);
	}
	//把命令行参数赋值给操作结构体
	led_ops1.leds = leds;
	led_ops1.operation = ops;
	ioctl(fd,LED_OPERATION,&led_ops1);
	printf("app:led%d on!\n",led_ops1.leds);

	sleep(5);
	printf("Flow leds demo\n");
	while(1)
	{
		for(val=1;val<=4;val++)
		{
			led_ops1.leds=val;
			led_ops1.operation=LED_ON;
			ioctl(fd,LED_OPERATION,&led_ops1);
			sleep(1);
		}
	}
	return 0;
}

