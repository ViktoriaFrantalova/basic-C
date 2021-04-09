#include <stdio.h>
#include <math.h>
#define MAXPOLE 1000
// vypíše informácie o subore na obrazovku + zoznam residua
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
int pocet_atom;      //pocet_atom riadkov suboru

int nacitanie(char vstupy_cesta[])
{ // otvorenie vstupneho suboru
    FILE *f = NULL;
    f = fopen(vstupy_cesta, "r"); // nacitanie suboru

    if (f == NULL)
    { // kontrola suboru
        printf("Neda sa otvorit subor!\n");
        return 1;
    }

    while (feof(f) == 0)
    {
        if (pocet_atom >= MAXPOLE)
        { // kontrola velikosti pola
            printf("Mala velkost pola!\n");
            break;
        }

        fscanf(f, "%6s %i %4s %3s %i %f %f %f %2s", atoms[pocet_atom].nazovzaznamu, &atoms[pocet_atom].cisloatomu, atoms[pocet_atom].menoatomu, atoms[pocet_atom].menoresidua, &atoms[pocet_atom].cisloresidua, &atoms[pocet_atom].x, &atoms[pocet_atom].y, &atoms[pocet_atom].z, atoms[pocet_atom].symbolprvku);
        pocet_atom++;
    }
    fclose(f);
    return 0;
}

int zapis(char vystupy_cesta[])
{ // otvorenie vystupneho suboru a zapis hodnot do suboru
    FILE *fout = NULL;
    int i = 0;
    fout = fopen(vystupy_cesta, "w"); // otvori subor pre zapis hodnot

    if (fout == NULL)
    { // kontrola
        printf("Neda sa otvorit subor!\n");
        return 1;
    }
    for (i = 0; i < pocet_atom; i++)
    {
        fprintf(fout, "%-6.6s %5d %-4.4s %3s %4d %8.3f %8.3f %8.3f %2.2s\n", atoms[i].nazovzaznamu, atoms[i].cisloatomu, atoms[i].menoatomu, atoms[i].menoresidua, atoms[i].cisloresidua, atoms[i].x, atoms[i].y, atoms[i].z, atoms[i].symbolprvku);
    }
    fclose(fout);
    return 0;
}

int residue()
{ //vypise info o residui
    int n = 0;
    for (n = 0; n < pocet_atom; n++) // pre každy atom
    {
        if (n == 0 || atoms[n].cisloresidua != atoms[n - 1].cisloresidua) // ak čísloresidua sa nezhoduje s predošlím cislom residua tak výpis
        {
            printf("%3s % 5i %-4s %3i\n", atoms[n].menoresidua, atoms[n].cisloresidua, atoms[n].menoatomu, atoms[n].cisloatomu);
        }
    }
}

int main()
{
    char cesta_naciatania[] = "./crambin_simple.pdb"; // cesta k suboru - nacitanie
    if (nacitanie(cesta_naciatania) != 0)
    {
        return 1;
    }

    char cesta_zapisu[] = "crambin.dat"; // nazov vzniknuteho suboru
    if (zapis(cesta_zapisu) != 0)
    {
        return 1;
    }
    residue();
    return 0;
}
