#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>
#include <Windows.h>

#define RESET \033[0m
#define RED   \033[31m
#define GREEN \033[32m

enum N_ROOTS {
    INF_ROOTS     = -1,
    NO_ROOTS      =  0,
    ONE_ROOT      =  1,
    TWO_ROOTS     =  2
};

enum ERRORS {
    NULLPTR        = 0,
    NAN_ERR        = 1,
    NOTHING        = 2,
    INFINITY_DIGIT = 3
};

const double EPS = 1e-6;

bool is_zero(double a);

ERRORS solve_linear_equation(double b, double c,
                             double* x, N_ROOTS* nroots);

ERRORS solve_square_equation(double *buf,
                             double* x1, double* x2, N_ROOTS* nroots);

ERRORS solve_equation(double *buf,
                      double* x1, double* x2, N_ROOTS* nroots);

void clear_buffer();

bool read(double* buf);

void input(double* buf); //add coef

void print_linear_equation(double b, double c);

void print_square_equation(double a, double b, double c);

void print_equation(double* buf);

void output(double &x1, double &x2, double* buf, N_ROOTS* nroots);

void print_string(char* str, int color);

void unit_tests();

double calc_func(double* buf, double x);

int main() {
    unit_tests();

    print_string("What's up my boychik, this program solve square equation\n\n$", 0);

    while (true)
    {
        print_string("Enter the coefficients a, b, c:\n$", 0);

        double buf[3] = {};
        input(buf);

        double x1 = NAN, x2 = NAN;
        N_ROOTS nroots = NO_ROOTS;
        ERRORS err = solve_equation(buf, &x1, &x2, &nroots);

        if (err != NOTHING)
            return 0;

        output(x1, x2, buf, &nroots);
        printf("\n");
    }
    return 0;
}

double calc_func(double* buf, double x)
{
    enum coef
    {
        a = 0,
        b = 1,
        c = 2
    };
    return buf[a] * x * x + buf[b] * x + buf[c];
}

void unit_tests()
{
    N_ROOTS nroots = NO_ROOTS;
    double buf[20][3] = {
    {1, -5, 6},
    {1, 5, 6},
    {1, 2, 1},
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
    };

    double x1 = NAN, x2 = NAN;
    int i = 0;

    while (i < 20)
    {
        x1 = NAN, x2 = NAN;
        solve_equation(buf[i], &x1, &x2, &nroots);

        if (buf[i][1] * buf[i][1] < 4 * buf[i][0] * buf[i][2])
        {
            if (nroots != NO_ROOTS)
            {
                print_string("Oy-oy\n$", 1);
                char str[200];
                sprintf(str, "UNIT TEST FAILED: %lg %lg %lg, wrong answer: %lg %lg\n$", buf[i][0], buf[i][1], buf[i][2], x1, x2);
                print_string(str, 1);
                assert(0);
            }
        }
        else if (!is_zero(calc_func(buf[i], x1)) || !is_zero(calc_func(buf[i], x2)))
        {
            print_string("Oy-oy\n$", 1);
            char str[200];
            sprintf(str, "UNIT TEST FAILED: %lg %lg %lg, wrong answer: %lg %lg\n$", buf[i][0], buf[i][1], buf[i][2], x1, x2);
            print_string(str, 1);
            assert(0);
        }

        ++i;
    }

    print_string("All the UNIT TESTS is OK.\n$", 2);
    Sleep(1000);
    print_string("Let's fucking go!\n\n$", 2);
    Sleep(1000);
}

bool is_zero(double a)
{
    if (!isfinite(a))
    {
        print_string("The number did not become finite\n$", 1);
        assert(0); //my assert
    }

    return fabs(a) < EPS;
}

ERRORS solve_linear_equation(double b, double c,
                             double* x, N_ROOTS* nroots)
{
    if (!x || !nroots)
    {
        print_string("Pointer went equal NULL\n$", 1);
        return NULLPTR;
    }

    if (!isfinite(b) || !isfinite(c))
    {
        print_string("The number did not become finite\n$", 1);
        return INFINITY_DIGIT;
    }

    if (is_zero(b))
    {
        *x = 0;

        if (is_zero(c))
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
        *x = -c / b;
        *nroots = ONE_ROOT;
    }

    return NOTHING;
}

ERRORS solve_square_equation(double* buf,
                             double* x1, double* x2, N_ROOTS* nroots)
{
    enum coef
    {
        a = 0,
        b = 1,
        c = 2
    };
    if (!x1 || !x2 || !buf || !nroots)
    {
        print_string("Link went equal NULL\n$", 1);
        return NULLPTR;
    }

    if (!is_zero(buf[a]) && !is_zero(buf[b]) && is_zero(buf[c]))
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

    if (discriminant < -EPS)
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


ERRORS solve_equation(double *buf,
                      double* x1, double* x2, N_ROOTS* nroots)
{
    enum coef
    {
        a = 0,
        b = 1,
        c = 2
    };

    if (!buf || !x1 || !x2 || !nroots)
    {
        print_string("Link went equal NULL\n$", 1);
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

void clear_buffer()
{
    char ch = 0;
    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }
}

bool read(double* buf)
{
    if (!buf)
    {
        print_string("Link went equal NULL\n$", 1);
        exit(1);
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
                    if (ind == 0)
                        print_string("Incorrect first coefficient$", 1);
                    else if (ind == 1)
                        print_string("Incorrect second coefficient$", 1);
                    else if (ind == 2)
                        print_string("Incorrect third coefficient$", 1);
                    else
                        print_string("You've entered too many arguments$", 1);
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

        if ((was_point && mn == 0.1) || (ind == 3) || (first_digit == 0 && count_digits > 1))
        {
            if (ind == 0)
                print_string("Incorrect first coefficient$", 1);
            else if (ind == 1)
                print_string("Incorrect second coefficient$", 1);
            else if (ind == 2)
                print_string("Incorrect third coefficient$", 1);
            else
                print_string("You've entered too many arguments$", 1);
            clear_buffer();
            return false;
        }

        if (neg)
            num *= -1;

        buf[ind++] = num;
    }

    if (ind != 3)
    {
        print_string("You didn't enter all the arguments$", 1);
        clear_buffer();
        return false;
    }
    return true;

}

void input(double* buf)
{
    if (!buf)
    {
        print_string("Link went equal NULL\n$", 1);
        exit(1);
    }

    while (!read(buf))
    {
        Sleep(700);
        print_string(", please try again:\n$", 1);
    }

}

void print_linear_equation(double b, double c)
{
    if (!isfinite(b) || !isfinite(c))
    {
        print_string("The number did not become finite\n$", 1);
        exit(1);
    }

    char str[100];

    if (is_zero(c) && is_zero(b))
    {
        sprintf(str, "0 = 0\n$");
        print_string(str, 0);
        return;
    }

    if (is_zero(c))
    {

        sprintf(str, "%lg * x = 0\n$", b);
        print_string(str, 0);
        return;
    }

    if (is_zero(b))
    {
        sprintf(str, "%lg = 0\n$", c);
        print_string(str, 0);
        return;
    }

    sprintf(str, "%lg * x + %lg = 0\n$", b, c);
    print_string(str, 0);
}

void print_square_equation(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c))
    {
        print_string("The number did not become finite\n$", 1);
        exit(1);
    }

    char str[100];
    sprintf(str, "%lg * x^2$", a);
    print_string(str, 0);
    if (!is_zero(b))
    {
        sprintf(str, " + %lg * x$", b);
        print_string(str, 0);
    }
    if (!is_zero(c))
    {
        sprintf(str, " + %lg$", c);
        print_string(str, 0);
    }
    sprintf(str, " = 0\n$");
    print_string(str, 0);
}

void print_string(char* str, int color)
{
    int i = 0;
    while (str[i] != '$')
    {
        if (color == 0)
            printf("%c", str[i++]);
        else if (color == 1)
            printf("\033[31m%c\033[0m", str[i++]);
        else
            printf("\033[32m%c\033[0m", str[i++]);
        Sleep(100);
    }
}

void print_equation(double* buf)
{
    Sleep(2000);
    print_string("Hm, hm\n$", 2);
    Sleep(1500);
    print_string("Analyze equation...\n$", 2);
    printf("\n");
    Sleep(3000);

    if (!buf)
    {
        print_string("Link went equal NULL\n$", 1);
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

        print_string("The equation reduces to a linear one.\n$", 2);
        Sleep(1500);
        print_string("Equation: $", 2);
        Sleep(800);
        print_linear_equation(buf[b], buf[c]);
        Sleep(1000);
        print_string("Solving...\n$", 2);
        Sleep(1500);
        return;
    }

    if (!is_zero(buf[a]) && !is_zero(buf[b]) && is_zero(buf[c]))
    {
        print_string("Since the third coefficient is zero, we can put X in parentheses.\n$", 2);
        Sleep(1500);
        print_string("Equation: $", 2);
        Sleep(800);

        char str[200];
        sprintf(str, "%lg * x^2 + %lg * x = x * (%lg * x + %lg) = 0\n$", buf[a], buf[b], buf[a], buf[b]);
        print_string(str, 0);

        Sleep(1000);
        print_string("Solving...\n$", 2);
        Sleep(1500);
        return;
    }

    print_string("The equation is an ordinary quadratic equation.\n$", 2);
    Sleep(1500);
    print_string("Equation: $", 2);
    Sleep(800);
    print_square_equation(buf[a], buf[b], buf[c]);
    Sleep(1000);
    print_string("Solving...\n$", 2);
    Sleep(1500);
}

void output(double &x1, double &x2, double* buf, N_ROOTS* nroots)
{
    if (!buf || !nroots)
    {
        print_string("Link went equal NULL\n$", 1);
        exit(1);
    }

    if (x1 == NAN || x2 == NAN)
    {
        print_string("Variable went equal NAN\n$", 1);
        exit(1);
    }

    if (!isfinite(x1) || !isfinite(x2))
    {
        print_string("The number did not become finite\n$", 1);
        exit(1);
    }

    //printf("%lg * x^2 + %lg * x + %lg = 0\n", buf[0], buf[1], buf[2]);
    print_equation(buf);
    char str[100];

    switch (*nroots)
    {
        case INF_ROOTS:
            print_string("Infinity roots\n$", 2);
            break;
        case NO_ROOTS:
            print_string("No roots\n$", 2);
            break;
        case ONE_ROOT:
            print_string("One root: $", 2);
            Sleep(500);
            sprintf(str, "%lg\n$", x1);
            print_string(str, 0);
            break;
        case TWO_ROOTS:
            print_string("Two roots: $", 2);
            Sleep(500);
            sprintf(str, "%lg %lg\n$", x1, x2);
            print_string(str, 0);
            break;
        default:
            print_string("Counts of roots went equal wrong\n$", 1);
    }
    Sleep(1000);
}

