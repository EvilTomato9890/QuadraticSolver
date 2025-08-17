
#include <stdio.h>
#include <math.h>
#include <float.h>

constexpr int EMAX = (DBL_MAX_EXP - 1);                  // 1023 
constexpr int EMIN = (DBL_MIN_EXP - DBL_MANT_DIG);       // -1074 

void normalize_pow2(double *a, double *b, double *c);
bool input(double *a, double *b, double *c);
bool linear_solve(double a, double b, double c, int *type_of_answer, double *x1);
void equation_solve(double a1, double b1, double c1, int *type_of_answer, double *x1, double *x2);
void print_answer(int type_of_answer, double x1, double x2);
void solver();
bool is_zero(double a);


bool is_zero(double a) {
    return fabs(a) < DBL_EPSILON;
}



void normalize_pow2(double *a, double *b, double *c) {
    if (is_zero_by_memcmp(*a) && is_zero_by_memcmp(*b) && is_zero_by_memcmp(*c)) return;

    int ea = (*a != 0) ? ilogb(*a) : 0;
    int eb = (*b != 0) ? ilogb(*b) : 0;
    int ec = (*c != 0) ? ilogb(*c) : 0;


    int t_min = EMIN; 
    int t_max = EMAX; 


    if (*b != 0) {
        int n  = EMAX - 2 * eb;
        int hi = (n >= 0) ? (n / 2) : ((n - 1) / 2); 
        if (hi < t_max) t_max = hi;
    }
    if (*a != 0 && *c != 0) {

        int n  = EMAX - 2 - ea - ec;
        int hi = (n >= 0) ? (n / 2) : ((n - 1) / 2); 
        if (hi < t_max) t_max = hi;
    }


    if (*b != 0) {
        int n  = EMIN - 2 * eb;
        int lo = (n >= 0) ? ((n + 1) / 2) : (n / 2);
        if (lo > t_min) t_min = lo;
    }
    if (*a != 0 && *c != 0) {
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
    printf("Введите коэффициенты:\n");
    if (scanf("%lf %lf %lf", a, b, c) != 3 || !isfinite(*a) || !isfinite(*b) || !isfinite(*c)) {
        printf("Неверный ввод\n");
        return false;
    }
    return true;
}

bool linear_solve(double a, double b, double c, int *type_of_answer, double *x1) {
    if (is_zero(a)) {
        if (is_zero(b)) {
            if (is_zero(c)) *type_of_answer = -1;
            else *type_of_answer = 0;
            return true;
        } else {
            *x1 = - c / b;
            *type_of_answer = 1;
            return true;
        }
    } 
    return false;
}

void print_answer(int type_of_answer, double x1, double x2) {
    switch (type_of_answer) {
    case -1:
        printf("x - любое\n");
        return ;
    case 0: 
        printf("Корней нет\n");
        return ;
    case 1:
        printf("Единственный корень: %.17g\n", x1);
        return ;
    case 2:
        printf("Корня два: x1 = %.17g, x2 = %.17g\n", x1, x2);
        return ;
    default:
        printf("Wrong Type");
        return ;
    }
}

void equation_solve(double a, double b, double c, int *type_of_answer, double *x1, double *x2) {
    
    if(linear_solve(a, b, c, type_of_answer, x1)) {
        return ;
    }

    double D = b * b - 4.0 * a * c;

    if (D > DBL_EPSILON) {
        double temp = -0.5 * (b + sqrt(D)); 
        if (is_zero(temp)) {
            *x1 = (-0.5 * b) / a;   
            *type_of_answer = 1;
        } else {
            *x1 = temp / a;
            *x2 = c / temp;
            *type_of_answer = 2;
        }
    } else if (is_zero(D)) {
        *x1 = (-0.5 * b) / a;   
        *type_of_answer = 1;
    } else {
        *type_of_answer = 0;
    }
}

void solver() {
    double a = 0.0, b = 0.0, c = 0.0;
    
    if(!input(&a, &b, &c)) return ;

    normalize_pow2(&a, &b, &c);

    int type_of_answer = -1;
    double x1 = 0.0, x2 = 0.0;

    
    equation_solve(a, b, c, &type_of_answer, &x1, &x2);

    print_answer(type_of_answer, x1, x2);
}

int main(void) {
    solver();
}
