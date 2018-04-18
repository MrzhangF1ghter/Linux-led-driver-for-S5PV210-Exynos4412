#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <mach/hardware.h>
#include <linux/gpio.h>
#include<linux/miscdevice.h>

#include <mach/map.h>
#include <mach/gpio.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>

#include "led.h"
#define GEC210

#ifdef GEC210
#define CON_REG 0xE0200280
#define DAT_REG 0xE0200284
#endif

#ifdef TINY4412
#define CON_REG 0x110002E0
#define DAT_REG 0x110002E4
#endif

unsigned long *con_reg = NULL;
unsigned long *dat_reg = NULL;

struct led_ops{
	int leds;
	int operation;
};
struct led_ops led_operation;

static int led_drv_open(struct inode *inode, struct file *file)
{
	*con_reg=(*con_reg&(~0xffff))|(0x1111);
	*dat_reg&=(~0xff);
	printk("led device opened!support ioctl writen by MrzhangF1ghter\n");
	printk("usage:./leds <led_no> <1/0>");
	return 0;
}

static int led_drv_close(struct inode *inode, struct file *file)
{
	
	printk("led device closed!\n");
	return 0;
}

static int led_drv_read(struct file *filp, char __user *buff,size_t count, loff_t *offp)
{
	printk("led device read!\n");
	return 0;
}


static long led_drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	if(_IOC_TYPE(cmd) != LED_IORESET || _IOC_TYPE(cmd) != LED_OPERATION) 
		return - EINVAL;
	if(_IOC_NR(cmd) > LED_MAXNUM) 
		return - EINVAL;
	switch(cmd)
	{
		case LED_IORESET:
			*dat_reg=(*dat_reg&(~0xff))|(0xff);//1111 1111
			printk("LED_IORESET!\n");
			break;
		case LED_OPERATION:
			if(copy_from_user(&led_operation,(struct led_ops*)arg,sizeof(led_operation)))
			{
				printk("wrong val!use struct led_ops to operate");
				return -1;
			}
			switch(led_operation.leds)
			{	
				case LED1:
					switch(led_operation.operation)
					{
						case LED_ON:
							*dat_reg=(*dat_reg&(~0xff))|(0xfe);//1111 1110
							printk("led1 on!\n");
							break;
						case LED_OFF:
							*dat_reg=(*dat_reg|(0x01));//0000 0001
							printk("led1 off!\n");
							break;
					}
				break;
				
				case LED2:
					switch(led_operation.operation)
					{
						case LED_ON:
							*dat_reg=(*dat_reg&(~0xff))|(0xfd);//1111 1101
							printk("led2 on!\n");
							break;
						case LED_OFF:
							*dat_reg=(*dat_reg|(0x02));//0000 0001
							printk("led2 off!\n");
							break;
					}
				break;
				
				case LED3:
					switch(led_operation.operation)
					{
						case LED_ON:
							*dat_reg=(*dat_reg&(~0xff))|(0xfb);//1111 1011
							printk("led3 on!\n");
							break;
						case LED_OFF:
							*dat_reg=(*dat_reg|(0x04));//0000 0001
							printk("led3 off!\n");
							break;
					}
				break;
				
				case LED4:
					switch(led_operation.operation)
					{
						case LED_ON:
							*dat_reg=(*dat_reg&(~0xff))|(0xf7);//1111 0111
							printk("led4 on!\n");
							break;
						case LED_OFF:
							*dat_reg=(*dat_reg|(0x08));//0000 0001
							printk("led4 off!\n");
							break;
					}
				break;
				
				case ALL_LED:
					switch(led_operation.operation)
					{
						case LED_ON:
							*dat_reg=(*dat_reg&(~0xff))|(0xf0);//1111 1110
							printk("all led on!\n");
							break;
						case LED_OFF:
							*dat_reg=(*dat_reg|(0xff));//0000 0001
							printk("all led off!\n");
							break;
					}
				break;
			}
			break;
		default:
			printk("ioctl error cmd!\n");
			return -EINVAL;
	}
	
	return 0;
}
static struct file_operations led_fops = {
	.owner		= THIS_MODULE,
	.open		= led_drv_open,
	.release	= led_drv_close, 
	.read		= led_drv_read,
	.unlocked_ioctl	= led_drv_ioctl,
	
};

static struct miscdevice led_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "led_f1ghter",
	.fops = &led_fops,
};

static int __init led_drv_init(void)
{
	//”≥…‰µÿ÷∑
	con_reg=ioremap(CON_REG,4);
	dat_reg=ioremap(DAT_REG,4);
	
	misc_register(&led_dev);
	
	printk("leds module initialized!support ioctl\n");
	return 0;
}

static void __exit led_drv_exit(void)
{
	*con_reg=*con_reg&(~0xffff);
	*dat_reg&=(~0xff);

	misc_register(&led_dev);
	printk("led uninstalled!support ioctl\n");
}

module_init(led_drv_init);
module_exit(led_drv_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MrzhangF1ghter");

