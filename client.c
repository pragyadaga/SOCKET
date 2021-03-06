/*
    Client Code
*/

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/types.h>  /* for Socket data types */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <netinet/in.h> /* for IP Socket data types */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <errno.h>       /* error code for the last system call */

int main(int argc , char *argv[])
{
    int sock,portno;
	int i;
    struct sockaddr_in server;
    struct in_addr *addr_server;
    char *p;
    p=argv[1];
    char message[1000] , server_reply[1000];
    if(argc<3)
    {
		fprintf(stderr, "usage %s hostname port \n", argv[0]);
		exit(0);
     }
    portno=atoi(argv[2]);
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        perror("\n Could not create socket");
    }
   	//server=gethostbyname(argv[1]);
	/*if(server==NULL)
	{
		fprintf(stderr, "ERROR, no such host \n");
		exit(0);
	} */  
    server.sin_addr.s_addr = inet_addr(p); 
    server.sin_family = AF_INET;
    server.sin_port = htons( portno );

       //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("\n Connect failed. Error");
        return 1;
    }
        //keep communicating with server
    while(1)
    {
        printf("\n Enter message : ");
        for(i=0;(message[i]=getchar())!='\n';i++)
	{
	;
	}
	message[i]='\0';
       //Send some data
	//while(1)
	//{
	int a; //check
        if( (send(sock , message , sizeof(message)+1 , 0)) < 0) 
        {
            perror("\n Send failed");
            return 1;
        }
        //if(a==strlen(message))
		//break;
        //}
 
        //Receive a reply from the server
       // while(1)
	//{
	 a=recv(sock , server_reply , sizeof(server_reply)+1 , 0); // sizeof
        if( a < 0)
        {
            perror("\n Receive failed");
            break;
        }
	//if(a==(strlen(message)+1))
             //    break;
       // }
	/*int i;
	printf("\n");
	for(i=0;i<strlen(message);i++)
		printf("%c",server_reply[i]); */
        printf("\n Server reply :");
        printf("%s",server_reply);
    }
   // printf("\n The server is disconnected. The connection to the server is closed ");    
    close(sock);
    return 0;
}