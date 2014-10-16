// YASHWANTH GOUD DURGAPATHI
// HTTP Client - Computer Networks
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>


/* getLine() Reads a line from a stream and stores it in "string"
   which will automatically be appropriately allocated.
  
   RETURNS: Number of characters in the line and stores the line in the
   variable "string". This may differ from strlen(string) if the string
   contains \0. The "string" variable should be free()'d by the caller.
   Returns -1 when the end of the stream is reached. Exits if some other
   error occurs.
  
   You should call this function this way:
   char *string = NULL;
   getLine(&string, stream);
 



*/
size_t getLine(char **string, FILE *stream)
{
    /* TODO: Call the getline() function with the given string, a variable
       for the string length to be stored, and the given stream.  Check the
       return value for an error (see getline() documentation). If error,
       print message and exit. Since it returns the same thing for an error
       and reaching the end of the file, you will need to check if you
       reached the end of file.  If feof(stream)!= 0, then the stream is
       at the end of file.
    */
FILE *fd;
char *str = NULL;
int rd=0;
int ln = getline(&str,&rd,fd);

    if(ln == -1)
    {
         fprintf(stderr,"error in reading string\n");     
     exit(-1);
     }
    else
    {
      while (fgetc(fd) != EOF)
       {   
        ++rd;
       }
     }    
     
       if(feof(fd) != 0)
       {
         printf("%x\n",rd);//total number of bytes read
        exit(EXIT_SUCCESS);
       }
                        
    return -1; // FIXME:  This always indicates we hit end of line.
}



/* Convert file descriptor into stream (i.e., FILE*).  Exit if there is a
 * failure. */
FILE* getStream(int sock)
{
    // TODO:
    // Call fdopen(sock, "a+b").
    // Check for errors. If one occurred, print message and exit.
    // Return the stream returned by fdopen().
    FILE *fp;
    fp = fdopen(sock,"a+b");
   
    if(fp == NULL)
    {
    fprintf(stderr,"error opening socket\n");
    exit(EXIT_FAILURE);
    }

return NULL; // FIXME
}

/* Creates a TCP socket and returns the file descriptor for it. */
int createSocket(char *hostname, char *port)
{
    if(hostname == NULL || port == NULL)
    {
        fprintf(stderr, "One or more parameters passed to createSocket() are NULL\n");
        exit(EXIT_FAILURE);
    }

    /* Request a TCP connection using the version of IP that is configured
       on the machine.
    */
    struct addrinfo * result, *h;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE|AI_ADDRCONFIG;
    char buf[1024];

    /* TODO: Call getaddrinfo() using hostname, port, hints and the
       result structure. If the hostname is NULL, getaddrinfo()
       returns a struct appropriate for a server (not a client). Check
       return value of getaddrinfo() and print message and exit if an
       error occurs.
    */
         int error = getaddrinfo(hostname, NULL, &hints, &result);
        
     if(error != 0)
         {
      fprintf(stderr,"\n error in getaddrinfo:%s\n",gai_strerror(error));
      exit(EXIT_FAILURE);
         }

    /* TODO: Create a socket using socket() and the "result" structure.
       Check for an error. If one occurs, print a message and exit.
    */
   
      for(h=result; h != NULL; h = h->ai_next)
      { 

       int sock = socket(h->ai_family, h->ai_socktype, h->ai_protocol);
   
    if(sock == -1)
        {
        fprintf(stderr,"\nerror in creating Socket");
        exit(EXIT_FAILURE);
        }
   

    /* TODO: Call connect() with "sock" and information from the
       "result" struct to start a TCP connection. Check for error. If
       one occurs, print message and exit.
    */
     if(connect(sock, h->ai_addr, h->ai_addrlen) == -1)
       {
         close(sock);
         fprintf(stderr,"\nerror in connecting");
         exit(EXIT_FAILURE);
       }
   
    if(h->ai_family==AF_INET)
    {
        struct sockaddr_in *x;
        x=(struct sockaddr_in *)h->ai_addr;
        inet_ntop(h->ai_family, &(((struct sockaddr_in *)(h->ai_addr))->sin_addr), buf,1024);
        printf("%s\n",buf);
    }

    if(h->ai_family==AF_INET6)
    {
        struct sockaddr_in6 *x;
        x=(struct sockaddr_in6*)h->ai_addr;
        inet_ntop(h->ai_family,&(((struct sockaddr_in6 *)(h->ai_addr))->sin6_addr),buf,1024);
        printf("%s\n",buf);
        }

    freeaddrinfo(result);
   
}




int main(int argc, char *argv[])
{
    /* TODO: Check number of arguments */
    if(argc<2)
    {
        printf("expected a name for resolving");
        exit(1);
    }

    /* Setup socket. */
    int sock = createSocket(argv[1], argv[2]);
    FILE *stream = getStream(sock);
    printf("\n###### CLIENT IS SENDING THE FOLLOWING TO THE SERVER\n");
   
    /* TODO: Write HTTP request to "stream" */

    fputs("GET /HTTP/1.0\n Host:Google.com\n Connection:close \r\n\r\n",stream);
    while(1) // while there is data to read
    {
        char *string = NULL;
        int len = getLine(&string, stream);

        // TODO: Process the line that we have read.
        printf("%d\n",len);//length of string
            printf("#####CLIENT RECEIVED THE FOLLOWING FROM SERVER \n%s", string);


        // TODO: When we reach the end of stream, fclose(stream), print
        // message that the connection was closed to console, and
        // exit(EXIT_SUCCESS).

        fclose(stream);
        printf("##### Connection closed by server");
        exit(EXIT_SUCCESS);
        free(string);

    } // end infinite loop

}
