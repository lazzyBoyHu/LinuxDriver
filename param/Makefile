ifeq ($(KERNELRELEASE),)

KERNELDIR ?= /usr/src/linux-headers-4.4.0-116-generic/
PWD :=$(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
	.PHONY: modules modules_install clean
else
	obj-m:= param.o
endif
