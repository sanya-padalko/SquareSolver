#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

const int INF_ROOTS = (int)1e9;
const int NO_ROOTS = 0;
const int ONE_ROOT = 1;
const int TWO_ROOTS = 2;

const double eps = 1e-6;

// add github
// add assert
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
    assert(x1);
    assert(x2);

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

void clear_buffer(char &ch)
{
    ch = getchar();
    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }
}

void input(double* buf)
{
    double a, b, c;
    unpack_massive(buf, a, b, c);
    char ch = 0;
    while (scanf("%lg %lg %lg", &a, &b, &c) != 3)
    {
        printf("Incorrect coefficient values, please try again:\n");
        clear_buffer(ch);
    }
    pack_in_massive(buf, a, b, c);
}

void print_equation(double a, double b, double c)
{

}

void output(int count_roots, double &x1, double &x2)
{
    //printf("Equation: %fx^2 + %fx + %f = 0\n", a, b, c);
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
            printf("Something went wrong\n");
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

        assert(x1 != NAN);
        assert(x2 != NAN);
        output(count_roots, x1, x2);
        printf("\n");
    }
    return 0;
}
