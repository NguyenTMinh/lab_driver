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
  
        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        1. Open thiet bi               \n");
                printf("        2. Nhap so he 10 va ghi ra thiet bi so he 10, 2, 8, 16                 \n");
                printf("        3. Doc so he 2                 \n");
                printf("        4. Doc so he 8                 \n");
                printf("        5. Doc so he 16                 \n");
                printf("        6. Dong thiet bi va ket thuc ctr                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                //Chu y truyen dung ten file thiet bi
                                fd = open("/dev/lab5.1_NguyenTrongMinh", O_RDWR);
                                if(fd < 0) {
                                        printf("Cannot open device file...\n");
                                        return 0;
                                }
                                printf("Open..\n");

                                break;
                        case '2':
                                if(fd < 0) {
                                        printf("Cannot open device file...\n");
                                        return 0;
                                }

                                printf("Nhap so :");
                                scanf("  %[^\t\n]s", write_buf);
                                printf("Data Writing ...");
                                write(fd, write_buf, strlen(write_buf)+1);
                                printf("Done!\n");

                                break;
                        case '3':
                                if(fd < 0) {
                                        printf("Cannot open device file...\n");
                                        return 0;
                                }

                                printf("Doc so he 2 ...");
                                read(fd, read_buf, 3);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);

                                break;
                        case '4':
                                if(fd < 0) {
                                        printf("Cannot open device file...\n");
                                        return 0;
                                }

                                printf("Doc so he 8 ...");
                                read(fd, read_buf, 4);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case '5':
                                if(fd < 0) {
                                        printf("Cannot open device file...\n");
                                        return 0;
                                }

                                printf("Doc so he 16 ...");
                                read(fd, read_buf, 5);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case '6':
                                if(fd < 0) {
                                        printf("Cannot open device file...\n");
                                        return 0;
                                }

                                printf("Close.");
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
