#include "clear_buffer.h"
#include "asserts.h"
#include "logger.h"
#include <stdio.h>
#include <ctype.h>
/**
 * @brief Функция, очищающая буфер ввода консоли и проверяющая его "пустоту".
 * @param [out] a Первый коэффицент.
 * 
 * Функция посимвольно очищает буфер ввода и, если опадется что-либо кроме пробела или таба, вернет false, иначе - true
 * 
 * @return Возвращает есть ли в буфере что=либо кроме пробельных символов
*/
bool discard_line_and_check_from_term() {
    LOGGER_DEBUG("Buffer clearing started");
    int ch = 0;
    bool is_float_correct = true; 
    while (!iscntrl(ch = getchar()) && ch != EOF) {
        if (!isblank(ch)) {
            is_float_correct = false; 
            LOGGER_WARNING("Buffer found incorrect symbol");
        }
    }
    return is_float_correct;
}

/**
 * @brief Функция, очищающая буфер ввода файла и проверяющая его "пустоту".
 * @param [out] a Первый коэффицент.
 * 
 * Функция посимвольно очищает буфер ввода и, если попадается что-либо кроме пробельного символа, вернет false, иначе - true
 * 
 * @return Возвращает есть ли в буфере что-либо кроме пробельных символов
*/
bool discard_line_and_check_from_file(const char *curr_file) {
    LOGGER_DEBUG("Buffer clearing started");
    int ch = 0;
    bool is_test_correct = 1;
    hard_assert(curr_file != nullptr, "File is missing");

    while (!iscntrl(ch = *(curr_file++))) {
        if (!isblank(ch)) is_test_correct = 0; 
    }
    return is_test_correct;
}