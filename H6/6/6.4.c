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

typedef struct //definice struktury
{
  int h;
  int c;
  int n;
  int o;
  int s;
  int ostatni;
  int residua;
} POCET;

POCET polozky[MAX];

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
  int n = 0;
  f = fopen(soubor_zapis, "w"); //otevre soubor pro zapis hodnot
  for (n = 0; n < count; n++)
    {
      fprintf(f, "%-6s %3i %-4s %3s % 5i %10.3f %7.3f %8.3f %10s\n", items[n].record_name, items[n].atom_number, items[n].atom_name, items[n].residue_name, items[n].residue_number, items[n].x, items[n].y, items[n].z, items[n].element_name);
    } 
  fclose(f);
  return 0;
}

int pocet(char soubor_cteni[]) //vypise pocet a druh atomu
{
  int i = 0;
  FILE *f = NULL;
  
  f = fopen(soubor_cteni, "r"); //otevre soubor pro cteni
  if (f == NULL) //kontrola souboru
    {
      printf("Nelze otevrit!\n");
      return 1;
    }
    
  while (feof(f) == 0)
  {    
    if(items[count].element_name == "h")
    {
      i++;
    }
    //fscanf(f, "%i %i %i %i %i %i %i", pocet[count].h, pocet[count].c, pocet[count].n, pocet[count].o, pocet[count].s, pocet[count].ostatni, pocet[count].residua);
    count++;
  }
  
  for (n = 0; n < count; n++)
    {   
      printf("Celkovy pocet atomu: %i\nPocet atomu H: %i\nPocet atomu C: %i\nPocet atomu N: %i\nPocet atomu O: %i\nPocet atomu S: %i\nPocet ostatnich atomu: %i\nPocet residui: %i\n", count, pocet[i].h, pocet[i].c, pocet[i].n, pocet[i].o, pocet[i].s, pocet[i].ostatni, pocet[i].residua);
    }
  fclose(f);
  return 0;
}

int main() 
{
  char soubor_cteni[] = "/home/martinp/C2160/data/crambin_simple.pdb";
  char soubor_zapis[] = "crambin.dat";
  
  if (cteni(soubor_cteni) !=0 )
    return 1;
  
  if (zapis(soubor_zapis) !=0 )
    return 1;
  
  return 0; 
} 