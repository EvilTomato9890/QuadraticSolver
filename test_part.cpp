#include "test_part.h"
#include "structers.h"
#include "input.h"
#include "equation_solvers.h"
#include "helpers.h"
#include "test_part.h"
#include <stdio.h>

#define RED   "\033[1;31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
void tester(char *curr_file, const long int test_number) {

    equation_info eq_correct;

    if (!input_from_file(&eq_correct, curr_file)) {
        printf("Test %ld: RE\n", test_number);
        return ;
    }

    equation_info eq;
    eq.a = eq_correct.a;
    eq.b = eq_correct.b;
    eq.c = eq_correct.c;
    equation_solve(&eq);

    if(!is_answer_correct(eq, eq_correct)) {
        printf("Test %ld:" RED "WA a = %.17g, b = %.17g, c = %.17g\n" RESET, test_number, eq.a, eq.b, eq.c);
    } else {
        printf("Test %ld: " GREEN "OK\n" RESET, test_number);
    }
}

void test(equation_info eq_correct, const long int test_number) {
    equation_info eq = {eq_correct.a, eq_correct.b, eq_correct.c};
    equation_solve(&eq);

    if(!is_answer_correct(eq, eq_correct)) {
        printf("Test %ld: WA a = %.17g, b = %.17g, c = %.17g\n", test_number, eq.a, eq.b, eq.c);
    } else {
        printf("Test %ld: OK\n", test_number);
    }
}

void test_all() {

    equation_info tasks[7] = {
        {1.0, 2.0, 1.0, SOLUTIONS_ONE, -1.0, 0.0},
        {1.0, -5.0, 6.0, SOLUTIONS_TWO, 2.0, 3.0},
        {1.0, 5.0, 6.0, SOLUTIONS_TWO, -2.0, -3.0},
        {1.0, 2.0, 5.0, SOLUTIONS_ZERO, 0.0, 0.0},
        {1.0, 0.0, -1.0, SOLUTIONS_TWO, -1.0, 1.0},
        {0.0, 2.0, 2.0, SOLUTIONS_ONE, -1.0, 0.0},
        {1.0, 1.0, 0.0, SOLUTIONS_TWO, 0.0, -1.0}};

    for (int i = 0; i < (int)sizeof(tasks) / (int)sizeof(equation_info); i++) {
        test(tasks[i], i + 1);
    }
}
