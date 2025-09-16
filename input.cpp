#include "input.h"
#include "asserts.h"
#include "clear_buffer.h"
#include "logger.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
 * @brief Функция, подсчитывающая число строк в файле.
 * @param [in] curr_file Файл, представленный в виде массива символов.
 * 
 * Функция проходиться по файлу и подсчитывает количество символов '\\n', обозначающих конец строки,
 * тем самым подсчитывая количество самих строк в файле.
 * @return Возвращает количество строк в файле.
*/
int calculate_num_of_strings(const char* curr_file) { 
    LOGGER_INFO("Calculating num of strings started");
    LOGGER_ERROR("File not found");
    hard_assert(curr_file != nullptr, "File not found");

    int num_of_tests = 0;
    for (int i = 0; i < (int)strlen(curr_file); i++) {
        if (curr_file[i] == '\n') {
            num_of_tests++;
        }
    }
    LOGGER_INFO("Calculating num of strings ended");
    return num_of_tests;
}

/**
 * @brief Функция, считывающая в буффер файл по переданному названию
 * @param [in] file_name Название файла, который требуется считать в буффер.
 * 
 * Функция считает длинну файла, выделяет буффер соотвествующего размера и записывает в него весь файл.
 * 
 * @return Возвращает считанный файл в формате строки
*/
char* read_file_into_buffer(char *file_name) { 
    LOGGER_INFO("Reading file started");
    FILE *curr_file = fopen(file_name, "r");
    LOGGER_ERROR("File not found");
    hard_assert(curr_file != nullptr, "File not found");

    char *buffer = 0;
    fseek (curr_file, 0, SEEK_END);
    long int length = ftell(curr_file);
    fseek (curr_file, 0, SEEK_SET);
    LOGGER_DEBUG("Memory allocation started");
    buffer = (char *)malloc ((length + 1) * sizeof(char)); 
    if(buffer == nullptr) {
        LOGGER_ERROR("Memory allocation failed");
        fprintf(stderr, "%s\n", "Memory allocation failed ");
        abort();
    }
    LOGGER_DEBUG("Memry allocation succes, taken %ld bytes", (long)((length + 1) * sizeof(char)));
    buffer[length] = '\0';
    fread(buffer, 1, length, curr_file);
    fclose(curr_file);
    LOGGER_INFO("File closed, buffer returned");
    return buffer;

}

/**
 * @brief Функция, производящая ввод и проверку коэфицентов квадратного уравнения из файла.
 * @param [out] eq Структура, содержащая поля под коэффиценты, корни уравнения и количество решений
 * Функция считывает из буффера коэффиценты, корни и количество решений одного уравнения.
 * 
 * @return Возвращает корректный ли ввод
*/
/*
bool input_from_buffer(const char *curr_file) { //TODO: ДОбавить hard assert functional
    LOGGER_INFO("Input from buffer started"); 
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
        soft_assert_functional(false, "Incorrect input", LOGGER_ERROR("Incorrect input"); return false);
    }
    curr_file += length;

    if (!discard_line_and_check_from_file(curr_file)) {
        soft_assert_functional(false, "Incorrect input", LOGGER_ERROR("Incorrect input"); return false);
    }    
    soft_assert_functional(nAnswerInt >= -1 && nAnswerInt <= 2, "Incorrect nAnswer in tests", LOGGER_WARNING("Incorrect nAnswer in tests");return false);
    eq->nAnswer = (type_of_answer)nAnswerInt;

    return true; 
}

*/