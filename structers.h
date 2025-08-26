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
    CALL_INTERACTIVE,
    CALL_TEST,
    CALL_HELP,
    CALL_INCORRECT
};


struct equation_info {
    double a = 0.0, b = 0.0, c = 0.0;
    type_of_answer nAnswer = SOLUTIONS_INF;
    double x1 = 0.0, x2 = 0.0;    
};

struct argument {
    const char* short_option;
    const char* long_option;
    const char* description;
};


#endif
