/*
 * small program to power on discrete GPU, run a GLX application with DRI
 * PRIME automatically enabled, and then power off the GPU.  Although one would
 * not ordinarily run two graphically-intensive applications simultaneously,
 * doing so under this will break whichever program exits last.
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		exit(0);

	int fd = open("/sys/kernel/debug/vgaswitcheroo/switch", O_WRONLY,
								O_CLOEXEC);
	if (!fd) {
		if (getuid() != 0)
			printf("This program needs to be run as superuser.");
		else
			printf("vgaswitheroo is unavailable.");
		exit(0);
	}
	write(fd, "ON", sizeof("ON"));
	fsync(fd);

	putenv("DRI_PRIME=1");

	if (!fork())
		execvp(argv[1], &argv[1]);

	wait(NULL);
	write(fd, "OFF", sizeof("OFF"));
	close(fd);
	exit(0);
}
