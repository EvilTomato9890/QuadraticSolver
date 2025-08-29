#ifndef STRUCTERS_H_INCLUDED
#define STRUCTERS_H_INCLUDED

enum type_of_answer {
    SOLUTIONS_INF = -1, ///< Бесконечное число решений
    SOLUTIONS_ZERO, ///< Нет решений
    SOLUTIONS_ONE, ///< Одно решение
    SOLUTIONS_TWO, ///< Два решения
    SOLUTIONS_ENUM_MAX,
};

enum type_of_call {
    CALL_INTERACTIVE, ///< Вызов с вводом с консоли
    CALL_TEST, ///< Вызов с проверкой тестов из файла
    CALL_HELP, ///< Вызов с выводом всех вохможных аргументов вызова
    CALL_PRANK, ///< uwu
    CALL_INCORRECT /// Некоректный тип вызова
};

enum type_of_log {
    DEBUG,
    INFO,
    WARNING,
    ERROR
}; 

struct equation_info {
    double a = 0.0, b = 0.0, c = 0.0; ///< Коэффиценты уравнения
    type_of_answer nAnswer = SOLUTIONS_INF; ///< Количество решений уравнения
    double x1 = 0.0, x2 = 0.0; ///< Корни уравнения
};

struct argument {
    const char* short_option; ///< Длинная запись аргумента
    const char* long_option; ///< Короткая запись аргумента
    const char* description; ///< Описание аргумента
};


#endif
