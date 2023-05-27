#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/string.h>
#include <linux/ctype.h>
#define MAX_SIZE 200
#define COL 3
#define ROW 3

int choice;
char XauRo[MAX_SIZE];
char XauMa[MAX_SIZE];
char K[MAX_SIZE];
int K2[MAX_SIZE];

module_param(choice, int, S_IRUGO);
module_param_string(XauRo, XauRo, sizeof(XauRo), 0644);
module_param_string(K, K, sizeof(K), 0644);
module_param_array(K2, int, NULL, 0644);

// ma hoa thay the
void maHoaThayThe(void) {
    int lenRo = strlen(XauRo);
    int i;

    // Duyệt qua từng ký tự trong XauRo
    for (i = 0; i < lenRo; i++) {
        char c = XauRo[i];

        // Nếu ký tự không thuộc bảng chữ cái tiếng Anh hoặc không có trong khóa K thì thêm ký tự đó vào XauMa mà không thay đổi
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') || strchr(K, c) == NULL) {
            XauMa[i] = c;
        }
        // Nếu ký tự nằm trong khóa K thì thay thế ký tự đó bằng ký tự tương ứng trong khóa K
        else {
            int pos = strchr(K, c) - K;
            XauMa[i] = K[pos];
        }
    }
    XauMa[lenRo] = '\0'; // Kết thúc chuỗi XauMa
    printk(KERN_INFO "lab3.bai2. ma hoa thay the: %s", XauMa);
}

// ma hoa hoan vi
void hoanViToanCuc(char xau[], int khoa[]) {
    char temp[MAX_SIZE];
    int i;
    int doDai = strlen(xau);

    for (i = 0; i < doDai; i++) {
        temp[i] = xau[khoa[i]];
    }

    // strcpy(xau, temp);
    temp[i] = '\0';
    printk(KERN_INFO "lab3.bai2. ma hoa thay the: %s", temp);
}

int __init doInit(void) {
	switch(choice) {
		case 1: {
			maHoaThayThe();
			break;
		}
		case 2: {
			hoanViToanCuc(XauRo, K2);
			break;
		} 
	}
	return 0;
}

void __exit doExit(void) {

}

module_init(doInit);
module_exit(doExit);
MODULE_LICENSE("GPL");