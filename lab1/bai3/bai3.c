#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

#define NUM_ARRAY 1000

static int matrix[3][3] = {{1, 2, 3}, {4, -5, 6}, {-7, 8, 9}};

/**
 * Tong phan tu trong ma tran
 * */
void sumOfMatrix(int mat[][]) {
	int i, j, sum = 0;

    // duyệt qua từng phần tử trong ma trận và tính tổng
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            sum += mat[i][j];
        }
    }

    printk(KERN_ALERT "lab1-bai3: tong phan tu=%d", sum);
}

/**
 * Dem phan tu am duong 
 * */
void count(int mat[][]) {
	int i, j, count_positive = 0, count_negative = 0;

    // duyệt qua từng phần tử trong ma trận và đếm số phần tử dương và âm
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (mat[i][j] > 0) {
                count_positive++;
            } else if (mat[i][j] < 0) {
                count_negative++;
            }
        }
    }

    printk(KERN_ALERT "lab1-bai3: so phan tu duong=%d, am=%d", count_positive, count_negative);
}

/**
 * Tim gia tri min, max duong cheo chinh, phu
 * */
void findMinMaxInLine(int mat[][]) {
	int i, max_diag = matrix[0][0], min_diag = matrix[0][0], max_anti = matrix[0][2], min_anti = matrix[0][2];

    // tìm giá trị lớn nhất và nhỏ nhất trên đường chéo chính và đường chéo phụ
    for (i = 1; i < 3; i++) {
        if (matrix[i][i] > max_diag) {
            max_diag = matrix[i][i];
        }
        if (matrix[i][i] < min_diag) {
            min_diag = matrix[i][i];
        }
        if (matrix[i][2-i] > max_anti) {
            max_anti = matrix[i][2-i];
        }
        if (matrix[i][2-i] < min_anti) {
            min_anti = matrix[i][2-i];
        }
    }

    printk(KERN_ALERT "lab1-bai3: min=%d, max=%d tren duong cheo chinh. min=%d, max=%d tren duong cheo phu", min_diag, max_diag, min_anti, max_anti);
}

/**
 * Tong chan, le
 * */
void sumOddAndEven(int mat[][]) {
	int i, j, even_sum = 0, odd_sum = 0;

    // tính tổng các số chẵn và lẻ trong ma trận
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (matrix[i][j] % 2 == 0) {
                even_sum += matrix[i][j];
            } else {
                odd_sum += matrix[i][j];
            }
        }
    }

    printk(KERN_ALERT "lab1-bai3: tong chan=%d, tong le=%d", even_sum, odd_sum);
}


int doInit(void) {
	sumOfMatrix(matrix);
	count(matrix);
	findMinMaxInLine(matrix);
	sumOddAndEven(matrix);
	return 0;
}

void doExit(void) {
	printk(KERN_ALERT "lab1-bai1. end");
}


module_init(doInit);
module_exit(doExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TRONG MINH");


