/*------------------------------
* client.c
* Description: HTTP client program

SOROUSH HAJIZADEH

-------------------------------*/
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include <resolv.h>  //NOTNEEDED?
/* define maximal string and reply length, this is just an example.*/
/* MAX_RES_LEN should be defined larger (e.g. 4096) in real testing. */
#define MAX_STR_LEN 120
#define MAX_RES_LEN 120

/* --------- Main() routine ------------
 * three main task will be excuted:
 * accept the input URI and parse it into fragments for further operation
 * open socket connection with specified sockid ID
 * use the socket id to connect sopecified server
 * don't forget to handle errors
 */

main(int argc, char *argv){
    char uri[MAX_STR_LEN];
    char hostname[MAX_STR_LEN];
    char identifier[MAX_STR_LEN];
    int sockid, port;
    char NAME[MAX_STR_LEN];
/////////////
port = 80;//81; //DEFAULT//////////////////////////////////////
//asked instructor and he said not to bother with other ports, just use 80

#define BUF_SIZE 4096

    printf("Open URI:  ");
    scanf("%s", uri);


 printf("\n");
 printf("\n");
 printf("%s", "test1: ACTUAL INPUT ");///////////////
 printf("%s", uri);///////////////
 printf("\n");

 printf("%s", "test2 hostname: ");//////////////
      parse_URI(uri, hostname, &port, identifier);

NAME == hostname;
strncpy(NAME, hostname, MAX_STR_LEN);
	struct hostent *test = gethostbyname(hostname);
	struct in_addr **addr_list = (struct in_addr **)test->h_addr_list;
	strncpy(hostname, test->h_name, MAX_STR_LEN);	
	strncpy(hostname, inet_ntoa(*addr_list[0]),MAX_STR_LEN);

printf("\n");
 printf("%s", "test2.5 PORT: ");///////////////
 printf("%d", port);///////////////
printf("\n");
 printf("%s", "test3 IP: ");///////////////
 printf("%s", hostname);///////////////
 printf("\n");
 printf("%s", "test4 (IDENTIFIER, MAY BE FALSE): ");///////////////
 printf("%s", identifier);///////////////
 printf("\n");
 printf("%s", "test5: ");///////////////
 printf("%s", "Let us begin!");///////////////
 printf("\n");

      sockid = open_connection(hostname, port);
      perform_http(sockid, identifier, NAME);


}


/*------ Parse an "uri" into "hostname" and resource "identifier" --------*/

parse_URI(char *uri, char *hostname, int *port, char *identifier){
//get URI, PARSE IT
 
char end[MAX_STR_LEN];
char str[MAX_STR_LEN];
 strcpy (str, uri);
 char final[MAX_STR_LEN];
 int i;
 int number = 0;
int COUNTER =0;
char final4[MAX_STR_LEN];
char final5[MAX_STR_LEN];
int portcount =0;
char porter[MAX_STR_LEN];
char sorter[MAX_STR_LEN];
////
int one = 0;
int two = 0;
////////////////
int CC = 0;
int DD = 0;

	if(str[0] != 'h'){
 		for (i = 0; i<MAX_STR_LEN; i++) {   //check for port in name
			if (str[i] != ':'){
			 	CC = CC+1;
			}else{
				portcount = portcount+1;
				break;
			}
		}/////
	DD = CC;
	}

	if (portcount !=0){
 		for (i = CC+1; i<MAX_STR_LEN; i++) {
			if (str[i] != '/' && str[i] != ' '){
			 	porter[one] = str[i];
				one = one +1;
			}else{
				break;
			}
		}
		*port = atoi(porter);
	//////////////////////

		one = 0;
		for (i = 0; i<MAX_STR_LEN; i++) {
				if (str[i] != ':'){
				 	end[i] = str[i];
					one = one +1;
				}else{
					 break;
				}
			}


		two = one;
		
	
		for (i = one; i<MAX_STR_LEN-one; i++) {
			if(str[i] != '/'){
				one = one+1;
			}else{
				break;
			}
		} 


		for (i = one; i<MAX_STR_LEN-one; i++) {
				if (str[one] != ':'){
				 	end[two] = str[i];
					two = two +1;
				}else{
					 break;
				}
			}


		strncpy(str, end,MAX_STR_LEN);	

	}


//////////////////////////////////////////


	if(str[0] == 'w'){

		 for (i = 0; i<MAX_STR_LEN; i++) {
			if (str[i] != '/' && str[i] != ' ' ){
			 	COUNTER = COUNTER +1;
			}else{
				break;
			}
		}
		 char final2[COUNTER];	
		 for (i = 0; i<COUNTER; i++) {
			final2[number] = str[i]; 
			number = number +1;	
		  }
				 	
		 strncpy(hostname, final2,MAX_STR_LEN);	
	///identifier	
		number = 0;
		char IDENTIFY[MAX_STR_LEN - COUNTER];
		 for (i = COUNTER; i<MAX_STR_LEN; i++) {
			IDENTIFY[number] = str[i]; 
			number = number +1;	
		  }

		strncpy(identifier, IDENTIFY,MAX_STR_LEN-COUNTER);	
		//return;
/////////////////////////////////////////////////////////////////////////////////

	} else if (str[0] == 'h'){
		
		 char BEGIN[7]= "http://";
		 char *temp;
		temp = strstr(str, BEGIN) ;
		 strncpy (temp, "       ", 7); 
		 for (i = 0; i<MAX_STR_LEN; i++) {
		 	if (temp[i] != ' '){
				final[number] = temp[i]; 
				number = number +1;
			}

		  }
		/////////////////////
	/*	 number = 0;
		 for (i = 0; i<MAX_STR_LEN; i++) {
		 	if (final[i] != '/'){
				final4[number] = final[i]; 
				number = number +1;	
			}else{
				i = MAX_STR_LEN;
			}

		  }

		 strncpy(hostname, final4,MAX_STR_LEN);
	*/
		number =0;
		 for (i = 0; i<MAX_STR_LEN; i++) {
			if (final[i] != '/' && final[i] != ' ' ){
			 	COUNTER = COUNTER +1;
			}else{
				break;
			}
		}
		 char final2[COUNTER];	
		 for (i = 0; i<COUNTER; i++) {
			final2[number] = final[i]; 
			number = number +1;	
		  }
				 	
		 strncpy(hostname, final2,MAX_STR_LEN);	
	///identifier	
		char IDENTIFY[MAX_STR_LEN-number];
		int up = 0;
		 for (i = number; i<(MAX_STR_LEN-number); i++) {
			IDENTIFY[up] = final[i]; 
			up = up +1;	
		  }

		strncpy(identifier, IDENTIFY,MAX_STR_LEN-COUNTER);	
		//return;
//////////////////////////////////////////////////////////////////////////////

	}else 	if(str[0] == '1'){

		 for (i = 0; i<MAX_STR_LEN; i++) {
			if (str[i] != '/' && str[i] != ' ' ){
			 	COUNTER = COUNTER +1;
			}else{
				break;
			}
		}
		 char final2[COUNTER];	
		 for (i = 0; i<COUNTER; i++) {
			final2[number] = str[i]; 
			number = number +1;	
		  }
				 	
		 strncpy(hostname, final2,MAX_STR_LEN);	

		char IDENTIFY[MAX_STR_LEN-COUNTER];
		int up = 0;
		 for (i = number; i<(MAX_STR_LEN-COUNTER); i++) {
			IDENTIFY[up] = str[i]; 
			up = up +1;	
		  }

		strncpy(identifier, IDENTIFY, MAX_STR_LEN-COUNTER);	
		//return;
	}else{
 		for (i = 0; i<MAX_STR_LEN; i++) {
			if (str[i] != '/' && str[i] != ' ' ){
			 	COUNTER = COUNTER +1;
			}else{
				break;
			}
		}
		 char final2[COUNTER];	
		 for (i = 0; i<COUNTER; i++) {
			final2[number] = str[i]; 
			number = number +1;	
		  }
				 	
		 strncpy(hostname, final2,MAX_STR_LEN);	
	}
		
	 printf("%s", hostname);
	

}


/*---------------------------------------------------------------------------*
 *
 * open_conn() routine. It connects to a remote server on a specified port.

 *
 *---------------------------------------------------------------------------*/

int open_connection(char *hostname, int port){

  int sockfd;

   struct sockaddr_in dest; 


///PRO ORACLE DAT BASE 10g CHAPTER 17 PAGE 452
    	struct sockaddr_in ADDRESS;
	 int c;
    	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	ADDRESS.sin_family = AF_INET;         // host byte order
	ADDRESS.sin_addr.s_addr = inet_addr(hostname);
	ADDRESS.sin_port = htons(port);  // Any local port will do

 	c = connect(sockfd,(struct sockaddr *) &ADDRESS,sizeof(ADDRESS));

	if(c<0) {
		fatal("connection failed");
	} else{
	        printf("%s \n", "test6: successfuly connected!");
		return sockfd;
	}
connect(sockfd,(struct sockaddr *) &ADDRESS,sizeof(ADDRESS));

  return sockfd;
}



/*------------------------------------*
* connect to a HTTP server using hostname and port,
* and get the resource specified by identifier
*--------------------------------------*/
perform_http(int sockid, char *identifier, char *NAME, int NUMBA){
char buf[BUF_SIZE];
int fd, got;
int s,bytes;
char recvline[BUF_SIZE + 1];
int n;

      printf("%s", "Good till now");
      printf("\n");
      printf("---Request begin---");

      printf("\n");
char HOSTER[strlen(NAME)] ;
char IDENTITY[strlen(identifier)] ;

strncpy(IDENTITY, identifier,strlen(identifier));	
strncpy(HOSTER, NAME,strlen(NAME));	
/////////////////////

//char request[MAX_STR_LEN] = "GET http://www.uvic.ca/index.html HTTP/1.0" "Host: www.uvic.ca" "Connection: Keep-Alive";
/*strcat(request, identifier);
strcat(request," HTTP/1.0\r\n\r\n"
 "Host: \r\n" 
 "Connection: Keep-alive\r\n");
request == "GET "
 "Host: \r\n"
 "Connection: Keep-alive\r\n";
*/

/*if (write(sockid, "GET http://www.uvic.ca/index.html HTTP/1.0\r\n\r\n" "Host: www.uvic.ca" "Connection: Keep-Alive", strlen("GET http://www.uvic.ca/index.html HTTP/1.0" "Host: www.uvic.ca" "Connection: Keep-Alive"),0)>= 0){

*/
	    printf("\n");
      printf("%s", HOSTER);
      printf("\n");
      printf("%s", identifier);
      printf("\n");


char request[BUF_SIZE]= "Get ";
//if(IDENTITY != NULL){
	//strcat(request, identifier);
//}
strcat(request, "/");
strcat(request, " HTTP/1.0\r\n");
strcat(request, "Host: ");
strcat(request, NAME);
strcat(request,"\r\n");
//strcat(request, "\r\n");
strcat(request,"Connection: Keep-Alive");
strcat(request,"\r\n");

//"GET /current-students/index.php/ HTTP/1.0\r\n" "Host: www.uvic.ca\r\n"  "\r\n"

	if (writen(sockid, request, strlen(request) ,0)>= 0){
      printf("\n");
	printf("---has been sent---");
      printf("\n");      printf("\n");      printf("\n");      printf("\n");
          

	 if( n = readn(sockid, recvline, sizeof(recvline), 0)){
		printf("\n%s", recvline);
            if (n > 0 )
                printf("%s", recvline);
	
 //	close(sockid);
	}
	}
}

	fatal(char *string){
		printf("%s\n", string);
		exit(1);
	}



/*
//extra: short method to get hostname from just name 
 struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( uri ) ) == NULL) 
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        strcpy(hostname , inet_ntoa(*addr_list[i]) );
        return 0;
    }
     
    return 1;*/

