SOCKET
======
SERVER STAGES THROUGH SOCKET PROGRAMMING 
======



Have to write proper documentation

To compile any server code :
						 	gcc server.c -o server
To run the server :
							./server portno.
							e.g 
							./server 12345


The servers are just an echo server. It just echoes back whatever message client gives.

For connecting to server:
 					To compile client code:
 											gcc client.c -o client
 					To run the client code:
 											./client IP-address portno
 											e.g.
 											./cllient 127.0.0.1 12345 (server's IP address and port no.)

 					Can also connect using nc command :
 											nc IP-address portno.
 											e.g.
 											nc 127.0.0.1 12345 


 					127.0.0.1 is the locahost IP address.


Stage-1:

The Stage 1 of the socket contains the code of the basic server.

The server accepts only 1 connection at a time. Its queues the request in form of a first come first server basis. 
So till the previous client has not been handled, it cannot handle any other request.

Stage-2:

The Stage 2 of the socket contains the code for the server that can process silmultaneous requests from the client.

The server can accept multiple clients request at the same time and process them. This server creates a seperate child process for handling the client and lets the child process handle the current client.

Stage-3

The Stage 3 of the socket contains the code for the server that can handle muliple client.

The server accept multiple  clients request at the same time by creating a new thread for every client connection. Thus the new thread handles the client request and the main thread waits for more incoming connection.