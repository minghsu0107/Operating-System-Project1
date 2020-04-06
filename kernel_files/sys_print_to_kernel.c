#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_print_to_kernel(const char *to_dmesg) {
	printk(to_dmesg);
	return 0;
}