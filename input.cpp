#include "input.h"
#include "helpers.h"
#include "asserts.h"
#include "clear_buffer.h"
#include "structers.h"
#include <stdio.h>
#include <math.h>
/**
 * @brief Функция, производящая ввод и проверку коэфицентов квадратного уравнения из консоли.
 * @param [out] a Первый коэффицент.
 * @param [out] b Второй коэффицент.
 * @param [out] c Третий коэффицент.
 * 
 * @return Возвращает корректный ли ввод
*/
bool input_from_term(equation_info *eq) {
    hard_assert(eq != nullptr, "eq is nullptr");

    printf("Введите коэффициенты:\n");
    if (scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c) != 3 || 
        !isfinite(eq->a) || !isfinite(eq->b) || !isfinite(eq->c) || !discard_line_and_check_from_term()) {
        soft_assert_functional(false, "Incorrect input", return false);
    }
    return true;
}

int calculate_num_of_strings(char *curr_file) { // TODO: const
    hard_assert(curr_file != nullptr, "Cannot find file");
    int length = 0, num_of_tests = 0;
    while(*curr_file != '\0') {
        sscanf(curr_file, "%*[^\n]%*c%n", &length); // TODO: приложение Б: поиск символа в строке
        num_of_tests++;
        curr_file += length;
        length = 0;
    }
    return num_of_tests;
}
char* open_file(char *file_name) { // Новое название (в буфер именно же)

    FILE *curr_file = fopen(file_name, "r");
    hard_assert(curr_file != nullptr, "File doesn`t found");

    char *buffer = 0;
    fseek (curr_file, 0, SEEK_END);
    long int length = ftell(curr_file);
    fseek (curr_file, 0, SEEK_SET);

    buffer = (char *)malloc (length * sizeof(char)); // Если malloc вернет NULL,
    hard_assert(buffer, "Memory allocation failed ");

    fread(buffer, 1, length, curr_file); // То тут краш =(
    fclose(curr_file);
    return buffer;

}

/**
 * @brief Функция, производящая ввод и проверку коэфицентов квадратного уравнения из файла.
 * @param [out] a Первый коэффицент.
 * @param [out] b Второй коэффицент.
 * @param [out] c Третий коэффицент.
 * @param [out] nAnswer Количество корней .
 * @param [out] x1 Первый корень.
 * @param [out] x2 Второй корень.
 * 
 * @return Возвращает корректный ли ввод
*/
bool input_from_file(equation_info *eq, char *curr_file) { // TODO: const
    hard_assert(eq != nullptr, "eq is nullptr");
    hard_assert(curr_file != nullptr, "File doesn`t found");

    int nAnswerInt = 0;
    int length = 0;

    if (sscanf(curr_file, "%lf %lf %lf %d %lf %lf%n", &eq->a, &eq->b, &eq->c, &nAnswerInt, &eq->x1, &eq->x2, &length) != 6 || 
        !isfinite(eq->a) || 
        !isfinite(eq->b) || 
        !isfinite(eq->c) || 
        !isfinite(eq->x1) || 
        !isfinite(eq->x2)) {
        soft_assert_functional(false, "Incorrect input", return false);
    }

    //Указатель же меняется
    curr_file += length;

    if (!discard_line_and_check_from_file(curr_file)) {
        soft_assert_functional(false, "Incorrect input", return false);
    }    
    soft_assert_functional(nAnswerInt >= -1 && nAnswerInt <= 2, "Incorrect nAnswer in tests", return false);
    eq->nAnswer = (type_of_answer)nAnswerInt;
    //Заменить свич на прямой каст

    return true; 
}

// 1 2 1 1 -1 0
// 0 0 1 0 0 0
// Считывать количество строк и убрать число в начале