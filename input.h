#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "structers.h"

int calculate_num_of_strings(const char *curr_file);

bool input_from_term(equation_info *eq);

char* read_file_into_buffer(char *file_name);

bool input_from_buffer(equation_info *eq, const char *curr_file);

#endif