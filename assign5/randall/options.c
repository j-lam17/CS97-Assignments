#include "options.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include "rand64-hw.h"
void parsing (int argc, char **argv, struct options* opts)
{
  // starting on my own with getopt 
  if (argc >= 2) 
  {
    char* endptr;
    errno = 0;
    opts->nbytes = strtoll (argv[argc-1], &endptr, 10);
    if (errno)
	perror(argv[1]);
    else
	opts->valid = !*endptr && 0 <= opts->nbytes;
  }
  if (!opts->valid)
  {
    fprintf(stderr, "%s: usage: %s NBYTES\n", argv[argc-1], argv[argc-1]);
  }
  
  int option_index = 0;
  opts->type_rng = 0;
  opts->output = 0;
  while (( option_index = getopt(argc, argv, ":i:o:")) != -1) {
    switch(option_index) {
      case 'i' :
	if (!strcmp(optarg, "rdrand"))
          {
            if (rdrand_supported ())
              {
                opts->type_rng = RDRAND;
              // set rdrand in struct to be true
              }
            else
              {  
                fprintf(stderr, "The option rdrand is not available on this machine");
		exit(1);
              }
          }
        else if (!strcmp(optarg, "mrand48_r"))
          {
  	    opts->type_rng = MRAND48_R;
	    // set mrand48_r to be true in the struct
          }
        else if (optarg[0]=='/' && isalpha(optarg[1]))
          {
  	    opts->type_rng = SLASH_F;
	    opts->r_src = optarg;
	    // fprintf(stderr, "My optarg is %s\n", optarg);
	    // set the file_slash to the string in optarg
          }
	else
	  {
	    fprintf(stderr, "Error: Invalid option for -i flag."); 
	    exit(1);
	  }
        break;
      case 'o' :
	;
	bool v = false;
	if (!strcmp(optarg, "stdio"))
	  {
	    // fprintf(stderr, "Hello The optarg for output 0 %s\n", optarg);
	    v = true;
	    opts->output = STDOUT;
	  }
	// figure out how to read in whole number string from optarg
	char str[100];
	strcpy(str, optarg);
	if (isdigit(str[0]))
	  {
	    bool num = true;
	    for (int i = 1; str[i] != '\0'; i++)
	      {
		if (!isdigit(str[i]))
		  {
		    num = false;
		  }	
	      }
	    if (num)
	      {
		// fprintf(stderr, "Hi The optarg or output 1 is %s\n", str);
		opts->output = 1;
	        opts->block_size = atoi(str);
		v = true;
	      }
	    else
	      {
		fprintf(stderr, "Error: Invalid number inputted");
		exit(1);
	      }
	if (!v)
	  {
	    fprintf(stderr, "Error: Invalid option for -o flag.");
	    exit(1);
	  }
	break;
      default : 
        break; // unrecognized option
      }
    }
  }
}
