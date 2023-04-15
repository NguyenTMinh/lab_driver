#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

#define MAX_LEN 20

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A module to convert hex to binary");

static char hex_str[MAX_LEN];
static int decimal;
static long bina;
static int octal;
static int choice;

module_param(decimal, int, S_IRUGO);
module_param(choice, int, S_IRUGO);
module_param(bina, long, S_IRUGO);
module_param(octal, int, S_IRUGO);
module_param_string(hex_str, hex_str, sizeof(hex_str), 0644);

static char binary_str[1024];
static char octal_str[1024];

module_param_string(binary_str, binary_str, 1024, 0644);

// Convert hex to decimal
int hex_to_dec(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else {
        return -1;
    }
}

// Convert hex string to decimal
int hex_str_to_dec(char *hex_str)
{
    int len = strlen(hex_str);
    int dec = 0;
    int i;

    for (i = 0; i < len; i++) {
        int digit = hex_to_dec(hex_str[i]);
        if (digit == -1) {
            printk(KERN_ALERT "Invalid hex string\n");
            return -1;
        }
        dec = dec * 16 + digit;
    }

    return dec;
}

// Convert decimal to binary
void dec_to_bin(int dec, char *bin_str)
{
    int i = 0;

    if (dec == 0) {
        bin_str[0] = '0';
        bin_str[1] = '\0';
        return;
    }

    while (dec > 0) {
        bin_str[i++] = (dec % 2 == 0) ? '0' : '1';
        dec /= 2;
    }

    bin_str[i] = '\0';

    // Reverse the binary string
    int len = strlen(bin_str);
    for (i = 0; i < len / 2; i++) {
        char temp = bin_str[i];
        bin_str[i] = bin_str[len - i - 1];
        bin_str[len - i - 1] = temp;
    }
}

// y 4
int bin2oct(unsigned long bin)
{
    int oct = 0, dec = 0, i = 0;

    // Convert binary to decimal
    while (bin != 0)
    {
        dec += (bin % 10) * (1 << i);
        ++i;
        bin /= 10;
    }

    // Convert decimal to octal
    i = 1;
    while (dec != 0)
    {
        oct += (dec % 8) * i;
        dec /= 8;
        i *= 10;
    }

    return oct;
}

// y 5
int octal_to_hex(unsigned int octal)
{
    int hex = 0, i = 0;
    while (octal != 0)
    {
        hex += (octal % 10) * (1 << i);
        ++i;
        octal /= 10;
    }
    return hex;
}

static int __init doInit(void)
{
    switch(choice) {
	    case 1: {
	    	int dec;
		    char bin_str[MAX_LEN];

		    printk(KERN_INFO "Hex string: %s\n", hex_str);

		    dec = hex_str_to_dec(hex_str);
		    if (dec == -1) {
		        return -EINVAL;
		    }

		    dec_to_bin(dec, bin_str);

		    printk(KERN_INFO "Binary string: %s\n", bin_str);
		    break;
	    }
	case 2: {
		int temp = decimal;
		int binary = 0, base = 1, rem;
		while (temp > 0) {
			rem = temp % 2;
		    binary += rem * base;
			base *= 10;
		    temp /= 2;
	    }
		printk(KERN_INFO "10->2: %d->%d", decimal, binary);
		break;
	}
	case 3: {
		char hex_str[20];
    	sprintf(hex_str, "%x", decimal);
    	printk(KERN_INFO "16->10: %d->%s", decimal, hex_str);
		break;
	}
	case 4: {
		int oct = bin2oct(bina);
		printk(KERN_INFO "2 -> 8: %d -> %d", bina, oct);
		break;
	}
	case 5: {
		int hex = octal_to_hex(octal);
		printk(KERN_INFO "8 -> 16: %o -> %x", octal, hex);
		break;
	} 
    }
    return 0;
}

static void __exit doExit(void)
{
    printk(KERN_INFO "Exiting hex_to_bin module\n");
}

module_init(doInit);
module_exit(doExit);
