#include "test_part.h"
#include "input.h"
#include "logger.h"
#include "asserts.h"
#include <stdio.h>

#define RED   "\033[1;31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define OUTPUT_EPS "17" ///<Константа отвечающая за то, с каким числом знаков после запятой будет выведено число с плавающей точкой.

/**
 * @brief Функция, проверяющая корректность кода на 1-ом примере из файла.
 * @param [in] curr_file Строка, содержащая тесты.
 * @param [in] test_number Количество тестов в файле.
 * Функция проверяет корректность корней квадратного уравнения, которые выдает программа, с помощью тестов из файла.
 * Проведя сравнение функция выведет результат
 * 
 * @note RE - не удалось считать ввод 
 * @note WA - Неверный ответ 
 * @note OK - все хорошо 
 * 
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


void tester(const char *curr_file, const long int test_number) { 
    return ;
}

