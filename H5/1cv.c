#include <stdio.h>
#define MAXPOLE 100

// program, kt. načita súbor data1.dat, v ktorom sa nachádza PDB kód komplexu, exp. vaz. energia a spočítaná vaz. energia. Následne vypíše hodnoty energie v opačnom poradí

int main()
{
    int i;
    int pocet = 0;                        // pocet nacitanych hodnot
    float experimvazene[MAXPOLE] = {0.0}; // hodnoty experimentalnej vazebnej energie, druhy stlpec
    float vazenergie[MAXPOLE] = {0.0};    // hodnoty vazebnej energie, treti stlpec
    FILE *f = NULL;

    f = fopen("./data1.dat", "r"); // R = režim iba pre čítanie
    if (f == NULL)
    { // kontrola
        printf("Neda sa otvorit subor!\n");
        return 1;
    }

    while (feof(f) == 0) // feof(identifikátor souboru), funkcia, kt použíjem ak nepoznám počet hodnot vo vstupnom súbore
    // prechádza súbor do kým nenarázi na koniec súboru a vracia honotu RôZNU OD 0
    {
        if (pocet >= MAXPOLE)
        {
            printf("Mala velkost pola!\n");
            break;
        }

        fscanf(f, "%*s %f %f", &experimvazene[pocet], &vazenergie[pocet]); // načítanie dát, dávame znak & OKREM REŤAZOVýCH PREMENNÝCH
        // príznak * spôsobí, že sa daná hodnota načíta ale neuloží sa do žiadnej premennej
        pocet++;
    }
    fclose(f);
    f = NULL;

    printf("Hodnoty: Energie:\n");

    for (i = pocet - 1; i >= 0; i--)
    {
        printf(" % .2f % .2f \n", experimvazene[i], vazenergie[i]);
    }
    return 0;
}
