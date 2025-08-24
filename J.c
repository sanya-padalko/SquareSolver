#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>
#include <Windows.h>

// upgrade read
// везде добавить все проверки, errors
// add struct
// read раздельная компиляция и разибение на файлы
// flag на unit-тесты
// my assert, print_to_stderr

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

const double EPS = 1e-6;

bool is_zero(const double integ);

ERRORS solve_linear_equation(const double b, const double c,
                            double* const x, N_ROOTS* const nroots);

ERRORS solve_square_equation(double const *buf,
                             double* const x1, double* const x2, N_ROOTS* const nroots);

ERRORS solve_equation(double* const buf,
                      double* const x1, double* const x2, N_ROOTS* const nroots);

void clear_buffer();

bool read(double* buf);

void input(double* buf); //add coef

void print_linear_equation(const double b, const double c);

void print_square_equation(const double a, const double b, const double c);

void print_equation(double* const buf);

void output(const double &x1, const double &x2, double* const buf, N_ROOTS* const nroots);

void print_string(char* const str, const int color);

void unit_tests();

bool continue_program();

double calc_func(double* const buf, const double x);

int main() {
    unit_tests();

    print_string("What's up my boychik, this program solve square equation\n\n\0", 0);

    do
    {
        print_string("Enter the coefficients a, b, c:\n\0", 0);

        double buf[3] = {};
        input(buf);

        double x1 = NAN, x2 = NAN;
        N_ROOTS nroots = NO_ROOTS;
        ERRORS err = solve_equation(buf, &x1, &x2, &nroots);

        if (err != NOTHING)
            return 0;

        output(x1, x2, buf, &nroots);
        printf("\n");



    } while (continue_program());
    return 0;
}

bool continue_program()
{
    print_string("Continue? (yes - y/ no - n/ suck my dick - s)\n\0", 3);
    char want = getchar();
    int cnt = 0;

    while (want != 'y' && want != 'n' && want != 's')
    {
        ++cnt;

        if (want != '\n' && want != EOF)
        {
            clear_buffer();
        }

        Sleep(700);
        print_string("Eeeee.... \0", 1);
        Sleep(700);

        if (cnt == 3)
        {
            for (int i = 0; i < 3; ++i)
            {
                print_string("FUCK! \0", 1);
                Sleep(150);
            }

            print_string("What a hell, bro?!?\n\0", 1);
            Sleep(400);
            print_string("You entered the wrong answer 3 times in a row. You're blocked for 30 seconds.\n\0", 1);
            Sleep(300);

            for (int i = 30; i > 15; --i)
            {
                char str[10];
                sprintf(str, "%ds \0", i);
                print_string(str, 1);
                Sleep(700);
            }

            for (int i = 15; i > 0; --i)
            {
                char str[10];
                sprintf(str, "%ds \0", i);
                print_string(str, 4);
                Sleep(700);
            }

            print_string("0s \0", 2);
            Sleep(500);
            print_string("You're free\0", 2);
            Sleep(500);
            print_string(", be careful next time\0", 2);
            Sleep(500);
            print_string(", only 'y' or 'n'\n\0", 2);
            Sleep(200);
        }

        else if (cnt == 6)
        {
            print_string("Oh... \0", 1);
            Sleep(700);
            print_string("I gave you 3 more attempts, but you couldn't enter one of the two characters, so I'll find someone else. GOODBYE, bro, good luck", 4);
            Sleep(2000);
            print_string("\nThe companion left the chat", 2);
            Sleep(500);

            return false;
        }

        else
        {
            print_string("Wrong answer, bro, please print only 'y' or 'n'\n\0", 1);
        }

        want = getchar();
    }

    clear_buffer();
    Sleep(700);

    if (want == 's')
    {
        Sleep(700);
        print_string("GREAT!!!\n\0", 4);
        Sleep(700);
        print_string("If you are a boy, then write to me in tg (\0", 4);
        Sleep(300);
        print_string("@EntryFr4ger\0", 2);
        Sleep(300);
        print_string("), girls - bye\n\0", 4);
        Sleep(1000);
        print_string("I'm Matvey :)\n\0", 2);
        Sleep(1000);

        return false;
    }

    if (want == 'n')
    {
        print_string("Why is it so fast??\0", 4);
        Sleep(1000);
        print_string(" Okey, bro, good luck\n\0", 4);
        Sleep(1000);
        print_string("You will always be with me, \0", 4);
        Sleep(1000);
        print_string("you will always be my brother...\n\0", 2);
        Sleep(1000);
    }

    else
    {
        print_string("Cool, let's go :)\n\0", 4);
    }

    print_string("\n\0", 0);
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

void print_string(char* const str, const int color)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (color == 0)
            printf("%c", str[i++]);
        else if (color == 1)
            printf("\033[31m%c\033[0m", str[i++]); //red
        else if (color == 2)
            printf("\033[32m%c\033[0m", str[i++]); //green
        else if (color == 3)
            printf("\033[36m%c\033[0m", str[i++]); //blue
        else if (color == 4)
            printf("\033[33m%c\033[0m", str[i++]); //yellow
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

double calc_func(double* const buf, const double x)
{
    enum coef
    {
        a = 0,
        b = 1,
        c = 2
    };

    return buf[a] * x * x + buf[b] * x + buf[c];
}

// ---------------------------------
//! @brief Тестирование программы на заранее заданных тестах
//!
//!@return Ничего не возвращает, но выводит пройдены ли все тесты или тест на котором решение сломалось
// ---------------------------------

void unit_tests()
{
    N_ROOTS nroots = NO_ROOTS;
    double buf[21][3] = {
        {1, -5, 6},
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
        {10, 16, 0},      //add infinity roots check
    };

    double x1 = NAN, x2 = NAN;
    int i = 0;
    bool fl = true;

    while (i < 21)
    {
        x1 = NAN, x2 = NAN;
        solve_equation(buf[i], &x1, &x2, &nroots);

        if (buf[i][1] * buf[i][1] < 4 * buf[i][0] * buf[i][2])
        {
            if (nroots != NO_ROOTS)
            {
                print_string("Oy-oy\n\0", 1);
                char str[200];
                sprintf(str, "UNIT TEST FAILED: %lg %lg %lg, wrong answer: %lg %lg\n\0", buf[i][0], buf[i][1], buf[i][2], x1, x2);
                print_string(str, 1);
                fl = false;
            }
        }
        else if (!is_zero(calc_func(buf[i], x1)) || !is_zero(calc_func(buf[i], x2)))
        {
            print_string("Oy-oy\n\0", 1);
            char str[200];
            sprintf(str, "UNIT TEST FAILED: %lg %lg %lg, wrong answer: %lg %lg\n\0", buf[i][0], buf[i][1], buf[i][2], x1, x2);
            print_string(str, 1);
            fl = false;
        }

        ++i;
    }

    if (fl)
    {
        print_string("All the UNIT TESTS is OK.\n\0", 2);
        Sleep(750);
        print_string("Let's fucking go!\n\n\0", 2);
        Sleep(750);
    }
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
        print_string("The number did not become finite\n\0", 1);
        assert(0); //my assert
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

ERRORS solve_linear_equation(const double a, const double b,
                             double* const x, N_ROOTS* const nroots)
{
    if (!x || !nroots)
    {
        print_string("Pointer went equal NULL\n\0", 1);
        return NULLPTR;
    }

    if (!isfinite(a) || !isfinite(b))
    {
        print_string("The number did not become finite\n\0", 1);
        return INFINITY_DIGIT;
    }

    if (is_zero(a))
    {
        *x = 0;

        if (is_zero(b))
        {
            *nroots = INF_ROOTS;
        }
        else
        {
            *nroots = NO_ROOTS;
        }
    }
    else
    {
        *x = -b / a;
        *nroots = ONE_ROOT;
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

ERRORS solve_square_equation(double* const buf,
                             double* const x1, double* const x2, N_ROOTS* const nroots)
{
    enum coef
    {
        a = 0,
        b = 1,
        c = 2
    };
    if (!x1 || !x2 || !buf || !nroots)
    {
        print_string("Link went equal NULL\n\0", 1);
        return NULLPTR;
    }

    if (is_zero(buf[c]))
    {
        *nroots = TWO_ROOTS;
        *x1 = 0;
        ERRORS err = solve_linear_equation(buf[a], buf[b], x2, nroots);

        if (err != NOTHING)
        {
            *nroots = ONE_ROOT;
            return err;
        }
        if (*nroots == NO_ROOTS)
        {
            *nroots = ONE_ROOT;
        }
        else if (*nroots == ONE_ROOT)
        {
            *nroots = TWO_ROOTS;
        }

        return err;
    }

    double discriminant = buf[b] * buf[b] - 4 * buf[a] * buf[c];

    if (discriminant < -EPS)    // maybe switch case less above equal
    {
        *x1 = *x2 = 0;
        *nroots = NO_ROOTS;
    }
    else if (is_zero(discriminant))
    {
        *x1 = *x2 = -buf[b] / (2 * buf[a]);
        *nroots = ONE_ROOT;
    }
    else
    {
    /* discriminant > 0 */
        *x1 = (-buf[b] + sqrt(discriminant)) / (2 * buf[a]);
        *x2 = (-buf[b] - sqrt(discriminant)) / (2 * buf[a]);
        *nroots = TWO_ROOTS;
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

ERRORS solve_equation(double* const buf,
                      double* const x1, double* const x2, N_ROOTS* const nroots)
{
    enum coef
    {
        a = 0,
        b = 1,
        c = 2
    };

    if (!buf || !x1 || !x2 || !nroots)
    {
        print_string("Link went equal NULL\n\0", 1);
        return NULLPTR;
    }

    if (is_zero(buf[a]))
    {
        ERRORS err = solve_linear_equation(buf[b], buf[c], x1, nroots);
        *x2 = *x1;

        return err;
    }

    return solve_square_equation(buf, x1, x2, nroots);
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
    if (ind == 0)
        print_string("Incorrect first coefficient\0", 1);
    else if (ind == 1)
        print_string("Incorrect second coefficient\0", 1);
    else if (ind == 2)
        print_string("Incorrect third coefficient\0", 1);
    else
        print_string("You've entered too many arguments\0", 1);
}

// ---------------------------------
//! @brief Посимвольное считывание строки и выделение из неё введенных коэффициентов
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!
//!@return Верно, ли что коэффициенты введены верно
// ---------------------------------

bool read(double* buf)
{
    if (!buf)
    {
        print_string("Link went equal NULL\n\0", 1);
        assert(0);
    }

    char ch = 0;
    ch = getchar();
    int cnt = 0;
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
            return false;
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
            return false;
        }

        double num = 0;
        double mn = 0.1;
        bool was_point = false;
        int count_digits = 0;
        int first_digit = 0;

        while (isdigit(ch) || (ch == '.'))
        {
            if (ch == '.')
            {
                if (was_point || count_digits == 0) {
                    print_coeff_err(ind);
                    clear_buffer();
                    return false;
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
            return false;
        }

        if (neg)
            num *= -1;

        buf[ind++] = num;
    }

    if (ind != 3)
    {
        print_string("You didn't enter all the arguments\0", 1);
        //clear_buffer();
        return false;
    }

    return true;

}

// ---------------------------------
//! @brief Ввод строк до тех пор, пока коэффициенты не будут введены верно
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!
//!@return Ничего не возвращает, но по итогу, получает введенные коэффициенты
// ---------------------------------

void input(double* buf)
{
    if (!buf)
    {
        print_string("Link went equal NULL\n\0", 1);
        exit(1);
    }

    while (!read(buf))
    {
        Sleep(525);
        print_string(", please try again:\n\0", 1);
    }

}

// ---------------------------------
//! @brief Вывод математического вида линейного уравнения
//!
//!@param[in] coefficents[0]  coefficents[0] - число типа double, первый коэффициент линейного уравнения
//!@param[in] coefficents[1]  coefficents[1] - число типа double, второй коэффициент линейного уравнения
//!
//!@return Ничего не возвращает, но по итогу выводит уравнение
// ---------------------------------

void print_linear_equation(const double a, const double b)
{
    if (!isfinite(a) || !isfinite(b))
    {
        print_string("The number did not become finite\n\0", 1);
        assert(0);
    }

    char str[100];

    if (is_zero(b) && is_zero(a))
    {
        sprintf(str, "0 = 0\n\0");
        print_string(str, 0);
        return;
    }

    if (is_zero(b))
    {

        sprintf(str, "%lg * x = 0\n\0", a);
        print_string(str, 0);
        return;
    }

    if (is_zero(a))
    {
        sprintf(str, "%lg = 0\n\0", b);
        print_string(str, 0);
        return;
    }

    sprintf(str, "%lg * x + %lg = 0\n\0", a, b);
    print_string(str, 0);
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

void print_square_equation(const double a, const double b, const double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c))
    {
        print_string("The number did not become finite\n\0", 1);
        exit(1);
    }

    char str[100];
    sprintf(str, "%lg * x^2\0", a);
    print_string(str, 0);

    if (!is_zero(b))
    {
        sprintf(str, " + %lg * x\0", b);
        print_string(str, 0);
    }

    if (!is_zero(c))
    {
        sprintf(str, " + %lg\0", c);
        print_string(str, 0);
    }

    sprintf(str, " = 0\n\0");
    print_string(str, 0);
}

// ---------------------------------
//! @brief Вывод уравнения с заданными коэффициентами (с маленькими рассуждениями)
//!
//!@param[in] coefficents[0]  coefficents[0] - указатель на массив чисел типа double, соответственно хранящий коэффициенты данного уравнения
//!
//!@return Ничего не возвращает, но по итогу выводит необходимое уравнение
// ---------------------------------

void print_equation(double* const buf)
{
    Sleep(1500);
    print_string("Hm, hm\n\0", 2);
    Sleep(1125);
    print_string("Analyze equation...\n\0", 2);
    printf("\n");
    Sleep(2250);

    if (!buf)
    {
        print_string("Link went equal NULL\n\0", 1);
        exit(1);
    }

    enum coef
    {
        a = 0,
        b = 1,
        c = 2
    };

    if (is_zero(buf[a]))
    {
        print_string("The equation reduces to a linear one.\n\0", 2);
        Sleep(1125);
        print_string("Equation: \0", 2);
        Sleep(600);
        print_linear_equation(buf[b], buf[c]);
        Sleep(750);
        print_string("Solving...\n\0", 2);
        Sleep(1125);
        return;
    }

    if (!is_zero(buf[a]) && !is_zero(buf[b]) && is_zero(buf[c]))
    {
        print_string("Since the third coefficient is zero, we can put X in parentheses.\n\0", 2);
        Sleep(1125);
        print_string("Equation: \0", 2);
        Sleep(600);

        char str[200];
        sprintf(str, "%lg * x^2 + %lg * x = x * (%lg * x + %lg) = 0\n\0", buf[a], buf[b], buf[a], buf[b]);
        print_string(str, 0);

        Sleep(750);
        print_string("Solving...\n\0", 2);
        Sleep(1125);
        return;
    }

    print_string("The equation is an ordinary quadratic equation.\n\0", 2);
    Sleep(1125);
    print_string("Equation: \0", 2);
    Sleep(600);
    print_square_equation(buf[a], buf[b], buf[c]);
    Sleep(750);
    print_string("Solving...\n\0", 2);
    Sleep(1125);
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

void output(const double &x1, const double &x2, double* const buf, N_ROOTS* const nroots)
{
    if (!buf || !nroots)
    {
        print_string("Link went equal NULL\n\0", 1);
        assert(0);
    }

    if (x1 == NAN || x2 == NAN)
    {
        print_string("Variable went equal NAN\n\0", 1);
        assert(0);
    }

    if (!isfinite(x1) || !isfinite(x2))
    {
        print_string("The number did not become finite\n\0", 1);
        exit(1);
    }

    print_equation(buf);
    char str[100] = "";  // init

    switch (*nroots)
    {
        case INF_ROOTS:
            print_string("Infinity roots\n\0", 2);
            break;
        case NO_ROOTS:
            print_string("No roots\n\0", 2);
            break;
        case ONE_ROOT:
            print_string("One root: \0", 2);
            Sleep(375);
            sprintf(str, "%lg\n\0", x1);
            print_string(str, 0);
            break;
        case TWO_ROOTS:
            print_string("Two roots: \0", 2);
            Sleep(375);
            sprintf(str, "%lg %lg\n\0", x1, x2);
            print_string(str, 0);
            break;
        default:
            print_string("Counts of roots went equal wrong\n\0", 1);
    }

    Sleep(750);
}

