/*
	Server Code
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <unistd.h>
#include <errno.h> 

typedef struct
{
	int sock;
	struct sockaddr address;
	int addr_len;
} connection_t;

void * process(void * ptr)
{
	//char * buffer;
	int len;
	connection_t * conn;
	long addr = 0;
	char client_message[256];

	if (!ptr) pthread_exit(0); 
	conn = (connection_t *)ptr;


	 while( (len = recv(conn->sock , client_message , 256 , 0)) > 0 )
    {
        //Send the message back to client
        write(conn->sock , client_message , len);
    }
	if(len==0)
	{
		perror("\n Client disconnected");
        	fflush(stdout);
	}
	 else if(len == -1)
    	{
        	perror("Receive failed");
    	}
	/* close socket and clean up */
	close(conn->sock);
	free(conn);
	pthread_exit(0);
}

int main(int argc, char ** argv)
{
	int sock = -1;
	struct sockaddr_in address;
	int port;
	connection_t * connection;
	pthread_t thread;

	/* check for command line arguments */
	 if(argc<2)
	 {
		fprintf(stderr, "ERROR, no port provided \n");
		exit(1);
	}


	/* create socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1)
	{
		  perror("Could not create socket");
	}
	
	port=atoi(argv[1]);
     
	/* bind socket to port */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
	{
		   perror("\n Bind failed. Error");
        	return 1;
	}
	 puts("\n Bind done");

	/* listen on port */
	if (listen(sock, 5) < 0)
	{
		fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
		return -5;
	}

	printf("%s: ready and listening\n", argv[0]);
	
	while (1)
	{
		/* accept incoming connections */
		connection = (connection_t *)malloc(sizeof(connection_t));
		connection->sock = accept(sock, &connection->address, &connection->addr_len);
		puts("\n Connection accepted");
		if (connection->sock <= 0)
		{
			free(connection);
		}
		else
		{
			/* start a new thread but do not wait for it */
			pthread_create(&thread, 0, process, (void *)connection);
			pthread_detach(thread);
		}
	}
	
	return 0;
}
