#include <stdio.h>
// program, v ktorom si vyberem mat. operaciu a zadam cisla
int main()
{
    float a = 0.0, b = 0.0;
    float c = 0.0;
    int n = 0;

    printf("Zadaj dve cisla\n");
    scanf("%f %f", &a, &b);

    printf("Vyber si mat. operaciu.\n");
    printf("1-nasobenie.\n"
           "2-delenie. \n"
           "3-scitavanie. \n"
           "4-odcitanie. \n");

    printf("Vyber operaciu a stlac enter: \n");
    scanf("%i", &n);

    if ((n < 1) || (n > 4))
    { // ak alebo
        printf("Nevybral si spravnu operaciu, program sa ukoncil.\n");
        return 0;
    }

    switch (n)
    {       // prevedie skup príkazov na základe hodnoty premenných (n) - musí byť cele čislo alebo znak
    case 1: // case N
        c = a * b;
        printf("Vysledok nasobenia je: %f \n", c);
        break; // vyskočenie

    case 2:
        if (b == 0.0)
        {
            printf("Nulou sa neda delit.\n");
            return 0;
        }

        c = a / b;
        printf("Vysledok delenia je: %f \n", c);
        break;

    case 3:
        c = a + b;
        printf("Vysledok scitania je: %f \n", c);
        break;

    case 4:
        c = a - b;
        printf("Vysledok odcitania je: %f \n", c);
        break;
    }
    return 0;
}
