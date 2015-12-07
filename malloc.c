#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char** av) {
	char *p;
	char s[16] = "";
	int i = 0, sum = 0;
	while(1) {
		printf("please input num (MB) to malloc or 'q' to exit: ");
		if (gets(s) == NULL) continue;
		if (strcmp("q", s) == 0) break;
		if (0 == strlen(s)) continue;
		int cnt = atoi(s);
		if (cnt == 0 ) continue;

		p = malloc(1024*1024* cnt);
		memset(p, '\0', 1024*1024* cnt );
		sum += cnt;
		printf("malloced %d\n", sum);
	}
	return 0;
}
