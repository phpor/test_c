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

//--------------------------------------------------------------------- 
unsigned long ip2long(const char* ip){ 
	unsigned char a, b, c, d; 
	sscanf(ip, "%hhu.%hhu.%hhu.%hhu", &a, &b, &c, &d); 
	return ((a << 24) | (b << 16) | (c << 8) | d); 
} 

//--------------------------------------------------------------------- 
char *long2ip(unsigned long ip, char buf[]){ 
	int i = 0; 
	unsigned long tmp[4] = {0}; 

	for(i = 0; i < 4; i++){ 
		tmp[i] = ip & 255; 
		ip = ip >> 8; 
	} 
	sprintf(buf, "%lu.%lu.%lu.%lu", tmp[3], tmp[2], tmp[1], tmp[0]); 
	return buf;
} 

//--------------------------------------------------------------------- 
int main(){ 
	char* ip = "192.168.1.2"; 
	char buf[16] = {0}; 
	unsigned long ip_long = 0; 

	ip_long = ip2long(ip); 
	printf("%lu\n", ip_long); 

	printf("%s", long2ip((unsigned long )ip_long, buf)); 
	puts(buf); 

	return 0; 
}
