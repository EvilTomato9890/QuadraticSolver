#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "structers.h"

bool input_from_term(equation_info *eq);

char* open_file(char *file_name);

bool input_from_file(equation_info *eq, char *curr_file);

#endif