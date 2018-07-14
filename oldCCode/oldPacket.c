/*------------------------------
* server.c
* Description: HTTP server program
* CSC 361
* Instructor: Kui Wu
Soroush Hajizadeh
-------------------------------*/
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <resolv.h> 

#define port 8082	//default
#define MAX_STR_LEN 120         /* maximum string length */
//#define SERVER_PORT_ID 8080     /* server port number */
#define BUF_SIZE 4096
#define QUEUE_SIZE 3		//number allowed???
		
void cleanExit();

/*---------------------main() routine--------------------------*
 * tasks for main
 * generate socket and get socket id,
 * max number of connection is 3 (maximum length the queue of pending connections may grow to)
 * Accept request from client and generate new socket
 * Communicate with client and close new socket after done
 *---------------------------------------------------------------------------*/

main(int argc, char *argv)
{
 	 int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	perform_http(sockfd);
	cleanExit();
}

/*---------------------------------------------------------------------------*
 *
 * cleans up opened sockets when killed by a signal.
 *
 *---------------------------------------------------------------------------*/

void cleanExit()
{
    exit(0);
}

/*---------------------------------------------------------------------------*
 *
 * Accepts a request from "sockid" and sends a response to "sockid".
 *
 *---------------------------------------------------------------------------*/

perform_http(int sockid)
{
 int newsockfd, clilen;
    int newsockid; /* return value of the accept() call */
	setsockopt(SO_REUSEADDR)   ;
   char buff[4096];
	int n;


if (sockid < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
	struct sockaddr_in serv_addr,cli_addr;;
   bzero((char *) &serv_addr, sizeof(serv_addr));

	 serv_addr.sin_family = AF_INET;
  	 serv_addr.sin_addr.s_addr = INADDR_ANY;
  	 serv_addr.sin_port = htons(port);
  
if (bind(sockid, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
  
 
   listen(sockid,3);
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockid, (struct sockaddr *)&cli_addr, &clilen);

 if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }

 bzero(buff,4096);
   n = read( newsockfd, 4096 );

  if (n < 0) {
  //    perror("ERROR reading from socket");
   //   exit(1);
   }
   
   printf("I was able to connect with you %s\n", buff);
 /*
 send(sockid, "GET / HTTP/1.0\r\n\r\n"
 "Host: \r\n" //"Host: localhost\r\n"
 "Connection: Keep-alive\r\n", 

strlen("GET / HTTP/1.0\r\n"
 "Host: \r\n" //"Host: localhost\r\n"
 "Connection: Keep-alive\r\n"),0);
*/
 n = write(newsockfd,"I got the message\n", 18);
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
      
   return 0; 
close(sockid); 
}











