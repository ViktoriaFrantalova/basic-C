#include <stdio.h>
// // program kt si vyziada od uzivatela cele kladne cislo a urci ci sa jedna o prvocislo
int main()
{
    int n = 0, i = 0, modulo = 0, prvocislo = 1;

    printf("Zadaj prvocislo: \n");
    scanf("%i", &n);
    i = 2;

    while (i < n)
    {
        modulo = n % i;

        if (modulo == 0)
        {
            prvocislo = 0;
            break;
        }
        else
        {
            prvocislo = 1;
        }

        i = i + 1;
    }
    if (prvocislo == 0)
    {
        printf("%i nie je prvocislo. \n", n);
    }
    else
    {
        printf("%i je prvocislo. \n", n);
    }

    printf("\n");
    return 0;
}