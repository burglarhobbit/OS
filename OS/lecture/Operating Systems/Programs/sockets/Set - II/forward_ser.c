/* forward_ser.c
   This is a simple server that forwards datagrams between two clients. 

   Algorithm outline
     a. Open a UDP socket 
     b. Initialize server socket address structure
     c. Bind SER_PORT and INADDR_ANY to the open socket
        (SER_PORT = 49499, an arbitrary number > 49151)
     d. Wait for a datagram from each of the two clients to set up a 
        logical connection. 
     e. Read a datagram from one client and send it to the other client
     f. go back to e.

   To compile:       gcc -o forward_ser forward_ser.c -lsocket    
   Command syntax:   forward_ser & 
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define  MAXCLI    2         /* max # of concurrent clients */
#define  SER_PORT  49499     /* an arbitrary number > 49151 */

main()
{
  int i, clino, ser_sock, ser_len, cli_len, maxfdp1;
  ssize_t nread;
  char tempbuf[BUFSIZ], buf[MAXCLI][BUFSIZ];
  struct sockaddr_in ser, tempaddr, cli[MAXCLI];
  fd_set readset;
  int bclients(struct sockaddr_in, struct sockaddr_in *), 
      clientno(struct sockaddr_in, struct sockaddr_in *);

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

          /* to initialize sockaddr_in structures in the clients array */
  for (i = 0; i < MAXCLI; i++)
      cli[i].sin_addr.s_addr = 0;

          /* to wait for the first datagram from each client */
  cli_len = sizeof(tempaddr);
  while (1) {
      nread = recvfrom(ser_sock, tempbuf, BUFSIZ, 0,  /* wait for a client */
                      (struct sockaddr *)&tempaddr, &cli_len);
      if (nread == (ssize_t)-1) {
          fprintf(stderr, "recvfrom() failed\n"); 
          exit(3);
      }
      clino = bclients(tempaddr, cli);
      strncpy(buf[clientno(tempaddr, cli)], tempbuf, (size_t)nread);/*memcpy BUG*/
      if (clino == MAXCLI)
          break;
  }

          /* to forward initial datagrams between clients */
  for (i = 0; i < MAXCLI; i++) {
      sendto(ser_sock, buf[i], strlen(buf[i]), 0,  /* send to another client */
             (struct sockaddr *)&cli[(i+1)%2], cli_len); 
  }

          /* to forward datagrams between clients - an infinite loop !! */
  while (1)  {                    
      for (i = 0; i < MAXCLI; i++) {
          nread = recvfrom(ser_sock, tempbuf, BUFSIZ, MSG_PEEK,  /* peek only */
                          (struct sockaddr *)&tempaddr, &cli_len);
          if (nread > 0) {
              nread = recvfrom(ser_sock, tempbuf, BUFSIZ, 0,  /* a real read */
                              (struct sockaddr *)&tempaddr, &cli_len);
              clino = clientno(tempaddr, cli);             /* which client? */ 
              sendto(ser_sock, tempbuf, (size_t)nread, 0,  /* forwarding */
                    (struct sockaddr *)&cli[(clino+1)%2], cli_len); 

          }
      }
  }

  close(ser_sock);                             /* close server socket */
  return(0);                                   /* currently not reachable */
}  /* main */

/* 
   bclients() is used to build an array of clients based on their IP addrs 
*/

int bclients(struct sockaddr_in cli, struct sockaddr_in *cliary) 
{
  int i;

  for (i = 0; i < MAXCLI; i++) {
      if (cliary[i].sin_addr.s_addr != 0) {
          if (cli.sin_addr.s_addr == cliary[i].sin_addr.s_addr)
              continue;                        /* skip */
      } else {
         cliary[i] = cli;                      /* copy cli infor over */
         return(i+1);                          /* return no of clients */
     }
  }
  return(i);                                   /* return no of clients */
}  /* bclients */

/* 
   clientno() is used to return the client number for a given IP addr 
*/

int clientno(struct sockaddr_in cli, struct sockaddr_in *cliary) 
{
  int i;

  for (i = 0; i < MAXCLI; i++) {
      if (cli.sin_addr.s_addr == cliary[i].sin_addr.s_addr)
          break;
  }
  return(i);
}  /* clientno */
