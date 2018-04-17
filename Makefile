obj-m +=led_drv.o
all:
	make -C /home/zhang/linux-2.6 M=`pwd` modules
clean:
	-rm -f *.o
	-rm -f *.ko
	-rm -f *.symvers
	-rm -f *.order
