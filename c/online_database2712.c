/* 
TITLE:ONLINE STUDENT DATABASE PROJECT.
DESCRIPTION: STUDENTS DATABASE IS STORED ONTO A 
             SERVER AND CAN BE ACCESSED BY CLIENTS.   
CREATED BY: SP UDAY KUMAR
DATE: 27-12-2012.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#define PORTNO 2084

struct student_database_encrypted
	{
	  int rollno;
      char name[100];
	  float mark;	
	};

void isr(int n)
{
  kill(getpid(),9);
}

void add_record();
void print_record();
void update_record();
void delete_record();
void sort_record();
void change_password();
void read_client(char *);
void write_client(char *);
void write_client_int(int);
void write_client_float(float);
void integer_to_string(char *,int );
void float_to_string(char *,float );
void encrypt(struct student_database_encrypted *);
void decrypt(struct student_database_encrypted *);

int sd,newsd,fd;

main()
{
   FILE *fp;
   int i,n1=0,n,choice,size_client,ret=0;//n1=counter in file if '0' password not set, '1' if password set
   char default_password[20]="password",password[100],pch,pc,ch;
   char rdbufp[100],rdbuf[100],wrbuf[100],rdbufc[100];
   struct sockaddr_in server_addr,client_addr;	
   signal(SIGPIPE,isr); // signal handling
   system("mkfifo fifo");
   fd=open("fifo",O_RDWR);
   /************  SERVER BEGINING ***********/
   //socket creation
   sd=socket(PF_INET,SOCK_STREAM,0);	
   if(sd==-1) 
      {
	     perror("SOCKET\n");
	     return;
	  }
   //socket initialisation
   server_addr.sin_family=PF_INET;
   server_addr.sin_port=htons(PORTNO);
   server_addr.sin_addr.s_addr=inet_addr("0.0.0.0");
   // connecting socket
   if(bind(sd,(struct sockaddr *)&server_addr,sizeof(server_addr))==-1)
         {
		         perror("BIND:\n");	 
		         return;
	     }
   listen(sd,3);
      size_client=sizeof(client_addr);
   printf("SERVER WAITING FOR connection..\n");
   newsd=accept(sd,(struct sockaddr *)&client_addr,&size_client);// waiting for clients request
   if(newsd==-1)
      {
	     perror("ACCEPT\n");
	     return;
	  }
  int var;
  var=1;
  setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&var,sizeof(var));
  printf("CONNECTION SUCCESSFUL\n");
  if(fork())
     { 
     while(1)
     {
	    PASSWORD_CHECK:fp=fopen("password.dat","r");
        if(fp==NULL)
          {
            goto SET_PASSWORD;//if program executed for 1st time file doesnot exist so goto check
          }
        fread(&n1,sizeof(int),1,fp);
           
        if(n1==0) // Password not yet created
         {  
            SET_PASSWORD:
            write_client("WANT TO SET PASSWORD Y/N");
            bzero(rdbufp,100);
            if(read(fd,rdbufp,100)<0)
		      {
				   printf("ERROR RADFING FIFO");
				   return;
		     }
	     
		   if(strcmp(rdbufp,"y")==0)//password creation block
             {  
               fp=fopen("password.dat","w");
      	       write_client("Enter New password:(max 20 characters)");
      	       bzero(rdbufp,100);
      	       read(fd,password,100);
		       n1=1;
	           fwrite(&n1,sizeof(int),1,fp);
      	       fwrite(password,sizeof(password),1,fp);
      	       fclose(fp);
	           write_client("password created succesfully");
      	       goto PASSWORD_CHECK;
            }
           else
             goto MENU;
        }
       if(n1==1)// Authentication block
         {
           
           write_client("ENTER PASSWORD TO LOGIN");
           bzero(rdbufp,100);
           read(fd,rdbufp,100);
         
           bzero(password,100);
           fread(password,4,1,fp);
         
           if(strcmp(password,rdbufp)==0)
            {
              write_client("LOGGED IN SUCCESSFULLY");
              while(1)
               {
				  MENU:
			     /************  MENU  *****************/
			      write_client("-------------MENU------------\n");
			      write_client("Enter choice:\n");
		          write_client("1.AddRecord\n");
		          write_client("2.PrintRecord\n");
		          write_client("3.UpdateRecord\n");
  	              write_client("4.Sort\n");
		          write_client("5.Delete\n");
		          write_client("6.Change password\n");
		          write_client("7.QUIT\n");
			    /************  MENU  END *****************/ 
			      bzero(rdbufp,100);
		          read(fd,rdbufp,100);
		       	  choice=atoi(rdbufp);  // STRING TO INTEGER CONVERSION
		          switch(choice)
   			        {
	  			       case 1:add_record();//function call to add a new record
                              break;
          		       case 2:print_record();//function call to print record data
                 			  break;
          		       case 3:update_record();//function call to sort
                 			  break;
          			   case 4:sort_record();//function call to update a record entry
                 			  break;
          			   case 5:delete_record();//function to delete
                 			  break;
				       case 6:change_password();
                              break;
                       case 7:EXIT:
                              write_client("EXITTING..");
                              printf("EXITTING..\n");
                              kill(ret,9);
                              close(sd);//closing socket
                              close(newsd);//closing socket
                              exit(0);
          			   default :write_client("ERROR: Invalid choice");
          			  
			      }
    		}
          }
        
       else  
         {
		     write_client("PASSWORD MISMATCH\n");
		     write_client("RETRY y/n\n");
		     bzero(rdbuf,100);
             read(fd,rdbuf,100);	
		     if(strcmp(rdbuf,"y")==0)
		       {
				  goto PASSWORD_CHECK;
		       }
		     else
		       goto EXIT;	
		 } 
	   }
	 }// WHILE ENDS
	}
  else
    {
	  while(1)
	  {
		bzero(rdbufc,100);
	    if(read(newsd,rdbufc,99)<0)
	    {
          perror("ERRORC:");
          return 0;   
        }
        write(fd,rdbufc,strlen(rdbufc));
	  }
    }
   system("rm fifo");
}//MAIN ENDS

void add_record()
{
   struct student_database_encrypted v;
   FILE *fp;
   char databuf[100];

   write_client("ENTER ROLL NO:");
   bzero(databuf,100);
   read(fd,databuf,100);
   v.rollno=atoi(databuf);

   write_client("ENTER NAME");
   bzero(databuf,100);
   read(fd,databuf,100);
   strcpy(v.name,databuf);
   
   write_client("ENTER MARKS");
   bzero(databuf,100);
   read(fd,databuf,100);
   strcat(databuf,"00");
   v.mark=atof(databuf);

   encrypt(&v); //encrypt called
   fp=fopen("student_data_encrypt.dat","a");
   fwrite(&v,sizeof(v),1,fp);
   fclose(fp);
   write_client("Record added succesfuly to database");
}

void print_record()
{
  struct student_database_encrypted v;
  FILE *fp;
  int choice,flag=0;
  char rdbuf[100];
  fp=fopen("student_data_encrypt.dat","r");
	if(fp==NULL)
		{
			write_client("ERROR: record not found\n");
			return;
		}
  write_client("Enter choice:1.print all records  2.print specific record\n");
  bzero(rdbuf,100);
  read(fd,rdbuf,100);
  choice=atoi(rdbuf);
  if(choice==1)// Printing whole database
	{	if(fgetc(fp)!=EOF)//File non empty testing
                  {       
                        rewind(fp);
                        write_client("NAME\tROLLNO\tMARKS\n");
	        	        while(fread(&v,sizeof(v),1,fp))
                              {
                                decrypt(&v);
                                strcpy(rdbuf,v.name);
                                write_client(rdbuf);
			                    bzero(rdbuf,100);
			                    integer_to_string(rdbuf, v.rollno);
			                    write_client(rdbuf);
			                    bzero(rdbuf,100);
			                    float_to_string(rdbuf, v.mark);
			                   	write_client(rdbuf);
			                    write_client("\n");
                              }
                    }  
                else
                        write_client("List is empty.");
        }
  else if(choice==2)// Printing single record
	{	
		write_client("Enter rollno to print data");
        bzero(rdbuf,100);
        read(fd,rdbuf,100);
        choice=atoi(rdbuf);
        write_client("NAME\tROLLNO\tMARKS");
		while(fread(&v,sizeof(v),1,fp))
			{
                    decrypt(&v);    
                	if(v.rollno==choice)				
					     {
					            write_client(v.name);
					            bzero(rdbuf,100);
					            integer_to_string(rdbuf, v.rollno);
			                    write_client(rdbuf);
			                    bzero(rdbuf,100);
			                    float_to_string(rdbuf, v.mark);
			                    write_client(rdbuf);
			                    write_client("\n");
			                    flag=1;
					     }
			 }
		 if(flag==0)
		     write_client("Record not found");
	}
  else
	write_client("Invalid choice to print\n");
  fclose(fp);
}

void update_record()
{
  FILE *fp;
  struct student_database_encrypted v;
  int choice,n;
  char rdbuf[100];
  fp=fopen("student_data_encrypt.dat","r+");
  if(fp==NULL)
	{
		write_client("ERROR: Data base doesnot exist");
		return;
	}
  write_client("Enter rollno of student to update:");
  bzero(rdbuf,100);
  
  read(fd,rdbuf,100);
  choice=atoi(rdbuf);
  write_client("Update 1.rollno 2.name 3.marks");
  bzero(rdbuf,100);
  
  read(fd,rdbuf,100);
  n=atoi(rdbuf);
  if(n==1||n==2||n==3)
      {
  	 while(fread(&v,sizeof(v),1,fp))
         	{   decrypt(&v);
                if(v.rollno==choice)
			      {
				    if(n==1)
					  {
						write_client("Enter rollno to update:");
						bzero(rdbuf,100);
  
                        read(fd,rdbuf,100);
                        v.rollno=atoi(rdbuf);	
					  }
				    else if(n==2)
					  {
						write_client("Enter name to update:");
						bzero(rdbuf,100);
  
                        read(fd,rdbuf,100);
                        strcpy(v.name,rdbuf);
         		      }
				    else if(n==3)
					  {
						write_client("Enter marks to update:");
					    bzero(rdbuf,100);
					    read(fd,rdbuf,100);
                      
                        v.mark=atof(rdbuf);			
					  }
                    else
			    		{
				    		write_client("Invalid choice to update");
				 	    	fclose(fp);
						    return;
					    } 
				fseek(fp,-1*sizeof(v),1);
                encrypt(&v);
				fwrite(&v,sizeof(v),1,fp);
			 }
		
	      }
    }
  else
     write_client("Invalid choice for updating");
  fclose(fp);
}

void delete_record()
{
  FILE *fp,*fp1;
  struct student_database_encrypted v,*p,*temp;
  int choice,n1=0,count=0;
  char rdbuf[100];
  fp=fopen("student_data_encrypt.dat","r+");
  if(fp==NULL)
	{
		write_client("ERROR: Data base doesnot exist");
		return;
	}
  write_client("Enter rollno to delete record");
  bzero(rdbuf,100);
  
  read(fd,rdbuf,100);
  choice=atoi(rdbuf);
  while(fread(&v,sizeof(v),1,fp)) // to find file size
	{
        	n1++;	
	} 
  rewind(fp);
  fp1=fopen("temp.dat","w");
  while(fread(&v,sizeof(v),1,fp))
	{	
		decrypt(&v);
		if(v.rollno!=choice)// testing if not the record to delete and copying to another file
			{   encrypt(&v);
				fwrite(&v,sizeof(v),1,fp1);	
			}
		else if(v.rollno==choice)
	        {
	          write_client("Record deleted succesfully");	    
	          count++;
	         }
		   
	}
  fclose(fp);
  fclose(fp1);
  fp=fopen("student_data_encrypt.dat","w");
  fp1=fopen("temp.dat","r");
  while(fread(&v,sizeof(v),1,fp1))// copying file(with requested data deleted) data to main file
  	{      
                fwrite(&v,sizeof(v),1,fp);
	}
  fclose(fp);
  fclose(fp1);
  remove("temp.dat");
  if(count==0)
     write_client("RECORD NOT FOUND\n");
}

void sort_record()
{
  FILE *fp;
  struct student_database_encrypted *sp,*tp,v,temp; 
  int choice,i,j,n=0;
  char rdbuf[100];
  bzero(rdbuf,100);
  write_client("Enter choice:to sort by 1.Roll NO 2.Name 3.Marks");
  
  read(fd,rdbuf,100);
  choice=atoi(rdbuf);
  fp=fopen("student_data_encrypt.dat","r");
  while(fread(&v,sizeof(v),1,fp))
       n++;
  rewind(fp);  
  sp=malloc(n*sizeof(v));
  if(sp==NULL)
	{
		write_client("Memory allocation Fault");
        return;
    }
   tp=sp;
   while(fread(&v,sizeof(v),1,fp))// copying whole data to dynamic memory
	{
                decrypt(&v);
		memcpy(sp,&v,sizeof(v));
		sp++;
	}
   fclose(fp);
   sp=tp;
   if(choice==1)// sort by rollno (bubble sort)
	{
		
                for(i=0;i<=n;i++)
			{
				for(j=0;j<n-i-1;j++)
					{	
					  if(((sp+j)->rollno)>((sp+j+1)->rollno))
						{
							temp.rollno=((sp+j)->rollno);
							((sp+j)->rollno)=((sp+j+1)->rollno);
							((sp+j+1)->rollno)=temp.rollno;	
							
							temp.mark=(sp+j)->mark;
							((sp+j)->mark)=((sp+j+1)->mark);
							((sp+j+1)->mark)=temp.mark;
			
							strcpy(temp.name,((sp+j)->name));
							strcpy(((sp+j)->name),((sp+j+1)->name));
 							strcpy(((sp+j+1)->name),temp.name);
						}
					}		
			}	
	}
   else if(choice==2)// sort by name (bubble sort)
	{
		
                for(i=0;i<=n;i++)
			{
				for(j=0;j<n-i-1;j++)
					{	
					  if(strcmp((sp+j)->name,(sp+j+1)->name)>0)
						{
							temp.rollno=(sp+j)->rollno;
							(sp+j)->rollno=(sp+j+1)->rollno;
							(sp+j+1)->rollno=temp.rollno;	
							
							temp.mark=(sp+j)->mark;
							(sp+j)->mark=(sp+j+1)->mark;
							(sp+j+1)->mark=temp.mark;
			
							strcpy(temp.name,(sp+j)->name);
							strcpy((sp+j)->name,(sp+j+1)->name);
 							strcpy((sp+j+1)->name,temp.name);
						}
					}		
			}	
	}
   else if(choice==3)// sort by marks (bubble sort)
	{
		
                for(i=0;i<=n;i++)
			{
				for(j=0;j<n-i-1;j++)
					{	
					  if((sp+j)->mark>(sp+j+1)->mark)
						{
							temp.rollno=(sp+j)->rollno;
							(sp+j)->rollno=(sp+j+1)->rollno;
							(sp+j+1)->rollno=temp.rollno;	
							
							temp.mark=(sp+j)->mark;
							(sp+j)->mark=(sp+j+1)->mark;
							(sp+j+1)->mark=temp.mark;
			
							strcpy(temp.name,(sp+j)->name);
							strcpy((sp+j)->name,(sp+j+1)->name);
 							strcpy((sp+j+1)->name,temp.name);
						}
					}		
			}	
	}
  else
      {
        write_client("ERROR:Invalid choice to sort ");
         return;
      }
  fp=fopen("student_data_encrypt.dat","w");
  sp=tp;
  for(i=0;i<n;i++)  
	{
        encrypt(sp+i);
		fwrite((sp+i),sizeof(v),1,fp);
	}
  fclose(fp);
write_client("Sorting succesfull");
}

void change_password()
{
  FILE *fp;
  int n1=0;
  char ch,password[100],s[100],rdbuf[100];
  fp=fopen("password.dat","r+");
  fread(&n1,sizeof(int),1,fp);
  if(n1==0) 
	{
           write_client("Password does not exist: want to set(y/n)");
         
            read_client(rdbuf);
         
           if(ch=='y')
              {
		          write_client("Enter New password:(max 20 characters)");
      	 
      	          bzero(password,100);
      	          read(fd,password,100);
      		      fwrite(password,sizeof(password),1,fp);
      		      rewind(fp);
		          n1=1;
		          fwrite(&n1,sizeof(int),1,fp);
      		      write_client("password crated succesfully");
		          fclose(fp);
                  return;
	          }
           else
              {
                write_client("password not changed");
                fclose(fp);
                 return;
              }
     }
 else if(n1==1)      
     {
          write_client("Enter Existing password:");
         
          bzero(password,100);
      	  read(fd,password,100);
          fread(s,sizeof(s),1,fp);
          if(strcmp(password,s)==0)
             {
                   write_client("Enter new password:");
         
                   bzero(password,100);
      	           read(fd,password,100);
                   rewind(fp); 
                   n1=1;
                   fwrite(&n1,sizeof(int),1,fp);
                   fwrite(password,sizeof(password),1,fp);
                   write_client("password changed succesfully");
                   fclose(fp);
                   return;
             }
           else
             {
                   write_client("Password mismatch");
                   return;
             }
     }  
}

//*******************************************************************

void write_client(char *msg)
{
   write(newsd,msg,strlen(msg));
}

void read_client(char *databuf)
{
   if(read(newsd,databuf,99)<0);
	    {
          perror("ERROR:");
          return;   
        }
}

void encrypt(struct student_database_encrypted *ptr)
{ 
  char s[20];
  int i=0,r;
  float m;
  strcpy(s,ptr->name);
  r=ptr->rollno;
  m=ptr->mark;
  while(s[i])
     {
          if(i%2==0)
              s[i]+=2*i;
          else
              s[i]-=2*i;
          i++;
     }
 strcpy(ptr->name,s);
 ptr->rollno=r+i;
 ptr->mark=m-i; 
}

void decrypt(struct student_database_encrypted *ptr)
{
  char s[20];
  int i=0,r;
  float m;
  strcpy(s,ptr->name);
  r=ptr->rollno;
  m=ptr->mark;
  while(s[i])
     {
          if(i%2==0)
              s[i]-=2*i;
          else
              s[i]+=2*i;
          i++;
     }
 strcpy(ptr->name,s);
 ptr->rollno=r-i;
 ptr->mark=m+i;
}


void float_to_string(char *str,float f)
{
  sprintf(str,"%f",f);
  
}


void integer_to_string(char *str, int n)
{
  sprintf(str,"%d",n);
  
}
