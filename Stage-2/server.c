/*
    Server Code
*/
 
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <sys/types.h>
#include <errno.h> 
#include <stdlib.h>
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    int portno;
    pid_t childpid;
    struct sockaddr_in server , client;
    char client_message[1000];
     if(argc<2)
	 {
		fprintf(stderr, "ERROR, no port provided \n");
		exit(1);
	}
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        perror("Could not create socket");  
    }

    portno=atoi(argv[1]);
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);
     
    //Bind
    if( bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        //print the error message
        perror("\n Bind failed. Error");
        return 1;
    }
    perror("\n Bind done");
     
    //Listen
    listen(socket_desc , 2);
     
    //Accept and incoming connection
     puts("Waiting for incoming connections ...");
   a: while(1)
    {
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    while(client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))
    {
    if (client_sock < 0)
    {
        perror("\n Accept failed");
        return 1;
    }
    perror("\n Connection accepted");
    if ((childpid = fork()) == 0) { 
        close(socket_desc);   
//stop listening for new connections by the main process.   
//the child will continue to listen.   
//the main process now handles the connected client.  
  
   for (;;) {  
    //memset(buffer, 0, BUF_SIZE);
           //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 256 , 0)) > 0 )
    {
	
        //Send the message back to client
        send(client_sock , client_message , read_size,0);
    }
    if(read_size == 0)
    {
        perror("\n Client disconnected");
	goto a;
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("Receive failed");
    }
     }
     }
    close(client_sock);
    } 
    }
    return 0;
}