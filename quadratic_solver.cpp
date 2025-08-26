#include "asserts.h"
#include "args_processing.h"
#include "equation_solvers.h"

//bool new_sscanf(char **curr_file, const char *format) стоит ли делать

int main(int argc, char *argv[]) {
    argument args[4] = {
        {"-t", "--test", "Runs program, where data comes from file"},
        {"-i", "--interactive", "Runs program, where coefs inputs from teminal"},
        {"-h", "--help", "Displays information about possible options"},
        {"-p", "--prank", "Some useless shit"}
    };
    hard_assert(argc == 2, "Incorrect num of args");

    type_of_call option = args_processing(argv);
    switch (option) {
        case CALL_INTERACTIVE:
            solver_from_interactive_input();
            break;
        case CALL_TEST:
            solver_from_test_input();
            break;
        case CALL_HELP:
            help_info(argv[0], args, (int)(sizeof(args) / sizeof(argument)));
            break;
        case CALL_PRANK:
            prank();
            break;
        case CALL_INCORRECT:
            incorrect_args(argv[0], argv[1]);
    }
    printf("Program runs normal\n");
}

/*
Оставлять ли ассерты или иначе как их заменять

*/