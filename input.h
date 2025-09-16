#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

int calculate_num_of_strings(const char *curr_file);

char* read_file_into_buffer(char *file_name);

bool input_from_buffer(const char *curr_file);

#endif