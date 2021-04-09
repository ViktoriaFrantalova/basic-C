#include <stdio.h>
#include <math.h>
#define MAX 1000
//vypise informace o crambinu do souboru
typedef struct //definice struktury
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

ATOM items[MAX]; //definice pole struktur
int count; //pocet radku souboru

int cteni(char soubor_cteni[]) //otevreni vstupniho souboru
{
  FILE *f = NULL;
  
  f = fopen(soubor_cteni, "r"); //otevre soubor pro cteni
  if (f == NULL) //kontrola souboru
    {
      printf("Nelze otevrit!\n");
      return 1;
    }
    
  while (feof(f) == 0)
  {
    if (count >= MAX) //kontrola velikosti pole
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

int zapis(char soubor_zapis[]) //otevreni vystupniho souboru a zapis hodnot do souboru
{
  FILE *f = NULL;
  int i = 0;
  f = fopen(soubor_zapis, "w"); //otevre soubor pro zapis hodnot
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
  int h = 0; //pocet atomu H
  int c = 0; //pocet atomu C
  int n = 0; //pocet atomu N
  int o = 0; //pocet atomu O
  int s = 0; //pocet atomu S
  int ostatni = 0; //pocet ostatnich atomu
  int residua = 0; //pocet residui
  
  char soubor_cteni[] = "/home/martinp/C2160/data/crambin_simple.pdb";
  char soubor_zapis[] = "crambin.dat";
  
  if (cteni(soubor_cteni) !=0 )
    return 1;
  
  if (zapis(soubor_zapis) !=0 )
    return 1;
  
  while (i <= count)
  {
    if(items[i].element_name == "h")
      {
	h++;
      }
    i++;
  }
  printf("Celkovy pocet atomu: %i\nPocet atomu H: %i\nPocet atomu C: %i\nPocet atomu N: %i\nPocet atomu O: %i\nPocet atomu S: %i\nPocet ostatnich atomu: %i\nPocet residui: %i\n", count, h, c, n, o, s, ostatni, residua);
  
  return 0; 
} 