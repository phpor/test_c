#include "ipauth.h"

long * parse_conf(const char* config_file, int* len) {
	FILE *fp_ip = fopen(config_file, "r");
	if (fp_ip == NULL) {
		fprintf(stderr, "open file %s fail\n", config_file);
		return NULL;
	}

	const int max_line_length = MAX_LINE_LENTH;
	int len_of_line = 0;
	int rows = 0;

	char line[MAX_LINE_LENTH] = "";
	while(NULL != fgets(line, max_line_length-1, fp_ip)) {
		rows++;
	}
	(*len) = rows;

	long *arr_ip = (long *)malloc(rows * sizeof(long));
	long *ptr = arr_ip;
	
	fseek(fp_ip, 0L, SEEK_SET);
	while(rows-- && fgets(line, max_line_length-1, fp_ip)) {
		len_of_line = strlen(line);
		(*ptr) = ip2long(line, len_of_line - 1);
		ptr++;
	}
	return arr_ip;
}

long ip2long(char *addr, int addr_len) {
#ifdef HAVE_INET_PTON
		struct in_addr ip;
#else
		unsigned long int ip;
#endif

#ifdef HAVE_INET_PTON
		if (addr_len == 0 || inet_pton(AF_INET, addr, &ip) != 1) {
			return 0;
		}
		return ntohl(ip.s_addr);
#else
		if (addr_len == 0 || (ip = inet_addr(addr)) == INADDR_NONE) {
			/* The only special case when we should return -1 ourselves,
			 * because inet_addr() considers it wrong. We return 0xFFFFFFFF and
			 * not -1 or ~0 because of 32/64bit issues. */
			if (addr_len == sizeof("255.255.255.255") - 1 &&
					!memcmp(addr, "255.255.255.255", sizeof("255.255.255.255") - 1)
			   ) {
				return 0xFFFFFFFF;
			}
			return 0;
		}
		return ntohl(ip);
#endif
}

char *long2ip(unsigned long ip) {
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
