#include <stdio.h>
// program vypise prvych n prvocisel, n bude zadane uzivatelom
int main()
{
    int n = 0, i = 0, modulo = 0, prvocislo = 1,
        count = 0 /*pocet doposial vypisanych cisel*/,
        max = 0 /*pocet zadanych prvocisel*/, sn = 0;

    printf("Zadaj pocet prvocislic: \n");
    scanf("%i", &max);
    n = 2 /*testujem ci n je prvocislo*/;
    while (count < max)
    {
        i = 2;
        while (i < n)
        {
            modulo = n % i; // zvyšok po delení

            if (modulo == 0)
            {
                prvocislo = 0;
                break;
            }
            else
            {
                prvocislo = 1;
            }
            i = i + 1; // i++
        }

        if (prvocislo != 0)
        {
            printf("%i, ", n);
        }

        count = count + 1; // count++
        n = n + 1;         // n++
    }
    printf("\n"); // odriadkovanie
    return 0;
}