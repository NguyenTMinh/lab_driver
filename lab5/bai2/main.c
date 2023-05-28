#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
int8_t write_buf[1024];
int8_t read_buf[1024];
int main()
{
        int fd = -1;
        char option;
        printf("**************************************************\n");
        printf("*******user application to test char driver*******\n");
        fd = open("/dev/lab5.2_NguyenTrongMinh", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
  
        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        1. Lay thoi gian tuyet doi, micro giay               \n");
                printf("        2. Lay thoi gian tuyet doi, nano giay                 \n");
                printf("        3. Lay thoi gian tuong doi                 \n");
                printf("        4. ket thuc ctr                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                read(fd, read_buf, 1);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case '2':
                                read(fd, read_buf, 2);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case '3':
                                read(fd, read_buf, 3);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);

                                break;
                        case '4':
                                printf("Ket thuc chuong trinh.");
                                close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fd);
}
