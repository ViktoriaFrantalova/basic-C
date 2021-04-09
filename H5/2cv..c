#include <stdio.h>
#define MAXPOLE 100

// program, kt. načita súbor data1.dat, v ktorom sa nachádza PDB kód komplexu, exp. vaz. energia a spočítaná vaz. energia. Následne zapíše do súboru hodnoty energie v opačnom poradí

int main()
{
    int i;
    int pocet = 0;                        // pocet nacitanych hodnot
    float experimvazene[MAXPOLE] = {0.0}; // hodnoty experimentalnej vazebnej energie, druhy stlpec
    float vazenergie[MAXPOLE] = {0.0};    // hodnoty vazebnej energie, treti stlpec
    FILE *f = NULL;
    FILE *fout = NULL; // nová funkcie

    f = fopen("./data1.dat", "r"); // nacitanie suboru

    if (f == NULL)
    { // kontrola
        printf("Neda sa otvorit subor!\n");
        return 1;
    }

    while (feof(f) == 0)
    {
        if (pocet >= MAXPOLE)
        {
            printf("Mala velkost pola!\n");
            break;
        }

        fscanf(f, "%*s %f %f", &experimvazene[pocet], &vazenergie[pocet]); // príznak * spôsobí, že sa daná hodnota načíta ale neuloží sa do žiadnej premennej
        pocet++;
    }
    fclose(f);
    f = NULL;

    fout = fopen("./data1.dat", "w");

    if (fout == NULL)
    { // kontrola
        printf("Neda sa otvorit subor!\n");
        return 1;
    }

    printf("Hodnoty Energie:\n"); // vypis stlpcou
    for (i = pocet - 1; i >= 0; i--)
    {                                                                      // opačne poradie
        fprintf(fout, " %8.2f %8.2f \n", experimvazene[i], vazenergie[i]); // presnosť dve desatine miesta a desatine čiarky su pod sebou
    }

    fclose(fout);
    fout = NULL;

    return 0;
}
