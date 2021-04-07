#include <stdio.h>
// program ohladom v7beru mat. operacii zo zoznamu pomocou cisel
int main()
{
    float a = 0.0, b = 0.0;
    float c = 0.0;
    int n;

    printf("Vyber si mat. operaciu.\n");
    printf("1-nasobenie.\n"
           "2-delenie. \n"
           "3-scitavanie. \n"
           "4-odcitanie. \n");

    printf("Vyber operaciu a stlac enter: \n");
    scanf("%i", &n);

    if ((n < 1) || (n > 4))
    {
        printf("Nevybral si spravnu operaciu, program sa ukoncil.\n");
        return 0;
    }

    printf("Zadaj dve cisla\n");
    scanf("%f %f", &a, &b);

    if (n == 1)
    {
        c = a * b;
        printf("Vysledok nasobenia je: %f \n", c);
    }
    if (n == 2)
    {
        if (b == 0)
        {
            printf("Nulou sa neda delit.\n");
            return 0;
        }

        c = a / b;
        printf("Vysledok delenia je: %f \n", c);
    }
    if (n == 3)
    {
        c = a + b;
        printf("Vysledok scitania je: %f \n", c);
    }
    if (n == 4)
    {
        c = a - b;
        printf("Vysledok odcitania je: %f \n", c);
    }
    return 0;
}
