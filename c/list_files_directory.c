/* Program to list all the files in a given
 directory.provided path in command line
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>

void display(DIR *,char *);
char temp_path[100],temp[100];

main(int argc, char **argv)
{
    DIR *directory_ptr;
    if(argc<2)
       {
          printf("INVALID Format use: <./a.out> <PATH>");
          return;
       }
    strcpy(temp_path,argv[1]);
    strcat(temp_path,"/");
    strcpy(temp,temp_path);
    // Opening the Directory using opendir()
    if((directory_ptr=opendir(argv[1]))==NULL)
       {
		  perror("OPEN DIRECTORY");
		  return;
	   }
	// Calling function to display files
	display(directory_ptr,temp);
}

void display(DIR *directory_ptr_arg,char *PATH)
{
 DIR *dir_ptr;
 struct dirent *files_ptr,*f;
 struct stat stat_buf={0};
 while(files_ptr=readdir(directory_ptr_arg))
       {  
           // Testing the file type
           if(files_ptr->d_type & DT_DIR)
              { 
                 if((strcmp(files_ptr->d_name,".")!=0)&&(strcmp(files_ptr->d_name,"..")!=0))
				  { 	
					printf("---------- %s---------\n",files_ptr->d_name);   
				    strcat(PATH,files_ptr->d_name);

                    if((dir_ptr=opendir(PATH))==NULL)
				      {
						perror("DIR");  
						return;
					  }
					strcat(PATH,"/");
 				    // Recursive call for printing inner directory
 				    display(dir_ptr,PATH);
                    strcpy(PATH,temp_path);
				    printf("---------DIR END------\n");
                  }
                }
          else if((strcmp(files_ptr->d_name,".")!=0)&&(strcmp(files_ptr->d_name,"..")!=0))
                 printf("%s\n",files_ptr->d_name);   
	   }
	   closedir(directory_ptr_arg);
}
