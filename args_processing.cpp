#include "args_processing.h"
#include "equation_solvers.h"
#include "input.h"
#include "asserts.h"
#include "test_part.h"
#include "structers.h"
#include <stdio.h>
#include <string.h>

void solver_from_interactive_input() {
    printf("Если хотите решить следующее уравнение - нажмите y\n");
    char flag = 'y';
    while (flag == 'y') {
        solver();
        printf("Следующее?\n");
        scanf(" %c", &flag);
    }
}

void solver_from_test_input() {
    printf("Введите имя файла:\n");

    char file_name[100];
    scanf("%s", file_name);
    int length = 0;
    
    char *curr_file = open_file(file_name);

    long num_of_tests = calculate_num_of_strings(curr_file);

    curr_file += length;

    long int test_number = 1;
    for(int i = 0; i < num_of_tests; i++) {
        tester(curr_file, test_number);
        test_number++;
    }
}

void help_info(const char *arg, const argument *args, const int lentgh_of_args) {
    printf("Usage: %s [OPTION]...\n", arg);
    printf("\nMandatory arguments to long options are mandatory for short options too.\n");
    for (int i = 0; i < lentgh_of_args; i++) {
        printf("  %s, %-20s %s\n", args[i].short_option, args[i].long_option, args[i].description);
    }
}

type_of_call args_processing(char *argv[]) {
    if (strcmp(argv[1], "--interactive") == 0 ||
        strcmp(argv[1], "-i") == 0) {
        return CALL_INTERACTIVE;
    } else if (strcmp(argv[1], "--test") == 0 ||
        strcmp(argv[1], "-t") == 0) {
        return CALL_TEST;
    } else if (strcmp(argv[1], "--help") == 0 ||
        strcmp(argv[1], "-h") == 0) {
        return CALL_HELP;
    } else if (strcmp(argv[1], "--prank") == 0 ||
        strcmp(argv[1], "-p") == 0) {
        return CALL_PRANK;
    } else {
        return CALL_INCORRECT;
        incorrect_args(argv[0], argv[1]);
    }
}

void prank() {
    printf("No one loves you\n");
}