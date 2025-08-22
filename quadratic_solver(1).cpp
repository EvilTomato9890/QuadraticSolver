
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>
const int EMAX = (DBL_MAX_EXP - 1);                  // 1023 
const int EMIN = (DBL_MIN_EXP - DBL_MANT_DIG);       // -1074 

enum type_of_answer {
    INF_SOLUTIONS = -1, 
    ZERO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS
};

#define stringify(a) #a
#define hard_assert(test, message) \
    if(!(test)) { \
        fprintf(stderr, "%s%s\nERROR WAS OCCURED IN %s IN %i LINE FROM %s BY %s%s\n", RED, message,__FILE__, __LINE__, __PRETTY_FUNCTION__, stringify(test), RESET); \
        abort(); \
    } 

#define soft_assert(test, message) \
    if(!(test)) { \
        printf("%s%s\nERROR WAS OCCURED IN %s IN %i LINE FROM %s BY %s%s\n", RED, message,__FILE__, __LINE__, __PRETTY_FUNCTION__, stringify(test), RESET); \
    }  

#define RED "\033[1;31m"
#define RESET "\033[0m"


bool is_buffer_empty();
void normalize_pow2(double *a, double *b, double *c);
bool input(double *a, double *b, double *c);
bool linear_solve(double a, double b, double c, type_of_answer *nAnswer, double *x1);
void equation_solve(double a1, double b1, double c1, type_of_answer *nAnswer, double *x1, double *x2);
void print_answer(type_of_answer nAnswer, double x1, double x2);
void solver();
int cmp_to_zero(double a);
bool discard_line_and_check();
bool is_correct(double a);


int cmp_to_zero(const double a) {
    soft_assert(is_correct(a), "error x1 is null");
    if (fabs(a) < DBL_EPSILON) {
        return 0;
    }
    if (a > DBL_EPSILON) {
        return 1;
    }
    return -1;
}


bool is_correct(const double a) {
    if (a == INFINITY || a == -INFINITY || a != a) return false;
    return true;
}


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

bool input(double *a, double *b, double *c) {
    hard_assert(a != nullptr, "a is nullptr");
    hard_assert(b != nullptr, "b is nullptr");
    hard_assert(c != nullptr, "c is nullptr");

    printf("Введите коэффициенты:\n");
    if (scanf("%lf %lf %lf", a, b, c) != 3 || 
        !isfinite(*a) || !isfinite(*b) || !isfinite(*c) || !discard_line_and_check()) {
        printf("Неверный ввод\n");
        return false;
    }
    return true;
}



bool discard_line_and_check() {
    int ch = 0;
    bool flag = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ' && ch != '\t') flag = 1;
    }
    if (flag) return false;
    return true;
}

bool /*try_*/linear_solve(const double a, const double b, const double c, 
                          type_of_answer *nAnswer, 
                          double* x1) {

    soft_assert(is_correct(a), "a is NAN");
    soft_assert(is_correct(b), "b is NAN"); 
    soft_assert(is_correct(c), "c is NAN"); 


    if (cmp_to_zero(a) == 0) {
        if (cmp_to_zero(b) == 0) {
            if (cmp_to_zero(c) == 0) *nAnswer = INF_SOLUTIONS;
            else *nAnswer = ZERO_SOLUTIONS;
            return true;
        } else {
            *x1 = - c / b;
            *nAnswer = ONE_SOLUTION;
            return true;
        }
    } 
    return false;
}

void print_answer(type_of_answer nAnswer, const double x1, const double x2) {

    soft_assert(is_correct(x1), "x1 is NAN");
    soft_assert(is_correct(x2), "x2 is NAN");

    switch (nAnswer) {
    case INF_SOLUTIONS:
        printf("x - любое\n");
        return ;
    case ZERO_SOLUTIONS: 
        printf("Корней нет\n");
        return ;
    case ONE_SOLUTION:
        printf("Единственный корень: %.17g\n", x1);
        return ;
    case TWO_SOLUTIONS:
        printf("Корня два: x1 = %.17g, x2 = %.17g\n", x1, x2);
        return ;
    default:
        printf("Wrong Type");
        return ;
    }
}

void equation_solve(const double a, const double b, const double c, 
                    type_of_answer *nAnswer, 
                    double *x1, double *x2) {
    hard_assert(x1 != nullptr, "x1 is nullptr");
    hard_assert(x2 != nullptr, "x2 is nullptr");
    hard_assert(nAnswer != nullptr, "nAnswer is nullptr");


    if(linear_solve(a, b, c, nAnswer, x1)) {
        return ;
    }

    double D = b * b - 4.0 * a * c;

    if (cmp_to_zero(D) > 0) {
        double temp = -0.5 * (b + sqrt(D)); 
        if (cmp_to_zero(temp) == 0) {
            *x1 =  - b / a;   
            *x2 = 0;
            *nAnswer = TWO_SOLUTIONS;
        } else {
            *x1 = temp / a;
            *x2 = c / temp;
            *nAnswer = TWO_SOLUTIONS;
        }
    } else if (cmp_to_zero(D) == 0) {
        *x1 = (-0.5 * b) / a;   
        *nAnswer = ONE_SOLUTION;
    } else {
        *nAnswer = ZERO_SOLUTIONS;
    }
}

void solver() {
    double a = 0.0, b = 0.0, c = 0.0;
    
    if(!input(&a, &b, &c)) return ;

    normalize_pow2(&a, &b, &c);

    type_of_answer nAnswer = INF_SOLUTIONS;
    double x1 = 0.0, x2 = 0.0;

    equation_solve(a, b, c, &nAnswer, &x1, &x2);

    print_answer(nAnswer, x1, x2);
}

int main(int args, char *argv[]) {
    printf("ВЫВОД: %s\n", argv[0]);
    printf("Если хотите решить следующее уравнение - нажмите y\n");
    soft_assert(false && 1234, "FUN");
    assert(false && 1234);
    
    char flag = 'y';
    while (flag == 'y') {
        solver();
        printf("Следующее?\n");
        scanf(" %c", &flag);
    }
}
