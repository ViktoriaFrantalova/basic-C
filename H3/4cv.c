#include <stdio.h>
#define SIZE 10
// program, kt vyhladava kladne cisla v danom poli
int main()
{
    int i = 0;
    int pocet = 0;
    int a[SIZE] = {3, 4, 7, 6, 12, 13, 14, 15, 36, 17};
    int b[SIZE] = {0};

    for (i = 0; i < SIZE; i++)
    {
        if ((a[i] % 2) == 0) // celočíselne delenie dvojkou
        {
            b[pocet] = a[i]; // priradia sa iba párne čisla
            pocet++;
        }
    }

    printf("Pocet kladnych cisel v poli je: %i \n", pocet);

    printf("Kladne cisla su: ");
    for (i = 0; i < pocet; i++)
    {
        printf("%i, ", b[i]);
    }
    printf("\n");
    return 0;
}
