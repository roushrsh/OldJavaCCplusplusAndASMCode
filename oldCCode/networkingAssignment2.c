/*------------------------------

* CSC 361
* Instructor: Kui Wu
Soroush Hajizadeh

//can have 2 cibbectuibsm sane siyrce abd destubatuib ip, but their source port can be different!!!

//for reset tco cibbectuibs can get 34 or 36 it deends. 36 if done twice. mention inr eadme

//find connections. Do filter per connection? so you can do things
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



int minimumWindow =0;
int maximumWindow =0;
int totalP = 0;
int NUMBER = 0;
int NumbSin = 0;
int NUMBEROFCONNECTIONS = 0;
int reset = 0;



struct NODE {
	int val;
	double time;
	int ttl;
	int protocol;
	char* sourceAdd;
	char* destinationAdd;
	int offset;
	int fragment;
	struct NODE * prev;
	struct NODE * next;
};

typedef struct NODE item;
item *curr, *head, *chosen;


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

	//flip stack
	stack_reverse(&head);

//	head = head ->next;
//	while ( head != NULL){
//		printf("The IP address of the source node: %s \n", head->sourceAdd);
//		printf("The IP address of the destination node: %s \n", head->destinationAdd);
//		printf("The ttl: %d \n", head->ttl);
//		head -> prev = head ->next;
//		head = head->next;
	//	front = head;
//	}

	char* maintain = (char*) malloc (100*1);
	strncpy(maintain , head->sourceAdd, 100);
	
	char* dodge = (char*) malloc (100*1);
	strncpy(dodge, head->destinationAdd, 100);	

 	char* dos = (char*) malloc (100*1);
				char* stupid = (char*) malloc (100*1);
	printf("The IP address of the source node: %s \n", head->sourceAdd);
	printf("The IP address of the ultimate destination node: %s \n", head->destinationAdd);
	printf("The IP addresses of the intermediate destination nodes:\n");
	
	int Z = 1;
		//chosen = (item *)malloc(sizeof(item));

		chosen = head;
		while (chosen != NULL){
			strncpy(dos , chosen->destinationAdd, 100);
		//					printf("%s\n", dos);	
					
			strncpy(stupid, chosen->sourceAdd, 100);

			//			printf("%s\n", stupid);
			
	//		printf("%s\n", chosen->sourceAdd);
		//			printf("%s\n", maintain);
		//			printf("%s\n", dos);	

			if(strcmp(dos, maintain) == 0) {
					if(strcmp(dos, dodge) != 0){
						printf("	router %d: ", Z);
						printf("%s\n", stupid);
						Z = Z+1;
					}
			}
			//		printf("SSSSSSSSSSSSSSSSSSSSSS\n");	
			chosen = chosen->next ;
		}
	
	printf("\nThe values in the protocol field of IP headers:\n\n");
	printf("The number of fragments created from the original datagram is:\n");
	printf("The offset of the last fragment is:\n");



}

int ipa_match(uint32_t addr1, uint32_t addr2, uint32_t mask)
{
    return !((addr1 ^ addr2) & mask);
}

stack_reverse(item **head){
    item *temp, *prev;
    if (*head == NULL)    {
        printf("Stack does not exist\n");
    }
    else if ((*head)->next == NULL){
        printf("Single node stack reversal brings no difference\n");
    }else if ((*head)->next->next == NULL){
        (*head)->next->next = *head;
        *head = (*head)->next;
        (*head)->next->next = NULL;
    } else{
        prev = *head;
        temp = (*head)->next;
        *head = (*head)->next->next;
        prev->next = NULL;
        while ((*head)->next != NULL)        {
            temp->next = prev;
            prev = temp;
            temp = *head;
            *head = (*head)->next;
        }
        temp->next = prev;
        (*head)->next = temp;
    }

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

	handle = pcap_open_offline(argv[1], errbuf); //resets
	packet_counter = Count(handle, "");
//	printf("%s %d \n", "The total number of packets: ", packet_counter);
	
//////////////////////////////////////////////////////////////
	handle = pcap_open_offline(argv[1], errbuf); 
//	filter(handle, "icmp || (udp && udp.dstport != 1900)");
	filter(handle, "icmp ");
	while (packet = pcap_next(handle, &header)) { 
		curr = (item *)malloc(sizeof(item));
		if (Counter(packet, header.ts) == -1){
			break;		
		}
		curr = head;
	//	Counter(packet);
		NUMBER = NUMBER+1;
   	}

	pcap_close(handle); 
  	return 0; 


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

	unsigned int IP_header_length;
 	unsigned char *buffer = (unsigned char *)malloc(65536);
	packet += sizeof(struct ether_header);
//	capture_len -= sizeof(struct ether_header);
	ip = (struct ip*) packet;
	IP_header_length = ip->ip_hl * 4;	

//	packet += IP_header_length;
//	capture_len -= IP_header_length; 

//	printf("%s \n", inet_ntoa(ip->ip_ttl) );


	curr -> ttl = ip->ip_ttl;

	char* srcIP = (char*) malloc (100*1);
	char* destIP = (char*) malloc (100*1);
	strncpy(srcIP , inet_ntoa(ip->ip_src), 100);
	strncpy(destIP, inet_ntoa(ip->ip_dst), 100);


	if (Boolean != 0 ){
		if (ip->ip_ttl == 1){
			return -1;			
		}

	//	printf("%d \n", ip->ip_ttl );
		prevTTL = ip->ip_ttl;
		//	printf(" \n boobb:  %d", bob);
		//	bob = bob+1;
		curr -> sourceAdd = srcIP;
		curr -> destinationAdd = destIP;
		curr -> fragment = ip->ip_off;
		curr -> protocol = ip->ip_tos;
		curr -> time = temps;
	
		curr -> next  = head;

  		head = curr;
			
	}

	if (Boolean == 0 && (ip->ip_ttl) == 1){		//else count Start++
	//	head = (item *)malloc(sizeof(item));
		prevTTL = ip->ip_ttl;
		Boolean = 1;
	//	printf("%d \n", prevTTL );
		curr -> sourceAdd = srcIP;
		curr -> destinationAdd = destIP;
		curr -> fragment = ip->ip_off;
		curr -> protocol = ip->ip_tos;
		curr -> time = temps;
	     
		 curr -> next  = head;
                 head = curr;
	} 



/////////////////////////////////888888888888
/*	
	


	

  	
    	   	printf("Val: %d\n", curr->val);
     	   	printf("TTL: %d \n", curr->ttl );
		printf("Source: %s \n", curr->sourceAdd );
		printf("Dest: %s \n", curr->destinationAdd );
		printf("Frag: %d \n", curr->fragment );
		printf("Proto: %d \n", curr->protocol );
		printf("Time: %f \n", curr->time );
		printf("\n");
  
	 */
	
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


