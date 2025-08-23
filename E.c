#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

const int INF_ROOTS = (int)1e9;
const int NO_ROOTS = 0;
const int ONE_ROOT = 1;
const int TWO_ROOTS = 2;
const int PROBLEM = 3;

const double eps = 1e-6;

// list read about calloc dynamic memory

bool equal(double a)
{
    return fabs(a) < eps;
}

int solve_linear_equation(double b, double c,
                          double* x)
{
    assert(x);

    if (equal(b))
    {
        *x = 0;
        if (equal(c))
        {
            return INF_ROOTS;
        }
        return NO_ROOTS;
    }
    *x = -c / b;
    return ONE_ROOT;
}

void unpack_massive(double* mas, double &a, double &b, double &c)
{
    a = mas[0];
    b = mas[1];
    c = mas[2];
}

void pack_in_massive(double* mas, double &a, double &b, double&c)
{
    mas[0] = a;
    mas[1] = b;
    mas[2] = c;
}

int solve_square_equation(double *buf,
                          double* x1, double* x2)
{
    if (!x1 || !x2)
    {
        return PROBLEM;
    }

    double a, b, c;
    unpack_massive(buf, a, b, c);

    double discriminant = b * b - 4 * a * c;

    if (discriminant < -eps)
    {
        *x1 = *x2 = 0;
        return NO_ROOTS;
    }
    else if (equal(discriminant))
    {
        *x1 = *x2 = -b / (2 * a);
        return ONE_ROOT;
    }
    /* discriminant > 0 */
    *x1 = (-b + sqrt(discriminant)) / (2 * a);
    *x2 = (-b - sqrt(discriminant)) / (2 * a);
    return TWO_ROOTS;
}

int solve_equation(double *buf,
                   double* x1, double* x2)
{
    double a, b, c;
    unpack_massive(buf, a, b, c);

    if (equal(a))
    {
        int count_roots = solve_linear_equation(b, c, x1);
        *x2 = *x1;
        return count_roots;
    }
    if (!equal(a) && !equal(b) && equal(c))
    {
        *x1 = 0;
        return solve_linear_equation(a, b, x2) + 1;
    }
    return solve_square_equation(buf, x1, x2);
}

void clear_buffer(char &ch)      // посимвольный ввод
{
    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }
}

bool is_digit(char c)
{
    for (int i = 0; i < 10; ++i)
    {
        if (char('0' + i) == c)
            return true;
    }
    return false;
}

bool read(double* buf)
{

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

        if (ch == '.' || !is_digit(ch))
        {
            clear_buffer(ch);
            return false;
        }

        double num = 0;
        double mn = 0.1;
        bool was_point = false;
        int count_digits = 0;
        int first_digit = 0;

        while (is_digit(ch) || (ch == '.'))
        {
            if (ch == '.')
            {
                if (was_point || count_digits == 0) {
                    clear_buffer(ch);
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
            clear_buffer(ch);
            return false;
        }
        buf[ind++] = num;
    }

    return true;
}

void input(double* buf)
{

    char ch = 0;
    while (!read(buf))
    {
        printf("Incorrect coefficient values, please try again:\n");
    }

}

void print_linear_equation(double b, double c)
{
    if (equal(c) && equal(b))
    {
        printf("0 = 0\n");
        return;
    }
    if (equal(c))
    {
        printf("%fx = 0\n", b);
        return;
    }
    if (equal(b))
    {
        printf("%f = 0\n", c);
        return;
    }
    printf("%fx + %f = 0\n", b, c);
}

void print_square_equation(double a, double b, double c)
{
    printf("%fx^2", a);
    if (!equal(b))
    {
        printf(" + %fx", b);
    }
    if (!equal(c))
    {
        printf(" + %f", c);
    }
    printf(" = 0\n");
}

void print_equation(double* buf)
{
    double a, b, c;
    unpack_massive(buf, a, b, c);

    printf("Equation: ");
    if (equal(a))
    {
        print_linear_equation(b, c);
        return;
    }
    if (!equal(a) && !equal(b) && equal(c))
    {
        printf("%fx^2 + %fx = 0\n", a, b);
        return;
    }
    print_square_equation(a, b, c);
}

void print_problem()
{
    printf("Something went wrong\n");
}

void output(int count_roots, double &x1, double &x2, double* buf)
{
    print_equation(buf);
    switch (count_roots)
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
            print_problem();
    }
}

int main() {
    printf("What's up my boychik, this program solve square equation\n\n");
    while (true)
    {
        printf("Enter the coefficients a, b, c:\n");

        double a = NAN, b = NAN, c = NAN;

        double* buf = (double*)calloc(3, sizeof(double));
        input(buf);

        double x1 = NAN, x2 = NAN;
        int count_roots = solve_equation(buf, &x1, &x2);

        if (x1 == NAN || x2 == NAN)
        {
            print_problem();
            continue;
        }

        output(count_roots, x1, x2, buf);
        printf("\n");
    }
    return 0;
}
