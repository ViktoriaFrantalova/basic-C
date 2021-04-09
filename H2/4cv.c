#include <stdio.h>
// nedokonceny program na vypisovanie prvocislic oddelene ciarkou, vzdy desat prvocisel na kazdom riadku
int main()
{
    int n = 0, i = 0, modulo = 0, prvocislo = 1;
    int rcount = 0; /*pocet prvoc. na aktualnom riadku*/
    int count = 0;  /*pocet doposial vypisanych cisel*/
    int max = 0;    /*pocet zadanych prvocisel*/

    printf("Zadaj pocet prvocislic: \n");
    scanf("%i", &max);
    n = 2 /*testujem ci n je prvocislo*/;

    while (count <= max)
    {
        i = 2;
        while (i < n)
        {
            modulo = n % i; // celočíselne delenie

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
        rcount = count;
        if (rcount == 10)
        {
            printf("\n");
            rcount = 0;
        }

        if (prvocislo != 0)
        {
            printf("%i, ", n);
            rcount = rcount + 1;
        }
        count = count + 1;
        n = n + 1;
    }
    // printf ("\n");
    return 0;
}