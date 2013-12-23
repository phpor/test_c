#include "ipauth.h"

int main(int ac, char **av) {
	if (ac <= 1) {
		printf("please input config file name\n");
		exit(1);
	}
	long *arr_ip = NULL;
	int len = 0;

	if (NULL == (arr_ip = parse_conf(av[1], &len))) {
		printf("parse conf fail\n");
		return 1;
	}
	long *ptr = arr_ip;
	while(len--) {
		printf("%ld: %s\n", *(ptr), long2ip((unsigned long)*(ptr)));
		ptr++;
	}
	free(arr_ip);
	arr_ip = NULL;
	ptr = NULL;

	return 0;
}

