SOCKET
======
The Stage 1 of the socket contains the code of the basic server and client.

The server accepts only 1 connection at a time. Its queues the request in form of a first come first server basis. 
So till the previous client has not been handled, it cannot handle any other request.