#include "asserts.h"
#include "args_processing.h"
#include "equation_solvers.h"
#include "logger.h"

int main(const int argc, const char *argv[]) {
    logger_initialize_file("logfile");
    LOGGER_INFO("Program started");
    argument args[] = {
        {"-t", "--test", "Runs program, where data comes from file"},
        {"-i", "--interactive", "Runs program, where coefs inputs from teminal"},
        {"-h", "--help", "Displays information about possible options"},
        {"-p", "--prank", "Some useless shit"}
    };
    if(argc == 1) {
        LOGGER_INFO("Entered 0 arguments");
        solver_from_interactive_input();
    } else if(argc > 2) {
        LOGGER_ERROR("Entered incorrect num of args. %d entered", argc);
        incorrect_args(argv[0], argv[argc - 1]);
        hard_assert(false, "Incorrect num of args");
    } else {
        LOGGER_INFO("Entered correct num of arguments");
        type_of_call option = args_processing(argv);
        switch (option) {
            case CALL_INTERACTIVE: solver_from_interactive_input();                                 break;
            case CALL_TEST:        solver_from_test_input();                                        break;
            case CALL_HELP:        help_info(argv[0], args, (int)(sizeof(args) / sizeof(argument)));break;
            case CALL_PRANK:       prank();                                                         break;
            default:               LOGGER_ERROR("Unknown option");hard_assert(false, "Incorrect enum encounter");      
            case CALL_INCORRECT:   incorrect_args(argv[0], argv[1]);                                 break; 
        }
    }
    LOGGER_INFO("Program ended correctly");
    logger_close();
    printf("Program runs normal\n");
    return 0;
}
