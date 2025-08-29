#include "args_processing.h"
#include "equation_solvers.h"
#include "input.h"
#include "asserts.h"
#include "test_part.h"
#include "structers.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>
/**
 * @brief Функция, обрабатывающая интерактивный ввод.
 *
*/
void solver_from_interactive_input() {
    LOGGER_INFO("Intercative call");
    printf("Если хотите решить следующее уравнение - нажмите y\n");
    char command = 'y';
    while (command == 'y') {
        solver();
        printf("Следующее?\n");
        scanf(" %c", &command);
    }
}

/**
 * @brief Функция, обрабатывающая тестовый ввод с файла
 * 
 * Функция считывает имя файла, сохраняет его содержимое в буфер и после запускает тесты
*/
void solver_from_test_input() {
    LOGGER_INFO("Test input call");  
    printf("Введите имя файла:\n");

    char file_name[100] = {};
    scanf("%99s", file_name); 
    
    char *curr_file = read_file_into_buffer(file_name); 
    hard_assert(curr_file != nullptr, "File is missing");

    long num_of_tests = calculate_num_of_strings(curr_file);
    LOGGER_DEBUG("Found %d tests\n", num_of_tests);

    long int test_number = 1;
    for(int i = 0; i < num_of_tests; i++) {
        tester(curr_file, test_number);
        test_number++;
    }

    free(curr_file);
}


/**
 * @brief Функция, выводящая все возможные аргументы запуска
 * 
 * Функция выводит все возможные аргументы запуска, их длинные и короткие версии, а также что они делают
 * @param [in] arg Относительный путь до файла запуска.
 * @param [in] args Все возможные аргументы запуска.
 * @param [in] length_of_args Сколько аргументов в данный момент существует.
 * 
*/
void help_info(const char *file_path, const argument *args, const int lentgh_of_args) {
    LOGGER_INFO("Help called");  
    printf("Usage: %s [OPTION]...\n", file_path);
    printf("\nMandatory arguments to long options are mandatory for short options too.\n");
    for (int i = 0; i < lentgh_of_args; i++) {
        printf("  %s, %-20s %s\n", args[i].short_option, args[i].long_option, args[i].description);
    }
}

/**
 * @brief Функция, обрабатывающая аргументы запуска.
 * @param [in] argv Полученные аргументы запуска
 * 
 * Функция принимает аргументы, с которыми была запущена программа и возвращает тип вызова, который требуется
 * 
 * @return Возвращает тип вызова
*/
type_of_call args_processing(const char *argv[]) {
    LOGGER_DEBUG("Args_processing started" "\n");
    if (strcmp(argv[1], "--interactive")  == 0 ||
        strcmp(argv[1], "-i")             == 0) {
        return CALL_INTERACTIVE;
    } else if (strcmp(argv[1], "--test")  == 0 ||
               strcmp(argv[1], "-t")      == 0) {
        return CALL_TEST;
    } else if (strcmp(argv[1], "--help")  == 0 ||
               strcmp(argv[1], "-h")      == 0) {
        return CALL_HELP;
    } else if (strcmp(argv[1], "--prank") == 0 ||
               strcmp(argv[1], "-p")      == 0) {
        return CALL_PRANK;
    } else {
        return CALL_INCORRECT;
    }
}


/**
 * @brief Функция, выступающая связующем звеном всей программы
 * lol
*/
void prank() {
    LOGGER_INFO("Prank func called");  
    printf("No one loves you\n");
}

/**
 * @brief Функция, обрабатывающая случай, когда введены неверные аргументы.
 * @param [in] file_path Относительный путь до файла запуска.
 * @param [in] arg Последний аргумент.
 * 
 * Функция обрабатывает неверные аргументы и выводит в консоль сообщение об ошибке с рекомендацией посмотреть --help
*/
void incorrect_args(const char *file_path, const char *arg) {
    LOGGER_ERROR("Entered wrong arguments. Last wrong argument: %s", arg);
    fprintf(stderr,"%s: unrecognized option %s\nTry \"%s --help\" for more information\n", file_path, arg, file_path);
}