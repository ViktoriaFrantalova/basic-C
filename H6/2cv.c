#include <stdio.h>
#define MAXPOLE 100

// program, kt. načita súbor data1.dat, v ktorom sa nachádza PDB kód komplexu, exp. vaz. energia a spočítaná vaz. energia. Následne zapíše do súboru hodnoty energie v opačnom poradí
// využíva štrukturý

typedef struct // definicia struktury
{
    char pdbkod[10];     // retazcova premenna
    float expvazenergia; // hodnoty experimentalnej vazebnej energie, druhy stlpec
    float vazenergia;    // hodnoty vazebnej energie, treti stlpec
} ENERGY;

ENERGY kod[MAXPOLE]; // definicia pola struktur
int pocet;           // pocet riadkov v subore

int nacitanie(char vstupy_cesta[]) // otvorenie vstupneho suboru
{
    FILE *f = NULL;
    f = fopen(vstupy_cesta, "r"); // nacitanie suboru pre čítanie

    if (f == NULL) // kontrola suboru
    {
        printf("Neda sa otvorit subor!\n");
        return 1;
    }

    while (feof(f) == 0)
    {
        if (pocet >= MAXPOLE) // kontrola velikosti pola
        {
            printf("Mala velkost pola!\n");
            break;
        }

        fscanf(f, "%s %f %f", kod[pocet].pdbkod, &kod[pocet].expvazenergia, &kod[pocet].vazenergia); // reťazcový parameter bez &
        // načitanie hodnot
        pocet++;
    }

    fclose(f);
    return 0;
}

int zapis(char vystupy_cesta[]) // otvorenie vystupneho suboru a zapis hodnot do suboru
{
    int i = 0;
    FILE *fout = NULL;
    fout = fopen(vystupy_cesta, "w"); // otvori subor pre zapis hodnot

    if (fout == NULL)
    { // kontrola
        printf("Neda sa otvorit subor!\n");
        return 1;
    }

    fprintf(fout, "PDBkod: Hodnoty energie:\n"); // vypis stlpcou
    for (i = pocet - 1; i >= 0; i--)
    {                                                                                                //opačne poradie
        fprintf(fout, " %s %8.2f %8.2f \n", kod[i].pdbkod, kod[i].expvazenergia, kod[i].vazenergia); // presnosť dve desatine miesta a desatine čiarky su pod sebou
    }

    fclose(fout);
    return 0;
}

int main()
{
    char cesta_nacitania[] = "./data1.dat";
    if (nacitanie(cesta_nacitania) != 0)
    {
        return 1;
    }

    char cesta_zapisu[] = "data2.dat";
    if (zapis(cesta_zapisu) != 0)
    {
        return 1;
    }

    return 0;
}
