
#include <stdio.h>
#include <math.h>
#include <float.h>

const int EMAX = (DBL_MAX_EXP - 1);                  // 1023 
const int EMIN = (DBL_MIN_EXP - DBL_MANT_DIG);       // -1074 

enum type_of_answer {
    INF_SOLUTIONS = -1, 
    ZERO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS
};


#define hard_assert(test, message) \
    if(!(test)) { \
        fprintf(stderr, "%s\nERROR WAS OCCURED IN %i LINE\n", message, __LINE__); \
        abort(); \
    } 

#define soft_assert(test, message) \
    if(!(test)) { \
        printf("%s\nERROR WAS OCCURED IN %i LINE\n", message, __LINE__); \
    }


bool is_buffer_empty();
void normalize_pow2(double *a, double *b, double *c);
bool input(double *a, double *b, double *c);
bool linear_solve(double a, double b, double c, type_of_answer *nAnswer, double *x1);
void equation_solve(double a1, double b1, double c1, type_of_answer *nAnswer, double *x1, double *x2);
void print_answer(type_of_answer nAnswer, double x1, double x2);
void solver();
int cmp_to_zero(double a);
bool discard_line_and_check();

int cmp_to_zero(double a) {
    if (fabs(a) < DBL_EPSILON) {
        return 0;
    }
    if (a > DBL_EPSILON) {
        return 1;
    }
    return -1;
}

void normalize_pow2(double *a, double *b, double *c) {
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

bool /*try_*/linear_solve(double a, double b, double c, type_of_answer *nAnswer, double *x1) {
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

void print_answer(type_of_answer nAnswer, double x1, double x2) {
    switch (nAnswer) {
    case INF_SOLUTIONS:
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

/*#define max(x, y) (x) > (y) ? (x) : (y)

max(a + b, b++);
*/
void equation_solve(double a, double b, double c, type_of_answer *nAnswer, double *x1, double *x2) {
    
    hard_assert(x1 != nullptr, "FUN");
    hard_assert(x2 != nullptr, "FUN");
    hard_assert(nAnswer != nullptr, "FUN");
    soft_assert(a != NAN, "error x1 is null");

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

int main(void) {
    printf("Если хотите решить следующее уравнение - нажмите y\n");
    char flag = 'y';
    while (flag == 'y') {
        solver();
        printf("Следующее?\n");
        scanf(" %c", &flag);
    }
}
