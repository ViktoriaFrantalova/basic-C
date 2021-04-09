#include <stdio.h>
#define MAXPOLE 50

// program, kt. načíta súbor obsahujúci n počet celých čísel oddelených čiarkami, vypíše počet týchto čísel a hodnoty sa vypíšu v opačnom poradí

int main()
{
    int i = 0;
    int pocet = 0; // pocet nacitanych hodnot
    int hodnoty[MAXPOLE] = {0};
    FILE *f = NULL;
    f = fopen("./cisla.dat", "r"); // nacitanie suboru

    if (f == NULL)
    { // kontrola
        printf("Neda sa otvorit subor!\n");
        return 1;
    }

    while (feof(f) == 0)
    {
        if (pocet >= MAXPOLE) // kontrola
        {
            printf("Mala velkost pola!\n");
            break;
        }

        fscanf(f, "%i , ", &hodnoty[pocet]); // ošetrenie množstva medzier a čiarok a načitanie hodnot
        pocet++;
    }

    fclose(f);
    f = NULL;

    printf("Pocet hodnot je: %i \n", pocet);
    printf("Hodnoty su: ");

    for (i = pocet - 1; i >= 0; i--)
    { // výpis v opačnom poradí
        printf("%i, ", hodnoty[i]);
    }
    return 0;
}
