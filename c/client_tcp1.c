#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

void isr(int n)
{
  kill(getpid(),9);
}

main(int argc, char **argv)
{
   int sd,fd;
   char str[100],str1[100],cl_name[100];
   struct sockaddr_in serv;
   if(argc<3)
     {
	     printf("Invalid format ENTER: ./a.out  <IP ADDRESS> <FRND'S NAME>");	
	     return;
     }
   signal(SIGPIPE,isr);
   //socket creation
   sd=socket(PF_INET,SOCK_STREAM,0);	 
   //socket initialisation
   serv.sin_family=PF_INET;
   serv.sin_port=htons(2049);
   serv.sin_addr.s_addr=inet_addr(argv[1]);
   // connecting socket
   if(connect(sd,(struct sockaddr *)&serv,sizeof(serv))==-1)
         {
		         perror("CONNECT:\n");	 
		         return;
	     }
   printf("Connection successful\n");
   // Entering your name so to display in chat on server
   fd=open("fifo",O_RDWR);
   //read(fd,cl_name,99);
  // write(sd,cl_name,strlen(cl_name));
  
   // Transferring message
   if(fork())
   {
      while(strcmp(str,"Q")!=0)
       {  bzero(str,100);
		  //gets(str);
		  read(fd,str,99);
		  printf("ME:%s\n",str);
		  write(sd,str,strlen(str));
	   }
	}
	else
	  {
		  while(strcmp(str1,"Q")!=0)
        { 
		 read(sd,str1,99);
		 printf("%s: %s\n",argv[2],str1);
	    }
	  }
   //wait(NULL);
   close(sd);//closing socket11
}

