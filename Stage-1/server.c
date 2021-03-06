/*
    Stage-1 server code 
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
        perror("Could not create socket");  //not proper thing
    }
    //puts("\n Socket created")
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
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    a: printf("Waiting for incoming connections ...");
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
     
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 256 , 0)) > 0 )
    {
        //Send the message back to client
        write(client_sock , client_message , read_size);
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
    return 0;
}