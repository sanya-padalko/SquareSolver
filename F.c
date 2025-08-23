#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>

enum N_ROOTS {
    INF_ROOTS = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};

enum ERRORS {
    NULLPTR = 0,
    NAN_ERR = 1,
    NOTHING = 3,
    INFINITY_DIGIT = 2
};

const double eps = 1e-6;

bool is_zero(double a);

ERRORS solve_linear_equation(double b, double c,
                                double* x, N_ROOTS* nroots);

ERRORS solve_square_equation(double *buf,
                          double* x1, double* x2, N_ROOTS* nroots);

ERRORS solve_equation(double *buf,
                   double* x1, double* x2, N_ROOTS* nroots);

void clear_buffer();

bool read(double* buf);

void input(double* buf);

void print_linear_equation(double b, double c);

void print_square_equation(double a, double b, double c);

void print_equation(double* buf);

void output(double &x1, double &x2, double* buf, N_ROOTS* nroots);

int main() {
    printf("What's up my boychik, this program solve square equation\n\n");
    while (true)
    {
        printf("Enter the coefficients a, b, c:\n");

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

bool is_zero(double a)
{
    if (!isfinite(a))
    {
        printf("The number did not become finite\n");
        exit(0);
    }

    return fabs(a) < eps;
}

ERRORS solve_linear_equation(double b, double c,
                             double* x, N_ROOTS* nroots)
{
    if (!x || !nroots)
    {
        printf("Pointer went equal NULL\n");
        return NULLPTR;
    }

    if (!isfinite(b) || !isfinite(c))
    {
        printf("The number did not become finite\n");
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

ERRORS solve_square_equation(double *buf,
                          double* x1, double* x2, N_ROOTS* nroots)
{
    if (!x1 || !x2 || !buf || !nroots)
    {
        printf("Link went equal NULL\n");
        return NULLPTR;
    }

    if (!is_zero(buf[0]) && !is_zero(buf[1]) && is_zero(buf[2]))
    {
        *nroots = TWO_ROOTS;
        *x1 = 0;
        ERRORS err = solve_linear_equation(buf[0], buf[1], x2, nroots);
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

    double discriminant = buf[1] * buf[1] - 4 * buf[0] * buf[2];

    if (discriminant < -eps)
    {
        *x1 = *x2 = 0;
        *nroots = NO_ROOTS;
    }
    else if (is_zero(discriminant))
    {
        *x1 = *x2 = -buf[1] / (2 * buf[0]);
        *nroots = ONE_ROOT;
    }
    else
    {
    /* discriminant > 0 */
        *x1 = (-buf[1] + sqrt(discriminant)) / (2 * buf[0]);
        *x2 = (-buf[1] - sqrt(discriminant)) / (2 * buf[0]);
        *nroots = TWO_ROOTS;
    }
    return NOTHING;
}


ERRORS solve_equation(double *buf,
                      double* x1, double* x2, N_ROOTS* nroots)
{
    if (!buf || !x1 || !x2 || !nroots)
    {
        printf("Link went equal NULL\n");
        return NULLPTR;
    }

    if (is_zero(buf[0]))
    {
        ERRORS err = solve_linear_equation(buf[1], buf[2], x1, nroots);
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
        printf("Link went equal NULL\n");
        exit(0);
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
            clear_buffer();
            return false;
        }

        if (neg)
            num *= -1;

        buf[ind++] = num;
    }

    if (ind != 3)
    {
        clear_buffer();
        return false;
    }
    return true;

}

void input(double* buf)
{
    if (!buf)
    {
        printf("Link went equal NULL\n");
        exit(0);
    }

    while (!read(buf))
    {
        printf("Incorrect coefficient values, please try again:\n");
    }

}

void print_linear_equation(double b, double c)
{
    if (!isfinite(b) || !isfinite(c))
    {
        printf("The number did not become finite\n");
        exit(0);
    }

    if (is_zero(c) && is_zero(b))
    {
        printf("0 = 0\n");
        return;
    }

    if (is_zero(c))
    {
        printf("%f * x = 0\n", b);
        return;
    }

    if (is_zero(b))
    {
        printf("%f = 0\n", c);
        return;
    }

    printf("%f * x + %f = 0\n", b, c);
}

void print_square_equation(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c))
    {
        printf("The number did not become finite\n");
        exit(0);
    }

    printf("%f * x^2", a);
    if (!is_zero(b))
    {
        printf(" + %f * x", b);
    }
    if (!is_zero(c))
    {
        printf(" + %f", c);
    }
    printf(" = 0\n");
}

void print_equation(double* buf)
{
    if (!buf)
    {
        printf("Link went equal NULL\n");
        exit(0);
    }

    printf("Equation: ");
    if (is_zero(buf[0]))
    {
        print_linear_equation(buf[1], buf[2]);
        return;
    }

    if (!is_zero(buf[0]) && !is_zero(buf[1]) && is_zero(buf[2]))
    {
        printf("%f * x^2 + %f * x = 0\n", buf[0], buf[1]);
        return;
    }

    print_square_equation(buf[0], buf[1], buf[2]);
}

void output(double &x1, double &x2, double* buf, N_ROOTS* nroots)
{
    if (!buf || !nroots)
    {
        printf("Link went equal NULL\n");
        exit(0);
    }

    if (x1 == NAN || x2 == NAN)
    {
        printf("Variable went equal NAN\n");
        exit(0);
    }

    if (!isfinite(x1) || !isfinite(x2))
    {
        printf("The number did not become finite\n");
        exit(0);
    }

    //printf("%f * x^2 + %f * x + %f = 0\n", buf[0], buf[1], buf[2]);
    print_equation(buf);
    switch (*nroots)
    {
        case INF_ROOTS:
            printf("Infinity roots\n");
            break;
        case NO_ROOTS:
            printf("No roots\n");
            break;
        case ONE_ROOT:
            printf("One root: %f\n", x1);
            break;
        case TWO_ROOTS:
            printf("Two roots: %f %f\n", x1, x2);
            break;
        default:
            printf("Counts of roots went equal wrong\n");
    }
}
