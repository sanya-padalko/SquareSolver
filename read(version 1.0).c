ERRORS read_double(char* const ch, double* const num, bool* const go_far, const int* const ind) {
    my_assert(!ch, NULLPTR);
    my_assert(!num, NULLPTR);
    my_assert(!go_far, NULLPTR);

    double mn = 0.1;
    bool was_point = false;
    int count_digits = 0;
    int first_digit = 0;

    while (isdigit(*ch) || (*ch == '.'))
    {
        if (*ch == '.')
        {
            if (was_point || count_digits == 0) {
                print_coeff_err(*ind);
                clear_buffer();
                *go_far = false;
                return NOTHING;
            }

            was_point = true;
            *ch = getchar();
            continue;
        }

        int x = (*ch - '0');

        if (was_point)
        {
            *num += mn * x;
            mn *= 0.1;
        }
        else
        {
            *num = *num * 10 + x;
            ++count_digits;
            if (count_digits == 1)
            {
                first_digit = x;
            }
        }

        *ch = getchar();
    }

    if ((*ch != ' ' && *ch != '\n' && *ch != EOF) || (was_point && mn == 0.1) || (*ind == 3) || (first_digit == 0 && count_digits > 1))
    {
        print_coeff_err(*ind);
        if (*ch != '\n' && *ch != EOF)
            clear_buffer();
        *go_far = false;
    }

    return NOTHING;
}

ERRORS read(COEF* const coefs, bool* const true_read)
{
    my_assert(!coefs, NULLPTR);

    *true_read = false;

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

        bool go_far = true;

        ERRORS err = read_double(&ch, &num, &go_far, &ind);

        if (err != NOTHING || !go_far) {
            return err;
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

    *true_read = true;

    return NOTHING;
}
