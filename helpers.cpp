#include "helpers.h"
#include "asserts.h"
#include "logger.h"
#include <float.h>
#include <math.h>
#include <stdio.h>

//const int EMAX = (DBL_MAX_EXP - 1);                  // 1023 
//const int EMIN = (DBL_MIN_EXP - DBL_MANT_DIG);       // -1074 
#define OUTPUT_EPS "17" ///<Константа отвечающая за то, с каким числом знаков после запятой будет выведено число с плавающей точкой.
/**
 * @brief Функция вывода.
 * @param [in] eq Структура, содержащая всю необходимую информациия о решаемом уравнении, в том числе корни и количество решений
 * 
 * Функция производит вывод корней уравнения
*/
void print_answer(const equation_info eq) {

    soft_assert_functional(is_float_correct(eq.x1), "x1 is NAN", LOGGER_WARNING("x1 is NAN"));
    soft_assert_functional(is_float_correct(eq.x2), "x2 is NAN", LOGGER_WARNING("x2 is NAN"));

    switch (eq.nAnswer) {
    case SOLUTIONS_INF:
        printf("x - любое\n");
        LOGGER_INFO("Answer printed, x - любое");
        return ;
    case SOLUTIONS_ZERO: 
        printf("Корней нет\n");
        LOGGER_INFO("Answer printed, корней нет");
        return ;
    case SOLUTIONS_ONE:
        printf("Единственный корень: %." OUTPUT_EPS "g\n", eq.x1);
        LOGGER_INFO("Answer printed, корень единственный - %g", eq.x1);
        return ;
    case SOLUTIONS_TWO:
        printf("Корня два: x1 = %." OUTPUT_EPS "g, x2 = %." OUTPUT_EPS "g\n", eq.x1, eq.x2);
        LOGGER_INFO("Answer printed, корня два: x1 = %g, x2 = %g", eq.x1, eq.x2);
        return ;
    default:
        soft_assert(false, "Wront type"); 
        LOGGER_WARNING("Incorrect num of roots");
        return ;
    }
}

/**
 * @brief Функция сравнения с нулем для действительных чисел.
 * @param [in] a Действительное число, которое требуется сравнить с 0.
 * @return Возвращает положительное число, если аргумент больше 0\n
 *         Возвращает отрицательное число, если аргумент меньше 0\n
 *         Возвращает 0, если аргумент равен 0
 * 
 * @note Использует DBL_EPSILON в качестве абсолютного eps
*/
int cmp_to_zero(const double a) {
    LOGGER_INFO("Comparing double to zero started");
    soft_assert(is_float_correct(a), "error a is null");
    if (fabs(a) < DBL_EPSILON) {
        return 0;
    }
    if (a > DBL_EPSILON) {
        return 1;
    }
    return -1;
}

/**
 * @brief Функция сравнения 2-х действительных чисел.
 * @param [in] a Действительное число для сравнения
 * @param [in] b Действительное число для сравнения
 * 
 * @return Возвращает положительное число, если a > b
 *         Возвращает отрицательное число, если b < 0
 *         Возвращает 0, если a = b
 * 
 * @note Использует DBL_EPSILON в качестве абсолютного eps
*/
int cmp_for_double(const double a, const double b) {
    LOGGER_INFO("Comparing 2 doubles started");
    soft_assert_functional(is_float_correct(a), "error a is null", LOGGER_WARNING("a is null"));
    soft_assert_functional(is_float_correct(b), "error b is null", LOGGER_WARNING("b is null"));
    if (fabs(a - b) < DBL_EPSILON) {
        return 0;
    }
    if (a - b > DBL_EPSILON) {
        return 1;
    }
    return -1;
}

/**
 * @brief Функция проверяющая НЕ является ли число NAN или INF.
 * @param [in] a Действительное число, которое нужно проверить.
*/
bool is_float_correct(const double a) {
    LOGGER_INFO("Checker started");
    if (a == INFINITY || a == -INFINITY || a != a) return false;
    return true;
}

/*
void normalize_pow2(double *a, double *b, double *c) {

    hard_assert(a != nullptr, "a is nullptr");
    hard_assert(b != nullptr, "b is nullptr");
    hard_assert(c != nullptr, "c is nullptr");


    if (*a == 0.0 && *b == 0.0 && *c == 0.0) return;

    int ea = (*a != 0.0) ? ilogb(*a) : 0;
    int eb = (*b != 0.0) ? ilogb(*b) : 0;
    int ec = (*c != 0.0) ? ilogb(*c) : 0;


    int t_min = EMIN; 
    int t_max = EMAX; 


    if (*b != 0.0) {
        int n  = EMAX - 2 * eb;
        int hi = (n >= 0) ? (n / 2) : ((n - 1) / 2); 
        if (hi < t_max) t_max = hi;
    }
    if (*a != 0.0 && *c != 0.0) {

        int n  = EMAX - 2 - ea - ec;
        int hi = (n >= 0) ? (n / 2) : ((n - 1) / 2); 
        if (hi < t_max) t_max = hi;
    }


    if (*b != 0.0) {
        int n  = EMIN - 2 * eb;
        int lo = (n >= 0) ? ((n + 1) / 2) : (n / 2);
        if (lo > t_min) t_min = lo;
    }
    if (*a != 0.0 && *c != 0.0) {
        int n  = EMIN - 2 - ea - ec;
        int lo = (n >= 0) ? ((n + 1) / 2) : (n / 2);   
        if (lo > t_min) t_min = lo;
    }


    int t = (t_min + t_max) / 2;
    *a = scalbn(*a, t);
    *b = scalbn(*b, t);
    *c = scalbn(*c, t);
}
*/


/**
 * @brief Функция, сравнивающая корни 2-х квадратных уравнений.
 * @param [in] eq Структура, содержащая всю необходимую информацию, в том числе корни уравнения, КОТОРЫЕ требуеться сравнить
 * @param [in] eq_correct Структура, содержащая всю необходимую информацию, в том числе корни уравнения, С КОТОРЫМИ требуеться сравнить
 * @return Возвращает совпадают ли корни уравнения
*/
bool is_answer_correct(const equation_info eq, const equation_info eq_correct) {
    LOGGER_INFO("Comparing answers started");
    if (cmp_for_double(eq.nAnswer, eq_correct.nAnswer) == 0 and 
       ((cmp_for_double(eq_correct.x1, eq.x1) == 0 and cmp_for_double(eq_correct.x2, eq.x2) == 0) or
        (cmp_for_double(eq_correct.x1, eq.x2) == 0 and cmp_for_double(eq_correct.x2, eq.x1) == 0))) {
        LOGGER_INFO("Answer correct");
        return true;
    }
    LOGGER_WARNING("Answer incorrect");
    return false;
}
