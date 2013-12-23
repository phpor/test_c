#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#if HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#define MAX_LINE_LENTH 20
long *parse_conf(const char* config_file, int* len);
long ip2long(char *addr, int addr_len);
char *long2ip(unsigned long ip);
