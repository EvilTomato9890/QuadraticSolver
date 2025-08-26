#include "helpers.h"
#include "asserts.h"
#include <float.h>
#include <math.h>
#include <stdio.h>

const int EMAX = (DBL_MAX_EXP - 1);                  // 1023 
const int EMIN = (DBL_MIN_EXP - DBL_MANT_DIG);       // -1074 

/**
 * @brief Функция вывода.
 * @param [in] nAnswer Количество корней уравнения.
 * @param [in] x1 Первый корень уравнения.
 * @param [in] x2 Второй корень уравнения.
 * 
 * Функция производит вывод корней уравнения
*/
void print_answer(equation_info eq) {

    soft_assert(is_float_correct(eq.x1), "x1 is NAN");
    soft_assert(is_float_correct(eq.x2), "x2 is NAN");

    switch (eq.nAnswer) {
    case SOLUTIONS_INF:
        printf("x - любое\n");
        return ;
    case SOLUTIONS_ZERO: 
        printf("Корней нет\n");
        return ;
    case SOLUTIONS_ONE:
        printf("Единственный корень: %.17g\n", eq.x1);
        return ;
    case SOLUTIONS_TWO:
        printf("Корня два: x1 = %.17g, x2 = %.17g\n", eq.x1, eq.x2);
        return ;
    default:
        soft_assert(false, "Wront type"); 
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
    soft_assert(is_float_correct(a), "error a is null");
    if (fabs(a) < DBL_EPSILON) {
        return 0;
    }
    if (a > DBL_EPSILON) {
        return 1;
    }
    return -1;
}

int cmp_for_double(const double a, const double b) {
    soft_assert(is_float_correct(a), "error a is null");
    soft_assert(is_float_correct(b), "error b is null");
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
bool is_answer_correct(equation_info eq, equation_info eq_correct) {
    if (cmp_for_double(eq.nAnswer, eq_correct.nAnswer) == 0 and 
       ((cmp_for_double(eq_correct.x1, eq.x1) == 0 and cmp_for_double(eq_correct.x2, eq.x2) == 0) or
        (cmp_for_double(eq_correct.x1, eq.x2) == 0 and cmp_for_double(eq_correct.x2, eq.x1) == 0))) {
        return true;
    }
    return false;
}