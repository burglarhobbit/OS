/* echoserver.c
   This program illustrates an iterative version echo server using TCP 

   Algorithm outline
     a. Open a TCP socket 
     b. Initialize server socket address structure
     c. Bind SER_PORT and INADDR_ANY to the open socket
        (SER_PORT = 49494, an arbitrary number > 49151)
     d. Create a queue to hold client requests
     e. Wait for connection request from a client
     f. Get data from client
     g. Send response back to client
     h. Close client connection 
     i. Go back to e.

   This program also shows:
     a. How to zero out a structure (bzero())
     b. Host to network byte order conversion short (htons())
     c. Host to network byte order conversion long (htonl())
     d. Use of recv(), which is read() + options 
     e. Use of send(), which is write() + options 
        Be aware that recv() and send() return values of ssize_t

   To compile:       gcc -o echoserver echoserver.c -lsocket    
   Command syntax:   echoserver & 
*/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define  LISTENQ 5           /* max concurrent client requests allowed */ 
#define  SER_PORT  49494     /* arbitrary; official echo server port is 7 */

main()
{
  int ser_sock, cli_sock, ser_len, cli_len;
  size_t nread;
  char buf[BUFSIZ];
  struct sockaddr_in ser, cli;

          /* to open a socket */
  if ((ser_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)  {
      fprintf(stderr, "Unable to create server socket\n");
      exit(1);
  }
          /* to initialize server sockaddr_in structure */
  ser_len = sizeof(ser);            /* to get ser socket struct length */
  bzero((char *)&ser, ser_len);     /* to zero out struct */
  ser.sin_family      = AF_INET;    /* domain Internet */
  ser.sin_port        = htons(SER_PORT);    /* echo server port */
  ser.sin_addr.s_addr = htonl(INADDR_ANY);  /* any IP address accepted */

          /* to bind open socket to an IPaddr/service port pair */
  if ((bind(ser_sock, (struct sockaddr *)&ser, ser_len)) == -1) {
      fprintf(stderr, "Unable to bind to service port for server\n");
      exit(2);
  }

          /* to place the socket in passive mode */
  if (listen(ser_sock, LISTENQ)) {   /* to create a connection request Q */
      fprintf(stderr, "Unable to create a client request queue\n");
      exit(3);                       /* listen() does not fail frequent */
  }
          /* to wait for connection requests from clients, 1 at a time */
  cli_len = sizeof(cli);
  for (;;) {       /* run forever till terminated manually */
      cli_sock = accept(ser_sock, (struct sockaddr *)&cli, &cli_len);
          /* accept() blocks until a client connection request arrives */
      if (cli_sock == -1) {
          fprintf(stderr, "accept() failed\n"); 
          exit(4);
      }
      nread = recv(cli_sock, buf, BUFSIZ, 0);  /* read from client */
      send(cli_sock, buf, nread, 0);           /* write back to client */
      close(cli_sock);                         /* close client connection */
  }
  close(ser_sock);                             /* close server socket */
  return(0);                                   /* currently not reachable */
}  /* main */
