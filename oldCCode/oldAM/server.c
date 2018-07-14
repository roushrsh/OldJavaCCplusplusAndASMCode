/*------------------------------
* server.c
* Description: HTTP server program

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

//declaring all values needed
#define port 8083	//default
#define MAX_STR_LEN 120         /* maximum string length */
#define BUF_SIZE 4096
#define filename "/home/roushrsh/Desktop/FORSERVER/"  //directory for files
		
void cleanExit();






/*---------------------main() routine--------------------------*
 * tasks for main
 * generate socket and get socket id,
 * max number of connection is 3 (maximum length the queue of pending connections may grow to)
 * Accept request from client and generate new socket
 * Communicate with client and close new socket after done
 *---------------------------------------------------------------------------*/

main(int argc, char *argv)		//setup sockfd to the desired ip address and perform http with perform_http(sockfd)
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

perform_http(int sockid){
 int newsockfd;


   char buff[BUF_SIZE];
	int n;



if (sockid < 0) {			//incase socket isn't properly initialized
      perror("ERROR opening socket");
      exit(1);
   }
	struct sockaddr_in serv_addr, cli_addr;
   	bzero((char *) &serv_addr, sizeof(serv_addr));
		
	serv_addr.sin_family = AF_INET;				//setting up socket
  	serv_addr.sin_addr.s_addr = INADDR_ANY;
  	serv_addr.sin_port = htons(port);
  
	if (bind(sockid, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {		//binding socket
	      perror("ERROR on binding");
	      exit(1);
	}else{
		printf("\n%s", "Has been bound.");
  	}

	listen(sockid,3);			//allowing up to 3 connections

	newsockfd = accept(sockid, (struct sockaddr *)&cli_addr, &sockid);		//setting up new socket which accepts connection

 	if (newsockfd < 0) {		//testing the socket
    		  perror("ERROR on accept");
     	exit(1);
  	}
	

 	bzero(buff,BUF_SIZE+1);
  	n = read( newsockfd, buff );		//recieveing message

 	char recvline[BUF_SIZE + 1];
	int s; 
	char *buffer=malloc(BUF_SIZE);
        recv(newsockfd, recvline, BUF_SIZE, 0);

	printf("\n%s", "The recieved line is: ");		//printing out the recieved message
	printf("\n%s", recvline);
	char message[BUF_SIZE + 1];
	strncpy(message, recvline, BUF_SIZE + 1);		//storing just for safety

	 
	int i;
	int S = 0;
	int counter = 0;
	char STRING[BUF_SIZE +1];
	int empty = 0;
	
					//making sure it's a GET command
	 if ((message[0] != 'G') || (message[1] != 'E') || (message[2] != 'T') || (message[3] != ' ') ){
		char BUFFS[BUF_SIZE]  = "HTTP/1.0 501 Not Implemented." ;
		n = writen(newsockfd, BUFFS, sizeof(BUFFS),0);
		close(sockid);	
		close(newsockfd);
	}
	

			//if get command, it will find out the indicator
	for( i=0; i<(BUF_SIZE + 1); i++){
		 if (empty > 1){
			break;	
		}

		if ((counter > 2) && (message[i] != ' ')){
			STRING[S] = message[i] ;
			S = S+1;		
		} 


		if (message[i] == ' '){
			empty = empty +1;
		}

		if (message[i] == '/'){
			counter = counter +1;
		}
	}
				
	char Address[BUF_SIZE + 1];
	strncpy(Address, STRING, BUF_SIZE + 1);
	printf("\n%s", "The location requested is: ");		

	printf("%s\n", Address);			//show file indicator
	char FORSERVER[BUF_SIZE] = filename;
	strcat(FORSERVER, Address);
	printf("\n%s", "The full location is: ");		
	printf("%s\n", FORSERVER);			//show complete directory

			//making sure the file exists, else throwing 404
   	char BUFF[BUF_SIZE] = "HTTP/1.0 404 Not Found. The file you request cannot be found\n";
	FILE *send;
	send = fopen(FORSERVER, "r");
		if (send == NULL) {
			n = writen(newsockfd, BUFF, sizeof(BUFF),0);
			close(sockid);	
			close(newsockfd);
			cleanExit();
		}else {
			printf("\n%s", " ");	
    			printf("The file as been found and is being sent: %s\n", Address);
	}

	char FF[BUF_SIZE];
	FILE * pFile;
	pFile=fopen (FORSERVER,"r");		//set up pointer to file again, this time in read
	int c;
	int q = 0;
	while (1) {			//while there are characters, set up FileF
		c = fgetc (send);
		if (feof(send)){
			break;
		}else{
			FF[q] = c;
			q++;
 		 }
	}
	n = writen(newsockfd, FF, sizeof(FF),0);		//sending out the request body to the requesting client
	close(n);   	
	fclose (pFile);
 
	close(sockid);	
	close(newsockfd);
	cleanExit();
}











