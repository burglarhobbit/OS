/* server process */ 
#include <ctype.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <signal.h> 
#define SIZE sizeof(struct sockaddr_in) 
void catcher(int sig); 
int newsockfd; 
int main(void) 
{ 
int sockfd; 
char c;
struct sockaddr_in server = {AF_INET, 7000, INADDR_ANY}; 
static struct sigaction act; 
act.sa_handler = catcher; 
sigfillset(&(act.sa_mask)); 
sigaction(SIGPIPE, &act, NULL); 
/* set up the transport end point */ 
if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{ 
	perror("socket call failed"); 
	exit(1); 
	} 
/* bind an address to the end point */ 
if ( bind(sockfd, (struct sockaddr *)&server, SIZE) == -1) 
	{ 
	perror("bind call failed"); 
	exit(1); 
	}
/* start listening for incoming connections */ 
if ( listen(sockfd, 5) == -1 ) 
{ 
	perror("listen call failed"); 
	exit(1) ; 
	} 
	for (;;) 
	{ 
		/* accept a connection */ 
		if ( (newsockfd = accept(sockfd, NULL, NULL)) == -1) 
		{ 
		perror("accept call failed"); 
		continue; 
		} 
	/* spawn a child to deal with the connection */
	if ( fork() == 0) 
	{ 
		while (recv(newsockfd, &c, 1, 0) > 0) 
		{ 
			c = toupper(c); 
			send(newsockfd, &c,1, 0); 
		} 
		/* when client is no longer sending information the socket can be closed and the child process terminated */ 
		close(newsockfd); 
		exit (0); 
	} 
		/* parent doesn't need the newsockfd */ 
	close(newsockfd); 
} 
} 
void catcher(int sig) 
{ 
	close(newsockfd); 
	exit (0); 
}
