#include "test_part.h"
#include "structers.h"
#include "input.h"
#include "logger.h"
#include "equation_solvers.h"
#include "helpers.h"
#include "test_part.h"
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
void tester(const char *curr_file, const long int test_number) { 
    LOGGER_INFO("Tester for 1 test started");
    equation_info eq_correct = {};

    if (!input_from_buffer(&eq_correct, curr_file)) {
        printf("Test %ld: RE\n", test_number);
        LOGGER_WARNING("RE on test %ld", test_number);
        return;
    }

    equation_info eq = eq_correct;
    eq.a = eq_correct.a;
    eq.b = eq_correct.b;
    eq.c = eq_correct.c;
    equation_solve(&eq);

    if(!is_answer_correct(eq, eq_correct)) {
        LOGGER_WARNING("WA on test %ld", test_number);
        printf("Test %ld:" RED "WA a = %." OUTPUT_EPS "g, b = %." OUTPUT_EPS "g, c = %." OUTPUT_EPS "g\n" RESET, test_number, eq.a, eq.b, eq.c);
    } else {
        LOGGER_INFO("OK on test %ld", test_number);
        printf("Test %ld: " GREEN "OK\n" RESET, test_number);
    }
}


/**
 * @brief Функция, проверяющая корректность кода на заданных примерах.
 * @note На данный момент не используется
 * 
*/
void test_all() {
    LOGGER_INFO("\"Test_all\" started");
    equation_info tasks[] = {
        {1.0,  2.0,  1.0, SOLUTIONS_ONE, -1.0,  0.0},
        {1.0, -5.0,  6.0, SOLUTIONS_TWO,  2.0,  3.0},
        {1.0,  5.0,  6.0, SOLUTIONS_TWO, -2.0, -3.0},
        {1.0,  2.0,  5.0, SOLUTIONS_ZERO, 0.0,  0.0},
        {1.0,  0.0, -1.0, SOLUTIONS_TWO, -1.0,  1.0},
        {0.0,  2.0,  2.0, SOLUTIONS_ONE, -1.0,  0.0},
        {1.0,  1.0,  0.0, SOLUTIONS_TWO,  0.0, -1.0}};

    for (int i = 0; i < (int)sizeof(tasks) / (int)sizeof(equation_info); i++) {
        test(tasks[i], i + 1);
    }
}

/**
 * @brief Функция, производящая один тест корректности работы кода.
 * @note Используется только для test_all(), который в данный момент не используется
 * 
*/
void test(const equation_info eq_correct, const long int test_number) {
    LOGGER_INFO("Test started");
    equation_info eq = {eq_correct.a, eq_correct.b, eq_correct.c};
    equation_solve(&eq);

    if(!is_answer_correct(eq, eq_correct)) {
        LOGGER_WARNING("WA on test %ld", test_number);
        printf("Test %ld:" RED "WA a = %." OUTPUT_EPS "g, b = %." OUTPUT_EPS "g, c = %." OUTPUT_EPS "g\n" RESET, test_number, eq.a, eq.b, eq.c);
    } else {
        LOGGER_INFO("OK on test %ld", test_number);
        printf("Test %ld: " GREEN "OK\n" RESET, test_number);
    }
}
