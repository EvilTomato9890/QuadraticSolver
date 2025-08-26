#ifndef EQUATION_SOLVERS_H_INCLUDED
#define EQUATION_SOLVERS_H_INCLUDED

#include "structers.h"

bool try_linear_solve(equation_info *eq);

void equation_solve(equation_info *eq);

void solver();

#endif
