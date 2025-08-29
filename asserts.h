
#ifndef ASSERTS_H_INCLUDED
#define ASSERTS_H_INCLUDED

#include <stdio.h>
#include <cstdlib>

//! @brief Строка, придающая выводу красный цвет.
#define RED "\033[1;31m"

//! @brief Строка, очищающая цвет вывода.   
#define RESET "\033[0m"

/**
 * @brief Превращает часть кода в строку.
 * @param [in] a Кусок кода, который будет преобразован в строку.
 * @return Строчное отображение кода
 * 
 * Макрос берет код, который ему передан и превращает его в строку.
 * 
 * @note В случае попытки перевода функций, может протребоваться дополнительное преобразование
*/
#define stringify(a) #a


/**
 * @brief Аналог assert, завершающий программу.
 * @param [in] test Условие, которое проверяется assert-ом.
 * @param [in] message Сообщение, которое будет выведено.
 * 
 * Макрос проверяет заданное условие и, если оно ложно, выдает сообщение об ошибке, 
 * содержащее имя функции и номер строки кода, где произошел вызол и аргумент, который вызвал этот assert. 
 * После завершает выполнение программы.
 * 
*/
#ifdef NDEBUG
    #define hard_assert(...) (void)0
#else
    #define hard_assert(test, message) \
        do {            \
            if(!(test)) { \
                fprintf(stderr, "%s%s\nERROR WAS OCCURED IN %s IN %i LINE FROM %s BY %s%s\n", RED, message,__FILE__, __LINE__, __PRETTY_FUNCTION__, stringify(test), RESET); \
                abort(); \
            }   \
        } while(0)
#endif


/**
 * @brief Аналог assert, НЕ завершающий программу.
 * @param [in] test Условие, которое проверяется assert-ом.
 * @param [in] message Сообщение, которое будет выведено.
 * 
 * Макрос проверяет заданное условие и, если оно ложно, выдает сообщение об ошибке, 
 * содержащее имя функции и номер строки кода, где произошел вызол и аргумент, который вызвал этот assert. 
 * После выполнения НЕ завершает выполнение программы.
 * 
*/
#ifdef NDEBUG
    #define soft_assert(...) (void)0
#else
    #define soft_assert(test, message) \
        do {        \
            if(!(test)) { \
                printf(RED "%s\nERROR WAS OCCURED IN %s IN %i LINE FROM %s BY %s" RESET "\n", \
                    message,__FILE__, __LINE__, __PRETTY_FUNCTION__, stringify(test)); \
            }  \
        } while(0)
#endif


/**
 * @brief Аналог assert, НЕ завершающий программу и выполняющий некоторый код.
 * @param [in] test Условие, которое проверяется assert-ом.
 * @param [in] message Сообщение, которое будет выведено.
 * @param [in] command Фрагмент кода, который необходимо выполнить.
 * 
 * Макрос проверяет заданное условие и, если оно ложно, выдает сообщение об ошибке, 
 * содержащее имя функции и номер строки кода, где произошел вызол и аргумент, который вызвал этот assert. 
 * Также, если условие ложно, выполняет переданный фрагмент кода.
 * После выполнения НЕ завершает выполнение программы.
 * 
*/
#ifdef NDEBUG
    #define soft_assert_functional(...) (void)0
#else 
    #define soft_assert_functional(test, message, command) \
        do { \
            if(!(test)) { \
                printf(RED "%s\nERROR WAS OCCURED IN %s IN %i LINE FROM %s BY %s" RESET "\n", \
                    message,__FILE__, __LINE__, __PRETTY_FUNCTION__, stringify(test)); \
                command; \
            }  \
        } while(0)
#endif

#endif