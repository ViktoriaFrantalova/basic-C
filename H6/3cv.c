#include <stdio.h>
#define MAXPOLE 1000

// program, kt. načíta PDB sub., potom zapíšedata do noveho suboru tak aby formát bol cca rovnaky ako pri načítaní sub.

typedef struct
{
    char nazovzaznamu[7];
    int cisloatomu;
    char menoatomu[5];
    char menoresidua[4];
    int cisloresidua;
    float x, y, z;
    char symbolprvku[3];
} ATOM;

ATOM atoms[MAXPOLE]; //pole struktur

int pocet; //pocet riadkov suboru

int nacitanie(char vstupy_cesta[]) // otvorenie vstupneho suboru
{
    FILE *f = NULL;
    f = fopen(vstupy_cesta, "r"); // nacitanie suboru

    if (f == NULL) // kontrola suboru
    {
        printf("Neda sa otvorit subor!\n");
        return 1;
    }

    while (feof(f) == 0)
    {
        if (pocet >= MAXPOLE)
        { // kontrola velikosti pola
            printf("Mala velkost pola!\n");
            break;
        }

        fscanf(f, "%6s %i %4s %3s %i %f %f %f %2s", atoms[pocet].nazovzaznamu, &atoms[pocet].cisloatomu, atoms[pocet].menoatomu, atoms[pocet].menoresidua, &atoms[pocet].cisloresidua, &atoms[pocet].x, &atoms[pocet].y, &atoms[pocet].z, atoms[pocet].symbolprvku);
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

    for (i = 0; i < pocet; i++)
    {
        fprintf(fout, "%-6s %3i %-4s %3s % 5i %10.3f %7.3f %8.3f %10s\n", atoms[i].nazovzaznamu, atoms[i].cisloatomu, atoms[i].menoatomu, atoms[i].menoresidua, atoms[i].cisloresidua, atoms[i].x, atoms[i].y, atoms[i].z, atoms[i].symbolprvku);
    }
    fclose(fout);
    return 0;
}

int main()
{
    char cesta_naciatania[] = "./crambin_simple.pdb";
    if (nacitanie(cesta_naciatania) != 0)
    {
        return 1;
    }

    char cesta_zapisu[] = "crambin.dat";
    if (zapis(cesta_zapisu) != 0)
    {
        return 1;
    }
    return 0;
}
