/*
 * latinlaunch [-n/--numvoc N] [-f/--vocfile FILENAME] command
 *
 * Execute a command (often used for starting a graphical application)
 * but ask the user to go throug N random latin words
 * from the voc file FILENAME before command is executed.
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, getenv
#include <unistd.h> // getopt_long
#include <getopt.h> // getopt_long
#include <string.h> // strcat

#define DEFAULT_NUM_VOC 5
#define DEFAULT_VOC_FILE strcat(getenv("HOME"), "/.local/share/latinvoc.csv")

void usage()
{
	fprintf(stderr, "Usage: latinlaunch [-n/--numvoc N] [-f/--vocfile FILENAME] command\n\
	command: command to be executed after asking the words\n\
	N: Number of vocabularies to ask (default: 5)\n\
	FILENAME: file where latin vocabulary tab separated value file is stored (default: ~/.local/share/latinvoc.csv\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	char opt;
	int option_index = 0;
	int numvoc = DEFAULT_NUM_VOC;
	char *command;
	char *vocfile = DEFAULT_VOC_FILE;

	while (1) {
		static struct option long_options[] =
		{
			{"numvoc", required_argument, 0, 'n'},
			{"vocfile", required_argument, 0, 'f'},
			{0, 0, 0, 0},
		};

		opt = getopt_long(argc, argv, "n:f:", long_options, &option_index);

		// detect end of options
		if (opt == -1)
			break;
		
		switch (opt) {
			case 'n':
				numvoc = atoi(optarg);
				break;
			case 'f':
				vocfile = optarg;
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

	printf("Asking '%i' latin words from file '%s' before executing '%s'\n", numvoc, vocfile, command);
	//execl("/usr/bin/urxvt", "/usr/bin/urxvt", "-e", command, NULL);
	execl(command, command, NULL);
}
