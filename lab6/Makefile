CONFIG_MODULE_SIG=n
CONFIG_MODULE_SIG_ALL=n

obj-m := lab6.o
ccflags-y := -Wframe-larger-than=4096

default:
	gcc test.c -o test
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	
clean:	
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm -rf test