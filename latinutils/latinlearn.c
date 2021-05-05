/*
 * latin_voc_learning -n num_vocs (default: 10) vocfilename
 *
 * Ask random num_vocs latin words from vocfilename (a file with fields separated by tabs)
 *
 * All words are in a queue data structure and wrongly answered ones go back to the beginning of the queue.
 * 
 * One line can have up to 255 characters
 */

#include <stdio.h>  // fopen, fclose, etc.
#include <stdlib.h> // exit
#include <unistd.h> // getopt

#define DEFAULT_NUM_VOC	10

void usage()
{
	fprintf(stderr, "Usage: latinlearn [-n num_vocs] vocfilename\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	FILE *vocfile;
	int numvoc = DEFAULT_NUM_VOC;
	char opt;
	while ((opt = getopt(argc, argv, "n:")) != -1) {
		switch (opt) {
			case 'n':
				numvoc = atoi(optarg);
				break;
			default:
				usage();
		}
	}

	argc -= optind;
	argv += optind;

	// check if filename is given
	if (argc < 1)
		usage();

	vocfile = fopen(argv[0], "r"); // argv[0] is the vocfilename argument
	fclose(vocfile);
}
