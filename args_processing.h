#ifndef ARGS_PROCESSING_H_INCLUDED
#define ARGS_PROCESSING_H_INCLUDED

#include "structers.h"
#include <stdio.h>



#define incorrect_args(file_path, arg)\
    do { \
        fprintf(stderr,"%s: unrecognized option %s\nTry \"%s --help\" for more information\n", file_path, arg, file_path); \
    } while (0)



void solver_from_interactive_input();

void solver_from_test_input();

void help_info(const char *arg, const argument *args, const int lentgh_of_args);

type_of_call args_processing(char *argv[]);




#endif