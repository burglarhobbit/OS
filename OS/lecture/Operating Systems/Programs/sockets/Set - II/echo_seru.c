/* echo_seru.c
   This program illustrates an iterative version echo server using UDP 

   Algorithm outline
     a. Open a UDP socket 
     b. Initialize server socket address structure
     c. Bind SER_PORT and INADDR_ANY to the open socket
        (SER_PORT = 49495, an arbitrary number > 49151)
     d. Wait for a datagram from a client
     e. Send response back to client
     f. Go back to d.

   This program also shows:
     a. How to zero out a structure (bzero())
     b. Host to network byte order conversion short (htons())
     c. Host to network byte order conversion long (htonl())
     d. Use of recv(), which is read() + options 
     e. Use of send(), which is write() + options 
        Be aware that recv() and send() return values of ssize_t

   To compile:       gcc -o echo_seru echo_seru.c -lsocket    
   Command syntax:   echo_seru & 
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define  SER_PORT  49495     /* arbitrary; official echo server port is 7 */

main()
{
  int ser_sock, ser_len, cli_len;
  ssize_t nread;
  char buf[BUFSIZ];
  struct sockaddr_in ser, cli;

          /* to open a socket */
  if ((ser_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  {
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
          /* to wait for datagrams from clients, 1 at a time */
  cli_len = sizeof(cli);
  for (;;) {       /* run forever till terminated manually */
      nread = recvfrom(ser_sock, buf, BUFSIZ, 0,  /* wait for client */
                       (struct sockaddr *)&cli, &cli_len);
      if (nread == (ssize_t)-1) {
          fprintf(stderr, "recvfrom() failed\n"); 
          exit(3);
      }
      sendto(ser_sock, buf, (size_t)nread, 0,  /* echo back to client */
             (struct sockaddr *)&cli, cli_len);
  }
  close(ser_sock);                             /* close server socket */
  return(0);                                   /* currently not reachable */
}  /* main */
