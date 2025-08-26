#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include "structers.h"

void print_answer(equation_info eq);

int cmp_to_zero(const double a);

int cmp_for_double(const double a, const double b);

bool is_float_correct(const double a);

bool is_answer_correct(equation_info eq, equation_info eq_correct);

#endif
