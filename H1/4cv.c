#include <stdio.h>
// program ohladom v7beru mat. operacii zo zoznamu pomocou znakou
int main()
{
    float a = 0.0, b = 0.0;
    float c = 0.0;
    char n;

    printf("Vyber si mat. operaciu.\n");
    printf("* asobenie.\n"
           "/ delenie. \n"
           "+ scitavanie. \n"
           "- odcitanie. \n");

    printf("Vyber operaciu a stlac enter: \n");
    scanf("%c", &n);

    if ((n != '*') && (n != '/') && (n != '+') && (n != '-'))
    {
        printf("Nevybral si spravnu operaciu, program sa ukoncil.\n");
        return 0;
    }

    printf("Zadaj dve cisla\n");
    scanf("%f %f", &a, &b);

    if (n == '*')
    {
        c = a * b;
        printf("Vysledok nasobenia je: %f \n", c);
    }

    if (n == '/')
    {
        if (b == 0)
        {
            printf("Nulou sa neda delit.\n");
            return 0;
        }

        c = a / b;
        printf("Vysledok delenia je: %f \n", c);
    }

    if (n == '+')
    {
        c = a + b;
        printf("Vysledok scitania je: %f \n", c);
    }

    if (n == '-')
    {
        c = a - b;
        printf("Vysledok odcitania je: %f \n", c);
    }

    return 0;
}
