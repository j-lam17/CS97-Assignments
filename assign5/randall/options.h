#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED
#include <stdbool.h>

enum Method { RDRAND, MRAND48_R, SLASH_F };
enum Write { STDOUT, N };

struct options {
    bool valid; // checking if input is valid
    long long nbytes; // number of bytes to produce
    enum Method type_rng; // way to generate the random sequence 
    char* r_src; // string that holds file path if necessary
    enum Write output; // where to output data
    int block_size; // outputted buffer size in kB
  };

void parsing (int argc, char **argv, struct options* opts);

#endif
