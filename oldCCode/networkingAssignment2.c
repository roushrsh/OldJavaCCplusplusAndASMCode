/*------------------------------
Ass2
Soroush Hajizadeh



-------------------------------*/
#include <stdio.h>
#include <stdlib.h> /////
#include <string.h> /////
#include <net/if.h>///
#include <linux/tcp.h>
#include <time.h>//lll
#include <sys/time.h>//lll
#include <errno.h>//lll
#include <signal.h>//lll


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
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
		//SETTING UP GLOBAL VARIABLES

int minimumWindow =0;
int maximumWindow =0;
int totalP = 0;
int NUMBER = 0;
int NumbSin = 0;
int NUMBEROFCONNECTIONS = 0;
int reset = 0;

struct TCP_hdr {  //SETTING UP TCP HEADER
	char name[33];		
	uint16_t	uh_sport;		/* source port */
	uint16_t	uh_dport;		/* destination port */
//	uint8_t seqnumber;	
	uint32_t seqnumber; 
	uint32_t acknumber;
	unsigned dataoff :4;  
	unsigned push  : 6;      
        unsigned  tcp_flags : 6; 
        uint16_t winsize;    
        uint16_t cksum;     
        uint16_t tcp_urp;

};


const char *timestamp_string(struct timeval ts)	{
	static char timestamp_string_buf[256];

	sprintf(timestamp_string_buf, "%d.%06d",
		(int) ts.tv_sec, (int) ts.tv_usec);

	return timestamp_string_buf;
	}

int main(int argc, char **argv){
	
	if (argc < 2) { 
		fprintf(stderr, "Usage: %s <pcap>\n", argv[0]); 
    		exit(1); 
  	}
 	struct bpf_program fp;

	pcap_t *handle; 
	ReadTraceFile(handle, argv);


}

//Open trace file & search for all unique connections
ReadTraceFile(pcap_t *handle, char **argv){			
   
    struct in_addr ip_src,ip_dst; /* source and dest address */

	unsigned int packet_counter =0;
	struct pcap_pkthdr header;
	pcap_t *pcap;
	const u_char *packet; 
   	char errbuf[PCAP_ERRBUF_SIZE]; 
   	handle = pcap_open_offline(argv[1], errbuf); 

	if (handle == NULL) { 
		fprintf(stderr,"Couldn't open pcap file %s: %s\n", argv[1], errbuf); 
     		return(2); 
  	 } 


//////////
	handle = pcap_open_offline(argv[1], errbuf); //resets
	packet_counter = Count(handle, "");

	printf("%s %d \n", "The total number of packets: ", packet_counter);
	
	handle = pcap_open_offline(argv[1], errbuf); //resets
	reset = Count(handle, "(tcp[tcpflags] & (tcp-rst) !=0)");	
	printf("Number of reset TCP connections: %d\n", reset);


	int NSIN;
	handle = pcap_open_offline(argv[1], errbuf); //resets
	NSIN = Count(handle, "tcp[tcpflags] & (tcp-syn) !=0");
	printf("Total number of connections with syn %d \n", NSIN);

	int NFIN;
	handle = pcap_open_offline(argv[1], errbuf); //resets
	NFIN = Count(handle, "tcp[tcpflags] & (tcp-fin) !=0");
	printf("Total number of connections with fin %d \n", NFIN);
	
	int NSYNACK;
	handle = pcap_open_offline(argv[1], errbuf); //resets
	NSYNACK = Count(handle, "tcp[0xd]&18=2"); //packets with syn and ack
	printf("Total number of connections with syn-ack %d \n", NSYNACK);

	int NSF;
	handle = pcap_open_offline(argv[1], errbuf); //resets
	NSF = Count(handle, "tcp[tcpflags] & (tcp-syn | tcp-fin ) != 0 && tcp[tcpflags] & (tcp-ack) == 0"); //packets with syn and ack
	printf("Total number of connections with syn or fin without ack %d \n", NSF);

//	 "tcp[tcpflags] & ((tcp-syn) ==1 && (tcp-ack) ==0)) || (tcp-fin != 0 && tcp-ack==0)"); //packets with syn and ack

///PUT SYN INTO ARRAY
	char* SYNSIP [NSIN];
	char* SYNDIP [NSIN];
	int SYNSPort [NSIN];
	int SYNDPort [NSIN];
	double TIMESIN[NSIN];
	handle = pcap_open_offline(argv[1], errbuf); //resets
	filter(handle, "(tcp[tcpflags] & (tcp-syn) !=0)");
	while (packet = pcap_next(handle, &header)) {
		cCount(packet, header.ts, header.caplen, SYNSIP, SYNDIP, SYNSPort, SYNDPort,TIMESIN);
		NUMBER = NUMBER +1;
	}
	NUMBER = 0;
//PUT FINS INTO ARRAY
	char* FINSIP [NFIN];
	char* FINDIP [NFIN];
	int FINSPort [NFIN];
	int FINDPort [NFIN];
	double TIMEFIN[NFIN];
	handle = pcap_open_offline(argv[1], errbuf); //resets
	filter(handle, "(tcp[tcpflags] & (tcp-fin) !=0)");
	while (packet = pcap_next(handle, &header)) {
		cCount(packet, header.ts, header.caplen, FINSIP, FINDIP, FINSPort, FINDPort, TIMEFIN);
		NUMBER = NUMBER +1;
	}
	NUMBER = 0;

//PUT SYN-ACK INTO ARRAY
	char* SASIP [NSYNACK];
	char* SADIP [NSYNACK];
	int SASPort [NSYNACK];
	int SADPort [NSYNACK];
	double TIMESA[NSYNACK];
	handle = pcap_open_offline(argv[1], errbuf); //resets
	filter(handle, "tcp[0xd]&18=2");
	while (packet = pcap_next(handle, &header)) {
		cCount(packet, header.ts, header.caplen, SASIP, SADIP, SASPort, SADPort,TIMESA);
		NUMBER = NUMBER +1;
	}
	NUMBER = 0;

//PUT SYN AND FIN INTO ARRAY
	char* SFSIP [NSF];
	char* SFDIP [NSF];
	int SFSPort [NSF];
	int SFDPort [NSF];
	double TIMESF[NSF];
	handle = pcap_open_offline(argv[1], errbuf); //resets
	filter(handle, "tcp[tcpflags] & (tcp-syn | tcp-fin ) != 0 && tcp[tcpflags] & (tcp-ack) == 0"); //only TCP SYN or fin packets but not ack");
	while (packet = pcap_next(handle, &header)) {
		cCount(packet, header.ts, header.caplen, SFSIP, SFDIP, SFSPort, SFDPort,TIMESF);
		NUMBER = NUMBER +1;
	}
	NUMBER = 0;

int i = 0;
int combien =0;
	char* FINALSIP[NSF];
	char* FINALDIP [NSF];
	int FINALSPort [NSF];
	int FINALDPort [NSF];
	
	for (i = 0; i<NSF-1; i++){
		if (i<1){
			if( (SFSIP[i] =  SFSIP[i-1])  ){
				continue;		
			}
		}
		FINALSIP[i] = SFSIP[i];	
		combien = combien+1;	
	}
NUMBEROFCONNECTIONS = combien;





int n = NSF;
int j = 0;
int k = 0;


//ACTUAL PRINTING

	printf("----------------------------------------------------- \n");
	printf("----------------------------------------------------- \n");
	printf("----------------------------------------------------- \n");
	printf("A) Total number of connections: %d\n", NUMBEROFCONNECTIONS);
	printf("----------------------------------------------------- \n");
	printf("B) Connections' details \n");

for (i =1; i<NUMBEROFCONNECTIONS+1; i++){
	if( SFSPort[i] != SFSPort[i-1]){
		printf("Connection: %d \n", i);
		printf("Source address: %s\n", SFSIP[i]);
		printf("Destination address: %s\n", SFDIP[i]);
		printf("Source Port: %d \n", SFSPort[i] );	
		printf("Destination Port: %d \n", SFDPort[i] );	
		printf("Status: \n");
		printf("Start time:  %e\n",TIMESF[i]);
		printf("End Time: \n");
		printf("Duration\n");
		printf("Number of packets sent\n");
	
		printf(" \n");
	}
}



	printf("C) General");
	printf("Total number of complete TCP connections \n");
	printf("Number of reset TCP connections  %d\n",reset );
	printf("Total number of complete TCP connections \n");
	printf("Number of TCP connections that were still open when the trace capture ended:\n");
		printf(" \n");

	printf("D) Complete TCP Connections");
	printf("Minimum time durations: \n");
	printf("Mean time durations: \n");
	printf("Maximum time durations: \n"); 
	printf("Minimum RTT values including both send/received:\n");
	printf("Mean RTT values including both send/received: \n"); 
	printf("Maximum RTT values including both send/received: \n"); 
	printf("Minimum number of packets including both send/received: \n");
	printf("Mean number of packets including both send/received: \n"); 
	printf("Maximum number of packets including both send/received: \n");
	printf("Minimum receive window sizes including both send/received: %d \n", minimumWindow);
	printf("Mean receive window sizes including both send/received: \n"); 
	printf("Maximum receive window sizes including both send/received: %d \n", maximumWindow); 




	totalP = packet_counter;
	char* sourceIPA [packet_counter]; 
	char* destIPA [packet_counter]; 
	int sourcePort[packet_counter]; 
	int destPort[packet_counter]; 
	double TIME[packet_counter];

	handle = pcap_open_offline(argv[1], errbuf); 
	filter(handle, "");
	while (packet = pcap_next(handle, &header)) { 
		cCount(packet, header.ts, header.caplen, &sourceIPA, &destIPA, sourcePort, destPort, TIME);
		NUMBER = NUMBER+1;
   	}

 	

	pcap_close(handle); 
  	return 0; 


}





 cCount(const u_char *packet, struct timeval ts, unsigned int capture_len, char* sourceIPA[], char* destIPA[], int* sourcePort, int* destPort, double* time){

	struct ip *ip;
	struct TCP_hdr *tcp;
	unsigned int IP_header_length;
 	unsigned char *buffer = (unsigned char *)malloc(65536);
	packet += sizeof(struct ether_header);
	capture_len -= sizeof(struct ether_header);
	ip = (struct ip*) packet;
	IP_header_length = ip->ip_hl * 4;	

	packet += IP_header_length;
	capture_len -= IP_header_length; 

//IP setup
	char* srcIP = (char*) malloc (100*1);
	char* destIP = (char*) malloc (100*1);
	strncpy(srcIP , inet_ntoa(ip->ip_src), 100);
	strncpy(destIP, inet_ntoa(ip->ip_dst), 100);
	sourceIPA[NUMBER] = srcIP;
	destIPA[NUMBER] = destIP;
//port setup	
	sourcePort[NUMBER] = ntohs(tcp->uh_sport);
	destPort[NUMBER] = ntohs(tcp->uh_dport);

//Time setup
	char* letemps = (char*) malloc (100*1);
	strcpy(letemps, timestamp_string(ts));
	double temps; 
	temps = strtod(letemps, NULL);
	time[NUMBER] = temps;
	if (tcp->winsize < minimumWindow){
		minimumWindow = tcp->winsize;
	}
	if (tcp->winsize > maximumWindow){
		maximumWindow = tcp->winsize;
	}

}


filter(pcap_t *handle, char test[]){
	
	struct bpf_program fp;		/* The compiled filter expression */ 
	bpf_u_int32 net;		/* The IP of our sniffing device */

	 if (pcap_compile(handle, &fp, test, 0, net) == -1) {
		fprintf(stderr, "Couldn't parse filter %s: %s\n", test, pcap_geterr(handle));
		 return(2);
	 }
	 if (pcap_setfilter(handle, &fp) == -1) {
		 fprintf(stderr, "Couldn't install filter %s: %s\n", test, pcap_geterr(handle));
		 return(2);
	 }

}



//Computer RTT
ComputerRTT(){
   
}

//Update min/mean/max values	
UpdateRTTtime(){
   
}


int Count(pcap_t *handle, char* filt){
	struct pcap_pkthdr header;
	filter(handle, filt); 
	const u_char *packet; 
	int reset =0;
	 while (packet = pcap_next(handle, &header)) { 
		packetLookup(packet, header.ts, header.caplen);
		reset++; 
   	}	
	return reset; 
}



finalTime(){


}




CheckConnection(){
   //Recheck the packet to see belongs to what connection
}


 packetLookup(const u_char *packet, struct timeval ts, unsigned int capture_len){
	struct ip *ip;
	struct TCP_hdr *tcp;
	unsigned int IP_header_length;

//	packet += sizeof(struct ether_header);
//	capture_len -= sizeof(struct ether_header);


	ip = (struct ip*) packet;
	IP_header_length = ip->ip_hl * 4;

	tcp = (struct TCP_hdr*) packet;

	

}



	
//JUNK CODE

/*
 getValueSYN(const u_char *packet, char* SourceIP[], char* DestIP[], int SourcePort[] , int DestPort[]){
	struct ip *ip;
	struct TCP_hdr *tcp;
	unsigned int IP_header_length;
 	unsigned char *buffer = (unsigned char *)malloc(65536);
	packet += sizeof(struct ether_header);
	ip = (struct ip*) packet;
	//IP_header_length = ip->ip_hl * 4;
	packet += IP_header_length;


	char* srcIP = (char*) malloc (100*1);
	char* destIP = (char*) malloc (100*1);
	strncpy(srcIP , inet_ntoa(ip->ip_src), 100);
	strncpy(destIP, inet_ntoa(ip->ip_dst), 100);
	
	printf("%d", ntohs(tcp->uh_sport));

	SourceIP[NumbSin] = srcIP;
	DestIP[NumbSin] = destIP;

	SourcePort[NumbSin] = ntohs(tcp->uh_sport);
	DestPort[NumbSin] = ntohs(tcp->uh_dport);
}*/





/*
//PUT FIN-ACK INTO ARRAY
	char* FASIP [NSYNACK];
	char* FADIP [NSYNACK];
	int FASPort [NSYNACK];
	int FADPort [NSYNACK];
	double TIMEFA[NSYNACK];
	handle = pcap_open_offline(argv[1], errbuf); //resets
	filter(handle, "tcp[0xd]&18=2");
	while (packet = pcap_next(handle, &header)) {
		cCount(packet, header.ts, header.caplen, SASIP, SADIP, SASPort, SADPort,TIMESA);
		NUMBER = NUMBER +1;
	}
	NUMBER = 0;
int i = 0;
for ( i= 0; i<NSYNACK; i++){
	printf("%s ", SASIP[i]);
}
*/

/*
int i =0;
int j = 0;
int NUMB = 0;

for (i=0; i < NSYNACK; i++){
	for (j =0; j < NFIN; j++){
		if ( ( strcmp(SASIP[i], FINSIP[j]) & strcmp(SADIP[i], FINDIP[j])) | ( strcmp( SASIP[i], FINDIP[j]) & strcmp(SADIP[i], FINSIP[j]) )){
		}
		if (i==j){	//no dup found
			NUMB = NUMB +1;
		}
	}
}

printf("%d", NUMB);*/
// 
////////////////////////////////////////////////////////////

//find unique sins
	
/*
	int i = 0;
	int j = 0;
	int NSINN = 0;
	for (i =0; i < NSIN; i++){
		for(j = 0; j<i; j++){
			if ( ( (SYNSPort[i] == SYNSPort[j]) & (SYNDPort[i] == SYNDPort[j]) & strcmp(SYNSIP[i],SYNSIP[j]) & strcmp(SYNDIP[i],SYNDIP[j]) ) | ( (SYNSPort[i] == SYNDPort[j]) & (SYNDPort[i] == SYNSPort[j]) & strcmp(SYNSIP[i], SYNDIP[j]) & strcmp(SYNDIP[i], SYNSIP[j]) )	)
				break;
		}
		if (i==j){	//no dup found
			NSINN = NSINN +1;
		}
	}

	printf("UNIQUE SIN %d ", NSINN); */
/*
	char* SYNSIPN [NSINN];
	char* SYNDIPN [NSINN];
	int SYNSPortN [NSINN];
	int SYNDPortN [NSINN];
	int follow =0;

	for (i =0; i < NSIN; i++){
		for(j = 0; j<i; j++){
			if ( ( (SYNSPort[i] == SYNSPort[j]) & (SYNDPort[i] == SYNDPort[j]) & strcmp(SYNSIP[i],SYNSIP[j]) & strcmp(SYNDIP[i],SYNDIP[j]) ) | ( (SYNSPort[i] == SYNDPort[j]) & (SYNDPort[i] == SYNSPort[j]) & strcmp(SYNSIP[i], SYNDIP[j]) & strcmp(SYNDIP[i], SYNSIP[j]) )	)
				break;
		}
		if (i==j){
		SYNSIPN[follow] = SYNSIP[i];
		SYNDIPN[follow] = SYNDIP[i];
		SYNSPortN[follow] = SYNSPort[i];
		SYNDPortN[follow] = SYNDPort[i];
		follow = follow +1;
		}
	}*/


////////////////////FOR FIN
/*	int NFINN = 0;
	for (i =0; i < NFIN; i++){
		for(j = 0; j<i; j++){
			if ( ( (FINSPort[i] == FINSPort[j]) & (FINDPort[i] == FINDPort[j]) & strcmp(FINSIP[i], FINSIP[j]) & strcmp(FINDIP[i], FINDIP[j]) )  | 
			(  (FINSPort[i] == FINDPort[j]) & (FINDPort[i] == FINSPort[j]) & strcmp(FINSIP[i], FINDIP[j]) & strcmp(FINDIP[i], FINSIP[j]) )	 )
				break;
		}
		if (i==j){
		NFINN= NFINN +1;
		}
	}

	printf("UNIQUE FIN %d", NFINN);
*/
/*
	char* FINSIPN [NFINN];
	char* FINDIPN [NFINN];
	int FINSPortN [NFINN];
	int FINDPortN [NFINN];
	int follow2 =0;

	for (i =0; i < NFIN; i++){
		for(j = 0; j<i; j++){
			if ( ( (FINSPort[i] == FINSPort[j]) & (FINDPort[i] == FINDPort[j]) & strcmp(FINSIP[i], FINSIP[j]) & strcmp(FINDIP[i], FINDIP[j]) )  | 
			(  (FINSPort[i] == FINDPort[j]) & (FINDPort[i] == FINSPort[j]) & strcmp(FINSIP[i], FINDIP[j]) & strcmp(FINDIP[i], FINSIP[j]) )	 )
				break;
		}
		if (i==j){
		FINSIPN[follow2] = FINSIP[i];
		FINDIPN[follow2] = FINDIP[i];
		FINSPortN[follow2] = FINSPort[i];
		FINDPortN[follow2] = FINDPort[i];
		follow2 = follow2 +1;
		}
	}



/////////////

//NUMBER OF CONNECTIONS
/*
	for (i =0; i < NSINN; i++){
		for(j = 0; j<NFINN; j++){
			if ( ( (FINSPortN[j] == SYNSPortN[i]) & (FINDPortN[j] == SYNDPortN[i]) ) & strcmp(FINSIP[j], SYNSIP[i]) & strcmp(FINDIP[j], SYNDIP[i])  | 
					( (FINSPort[j] == FINDPort[i]) & (FINDPort[j] == FINSPort[i]) & strcmp(FINSIP[j], SYNDIP[i]) & strcmp(FINDIP[j], SYNSIP[i]) ) )	
				NUMBEROFCONNECTIONS = NUMBEROFCONNECTIONS+1;
		}
	}
	
printf(" %d", NUMBEROFCONNECTIONS);





///////////

/*

	printf("\n first 3 source IP");
	printf("\n%s", SYNSIP[0]);
	printf("\n%s", SYNSIP[1]);
	printf("\n%s\n", SYNSIP[2]);

	printf("\n first 3 dest IP");
	printf("\n%s", SYNDIP[0]);
	printf("\n%s", SYNDIP[1]);
	printf("\n%s\n", SYNDIP[2]);

	printf("\n first 3 source PORT");
	printf("\n%d", SYNSPort[0]);
	printf("\n%d", SYNSPort[1]);
	printf("\n%d", SYNSPort[2]);
	printf("\n%d", SYNSPort[3]);
	printf("\n%d\n", SYNSPort[4]);


	printf("\n first 3 dest PORT");
	printf("\n%d", SYNDPort[0]);
	printf("\n%d", SYNDPort[1]);
	printf("\n%d", SYNDPort[2]);
	printf("\n%d", SYNDPort[3]);
	printf("\n%d\n", SYNDPort[4]);

*/
////CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC



//COMPARE THINGS TO GET NUMBER OF CONNECTINOS
/*	int i =0;
	int j =0;
	for (i = 0; i< NSYNACK; i++){
		for(j = 0; j<NFIN; j++){
			if( 
				( (SASPort[i] == FINSPort[j]) & (SADPort[i] == FINDPort[j]) & strcmp(SASIP[i], FINDIP[j]) & strcmp(SADIP[i], FINSIP[j])) //|
				|
				( (SASPort[i] == FINDPort[j]) & (SADPort[i] == FINSPort[j]) & strcmp(SASIP[i], FINSIP[j]) & strcmp(SADIP[i], FINDIP[j])) //|
			){
				NUMBEROFCONNECTIONS = NUMBEROFCONNECTIONS +1;
				printf("Connection: %d\n", NUMBEROFCONNECTIONS);
				printf("%d %d %s %s \n", SASPort[i], SADPort[i], SASIP[i], SADIP[i]);
				printf("%d %d %s %s \n \n", FINSPort[j], FINDPort[j], FINSIP[j], FINDIP[j]);
	
			}
		}	
	}*/

