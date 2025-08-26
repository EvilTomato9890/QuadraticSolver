#include "clear_buffer.h"
#include "asserts.h"
#include <stdio.h>
/**
 * @brief Функция, очищающая буфер ввода консоли и проверяющая его "пустоту".
 * @param [out] a Первый коэффицент.
 * 
 * Функция посимвольно очищает буфер ввода и, если опадется что-либо кроме пробела или таба, вернет false, иначе - true
 * 
 * @return Возвращает есть ли в буфере что=либо кроме пробельных символов
*/
bool discard_line_and_check_from_term() {
    int ch = 0;
    bool is_float_correct = true; 
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ' && ch != '\t') is_float_correct = false;
    }
    if (!is_float_correct) return false;
    return true; 
}

/**
 * @brief Функция, очищающая буфер ввода файла и проверяющая его "пустоту".
 * @param [out] a Первый коэффицент.
 * 
 * Функция посимвольно очищает буфер ввода и, если опадется что-либо кроме пробела или таба, вернет false, иначе - true
 * 
 * @return Возвращает есть ли в буфере что=либо кроме пробельных символов
*/
bool discard_line_and_check_from_file(char *curr_file) {
    int ch = 0;
    bool flag = 0;
    //Как не выйти за пределы строки
    hard_assert(curr_file != nullptr, "File doesn`t found");

    while ((ch = *(curr_file++)) != '\n' && ch != EOF && ch != '\r') {
        if (ch != ' ' && ch != '\t') flag = 1; // K&R priloJILenie B (is...)
    }
    if (flag) return false;
    return true; 
}