/* forward_cli.c
   This the client program for forward_ser.c

   Algorithm outline:
     a. Open a UDP socket.
     b. Initialize server socket address structure
     c. Get filename from user, open it for read, and send filename to server
     d. Wait for server to send filename from another client
     e. Get ready to use select()
     f. Use select() to see which fd is ready for read/write
     g. go back to f until no more fd is ready, or timeout
     h. Close socket.

   To compile:       gcc -o forward_cli forward_cli.c -lsocket -lnsl 
   Command syntax:   forward_cli  server_name (either DNS or IP)
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> 
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <sys/time.h> 
#include <netinet/in.h>
#include <netdb.h>
#define  max(a1, a2)   (a1 >= a2 ? a1 : a2)
#define  SER_PORT  49499     

main(int argc, char *argv[])
{
  int cli_sock, ser_len, port_number;
  int res, rfd, maxfdp1;
  size_t nread;
  fd_set readset;
  char buf[BUFSIZ], filename[BUFSIZ];
  struct sockaddr_in  ser;
  struct hostent *ser_info;
  struct timeval timeout;
  fd_set saverset;

          /* to open a socket */
  if ((cli_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  {
      fprintf(stderr, "Unable to create socket for client\n");
      exit(1);
  }
          /* to initialize server sockaddr_in structure */
  ser_len = sizeof(ser);            /* to get ser length */
  bzero((char *)&ser, ser_len);     /* to zero out struct */
  ser.sin_family = AF_INET;         /* Internet domain */
  ser.sin_port = htons(SER_PORT);   /* echo server port number */

  if ((ser_info = gethostbyname(argv[1])) == (struct hostent *)NULL) {
      fprintf(stderr, "unknown server\n");
      exit(2);
  }
  bcopy((char *)ser_info->h_addr, (char *)&ser.sin_addr, ser_info->h_length);

          /* to get filename, open it, and send filename to server */
  nread = read(STDIN_FILENO, buf, BUFSIZ);    /* get filename from stdin */
  strncpy(filename, buf, nread);
  filename[nread-1] = '\0';                   /* remove '\n' & end with '\0' */
  if ((rfd = open(filename, O_RDONLY)) == -1)  {
      fprintf(stderr, "Can't open file\n");
      exit(3);
  }
  sendto(cli_sock, buf, nread, 0, (struct sockaddr *)&ser, ser_len);
  nread = recvfrom(cli_sock, buf, BUFSIZ, 0,  
                              (struct sockaddr *)&ser, &ser_len);
  write(STDOUT_FILENO, buf, nread);   /* write out to screen */

          /* to get ready for test for read using select() */
  FD_ZERO(&readset);                  /* clear all bits in readset */
  FD_SET(rfd, &readset);              /* turn on bit for rfd in readset */
  FD_SET(cli_sock, &readset);         /* turn on bit for cli_sock */
  maxfdp1 = max(rfd, cli_sock) + 1;   /* get the max number of fd's */
  timeout.tv_sec = 60;                /* max wait 60 sec */

          /* to start read/send using select() */
  saverset = readset;
  while (1) {
       if (res = select(maxfdp1, &readset, NULL, NULL, &timeout)) {
          if (res == -1) {
              perror("select() failed");
              break;                             /* error */
          }
          if (FD_ISSET(cli_sock, &readset))  {   /* socket is readable */
              nread = recvfrom(cli_sock, buf, BUFSIZ, 0,  
                              (struct sockaddr *)&ser, &ser_len);
              write(STDOUT_FILENO, buf, nread);  /* write out to screen */
          } 
          if (FD_ISSET(rfd, &readset))  { /* more data in file */
              nread = read(rfd, buf, BUFSIZ);    /* get data from file */
              if (nread == 0) {
                  close(rfd);                    /* must close */
                  FD_CLR(rfd, &saverset);        /* remove it from read */
              } else
                  sendto(cli_sock, buf, nread, 0,  /* send to server */
                        (struct sockaddr *)&ser, ser_len);
          } 
      } else
          break;                      /* exit infinite loop on tiemout */
      readset = saverset;             /* to reset it */
  }
  close(cli_sock);
}  /* main */
