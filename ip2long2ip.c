#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#if HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif

char *_long2ip(unsigned long ip) {
	/* "It's a long but it's not, PHP ints are signed */
	struct in_addr myaddr;
#ifdef HAVE_INET_PTON
	char str[40];
#endif

	myaddr.s_addr = htonl(ip);
#ifdef HAVE_INET_PTON
	if (inet_ntop(AF_INET, &myaddr, str, sizeof(str))) {
		return str;
	} else {
		return NULL;
	}
#else
	return inet_ntoa(myaddr);
#endif

}
//--------------------------------------------------------------------- 
unsigned long ip2long(const char* ip){ 
	unsigned char a, b, c, d; 
	sscanf(ip, "%hhu.%hhu.%hhu.%hhu", &a, &b, &c, &d); 
	return ((a << 24) | (b << 16) | (c << 8) | d); 
} 

//--------------------------------------------------------------------- 
void long2ip(unsigned long ip, char buf[]){ 
	int i = 0; 
	unsigned long tmp[4] = {0}; 

	for(i = 0; i < 4; i++){ 
		tmp[i] = ip & 255; 
		ip = ip >> 8; 
	} 
	sprintf(buf, "%lu.%lu.%lu.%lu", tmp[3], tmp[2], tmp[1], tmp[0]); 
} 

//--------------------------------------------------------------------- 
int main(){ 
	char* ip = "192.168.1.2"; 
	char buf[16] = {0}; 
	unsigned long ip_long = 0; 

	ip_long = ip2long(ip); 
	printf("%lu\n", ip_long); 

	printf("%s", _long2ip((unsigned long )ip_long)); 
	puts(buf); 

	return 0; 
}
