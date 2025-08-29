#include "equation_solvers.h"
#include "asserts.h"
#include "helpers.h"
#include "input.h"
#include "structers.h"
#include "logger.h"
#include <math.h>
/**
 * @brief Функция, решающая линейное уравнение, если оно таковым является.
 * @param [in] eq Структура содержащая всю необходимую информацию о решаемом уравнении, в том числе его коеффиценты
 * 
 * @return Возвращает является ли уравнение линейным
*/
bool try_linear_solve(equation_info *eq) {
    LOGGER_DEBUG("Linear solver started");
    const double a = eq->a, b = eq->b, c = eq->c;

    soft_assert_functional(is_float_correct(eq->a), "a is NAN", LOGGER_WARNING("a is NAN"));
    soft_assert_functional(is_float_correct(eq->b), "b is NAN", LOGGER_WARNING("b is NAN")); 
    soft_assert_functional(is_float_correct(eq->c), "c is NAN", LOGGER_WARNING("c is NAN")); 

    if (cmp_to_zero(a) == 0) {
        if (cmp_to_zero(b) == 0) {
            eq->nAnswer = cmp_to_zero(c) == 0 ? SOLUTIONS_INF : SOLUTIONS_ZERO;
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
 * @param [in] eq Стуктура, содержащая всю необходимую информацию о решаемом уравнении, в том числе его коэффиценты
*/
void equation_solve(equation_info *eq) {
    LOGGER_DEBUG("Equation solver started");
    hard_assert(eq != nullptr, "x1 is nullptr");

    const double a = eq->a, b = eq->b, c = eq->c;
    if(try_linear_solve(eq)) {
        LOGGER_INFO("Equation is linear");
        return;
    }

    double D = b * b - 4.0 * a * c;

    if (cmp_to_zero(D) > 0) {
        LOGGER_INFO("Discriminant > 0");
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
        if (cmp_to_zero(eq->x1) == 0) eq->x1 = 0.0; //Чтобы избежать вывода -0
        eq->nAnswer = SOLUTIONS_ONE;
    } else {
        eq->nAnswer = SOLUTIONS_ZERO;
    }
    LOGGER_INFO("Equation_solver ended");
}

/**
 * @brief Функция, обрабатывающая 1 уравнение
 * 
 * Данная функция осуществляет ввод данных, 
 * решение квадратного уравнение и вывод ответа
 * 
*/
void solver() { 
    LOGGER_INFO("Solver started");
    equation_info eq = {};
    if(!input_from_term(&eq)) return;
    //normalize_pow2(&a, &b, &c);
    equation_solve(&eq);
    print_answer(eq);
    LOGGER_INFO("Solver ended");
}
