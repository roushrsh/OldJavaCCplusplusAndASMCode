/*------------------------------

Soroush Hajizadeh
Assignment 3

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
#include <netinet/in.h>
//#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <pcap.h>


#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <resolv.h> 


#include <netinet/if_ether.h>
#include <arpa/inet.h>


#include <sys/cdefs.h>
#include <sys/types.h>

int minimumWindow =0;
int maximumWindow =0;
int totalP = 0;
int NUMBER = 0;
int NumbSin = 0;
int NUMBEROFCONNECTIONS = 0;
int reset = 0;

int frags =0;
int lastFragOff = 0;

struct icmphdr{
unsigned fixbug :32;  
unsigned fixbugg :32;
unsigned fixbuggg :32;
unsigned fixbugggg :32;
unsigned fixbuggggg :32;        
  u_int8_t type;		/* message type */
 u_int8_t code;		/* type sub-code */
 u_int16_t checksum;
	u_int16_t filler1;
	u_int16_t sequenceA;
	u_int32_t filler3;
	u_int32_t filler4;
	u_int32_t filler5;
	u_int32_t filler6;
	u_int32_t filler7;
	u_int32_t filler8;
	u_int16_t filler11;
	u_int16_t sequenceB;

  union  {
    struct    {
//unsigned datsaofsf :32;
//unsigned dataofsf :16;
//unsigned dataoff :32;
//unsigned dataoffdf :32;
//unsigned dataofedfdf :32;
///unsigned dataoffedf :32;
//unsigned dataofsdfdf :32;
//unsigned dataofff :32;
//unsigned datadsofff :32;
//unsigned datadsoffwf :32;
//unsigned datadsssofff :32;
//unsigned datadsoffwwf :32;
//unsigned datadsoffwf2 :32;
//unsigned datadwesoffwf :32;
      u_int16_t	id;
      u_int16_t	sequence;
    } echo;			/* echo datagram */
    u_int32_t	gateway;	/* gateway address */
    struct    {
      u_int16_t	__unused;
      u_int16_t	mtu;
    } frag;			/* path mtu discovery */
  } un;
};


struct NODE {
	int val;
	double time;
	int ttl;
	int protocol;
	char* sourceAdd;
	char* destinationAdd;
	int offset;
	int fragment;
	int seqNumWindowsA;
	int seqNumWindowsB;
	int portNumLinux;
	struct NODE * prev;
	struct NODE * next;
};

typedef struct NODE item;
item *curr, *head, *chosen, *timeA, *timeB, *TCALC;



const char *timestamp_string(struct timeval ts)	{
	static char timestamp_string_buf[256];

	sprintf(timestamp_string_buf, "%d.%06d",
		(int) ts.tv_sec, (int) ts.tv_usec);

	return timestamp_string_buf;
	}
	int j = 0;
char* ErrA;
char* ErrB;
char* list [999];
double listFinalTime [999];
int sourcePortA[999];
int sourcePortB[999];

int main(int argc, char **argv){

	if (argc < 2) { 
		fprintf(stderr, "Usage: %s <pcap>\n", argv[0]); 
    		exit(1); 
  	}
 	struct bpf_program fp;

////////////


	pcap_t *handle; 
	ReadTraceFile(handle, argv);

	stack_reverse(&head);

	char* maintain = (char*) malloc (100*1);
	strncpy(maintain , head->sourceAdd, 100);
	
	char* dodge = (char*) malloc (100*1);
	strncpy(dodge, head->destinationAdd, 100);	

 	char* dos = (char*) malloc (100*1);
	char* stupid = (char*) malloc (100*1);



	printf("The IP address of the source node: %s \n", head->sourceAdd);
	printf("The IP address of the ultimate destination node: %s \n", head->destinationAdd);
	printf("The IP addresses of the intermediate destination nodes:\n");
	
	int m ;
	for (m=0; m<999; m++){
	//	listTime[m] = malloc (100);
	//int SourcePORT[999];
	 	list[m] = malloc (100);
	}

	int Z = 1;
	int x = 0;
		chosen = head;
		while (chosen != NULL){
			strncpy(dos , chosen->destinationAdd, 100);		
			strncpy(stupid, chosen->sourceAdd, 100);
			if(strcmp(dos, maintain) == 0) {
					if((strcmp(dodge, stupid) == 0) ){
						break;
					}
					
					if(strcmp(dos, dodge) != 0){

						if (Unique(stupid) ==1){
							printf("	router %d: ", Z);
							printf("%s\n", stupid);
							strcpy(list[j],stupid);

							listFinalTime[j] = (double)chosen->time;
							sourcePortA[j] = chosen->seqNumWindowsA;
							sourcePortB[j] = chosen->seqNumWindowsB;
							j = j+1;

							Z = Z+1;
							
						}
						
					}
			}

			chosen = chosen->next ;
		}
	
	printf("\nThe values in the protocol field of IP headers:\n");
	int UDPQ = 0;
	int ICMPQ = 0;

	chosen = head;
	while (chosen != NULL){
		if (chosen->protocol == 1){
			ICMPQ = ICMPQ+1;
		}
		if (chosen->protocol == 17){
			UDPQ = UDPQ+1;
		}			
		chosen = chosen->next ;
	}

	if(ICMPQ !=0){
		printf("1: ICMP\n");
	}
	if (UDPQ !=0){
		printf("17: UDP");	
	}
	printf("\n\n");	

	printf("The number of fragments created from the original datagram is:\n");
	printf("%d\n", frags);

	printf("The offset of the last fragment is:\n");
	printf("%d\n\n", lastFragOff);

	int bb;
	if (frags ==0){
	 bb = 0;
	}

	if (UDPQ == 0){ 			//ip packet WINDOWS
	double RRT;
	int n ;
	for (m=0; m<j; m++){
		RRT = RRTCal(sourcePortB[m], listFinalTime[m] );
		//printf("%f \n", listFinalTime[m]);
	//	printf("%d \n", sourcePortB[m]);
		//printf("%d \n", sourcePortA[m]);
		printf("The avg RRT between %s and %s is (see above) ms, the s.d. is: %d ms \n", ErrA, list[m],  bb);
	}


	printf("The avg RRT between %s and %s is (see above) ms, the s.d. is: %d ms\n", ErrA, ErrB,  bb);



	}else{					//non ip packet LINUX

	}
}


int RRTCal(int input, double time){
	double timefinal;
	chosen = head;
	while (chosen != NULL){
		if ((chosen->seqNumWindowsA) == input){
			timefinal = (chosen->time);

			break;
		}
		chosen = chosen->next ;
	}
	printf("\n%f - %f\n", timefinal, time);

	double m = (timefinal - time);
	return m;
}



int Unique(char *input){
	int i;
    for (i = 0; i < 999; i++) {
        if (strcmp(input, list[i]) == 0){
            return 0;
        }
    }
    return 1;
}


stack_reverse(item **head){
    item *temp, *prev;
    if (*head == NULL)    {

    }else if ((*head)->next == NULL){
    }else if ((*head)->next->next == NULL){
        (*head)->next->next = *head;
        *head = (*head)->next;
        (*head)->next->next = NULL;
    } else{
        prev = *head;
        temp = (*head)->next;
        *head = (*head)->next->next;
        prev->next = NULL;
        while ((*head)->next != NULL){
            temp->next = prev;
            prev = temp;
            temp = *head;
            *head = (*head)->next;
        }
        temp->next = prev;
        (*head)->next = temp;
    }

}





double standarddev() {
}
 

//Open trace file & search for all unique connections
ReadTraceFile(pcap_t *handle, char **argv){
   	char *src = (char*) malloc (100*1);
	char *dest = (char*) malloc (100*1);
	char *filtfinal = (char*) malloc (100*1);
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

	handle = pcap_open_offline(argv[1], errbuf); //resets
	packet_counter = Count(handle, "");

	
	handle = pcap_open_offline(argv[1], errbuf); 

	filter(handle, "(icmp && port ! 53) or (udp && dst port ! 1900 && dst port ! 123)");
	while (packet = pcap_next(handle, &header)) { 
		curr = (item *)malloc(sizeof(item));
		if (Counter(packet, header.ts) == -1){
			break;		
		}
		curr = head;

		NUMBER = NUMBER+1;
   	}


	src = head->sourceAdd;
	dest = head->destinationAdd;
	handle = pcap_open_offline(argv[1], errbuf);



	char filterz[] = "src host %s and dst host %s";

    	sprintf(filtfinal, filterz, ErrA, ErrB);
	filter(handle, filtfinal);

	while (packet = pcap_next(handle, &header) ) { 
			if (OffSetCount(packet, header.ts) == -1){
				break;		
			}
   	}



	pcap_close(handle); 
  	return 0; 


}


OffSetCount(const u_char *packet, struct timeval ts){

	struct ip *ip;
	struct icmphdr *icmp;	

	unsigned int IP_header_length;
 	unsigned char *buffer = (unsigned char *)malloc(65536);
	packet += sizeof(struct ether_header);
	icmp = (struct icmphdr*) packet;
	ip = (struct ip*) packet;

	IP_header_length = ip->ip_hl * 4;	

	packet += IP_header_length;

	if (ntohs(ip->ip_off) & IP_MF){
		frags++;
	}else{
		lastFragOff = (ntohs(ip->ip_off) & IP_OFFMASK) *8;
		return -1;
	}
	

	
}




int COUNTSTART =0;
int COUNTEND =0;
int prevTTL =9999;
int Boolean = 0;
int bob = 0;
int sure = 0;
int IPSOURCE;
int IPDEST;


char* ipAvant;
char* ipApres;


/////////////////////////////////////////////////////////////////////////////////////
Counter(const u_char *packet, struct timeval ts){


	ipAvant = (char*) malloc (100*1);
	ipApres = (char*) malloc (100*1);

	char* letemps = (char*) malloc (100*1);
	strcpy(letemps, timestamp_string(ts));
	double temps; 
	temps = strtod(letemps, NULL);

	struct ip *ip;
	struct icmphdr *icmp;	

	unsigned int IP_header_length;
 	unsigned char *buffer = (unsigned char *)malloc(65536);
	packet += sizeof(struct ether_header);
	icmp = (struct icmphdr*) packet;
	ip = (struct ip*) packet;

	IP_header_length = ip->ip_hl * 4;	

	packet += IP_header_length;

	
	int seq = htons(icmp->sequenceA);
	int seq2 = htons(icmp->sequenceB);

	curr -> ttl = ip->ip_ttl;

	char* srcIP = (char*) malloc (100*1);
	char* destIP = (char*) malloc (100*1);
	strncpy(srcIP , inet_ntoa(ip->ip_src), 100);
	strncpy(destIP, inet_ntoa(ip->ip_dst), 100);
	if (icmp->type ==9){
		return 0;	
	}


	if (Boolean != 0 ){

	if (icmp->type ==3){
		return 0;	
	}

		prevTTL = ip->ip_ttl;;
		curr -> sourceAdd = srcIP;
		curr -> destinationAdd = destIP;
		curr -> fragment = ip->ip_off;
		curr -> protocol = ip->ip_p;
		curr -> time = temps;;

		//printf("%d \n", seq);
		
		curr->seqNumWindowsA = seq;
		curr->seqNumWindowsB = seq2;
		curr -> next  = head;


  		head = curr;
	if (icmp->type ==0){
		return -1;
	}
			
	}

	if (Boolean == 0 && (ip->ip_ttl) == 1){		//else count Start++
	char* ErrAR= (char*) malloc (100*1);
	char* ErrBR = (char*) malloc (100*1);

		prevTTL = ip->ip_ttl;
		Boolean = 1;
		curr -> sourceAdd = srcIP;
		curr -> destinationAdd = destIP;
		curr -> fragment = ip->ip_off;
		curr -> protocol = ip->ip_p;
		curr -> time = temps;
		curr->seqNumWindowsA = seq;
		curr->seqNumWindowsB = seq2;
		 curr -> next  = head;
                 head = curr;
		//	printf("%d \n", seq);
	strncpy(ErrAR , inet_ntoa(ip->ip_src), 100);
	strncpy(ErrBR, inet_ntoa(ip->ip_dst), 100);
	
		ErrA = ErrAR;
		ErrB = ErrBR;
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





int Count(pcap_t *handle){
	struct pcap_pkthdr header;
//	filter(handle, filt); 
	const u_char *packet; 
	int reset =0;
	 while (packet = pcap_next(handle, &header)) { 
		packetLookup(packet, header.ts, header.caplen);
		reset++; 
   	}	
	return reset; 
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


