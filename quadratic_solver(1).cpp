
#include <stdio.h>
#include <math.h>
#include <float.h>

constexpr int EMAX = (DBL_MAX_EXP - 1);                  // 1023 
constexpr int EMIN = (DBL_MIN_EXP - DBL_MANT_DIG);       // -1074 


void normalize_pow2(double *a, double *b, double *c) {
    if (*a == 0.0 && *b == 0.0 && *c == 0.0) return;

    int ea = (*a != 0.0) ? ilogb(*a) : 0;
    int eb = (*b != 0.0) ? ilogb(*b) : 0;
    int ec = (*c != 0.0) ? ilogb(*c) : 0;


    int t_min = EMIN; 
    int t_max = EMAX; 


    if (*b != 0.0) {
        int n  = EMAX - 2*eb;
        int hi = (n >= 0) ? (n/2) : ((n - 1)/2); 
        if (hi < t_max) t_max = hi;
    }
    if (*a != 0.0 && *c != 0.0) {

        int n  = EMAX - 2 - ea - ec;
        int hi = (n >= 0) ? (n/2) : ((n - 1)/2); 
        if (hi < t_max) t_max = hi;
    }


    if (*b != 0.0) {
        int n  = EMIN - 2*eb;
        int lo = (n >= 0) ? ((n + 1)/2) : (n/2);
        if (lo > t_min) t_min = lo;
    }
    if (*a != 0.0 && *c != 0.0) {
        int n  = EMIN - 2 - ea - ec;
        int lo = (n >= 0) ? ((n + 1)/2) : (n/2);   
        if (lo > t_min) t_min = lo;
    }


    int t = (t_min + t_max) / 2;
    *a = scalbn(*a, t);
    *b = scalbn(*b, t);
    *c = scalbn(*c, t);
}




int main(void) {
    double a, b, c;

    printf("Введите коэффициенты:\n");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3 || !isfinite(a) || !isfinite(b) || !isfinite(c)) {
        printf("Неверный ввод\n");
        return 1;
    }

    normalize_pow2(&a, &b, &c);

    if (a == 0.0) {
        if (b == 0.0) {
            if (c == 0.0) printf("x - любое\n");
            else printf("Корней нет\n");
            return 0;
        } else {
            double x = -c / b;
            printf("Единственный корень: %.17g\n", x);
            return 0;
        }
    }

    double D = b * b - 4.0 * a * c;

    double tolD = DBL_EPSILON * (fabs(b) * fabs(b) + 4.0 * fabs(a) * fabs(c));

    if (D > tolD) {
        double temp = -0.5 * (b + sqrt(D)); 
        if (temp == 0.0) {
            double x = (-0.5 * b) / a;   
            printf("Единственный корень: %.17g\n", x);
        } else {
            double x1 = temp / a;
            double x2 = c / temp;
            printf("Корня два: x1 = %.17g, x2 = %.17g\n", x1, x2);
        }
    } else if (fabs(D) < tolD) {
        double x = (-0.5 * b) / a;   
        printf("Единственный корень: %.17g\n", x);
    } else {
        printf("Корней нет\n");
    }
    return 0;
}

