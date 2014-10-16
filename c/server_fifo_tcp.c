#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>

main()
{
  int ret;
  char wbuf[100];
  int fd;
         system("mkfifo fifo1");
         fd=open("fifo1",O_RDWR);
         while(strcmp(wbuf,"Q")!=0)
           {
			 bzero(wbuf,100);
             gets(wbuf);
             write(fd,wbuf,strlen(wbuf));
           }
         system("rm fifo1");
}
