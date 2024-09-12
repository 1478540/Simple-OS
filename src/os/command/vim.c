#include "syscall.h"
#include "stdio.h"
#include "string.h"
#include "fs.h"
#include"file.h"
int main(int argc, char **argv)
{
    if (argc > 2||argc==1)
    {
        printf("cat: argument error\n");
        exit(-2);
    }
    int buf_size = 1024;
    char abs_path[512] = {0};
    void*buf=malloc(buf_size);
    char op[3]={0};
    if (buf == NULL||op==NULL)
    {
        printf("cat: malloc memory failed\n");
        return -1;
    }
    if (argv[1][0] != '/')
    {
        getcwd(abs_path, 512);
        strcat(abs_path, "/");
        strcat(abs_path, argv[1]);
    }
    else
    {
        strcpy(abs_path, argv[1]);
    }
    int fd = open(abs_path,O_CREAT|O_RDWR);
    if (fd == -1)
    {
        printf("cat: open: open %s failed\n", argv[1]);
        return -1;
    }
    clear();
    int read_bytes = 0;
    printf("Enter a command ('i' to insert,'q' to quit,'s' to save): \n");
    read(stdin_no, op, 1);
    clear();
   // char* str="a";
    while(1){
        switch (op[0]) {
            case 'i':
                while(1){
                    read(stdin_no, op, 1);
                    op[1]='\0';
                    write(stdout_no,op,1);
                    if(op[0]=='\033'){
                        break;
                    }
                    strcat(buf, op);
                    read_bytes++;
                }
                break;
            case 's':
                write(fd, buf, read_bytes);
                break;
            case 'q':
                free(buf);
                close(fd);
                //free(op);
                exit(-1);
            default:
                printf("Invalid command\n");
        }
        printf("Enter a command ('i' to insert,  's' to save, 'q' to quit): \n");
        read(stdin_no, op, 1);
    }
    return 8;
}

