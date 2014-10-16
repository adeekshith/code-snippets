#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

main(int argc, char **argv)
{
   int sd;
   char str[100],str1[100],cl_name[100];
   struct sockaddr_in serv;
   if(argc<2)
     {
	   printf("Invalid format: ENTER  ./a.out  <IP ADDRESS>");	 
	    return;
	 }
   //socket creation
   sd=socket(PF_INET,SOCK_STREAM,0);	 
   //socket initialisation
   serv.sin_family=PF_INET;
   serv.sin_port=htons(2084);
   serv.sin_addr.s_addr=inet_addr(argv[1]);
   // connecting socket
   if(connect(sd,(struct sockaddr *)&serv,sizeof(serv))==-1)
         {
		         perror("CONNECT:\n");	 
		         return;
	     }
   printf("Connection successful\n");
   if(fork())
   {
     while(strcmp(str,"Q")!=0)
       { 
		   bzero(str,100);
		   gets(str);
		   write(sd,str,strlen(str));
	   }
	}
	else
	  {
	   while(strcmp(str1,"Q")!=0)
        { 
	     bzero(str1,100);
		 read(sd,str1,99);
		 printf("%s\n",str1);
	    }
	  }
   close(sd);//closing socket11
}

