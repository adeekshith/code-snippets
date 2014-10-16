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

main()
{
   int sd,newsd,fd;
   char rdbuf[100],wrbuf[100],client_name[100]="UDAY";
   struct sockaddr_in serv,client;
   //socket creation
   sd=socket(PF_INET,SOCK_STREAM,0);	
   if(sd==-1) 
      {
	     perror("SOCKET\n");
	     return;
	  }
   signal(SIGPIPE,isr);
   //socket initialisation
   serv.sin_family=PF_INET;
   serv.sin_port=htons(2049);
   serv.sin_addr.s_addr=inet_addr("0.0.0.0");
   // connecting socket
   if(bind(sd,(struct sockaddr *)&serv,sizeof(serv))==-1)
         {
		         perror("BIND:\n");	 
		         return;
	     }
   listen(sd,3);
   int len;
   len=sizeof(client);
   printf("SERVER WAITING FOR connection..\n");
   newsd=accept(sd,(struct sockaddr *)&client,&len);// waiting for clients request
   if(newsd==-1)
      {
	     perror("ACCEPT\n");
	     return;
	  }
  printf("CONNECTION SUCCESSFUL\n");
  fd=open("fifo1",O_RDWR);
  //read(newsd,client_name,99);
  if(fork())
  {
	    while(strcmp(wrbuf,"Q")!=0)
       {
		  bzero(wrbuf,100);
		  read(fd,wrbuf,99);
		  printf("ME:%s\n",wrbuf);
		  write(newsd,wrbuf,99);
		 
	   } 
 
  }
  else
   {
	  while(strcmp(rdbuf,"Q")!=0)
       {
		  bzero(rdbuf,100);
		  read(newsd,rdbuf,99);
		  printf("%s:%s\n",client_name,rdbuf);
	   }
	   
	}
   //wait(NULL);
   close(sd);//closing socket
   close(newsd);//closing socket
   //kill(9,getpid());
}


