/*
 * small program to power on discrete GPU, run a GLX application with DRI
 * PRIME automatically enabled, and then power off the GPU.  Although one would
 * not ordinarily run two graphically-intensive applications simultaneously,
 * doing so under this will break whichever program exits last.
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

static int fd, pid;
const char off[] = "OFF", on[] = "ON";

static void quit(int code)
{
	if (pid)
		kill(SIGKILL, pid);
	if (write(fd, off, sizeof off) != sizeof off)
		fprintf(stderr, "Couldn't turn off discrete GPU");
	close(fd);
	exit(code ? code : errno);
}

void main(int argc, char **argv)
{
	if (argc < 2)
		exit(0);

	signal(SIGINT, quit);

	fd = open("/sys/kernel/debug/vgaswitcheroo/switch", O_WRONLY, O_SYNC,
								O_CLOEXEC);
	if (fd == -1) {
		if (getuid() != 0)
			printf("This program needs to be run as superuser.");
		else
			fprintf(stderr, "vgaswitheroo unavailable.");
		exit(errno);
	}
	if (write(fd, on, sizeof on) != sizeof on) {
		fprintf(stderr, "Couldn't turn on discrete GPU");
		quit(errno);
	}

	putenv("DRI_PRIME=1");

	if (!(pid = fork()))
		execvp(argv[1], &argv[1]);

	wait(NULL);
	pid = 0;
	quit(0);
}
