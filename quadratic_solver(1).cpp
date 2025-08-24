
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>


const int EMAX = (DBL_MAX_EXP - 1);                  // 1023 
const int EMIN = (DBL_MIN_EXP - DBL_MANT_DIG);       // -1074 

const char *file = "tests";

//! @brief Набор констант, обозначающих количество решений квадратного уравнения
enum type_of_answer {
    SOLUTIONS_INF = -1, ///< Бесконечное число решений
    SOLUTIONS_ZERO, ///< Нет решений
    SOLUTIONS_ONE, ///< Одно решение
    SOLUTIONS_TWO, ///< Два решения
    SOLUTIONS_ENUM_MAX,
};

/**
 * @brief Превращает часть кода в строку.
 * @param [in] a Кусок кода, который будет преобразован в строку.
 * @return Строчное отображение кода
 * 
 * Макрос берет код, который ему передан и превращает его в строку.
 * 
 * @note В случае попытки перевода функций, может протребоваться дополнительное преобразование
*/
#define stringify(a) #a


#define codify(a)

/**
 * @brief Аналог assert, завершающий программу.
 * @param [in] test Условие, которое проверяется assert-ом.
 * @param [in] message Сообщение, которое будет выведено.
 * 
 * Макрос проверяет заданное условие и, если оно ложно, выдает сообщение об ошибке, 
 * содержащее имя функции и номер строки кода, где произошел вызол и аргумент, который вызвал этот assert. 
 * После завершает выполнение программы.
 * 
*/
#ifdef NDEBUG
    #define soft_assert(...) (void)0
#else
    #define hard_assert(test, message) \
        do {            \
            if(!(test)) { \
                fprintf(stderr, "%s%s\nERROR WAS OCCURED IN %s IN %i LINE FROM %s BY %s%s\n", RED, message,__FILE__, __LINE__, __PRETTY_FUNCTION__, stringify(test), RESET); \
                abort(); \
            }   \
        } while(0)
#endif


/**
 * @brief Аналог assert, НЕ завершающий программу.
 * @param [in] test Условие, которое проверяется assert-ом.
 * @param [in] message Сообщение, которое будет выведено.
 * 
 * Макрос проверяет заданное условие и, если оно ложно, выдает сообщение об ошибке, 
 * содержащее имя функции и номер строки кода, где произошел вызол и аргумент, который вызвал этот assert. 
 * После выполнения НЕ завершает выполнение программы.
 * 
*/
#ifdef NDEBUG
    #define soft_assert(...) (void)0
#else
    #define soft_assert(test, message) \
        do {        \
            if(!(test)) { \
                printf(RED "%s\nERROR WAS OCCURED IN %s IN %i LINE FROM %s BY %s" RESET "\n", \
                    message,__FILE__, __LINE__, __PRETTY_FUNCTION__, stringify(test)); \
            }  \
        } while(0)
#endif


#ifdef NDEBUG
    #define soft_assert_functional(...) (void)0
#else 
    #define soft_assert_functional(test, message, command) \
        do { \
            if(!(test)) { \
                printf(RED "%s\nERROR WAS OCCURED IN %s IN %i LINE FROM %s BY %s" RESET "\n", \
                    message,__FILE__, __LINE__, __PRETTY_FUNCTION__, stringify(test)); \
            }  \
            command; \
        } while(0)
#endif



//! @brief Строка, придающая выводу красный цвет.
#define RED "\033[1;31m"

//! @brief Строка, очищающая цвет вывода.   
#define RESET "\033[0m"

struct equation_info;
bool is_answer_correct(equation_info eq, equation_info eq_correct);
void normalize_pow2(equation_info *eq);
bool input_from_term(equation_info *eq);
bool input_from_file(equation_info *eq, FILE *curr_file);
bool try_linear_solve(equation_info *eq);
void equation_solve(equation_info *eq);
void print_answer(equation_info eq);
void solver();
void test(equation_info eq, const long int test_number);
int cmp_to_zero(double a);
bool discard_line_and_check_from_term();
bool discard_line_and_check_from_file(char *curr_file) ;
bool is_float_correct(double a);
void tester();


struct equation_info {
    double a = 0.0, b = 0.0, c = 0.0;
    type_of_answer nAnswer = SOLUTIONS_INF;
    double x1 = 0.0, x2 = 0.0;
    
};


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

bool is_answer_correct(equation_info eq, equation_info eq_correct) {
    if (cmp_for_double(eq.nAnswer, eq_correct.nAnswer) == 0 and 
       ((cmp_for_double(eq_correct.x1, eq.x1) == 0 and cmp_for_double(eq_correct.x2, eq.x2) == 0) or
        (cmp_for_double(eq_correct.x1, eq.x2) == 0 and cmp_for_double(eq_correct.x2, eq.x1) == 0))) {
        return true;
    }
    return false;
}


//---------------------------------------------------------------------------
/**
 * @brief Функция, очищающая буфер ввода консоли и проверяющая его "пустоту".
 * @param [out] a Первый коэффицент.
 * 
 * Функция посимвольно очищает буфер ввода и, если опадется что-либо кроме пробела или таба, вернет false, иначе - true
 * 
 * @return Возвращает есть ли в буфере что=либо кроме пробельных символов
*/
bool discard_line_and_check_from_term() {
    int ch = 0;
    bool is_float_correct = true; 
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ' && ch != '\t') is_float_correct = false;
    }
    if (!is_float_correct) return false;
    return true; 
}

/**
 * @brief Функция, очищающая буфер ввода файла и проверяющая его "пустоту".
 * @param [out] a Первый коэффицент.
 * 
 * Функция посимвольно очищает буфер ввода и, если опадется что-либо кроме пробела или таба, вернет false, иначе - true
 * 
 * @return Возвращает есть ли в буфере что=либо кроме пробельных символов
*/
bool discard_line_and_check_from_file(char *curr_file) {
    int ch = 0;
    bool flag = 0;

//Большие буквы или нижние подчеркивания
    hard_assert(curr_file != nullptr, "File doesn`t found");

    while ((ch = *(curr_file++)) != '\n' && ch != EOF) {
        if (ch != ' ' && ch != '\t') flag = 1; // K&R priloJILenie B (is...)
    }
    if (flag) return false;
    return true; 
}
//---------------------------------------------------------------------------

/**
 * @brief Функция, производящая ввод и проверку коэфицентов квадратного уравнения из консоли.
 * @param [out] a Первый коэффицент.
 * @param [out] b Второй коэффицент.
 * @param [out] c Третий коэффицент.
 * 
 * @return Возвращает корректный ли ввод
*/
bool input_from_term(equation_info *eq) {
    hard_assert(eq != nullptr, "eq is nullptr");

    printf("Введите коэффициенты:\n");
    if (scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c) != 3 || 
        !isfinite(eq->a) || !isfinite(eq->b) || !isfinite(eq->c) || !discard_line_and_check_from_term()) {
        printf("Неверный ввод\n");
        return false;
    }
    return true;
}

/**
 * @brief Функция, производящая ввод и проверку коэфицентов квадратного уравнения из файла.
 * @param [out] a Первый коэффицент.
 * @param [out] b Второй коэффицент.
 * @param [out] c Третий коэффицент.
 * @param [out] nAnswer Количество корней .
 * @param [out] x1 Первый корень.
 * @param [out] x2 Второй корень.
 * 
 * @return Возвращает корректный ли ввод
*/

/*
bool input_from_file_legacy(equation_info *eq, FILE *curr_file) {
    hard_assert(eq != nullptr, "eq is nullptr");

    hard_assert(curr_file != nullptr, "File doesn`t found");
    int nAnswerInt = 0;
    if (fscanf(curr_file, "%lf %lf %lf %i", &eq->a, &eq->b, &eq->c, &nAnswerInt) != 4 || 
        !isfinite(eq->a) || !isfinite(eq->b) || !isfinite(eq->c)) {
        printf("Неверный ввод\n");
        return false;
    }

    switch(nAnswerInt) {
        case -1:
            eq->nAnswer = SOLUTIONS_INF;
            break;
        case 0:
            eq->nAnswer = SOLUTIONS_ZERO;
            break;
        case 1:
            eq->nAnswer = SOLUTIONS_ONE;
            break;
        case 2:
            eq->nAnswer = SOLUTIONS_TWO;
            break;
        default:
            soft_assert_functional(false, "Inccorect nAnswer", return false);
            break;
    }
    switch(eq->nAnswer) {
        case SOLUTIONS_ZERO:
            if (!discard_line_and_check_from_file(curr_file)) {
                printf("Неверный ввод\n");
                return false;
            }
            break;
        case SOLUTIONS_ONE:
            if (fscanf(curr_file, "%lf", &eq->x1) != 1 || 
                !isfinite(eq->x1) || !discard_line_and_check_from_file(curr_file)) {
                printf("Неверный ввод\n");
                return false;
            }
            break;
        case SOLUTIONS_TWO:
            if (fscanf(curr_file, "%lf %lf", &eq->x1, &eq->x2) != 2 || 
                !isfinite(eq->x1) || !isfinite(eq->x2) || !discard_line_and_check_from_file(curr_file)) {
                printf("Неверный ввод\n");
                return false;
            }
            break;
        case SOLUTIONS_INF:
            if (!discard_line_and_check_from_file(curr_file)) {
                printf("Неверный ввод\n");
                return false;
            }
            break;
        default:
            soft_assert_functional(false, "Something wrong with input from file", return false);
            break;
    }
    return true;
}
*/
bool input_from_file(equation_info *eq, FILE *curr_file) {
    hard_assert(eq != nullptr, "eq is nullptr");
    hard_assert(curr_file != nullptr, "File doesn`t found");

    char *buffer = 0;
    fseek (curr_file, 0, SEEK_END);
    long int length = ftell(curr_file);
    fseek (curr_file, 0, SEEK_SET);
    buffer = (char *)malloc (length * sizeof(char));
    hard_assert(!buffer, "Memory allocation failed ");

    fread(buffer, 1, length, curr_file);

    int nAnswerInt = 0;
    if (sscanf(buffer, "%lf %lf %lf %i", &eq->a, &eq->b, &eq->c, &nAnswerInt) != 4 || 
        !isfinite(eq->a) || !isfinite(eq->b) || !isfinite(eq->c)) {
        printf("Неверный ввод\n");
        return false;
    }
    //Заменить свич на прямой каст
    switch(nAnswerInt) {
        case -1:
            eq->nAnswer = SOLUTIONS_INF;
            break;
        case 0:
            eq->nAnswer = SOLUTIONS_ZERO;
            break;
        case 1:
            eq->nAnswer = SOLUTIONS_ONE;
            break;
        case 2:
            eq->nAnswer = SOLUTIONS_TWO;
            break;
        default:
            soft_assert_functional(false, "Inccorect nAnswer", return false);
            break;
    }
    switch(eq->nAnswer) {
        case SOLUTIONS_ZERO:
            if (!discard_line_and_check_from_file(buffer)) {
                printf("Неверный ввод\n");
                return false;
            }
            break;
        case SOLUTIONS_ONE:
            if (fscanf(curr_file, "%lf", &eq->x1) != 1 || 
                !isfinite(eq->x1) || !discard_line_and_check_from_file(buffer)) {
                printf("Неверный ввод\n");
                return false;
            }
            break;
        case SOLUTIONS_TWO:
            if (fscanf(curr_file, "%lf %lf", &eq->x1, &eq->x2) != 2 || 
                !isfinite(eq->x1) || !isfinite(eq->x2) || !discard_line_and_check_from_file(buffer)) {
                printf("Неверный ввод\n");
                return false;
            }
            break;
        case SOLUTIONS_INF:
            if (!discard_line_and_check_from_file(buffer)) {
                printf("Неверный ввод\n");
                return false;
            }
            break;
        default:
            soft_assert_functional(false, "Something wrong with input from file", return false);
            break;
    }
    return true;

}



//---------------------------------------------------------------------------

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
        return ;
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

void tester(FILE* file_pointer, const long int test_number) {

    equation_info eq_correct;

    input_from_file(&eq_correct, file_pointer);

    equation_info eq;
    eq.a = eq_correct.a;
    eq.b = eq_correct.b;
    eq.c = eq_correct.c;
    equation_solve(&eq);

    if(!is_answer_correct(eq, eq_correct)) {
        printf("Test %ld: WA a = %.17g, b = %.17g, c = %.17g\n", test_number, eq.a, eq.b, eq.c);
    } else {
        printf("Test %ld: OK\n", test_number);
    }
}

void test(equation_info eq_correct,
          const long int test_number) {
    equation_info eq = {eq_correct.a, eq_correct.b, eq_correct.c};
    equation_solve(&eq);

    if(!is_answer_correct(eq, eq_correct)) {
        printf("Test %ld: WA a = %.17g, b = %.17g, c = %.17g\n", test_number, eq.a, eq.b, eq.c);
    } else {
        printf("Test %ld: OK\n", test_number);
    }
}


void test_all() {

    equation_info tasks[7] = {
        {1.0, 2.0, 1.0, SOLUTIONS_ONE, -1.0, 0.0},
        {1.0, -5.0, 6.0, SOLUTIONS_TWO, 2.0, 3.0},
        {1.0, 5.0, 6.0, SOLUTIONS_TWO, -2.0, -3.0},
        {1.0, 2.0, 5.0, SOLUTIONS_ZERO, 0.0, 0.0},
        {1.0, 0.0, -1.0, SOLUTIONS_TWO, -1.0, 1.0},
        {0.0, 2.0, 2.0, SOLUTIONS_ONE, -1.0, 0.0},
        {1.0, 1.0, 0.0, SOLUTIONS_TWO, 0.0, -1.0}};

    for (int i = 0; i < sizeof(tasks) / sizeof(equation_info); i++) {
        test(tasks[i], i + 1);
    }
}


/**
 * @brief Функция, обрабатывающая 1 уравнение
 * 
 * Данная функция осуществляет ввод данных, решение квадратного уравнение и вывод ответа
 * 
 * 
*/
void solver() {
    equation_info eq;
    if(!input_from_term(&eq)) return ;

    //normalize_pow2(&a, &b, &c);

    equation_solve(&eq);

    print_answer(eq);
}

int main() {
    printf("Введите имя файла:\n");

    char file_name[100];
    scanf("%s", file_name);

    FILE *file_pointer = fopen(file_name, "r");
    hard_assert(file_pointer != nullptr, "File doesn`t found");
    long num_of_tests = 0;
    fscanf(file_pointer,"%ld", &num_of_tests);


    long int test_number = 1;
    for(int i = 0; i < num_of_tests; i++) {
        tester(file_pointer, test_number);
        test_number++;

    }
    test_all();

    printf("Если хотите решить следующее уравнение - нажмите y\n");
    char flag = 'y';
    while (flag == 'y') {
        solver();
        printf("Следующее?\n");
        scanf(" %c", &flag);
    }
} 
