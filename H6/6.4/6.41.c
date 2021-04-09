#include <stdio.h>
#include <math.h>
#define MAX 1000
//vypise informacie o crambinu do suboru
typedef struct //definicia struktury
{
  char record_name[7];
  int atom_number;
  char atom_name[5];
  char residue_name[4];
  int residue_number;
  float x;
  float y;
  float z;
  char element_name[3];
} ATOM;

ATOM items[MAX]; //definicia pole struktur
int count;       //pocet riadkov suboru

int cteni(char subor_cteni[]) //otvorenie vstupniho suboru
{
  FILE *f = NULL;

  f = fopen(subor_cteni, "r"); //otevre subor na citanie
  if (f == NULL)               //kontrola suboru
  {
    printf("Neda sa otvorit!\n");
    return 1;
  }

  while (feof(f) == 0)
  {
    if (count >= MAX) //kontrola velikosti pola
    {
      printf("Male pole!\n");
      break;
    }
    fscanf(f, "%6s %i %4s %3s %i %f %f %f %2s", items[count].record_name, &items[count].atom_number, items[count].atom_name, items[count].residue_name, &items[count].residue_number, &items[count].x, &items[count].y, &items[count].z, items[count].element_name);
    count++;
  }

  fclose(f);
  return 0;
}

int zapis(char subor_zapis[]) //otvorenie vystupniho suboru a zapis hodnot do suboru
{
  FILE *f = NULL;
  int i = 0;
  f = fopen(subor_zapis, "w"); //otevre subor pro zapis hodnot
  for (i = 0; i < count; i++)
  {
    fprintf(f, "%-6s %3i %-4s %3s % 5i %10.3f %7.3f %8.3f %10s\n", items[i].record_name, items[i].atom_number, items[i].atom_name, items[i].residue_name, items[i].residue_number, items[i].x, items[i].y, items[i].z, items[i].element_name);
  }
  fclose(f);
  return 0;
}

int main()
{
  int i = 0;
  int h = 0;       //pocet atomov H
  int c = 0;       //pocet atomov C
  int n = 0;       //pocet atomov N
  int o = 0;       //pocet atomov O
  int s = 0;       //pocet atomov S
  int ostatni = 0; //pocet ostatnich atomov
  int residua = 0; //pocet residui

  char subor_cteni[] = "/home/martinp/C2160/data/crambin_simple.pdb";
  char subor_zapis[] = "crambin.dat";

  if (cteni(subor_cteni) != 0)
    return 1;

  if (zapis(subor_zapis) != 0)
    return 1;

  while (i <= count)
  {
    if (items[i].element_name == "h")
    {
      h++;
    }
    i++;
  }
  printf("Celkovy pocet atomov: %i\nPocet atomov H: %i\nPocet atomov C: %i\nPocet atomov N: %i\nPocet atomov O: %i\nPocet atomov S: %i\nPocet ostatnich atomov: %i\nPocet residui: %i\n", count, h, c, n, o, s, ostatni, residua);

  return 0;
}