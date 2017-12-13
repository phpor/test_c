#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <linux/if_tun.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>

#include <sys/select.h>

int tun_alloc(int flags, char *devname)
{

	struct ifreq ifr;
	int fd, err;
	char *clonedev = "/dev/net/tun";

	if ((fd = open(clonedev, O_RDWR)) < 0) {
		return fd;
	}

	memset(&ifr, 0, sizeof(ifr));
	// tips: ifr_flags and ifr_name are macro
	ifr.ifr_flags = flags;
	if (strlen(devname) > 0) {
		strcpy(ifr.ifr_name, devname);
	}

	if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
		close(fd);
		return err;
	}

	char buf[255];
	sprintf(buf, "Open tun/tap device: %s for reading...\n", ifr.ifr_name);
	write(2, buf, strlen(buf));

	return fd;
}

int main(int ac, char **av)
{

	int fd, nread, ret;
	fd_set set;
	struct timeval timeout;
	char buffer[1500];
	char devname[16] = {0,};
	if (ac >= 2) {
		strncpy(devname, av[1], 15);
	}
	int flag = IFF_TUN | IFF_NO_PI;
	if (ac >= 3 ) {
		if (strcmp("tap", av[2]) == 0) flag = IFF_TAP;
	}
	/* Flags: IFF_TUN   - TUN device (no Ethernet headers)
	 *        IFF_TAP   - TAP device
	 *        IFF_NO_PI - Do not provide packet information
	 */
	fd = tun_alloc(flag, devname);

	if (fd < 0) {
		perror("Allocating interface");
		exit(1);
	}
	FD_ZERO(&set); /* clear the set */
	fcntl(fd, F_SETFL, O_NONBLOCK);
	while (1) {
/*
		FD_SET(fd, &set); // add our file descriptor to the set
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		ret = select(fd + 1, &set, NULL, NULL, &timeout);
		if (ret == -1 ) {
			perror("Reading from interface");
			break;
		}
		if (ret == 0 ) continue;
*/
		while(1) {
				nread = read(fd, buffer, sizeof(buffer));
				if (nread > 0) write(1, buffer, nread);
				if (nread < 0 && errno == EAGAIN || nread > 0 && nread < sizeof(buffer)) sleep(1);
				if (nread < 0 && errno != EAGAIN ) break;
		}
/*
		if (nread < 0) {
			perror(strerror(errno));
			continue;
		}
*/
		//printf("Read %d bytes from tun/tap device\n", nread);
	}
	close(fd);
	return 0;
}
//vim: se ts=4
