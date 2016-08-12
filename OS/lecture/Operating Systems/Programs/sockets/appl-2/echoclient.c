/* echoclient.c
   This the client program for echoserver.c

   Algorithm outline:
     a. Open a TCP socket.
     b. Initialize server socket address structure
     c. Connect to server
     d. Send user input to server
     e. Display server response on screen
     f. Notify server of intent to close
     g. Close socket.

   This program also illustrates:
     a. Use of gethostbyname() to get some infor. on intended server.
     b. Use of bcopy() to copy an element into a structure.
     c. Use of shutdow() to notify server of closing connection.

   To compile:       gcc -o echocliient echoclient.c -lsocket -lnsl 
   Command syntax:   echoclient  server_name (either DNS or IP)
*/

#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define  SER_PORT  49494     /* arbitrary; official echo server port is 7 */

main(int argc, char *argv[])
{
  int cli_sock, ser_len, port_number;
  size_t nread;
  char buf[BUFSIZ];
  struct sockaddr_in  ser;
  struct hostent *ser_info;

          /* to open a socket */
  if ((cli_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)  {
      fprintf(stderr, "Unable to create socket for client\n");
      exit(1);
  }
          /* to initialize server sockaddr_in structure */
  ser_len = sizeof(ser);            /* to get ser length */
  bzero((char *)&ser, ser_len);     /* to zero out struct */
  ser.sin_family      = AF_INET;    /* Internet domain */
  ser.sin_port = htons(SER_PORT);   /* echo server port number */

  if ((ser_info = gethostbyname(argv[1])) == (struct hostent *)NULL) {
      fprintf(stderr, "unknown server\n");
      exit(2);
  }
  bcopy((char *)ser_info->h_addr, (char *)&ser.sin_addr, ser_info->h_length);

          /* to connect to server */
  if ((connect(cli_sock, (struct sockaddr *)&ser, ser_len)) == -1) {
      fprintf(stderr, "can't connect to  server\n");
      exit(3);
  }

  nread = read(STDIN_FILENO, buf, BUFSIZ);  /* get input from stdin */
  send(cli_sock, buf, nread, 0);            /* send data to server */
  nread = recv(cli_sock, buf, BUFSIZ, 0);   /* read back data */
  write(STDOUT_FILENO, buf, nread);         /* display it on screen */

  shutdown(cli_sock, SHUT_RDWR);            /* notify server of closing */
  close(cli_sock);
}  /* main */
