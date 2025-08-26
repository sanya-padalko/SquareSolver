#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>
#include <Windows.h>

#define Sleep(x) Sleep(x / print_speed)

#define my_assert print_string("Program catched error, so it must be stopped\n\0", RED); \
                  Sleep(3000); \
                  exit(0);

#define nan_err(comp) if (comp) { \
                          print_string("Variable went equal NAN in function \0", RED); \
                          char str[200]; \
                          sprintf(str, "%s ", __FUNCTION__); \
                          print_string(str, YELLOW); \
                          print_string("from ", RED); \
                          sprintf(str, "%s ", __FILE__); \
                          print_string(str, YELLOW); \
                          print_string("in line ", RED); \
                          sprintf(str, "%d\n\0", __LINE__); \
                          print_string(str, YELLOW); \
                          return NAN_ERR; \
                      }

#define null_err(comp) if (comp) { \
                          print_string("Pointer went equal NULLPTR in function \0", RED); \
                          char str[200]; \
                          sprintf(str, "%s ", __FUNCTION__); \
                          print_string(str, YELLOW); \
                          print_string("from ", RED); \
                          sprintf(str, "%s ", __FILE__); \
                          print_string(str, YELLOW); \
                          print_string("in line ", RED); \
                          sprintf(str, "%d\n\0", __LINE__); \
                          print_string(str, YELLOW); \
                          return NULLPTR; \
                      }

#define inf_err(comp) if (comp) { \
                          print_string("The digit didn't become finite in function \0", RED); \
                          char str[200]; \
                          sprintf(str, "%s ", __FUNCTION__); \
                          print_string(str, YELLOW); \
                          print_string("from ", RED); \
                          sprintf(str, "%s ", __FILE__); \
                          print_string(str, YELLOW); \
                          print_string("in line ", RED); \
                          sprintf(str, "%d\n\0", __LINE__); \
                          print_string(str, YELLOW); \
                          return INFINITY_DIGIT; \
                       }

// upgrade read
// read раздельная компиляция и разибение на файлы
// ДОКУМЕНТАЦИЮ ПЕРЕПИСАТЬ
// скорость вывода scanf одного элемента без чистки буфера + число не отрицательное
// сделать print_string для ошибок
// посмотреть избраный клип

enum N_ROOTS {
    INF_ROOTS     = -1,
    NO_ROOTS      =  0,
    ONE_ROOT      =  1,
    TWO_ROOTS     =  2
};

enum ERRORS {
    NOTHING        = 0,
    NAN_ERR        = 1,
    NULLPTR        = 2,
    INFINITY_DIGIT = 3
};

enum COLORS {
    WHITE          = 0,
    RED            = 1,
    GREEN          = 2,
    BLUE           = 3,
    YELLOW         = 4
};

const double EPS = 1e-6;

double print_speed = 1.0;

struct COEF
{
    double a = 0, b = 0, c = 0;
};

struct SOLVE
{
    double x1 = 0, x2 = 0;
    N_ROOTS nroots = NO_ROOTS;
};

bool do_unit(bool &is_unit, int &count_s);                                  /* done       */

bool naebalovo(const int n_queries);                                        /* add img    */

bool get_symbol(char &want);                                                /* fix 's'    */

bool continue_program();                                                    /* RELOOK     */

ERRORS print_string(const char* const str, const COLORS color);             /* add colors */

double calc_func(const COEF* const coefs, const double x);                  /* add errors */

ERRORS OneTest(const double* const mas, bool &fl);                          /* done  */

ERRORS unit_tests();                                                        /* print y/n  */

bool is_zero(const double integ);                                           /* del assert */

ERRORS solve_linear_equation(const COEF* const coefs, SOLVE* const solve);  /* показать   */

ERRORS solve_square_equation(const COEF* const coefs, SOLVE* const solve);  /* показать   */

ERRORS solve_equation(       const COEF* const coefs, SOLVE* const solve);  /* done       */

void clear_buffer();                                                        /* done       */

void print_coeff_err(const int ind);                                        /* done       */

ERRORS read(COEF* const coefs, bool &true_read);                            /* УПРОСТИТЬ  */

ERRORS input(COEF* const coefs);                                            /* add n_coef */

ERRORS print_linear_equation(const COEF* const coefs);                      /* done       */

ERRORS print_square_equation(const COEF* const coefs);                      /* done       */

ERRORS print_equation(const COEF* const coefs);                             /* done       */

ERRORS output(const COEF* const coefs, const SOLVE* const solve);           /* done       */

int main() {

    print_string("What's up my boychik, this program solve square equation\n\n\0", WHITE);

    int n_queries = 0;

    bool is_unit = false;

    ERRORS err = NOTHING;

    int count_s = 0;

    do
    {
        if (!do_unit(is_unit, count_s))
            return 0;

        print_string("Enter the coefficients a, b, c:\n\0", WHITE);

        COEF coefs = {};

        err = input(&coefs);

        if (err != NOTHING)
            return 0;

        if (naebalovo(n_queries))
            return 0;

        SOLVE solve = {};

        err = solve_equation(&coefs, &solve);

        if (err != NOTHING)
            return 0;

        err = output(&coefs, &solve);

        if (err != NOTHING)
            return 0;

        printf("\n");

        ++n_queries;

    } while (continue_program());

    return 0;
}

bool do_unit(bool &is_unit, int &count_s)
{
    if (!is_unit)
    {
        print_string("Do you want check program on unit-test? (yes - y, no - n, kiss my lips and kick my ass - s)\n\0", BLUE);

        char want_unit = 0;

        if (!get_symbol(want_unit)) {
            return false;
        }

        if (want_unit == 'y') {
            is_unit = true;

            ERRORS err = unit_tests();

            if (err != NOTHING)
                return false;
        }

        else if (want_unit == 's')
        {
            ++count_s;

            print_string("Soon, Eminem will be there\n\0", GREEN);
        }

        else
        {
            print_string("Ok, maybe next time\n\n\0", BLUE);
        }

        Sleep(600);
    }

    return true;
}

bool naebalovo(const int n_queries)
{

    if (n_queries < 5)
    {
        return false;
    }

    print_string("Sorry, bro \0", GREEN);
    print_string("your free queries is end\0", GREEN);
    print_string(", please pay 15$ for more questions (\0", GREEN);
    print_string("+79000909081\0", BLUE);
    print_string(")\n\0", GREEN);

    return true;
}

bool get_symbol(char &want)
{
    want = getchar();
    char last = want;
    int cnt = 0;

    while ((want != 'y' && want != 'n' && want != 's') || ((want = getchar()) != '\n' && (want != EOF)))
    {
        ++cnt;

        if (want != '\n' && want != EOF)
        {
            clear_buffer();
        }

        Sleep(700);
        print_string("Eeeee.... \0", RED);
        Sleep(700);

        if (cnt == 3)
        {
            for (int i = 0; i < 3; ++i)
            {
                print_string("FUCK! \0", RED);
                Sleep(150);
            }

            print_string("What a hell, bro?!?\n\0", RED);
            Sleep(400);
            print_string("You entered the wrong answer 3 times in a row. You're blocked for 30 seconds.\n\0", RED);
            Sleep(300);

            for (int i = 30; i > 15; --i)
            {
                char str[10] = "";
                sprintf(str, "%ds \0", i);
                print_string(str, RED);
                Sleep(700);
            }

            for (int i = 15; i > 5; --i)
            {
                char str[10] = "";
                sprintf(str, "%ds \0", i);
                print_string(str, YELLOW);
                Sleep(700);
            }

            for (int i = 5; i >= 0; --i)
            {
                char str[10] = "";
                sprintf(str, "%ds \0", i);
                print_string(str, GREEN);
                Sleep(700);
            }

            Sleep(500);
            print_string("You're free\0", GREEN);
            Sleep(500);
            print_string(", be careful next time\0", GREEN);
            Sleep(500);
            print_string(", only 'y' or 'n'\n\0", GREEN);
            Sleep(200);
        }

        else if (cnt == 6)
        {
            print_string("Oh... \0", RED);
            Sleep(700);
            print_string("I gave you 3 more attempts, but you couldn't enter one of the two characters, so I'll find someone else. GOODBYE, bro, good luck", YELLOW);
            Sleep(2000);
            print_string("\nThe companion left the chat", GREEN);
            Sleep(500);

            return false;
        }

        else
        {
            print_string("Wrong answer, bro, please print only 'y' or 'n'\n\0", RED);
        }

        want = getchar();
        last = want;
    }

    if (want != '\n' && want != EOF)
        clear_buffer();
    else
        want = last;

    return true;
}

bool continue_program()
{
    print_string("Continue? (yes - y/ no - n/ suck my dick - s)\n\0", BLUE);

    char want = 0;

    if (!get_symbol(want))
    {
        return false;
    }

    Sleep(700);

    switch (want)
    {
        case 's':
            Sleep(700);
            print_string("GREAT!!!\n\0", YELLOW);
            Sleep(700);
            print_string("If you are a boy, then write to me in tg (\0", YELLOW);
            Sleep(300);
            print_string("@EntryFr4ger\0", GREEN);
            Sleep(300);
            print_string("), girls - bye\n\0", YELLOW);
            Sleep(1000);
            print_string("I'm Matvey :)\n\0", GREEN);
            Sleep(1000);
            break;

        case 'n':
            print_string("Why is it so fast??\0", YELLOW);
            Sleep(1000);
            print_string(" Okey, bro, good luck\n\0", YELLOW);
            Sleep(1000);
            print_string("You will always be with me, \0", YELLOW);
            Sleep(1000);
            print_string("you will always be my brother...\n\0", GREEN);
            Sleep(1000);
            break;

        default:
            print_string("Cool, let's go :)\n\0", YELLOW);

    }

    print_string("\n\0", WHITE);
    return (want == 'y');
}

// ---------------------------------
//! @brief Вывод строки опредленного цвета до символа '\0'
//!
//!@param[in] coefficents[0]  coefficents[0] - массив char-ов, строка, которую хотим вывести
//!@param[in] coefficents[1]  coefficents[1] - число типа int, отвечает за цвет текста, который хотим вывести (0 - белый, 1 - красный, 2 - зеленый)
//!
//!@return Ничего не возвращает, но выводит строку определенного цвета
// ---------------------------------

ERRORS print_string(const char* const str, const COLORS color)
{
    null_err(str == nullptr);

    int i = 0;

    while (str[i] != '\0')
    {
        switch (color)
        {
            case RED:
                printf("\033[31m%c\033[0m", str[i++]);
                break;

            case GREEN:
                printf("\033[32m%c\033[0m", str[i++]);
                break;

            case YELLOW:
                printf("\033[33m%c\033[0m", str[i++]);
                break;

            case BLUE:
                printf("\033[36m%c\033[0m", str[i++]);
                break;

            default:
                printf("%c", str[i++]);
        }

        Sleep(75);
    }
}

// ---------------------------------
//! @brief Подсчет значения квадаратичной функции с заданными коэффициентами в конкретной точке
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!@param[in] coefficents[1]  coefficents[1] - число типа double, x, который подставляется в функцию
//!
//!@return Значение функции в точке
// ---------------------------------

double calc_func(const COEF* const coefs, const double x)
{
    return coefs->a * x * x + coefs->b * x + coefs->c;
}

ERRORS OneTest(const double* const mas, bool &fl)
{
    null_err(!mas);

    COEF coefs = {};

    coefs.a = mas[0];
    coefs.b = mas[1];
    coefs.c = mas[2];

    SOLVE solve = {};

    ERRORS err = solve_equation(&coefs, &solve);

    if (err != NOTHING)
    {
        return err;
    }

    if (is_zero(coefs.a))
    {
        if (is_zero(coefs.b))
        {
            N_ROOTS results[] = {NO_ROOTS, INF_ROOTS};

            if (results[is_zero(coefs.c)] != solve.nroots) // при с = 0 будет бесконечно много, иначе не будет
            {
                print_string("Oy-oy\n\0", RED);
                char str[200] = "";
                sprintf(str, "UNIT TEST FAILED: %lg %lg %lg, wrong answer: %lg %lg\n\0", coefs.a, coefs.b, coefs.c, solve.x1, solve.x2);
                print_string(str, RED);
                Sleep(600);

                fl = false;
            }

            return NOTHING;
        }

        if ((solve.nroots != ONE_ROOT) || !is_zero(calc_func(&coefs, solve.x1)))
        {
            print_string("Oy-oy\n\0", RED);
            char str[200] = "";
            sprintf(str, "UNIT TEST FAILED: %lg %lg %lg, wrong answer: %lg %lg\n\0", coefs.a, coefs.b, coefs.c, solve.x1, solve.x2);
            print_string(str, RED);
            Sleep(600);

            fl = false;
        }

        return NOTHING;
    }

    if (coefs.b * coefs.b < 4 * coefs.a * coefs.c)
    {
        if (solve.nroots != NO_ROOTS)
        {
            print_string("Oy-oy\n\0", RED);
            char str[200] = "";
            sprintf(str, "UNIT TEST FAILED: %lg %lg %lg, wrong answer: %lg %lg\n\0", coefs.a, coefs.b, coefs.c, solve.x1, solve.x2);
            print_string(str, RED);
            Sleep(600);

            fl = false;
        }
    }

    else if (!is_zero(calc_func(&coefs, solve.x1)) || !is_zero(calc_func(&coefs, solve.x2)))
    {
        print_string("Oy-oy\n\0", RED);
        char str[200] = "";
        sprintf(str, "UNIT TEST FAILED: %lg %lg %lg, wrong answer: %lg %lg\n\0", coefs.a, coefs.b, coefs.c, solve.x1, solve.x2);
        print_string(str, RED);
        Sleep(600);

        fl = false;
    }

    return NOTHING;
}

// ---------------------------------
//! @brief Тестирование программы на заранее заданных тестах
//!
//!@return Ничего не возвращает, но выводит пройдены ли все тесты или тест на котором решение сломалось
// ---------------------------------

ERRORS unit_tests()
{
    N_ROOTS nroots = NO_ROOTS;

    double mas[26][3] = {
        {0, 0, 0},
        {0, 0, 5},
        {1, 5, 6},
        {1, 2, 1},
        {0, 5, 4},
        {1, 3, 2},
        {2, 5, 2},
        {2, 7, 3},
        {3, 8, 5},
        {4, 8, 3},
        {2, 15, 5},
        {14, 115, 10},
        {3, 6, 5},
        {14, 69, 88},
        {15, 60, 1001},
        {100, 3, 13},
        {13, 26, 7},
        {17, 8, 25},
        {17, 25, 8},
        {34, 15, 1},
        {16, 0, 10},
        {10, 16, 0},
        {1, -5, 6},
        {0, 5, 0},
        {3, 0, -1},
        {158.6, 0, 0}
    };

    int i = 0;

    int test_wrong = 0;

    int count_tests = (sizeof(mas) / sizeof(mas[0]));

    while (i < count_tests)
    {
        bool fl = true;

        ERRORS err = OneTest(mas[i], fl);

        if (err != NOTHING)
        {
            return err;
        }

        if (fl)
        {
            print_string("Test is OK\n\0", GREEN);
        }

        test_wrong += !fl;

        ++i;

        Sleep(300);
    }

    Sleep(90);

    if (test_wrong == 0)
    {
        print_string("All the UNIT TESTS is OK.\n\0", GREEN);
        print_string("100% tests is accepted!!!\n\n\0", GREEN);
        Sleep(750);
        print_string("Let's fucking go!\n\n\0", GREEN);
        Sleep(750);
    }

    else
    {
        char str[200] = "";

        sprintf(str, "%d test\0", test_wrong);
        print_string(str, YELLOW);

        if (test_wrong > 1)
            print_string("s\0", YELLOW);

        print_string(" didn't accept, \0", YELLOW);

        Sleep(750);

        sprintf(str, "%d test\0", (count_tests - test_wrong));
        print_string(str, GREEN);

        if ((count_tests - test_wrong) > 1)
            print_string("s\0", GREEN);

        print_string(" accepted\n\0", GREEN);

        Sleep(600);

        double ok_percent = (double)(count_tests - test_wrong) / (double)count_tests * (double)100;

        sprintf(str, "%.2f\0", ok_percent);

        COLORS color = GREEN;

        if (ok_percent < 50)
            color = YELLOW;

        if (ok_percent < 25)
            color = RED;

        print_string(str, color);
        print_string("% tests is accepted\n\n\0", color);

        Sleep(750);
    }

    return NOTHING;
}

// ---------------------------------
//! @brief Проверка равенства нулю числа типа double
//!
//!@param[in] coefficents[0]  coefficents[0] - число типа double, которое хотим проверить на равенство с нулём
//!
//!@return Равняется ли число нулю
// ---------------------------------

bool is_zero(const double integ)
{
    if (!isfinite(integ))
    {
        print_string("The number did not become finite\n\0", RED);
        my_assert;
    }

    return fabs(integ) < EPS;
}

// ---------------------------------
//! @brief Решение линейного уравнения с заданными коэффициентами
//!
//!@param[in] coefficents[0]  coefficents[0] - число типа double, первый коэффициент линейного уравнения
//!@param[in] coefficents[1]  coefficents[1] - число типа double, второй коэффициент линейного уравнения
//!@param[in] coefficents[2]  coefficents[2] - указатель на число типа double, в ячейке, на которую он указывает, будет храниться корень уравнения, если он есть или 0, если корней нет или бесконечно много
//!@param[in] coefficents[3]  coefficents[3] - указатель на число типа enum (N_ROOTS), в ячейке, на которую он указывает, будет храниться количество корней уравнения
//!
//!@return Ошибку, произошедшую в ходе выполнения функции, либо её отсутствие
// ---------------------------------

ERRORS solve_linear_equation(const COEF* const coefs, SOLVE* const solve)
{
    null_err(!solve || !coefs);

    inf_err(!isfinite(coefs->a) || !isfinite(coefs->b));

    if (is_zero(coefs->a))
    {
        solve->x1 = 0;    // это что за дерьмо

        if (is_zero(coefs->b))
        {
            solve->nroots = INF_ROOTS;
        }
        else
        {
            solve->nroots = NO_ROOTS;
        }
    }

    else
    {
        solve->x1 = -coefs->b / coefs->a;
        solve->nroots = ONE_ROOT;
    }

    return NOTHING;
}

// ---------------------------------
//! @brief Решение квадаратного уравнения с заданными коэффициентами
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!@param[in] coefficents[1]  coefficents[1] - указатель на число типа double, в ячейке, на которую он указываат, будет храниться первый корень, если он есть, 0, если корней нет и NAN, если в ходе работы функции произошла ошибка
//!@param[in] coefficents[2]  coefficents[2] - указатель на число типа double, в ячейке, на которую он указывает, будет храниться второй корень, если он есть или 0, если корней нет или бесконечно много
//!@param[in] coefficents[3]  coefficents[3] - указатель на число типа enum (N_ROOTS), в ячейке, на которую он указывает будет храниться количество корней уравнения
//!
//!@return Ошибку, произошедшую в ходе выполнения функции, либо её отсутствие
// ---------------------------------

ERRORS solve_square_equation(const COEF* const coefs, SOLVE* const solve)
{
    null_err(!coefs || !solve);

    if (is_zero(coefs->c))
    {
        solve->nroots = TWO_ROOTS;
        solve->x2 = 0;

        ERRORS err = solve_linear_equation(coefs, solve);

        if (err != NOTHING)   // дерьмо, прям насрал хуйни
        {
            solve->nroots = ONE_ROOT;
            return err;
        }

        if (solve->nroots == NO_ROOTS)
        {
            solve->nroots = ONE_ROOT;
        }

        else if (solve->nroots == ONE_ROOT)
        {
            solve->nroots = TWO_ROOTS;
        }

        return err;
    }

    double discriminant = coefs->b * coefs->b - 4 * coefs->a * coefs->c;

    if (discriminant < -EPS)
    {
        solve->x1 = solve->x2 = 0;
        solve->nroots = NO_ROOTS;
    }

    else if (is_zero(discriminant))
    {
        solve->x1 = solve->x2 = -coefs->b / (2 * coefs->a);
        solve->nroots = ONE_ROOT;
    }

    else
    {
        solve->x1 = (-coefs->b + sqrt(discriminant)) / (2 * coefs->a);
        solve->x2 = (-coefs->b - sqrt(discriminant)) / (2 * coefs->a);
        solve->nroots = TWO_ROOTS;
    }

    return NOTHING;
}

// ---------------------------------
//! @brief Решение уравнения с заданными коэффициентами
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!@param[in] coefficents[1]  coefficents[1] - указатель на число типа double, в ячейке, на которую он указываат, будет храниться первый корень, если он есть, 0, если корней нет и NAN, если в ходе работы функции произошла ошибка
//!@param[in] coefficents[2]  coefficents[2] - указатель на число типа double, в ячейке, на которую он указывает, будет храниться второй корень, если он есть или 0, если корней нет или бесконечно много
//!@param[in] coefficents[3]  coefficents[3] - указатель на число типа enum (N_ROOTS), в ячейке, на которую он указывает будет храниться количество корней уравнения
//!
//!@return Ошибку, произошедшую в ходе выполнения функции, либо её отсутствие
// ---------------------------------

ERRORS solve_equation(const COEF* const coefs, SOLVE* const solve)
{

    null_err(!coefs || !solve);

    if (is_zero(coefs->a))
    {
        COEF linear_coefs = {};
        linear_coefs.a = coefs->b;
        linear_coefs.b = coefs->c;

        ERRORS err = solve_linear_equation(&linear_coefs, solve);

        solve->x2 = solve->x1;

        return err;
    }

    return solve_square_equation(coefs, solve);
}

// ---------------------------------
//! @brief Досчитывает оставшиеся символы в читаемой строке ввода
//!
//!@return Ничего не возвращает, но сдвигает указатель ввода на начало следующей строки
// ---------------------------------

void clear_buffer()
{
    char ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// ---------------------------------
//! @brief Вывод типа ошибки ввода коэффициентов
//!
//!@param[in] coefficents[0]  coefficents[0] - число типа int, номер первого коэффициента, введенного неправильно
//!
//!@return Ничего не возвращает, но выводит строку, сообщающую об ошибке во вводе
// ---------------------------------

void print_coeff_err(const int ind)
{
    switch (ind)
    {
        case 0:
            print_string("Incorrect first coefficient\0", RED);
            break;
        case 1:
            print_string("Incorrect second coefficient\0", RED);
            break;
        case 2:
            print_string("Incorrect third coefficient\0", RED);
            break;
        default:
            print_string("You've entered too many arguments\0", RED);
    }
}

// ---------------------------------
//! @brief Посимвольное считывание строки и выделение из неё введенных коэффициентов
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!
//!@return Верно, ли что коэффициенты введены верно
// ---------------------------------

ERRORS read(COEF* const coefs, bool &true_read)
{
    null_err(!coefs);

    true_read = false;

    char ch = getchar();
    int ind = 0;

    while (ch != '\n' && ch != EOF)
    {
        if (ch == ' ')
        {
            ch = getchar();
            continue;
        }

        if (ch == '.' || (!isdigit(ch) && ch != '-'))
        {
            print_coeff_err(ind);
            if (ch != '\n' && ch != EOF)
                clear_buffer();
            return NOTHING;
        }

        bool neg = false;

        if (ch == '-')
        {
            neg = true;
            ch = getchar();
        }

        if (ch == '.' || !isdigit(ch))
        {
            print_coeff_err(ind);
            if (ch != '\n' && ch != EOF)
                clear_buffer();
            return NOTHING;
        }

        double num = 0;
        double mn = 0.1;
        bool was_point = false;
        int count_digits = 0;
        int first_digit = 0;

        while (isdigit(ch) || (ch == '.'))    //вынести double
        {
            if (ch == '.')
            {
                if (was_point || count_digits == 0) {
                    print_coeff_err(ind);
                    clear_buffer();
                    return NOTHING;
                }

                was_point = true;
                ch = getchar();
                continue;
            }

            int x = (ch - '0');

            if (was_point)
            {
                num += mn * x;
                mn *= 0.1;
            }
            else
            {
                num = num * 10 + x;
                ++count_digits;
                if (count_digits == 1)
                {
                    first_digit = x;
                }
            }

            ch = getchar();
        }

        if ((ch != ' ' && ch != '\n' && ch != EOF) || (was_point && mn == 0.1) || (ind == 3) || (first_digit == 0 && count_digits > 1))
        {
            print_coeff_err(ind);
            if (ch != '\n' && ch != EOF)
                clear_buffer();
            return NOTHING;
        }

        if (neg)
            num *= -1;

        switch(ind)
        {
            case 0:
                coefs->a = num;
                break;
            case 1:
                coefs->b = num;
                break;
            case 2:
                coefs->c = num;
                break;
        }

        ++ind;
    }

    if (ind != 3)
    {
        print_string("You didn't enter all the arguments\0", RED);
        //clear_buffer();
        return NOTHING;
    }

    true_read = true;

    return NOTHING;

}

// ---------------------------------
//! @brief Ввод строк до тех пор, пока коэффициенты не будут введены верно
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!
//!@return Ничего не возвращает, но по итогу, получает введенные коэффициенты
// ---------------------------------

ERRORS input(COEF* const coefs)
{
    null_err(!coefs);

    bool true_read = false;

    ERRORS err = NOTHING;

    while (!true_read)
    {
        err = read(coefs, true_read);

        if (err != NOTHING)
        {
            return err;
        }

        if (true_read)
        {
            break;
        }

        Sleep(525);
        print_string(", please try again:\n\0", RED);
    }

    return NOTHING;
}

// ---------------------------------
//! @brief Вывод математического вида линейного уравнения
//!
//!@param[in] coefficents[0]  coefficents[0] - число типа double, первый коэффициент линейного уравнения
//!@param[in] coefficents[1]  coefficents[1] - число типа double, второй коэффициент линейного уравнения
//!
//!@return Ничего не возвращает, но по итогу выводит уравнение
// ---------------------------------

ERRORS print_linear_equation(const COEF* const coefs)
{
    nan_err(coefs->a == NAN || coefs->b == NAN);

    inf_err(!isfinite(coefs->a) || !isfinite(coefs->b));

    char str[100] = "";

    if (is_zero(coefs->b) && is_zero(coefs->a))
    {
        sprintf(str, "0 = 0\n\0");
        print_string(str, WHITE);

        return NOTHING;
    }

    if (is_zero(coefs->b))
    {

        sprintf(str, "%lg * x = 0\n\0", coefs->a);
        print_string(str, WHITE);

        return NOTHING;
    }

    if (is_zero(coefs->a))
    {
        sprintf(str, "%lg = 0\n\0", coefs->b);
        print_string(str, WHITE);

        return NOTHING;
    }

    sprintf(str, "%lg * x + %lg = 0\n\0", coefs->a, coefs->b);
    print_string(str, WHITE);

    return NOTHING;
}

// ---------------------------------
//! @brief Вывод математического вида квадартного уравнения
//!
//!@param[in] coefficents[0]  coefficents[0] - число типа double, первый коэффициент линейного уравнения
//!@param[in] coefficents[1]  coefficents[1] - число типа double, второй коэффициент линейного уравнения
//!@param[in] coefficents[2]  coefficents[2] - число типа double, третий коэффициент линейного уравнения
//!
//!@return Ничего не возвращает, но по итогу выводит уравение
// ---------------------------------

ERRORS print_square_equation(const COEF* const coefs)
{
    nan_err(coefs->a == NAN || coefs->b == NAN || coefs->c == NAN);

    inf_err(!isfinite(coefs->a) || !isfinite(coefs->b) || !isfinite(coefs->c));

    char str[100] = "";
    sprintf(str, "%lg * x^2\0", coefs->a);
    print_string(str, WHITE);

    if (!is_zero(coefs->b))
    {
        sprintf(str, " + %lg * x\0", coefs->b);
        print_string(str, WHITE);
    }

    if (!is_zero(coefs->c))
    {
        sprintf(str, " + %lg\0", coefs->c);
        print_string(str, WHITE);
    }

    sprintf(str, " = 0\n\0");
    print_string(str, WHITE);
}

// ---------------------------------
//! @brief Вывод уравнения с заданными коэффициентами (с маленькими рассуждениями)
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!
//!@return Ничего не возвращает, но по итогу выводит необходимое уравнение
// ---------------------------------

ERRORS print_equation(const COEF* const coefs)
{
    Sleep(1500);
    print_string("Hm, hm\n\0", GREEN);
    Sleep(1125);
    print_string("Analyze equation...\n\n\0", GREEN);
    Sleep(2250);

    null_err(!coefs);

    if (is_zero(coefs->a))
    {
        print_string("The equation reduces to a linear one.\n\0", GREEN);
        Sleep(1125);
        print_string("Equation: \0", GREEN);
        Sleep(600);

        COEF linear_coefs = {};
        linear_coefs.a = coefs->b;
        linear_coefs.b = coefs->c;

        ERRORS err = print_linear_equation(&linear_coefs);

        if (err != NOTHING)
        {
            return err;
        }

        Sleep(750);
        print_string("Solving...\n\0", GREEN);
        Sleep(1125);

        return NOTHING;
    }

    if (!is_zero(coefs->a) && !is_zero(coefs->b) && is_zero(coefs->c))
    {
        print_string("Since the third coefficient is zero, we can put X in parentheses.\n\0", GREEN);
        Sleep(1125);
        print_string("Equation: \0", GREEN);
        Sleep(600);

        char str[200] = "";
        sprintf(str, "%lg * x^2 + %lg * x = x * (%lg * x + %lg) = 0\n\0", coefs->a, coefs->b, coefs->a, coefs->b);
        print_string(str, WHITE);

        Sleep(750);
        print_string("Solving...\n\0", GREEN);
        Sleep(1125);

        return NOTHING;
    }

    print_string("The equation is an ordinary quadratic equation.\n\0", GREEN);
    Sleep(1125);
    print_string("Equation: \0", GREEN);
    Sleep(600);

    ERRORS err = print_square_equation(coefs);
    if (err != NOTHING)
    {
        return err;
    }

    Sleep(750);
    print_string("Solving...\n\0", GREEN);
    Sleep(1125);

    return NOTHING;
}

// ---------------------------------
//! @brief Вывод решения уравнения с заданными коэффициентами и полученными корнями
//!
//!@param[in] coefficents[0]  coefficents[0] - число типа double, первый корень уравнения
//!@param[in] coefficents[1]  coefficents[1] - число типа double, второй корень уравнения
//!@param[in] coefficents[0]  coefficents[2] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!@param[in] coefficents[3]  coefficents[3] - указатель на число типа enum (N_ROOTS), в ячейке, на которую он указывает, будет храниться количество корней уравнения
//!
//!@return Ничего не возвращает, но в итоге выводит решение уравнения
// ---------------------------------

ERRORS output(const COEF* const coefs, const SOLVE* const solve)
{
    null_err(!coefs || !solve);

    nan_err(solve->x1 == NAN || solve->x2 == NAN);

    inf_err(!isfinite(solve->x1) || !isfinite(solve->x2));

    ERRORS err = print_equation(coefs);

    if (err != NOTHING)
    {
        return err;
    }

    char str[100] = "";

    switch (solve->nroots)
    {
        case INF_ROOTS:
            print_string("Infinity roots\n\0", GREEN);
            break;
        case NO_ROOTS:
            print_string("No roots\n\0", GREEN);
            break;
        case ONE_ROOT:
            print_string("One root: \0", GREEN);
            Sleep(375);
            sprintf(str, "%lg\n\0", solve->x1);
            print_string(str, WHITE);
            break;
        case TWO_ROOTS:
            print_string("Two roots: \0", GREEN);
            Sleep(375);
            sprintf(str, "%lg %lg\n\0", solve->x1, solve->x2);
            print_string(str, WHITE);
            break;
        default:
            print_string("Counts of roots went equal wrong\n\0", RED);
    }

    Sleep(750);

    return NOTHING;
}

