#ifndef ARGS_PROCESSING_H_INCLUDED
#define ARGS_PROCESSING_H_INCLUDED

#include "structers.h"
#include <stdio.h>



void incorrect_args(const char *file_path, const char *arg);

void solver_from_interactive_input();

void solver_from_test_input();

void help_info(const char *file_path, const argument *args, const int lentgh_of_args);

type_of_call args_processing(const char *argv[]);

void prank();


#endif