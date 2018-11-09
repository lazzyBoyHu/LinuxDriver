#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
char buf[] = "Hello,XiDianXiDianXiDianXiDianXiDianXiDianXiDianXiDianXiDianXiDianXiDianXiDian";
char temp[28]={0};

int main()
{
  int fd,i;

  fd= open("/dev/cdev_drv",O_RDWR);
  if(fd<0)
  {
      printf("cannot open file..\n");
      exit(0);
    }

  write(fd,buf,strlen(buf));

  i=read(fd,temp,30);

  printf("len=%d,%s \n",i,temp);

  close(fd);

  return 0;
}

