/*
 * latinlaunch [-n/--numvoc N (default: 5)] [-f/--vocfile FILENAME (default: ~/.local/share/latinvoc.txt)] [-t/--terminal TERM_NAME (default: /usr/bin/urxvt)] command
 *
 * Execute a command (often used for starting a graphical application)
 * but ask the user to go throug N random latin words
 * from the voc file FILENAME before command is executed.
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, getenv
#include <unistd.h> // getopt_long
#include <getopt.h> // getopt_long
#include <string.h> // strcat, strerror
#include <errno.h> // errno
#include <sys/wait.h> // waitpid

#define DEFAULT_NUM_VOC "5" // this is a string because giving arguments via exec requires char pointers
#define DEFAULT_VOC_FILE ".local/share/latinvoc.txt" // relative to current user home directory
#define DEFAULT_TERM "/usr/bin/urxvt"

void usage()
{
	fprintf(stderr, "Usage: latinlaunch [-n/--numvoc N] [-f/--vocfile FILENAME] [-t/--terminal TERM_NAME] command\n\
	command: command to be executed after asking the words\n\
	N: Number of vocabularies to ask (default: 5)\n\
	FILENAME: file where latin vocabulary tab separated value file is stored (default: ~/.local/share/latinvoc.csv\n\
	TERM_NAME: terminal in which latinlearn program is executed (default: /usr/bin/urxvt)");
	exit(1);
}

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int main(int argc, char *argv[])
{
	char opt;
	int option_index = 0;
	char *numvoc = DEFAULT_NUM_VOC; // string because exec commands only accept strings
	char *term = DEFAULT_TERM;
	char *command;
	char vocfile[255];

	snprintf(vocfile, 255, "%s/%s", getenv("HOME"), DEFAULT_VOC_FILE);

	while (1) {
		static struct option long_options[] =
		{
			{"numvoc", required_argument, 0, 'n'},
			{"vocfile", required_argument, 0, 'f'},
			{"terminal", required_argument, 0, 't'},
			{0, 0, 0, 0},
		};

		opt = getopt_long(argc, argv, "n:f:t:", long_options, &option_index);

		// detect end of options
		if (opt == -1)
			break;
		
		switch (opt) {
			case 'n':
				numvoc = optarg;
				break;
			case 'f':
				strncpy(vocfile, optarg, 254);
				vocfile[254] = '\0';
				break;
			case 't':
				term = optarg;
				break;
			default:
				// handle unrecognized options
				usage();
		}
	}
	argc -= optind;
	argv += optind;

	// detect if command is given
	if (argc < 1)
		usage();

	command = argv[0];

	pid_t child_pid = fork();
	if (child_pid == -1)
		error("Can't fork process");

	if (!child_pid)
		if (execl(term, term, "-e", "latinlearn", "--numvoc", numvoc, vocfile, (char *) NULL) == -1)
			error("Can't run latinlearn script");

	int pid_status;
	if (waitpid(child_pid, &pid_status, 0) == -1)
		error("Error waiting for child process");
	
	// this is just the exec call used by system as well but without forking
	execl("/bin/sh", "sh", "-c", command, (char *) NULL);
}
