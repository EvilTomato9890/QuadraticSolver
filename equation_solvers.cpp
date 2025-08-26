#include "equation_solvers.h"
#include "asserts.h"
#include "helpers.h"
#include "input.h"
#include "structers.h"
#include <math.h>
/**
 * @brief Функция решающая линейное уравнение, если оно таковым является.
 * @param [in] a Первый коэффицент.
 * @param [in] b Второй коэффицент.
 * @param [in] c Третий коэффицент.
 * 
 * @param [out] nAnswer Количество корней.
 * @param [out] x1 Корень уравнения
 * 
 * @return Возвращает является ли уравнение линейным
*/
bool try_linear_solve(equation_info *eq) {

    const double a = eq->a, b = eq->b, c = eq->c;

    soft_assert(is_float_correct(eq->a), "a is NAN");
    soft_assert(is_float_correct(eq->b), "b is NAN"); 
    soft_assert(is_float_correct(eq->c), "c is NAN"); 

    if (cmp_to_zero(a) == 0) {
        if (cmp_to_zero(b) == 0) {
            if (cmp_to_zero(c) == 0) eq->nAnswer = SOLUTIONS_INF;
            else eq->nAnswer = SOLUTIONS_ZERO;
            return true;
        } else {
            eq->x1 = - c / b;
            eq->nAnswer = SOLUTIONS_ONE;
            return true;
        }
    } 
    return false;
}

/**
 * @brief Функция, решающая квадратное и линейное уравнения
 * @param [in] a Первый коэффицент.
 * @param [in] b Второй коэффицент.
 * @param [in] c Третий коэффицент.
 * 
 * @param [out] nAnswer Количество корней.
 * @param [out] x1 Первый корень уравнения
 * @param [out] x2 Второй корень уравнения
*/
void equation_solve(equation_info *eq) {
    hard_assert(eq != nullptr, "x1 is nullptr");

    const double a = eq->a, b = eq->b, c = eq->c;
    if(try_linear_solve(eq)) {
        return;
    }

    double D = b * b - 4.0 * a * c;

    if (cmp_to_zero(D) > 0) {
        double temp = -0.5 * (b + sqrt(D)); 
        if (cmp_to_zero(temp) == 0) {
            eq->x1 =  - b / a;   
            eq->x2 = 0;
            eq->nAnswer = SOLUTIONS_TWO;
        } else {
            eq->x1 = temp / a;
            eq->x2 = c / temp;
            eq->nAnswer = SOLUTIONS_TWO;
        }
    } else if (cmp_to_zero(D) == 0) {
        eq->x1 = (-0.5 * b) / a;   
        eq->nAnswer = SOLUTIONS_ONE;
    } else {
        eq->nAnswer = SOLUTIONS_ZERO;
    }
}

/**
 * @brief Функция, обрабатывающая 1 уравнение
 * 
 * Данная функция осуществляет ввод данных, решение квадратного уравнение и вывод ответа
 * 
 * 
*/
void solver() { //Как назвать
    equation_info eq = {};
    if(!input_from_term(&eq)) return;
    //normalize_pow2(&a, &b, &c);
    equation_solve(&eq);
    print_answer(eq);
}