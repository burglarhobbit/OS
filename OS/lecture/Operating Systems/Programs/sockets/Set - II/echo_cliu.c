/* echo_cliu.c
   This the client program for echo_seru.c

   Algorithm outline:
     a. Open a UDP socket.
     b. Initialize server socket address structure
     c. Send user input to server
     d. Display server response on screen
     e. Close socket.

   This program also illustrates:
     a. Use of gethostbyname() to get some infor. on intended server.
     b. Use of bcopy() to copy an element into a structure.

   To compile:       gcc -o echo_cliu echo_cliu.c -lsocket -lnsl 
   Command syntax:   echo_cliu  server_name (either DNS or IP)
*/

#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define  SER_PORT  49495     /* arbitrary; official echo server port is 7 */

main(int argc, char *argv[])
{
  int cli_sock, ser_len, port_number;
  size_t nread;
  char buf[BUFSIZ];
  struct sockaddr_in  ser;
  struct hostent *ser_info;

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

          /* to send user input to server */
  nread = read(STDIN_FILENO, buf, BUFSIZ);    /* get input from stdin */
  nread = sendto(cli_sock, buf, nread, 0,     /* send data to server */
                 (struct sockaddr *)&ser, ser_len);

          /* to get and display server response */
  nread = recvfrom(cli_sock, buf, BUFSIZ, 0,  /* get server response */
                 (struct sockaddr *)&ser, &ser_len);
  write(STDOUT_FILENO, buf, nread);           /* write out to screen */
  close(cli_sock);
}  /* main */
