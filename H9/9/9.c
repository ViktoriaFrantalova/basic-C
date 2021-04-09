#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#define MAX 100000
#define BUF_SIZE 10000
//vypise informace o crambinu do souboru

typedef struct //definice struktury residui
{
  int first_atom;
  int last_atom;
  int residue_number;			// toto je správnì, dle zadání
  char residue_name[4];			// toto je správnì, dle zadání
} RESIDUE;
RESIDUE items[MAX];

typedef struct //definice struktury
{
  char record_name[7];
  int atom_number;
  char atom_name[5];
  char alt_loc;
  char residue_name[4];
  char chain_id;
  int residue_number;
  char i_code;
  float x;
  float y;
  float z;
  float occupancy;
  float temp_factor;
  char element_name[3];
  char formal_charge[3];
} ATOM;
ATOM atoms[MAX]; //definice pole struktur

int count; //pocet radku souboru

int residue() //vypise info o residuich
{
// je treba si uvedomit, co presne potrebujeme zjistovat a jak probiha cyklus a indexovani
// vlastne porovnavame dva radky s informacemi o residuich a podminka, ktera nas zajima je tato:
//		1. Pokud jsme na prvnim radku, pak pouze nacitame prvni residuum a jeho prvni atom 
//		2. Je residuum na aktualnim radku rozdilne od residua na radku predchozim?
//				 - pokud ANO, pak aktualni radek je nove residuum (prvni atom noveho residua)
//						a predchozi radek obsahoval predchozi residuum, (posledni atom predchoziho residua)

  int i = 0;
  int itemCount = 0;	// zde budeme mit citac jednotlivych polozek zaznamu
						// POZOR: Tento index zvysujeme, teprve az mame dalsi residuum !!!!
  for (i = 0; i < count; i++)
  {		
		if (i == 0)
		{
			// prvni radek, nacitame tedy prvni residuum
			items[itemCount].residue_number = atoms[i].residue_number;
			strcpy(items[itemCount].residue_name, atoms[i].residue_name);
			items[itemCount].first_atom		= atoms[i].atom_number;			
		}
		else if (items[itemCount].residue_number != atoms[i].residue_number) 
		{
			// ukladame informace o puvodnim residuu
			items[itemCount].last_atom = atoms[i-1].atom_number; // index posledního atomu
			
			itemCount++;	// mame nove residuum, zvysujeme cislo indexu pro polozky vypisu

			// nove residuum, nacitame tedy ifnromace o nazvu, cosle a prvnim atomu
			items[itemCount].residue_number = atoms[i].residue_number;
			strcpy(items[itemCount].residue_name, atoms[i].residue_name);
			items[itemCount].first_atom		= atoms[i].atom_number;						
		}
		else
		{
			// ukladame informace o poslednim residuu
			items[itemCount].last_atom = atoms[i].atom_number; // index posledního atomu
		}
  }

  for (i = 0;i <= itemCount; i++)
  {	
	// vypiseme prvky v nasem poli struktur
	printf("Residuum: % 5i %3s, indexy atomu: %3i %3i\n", items[i].residue_number, items[i].residue_name, items[i].first_atom, items[i].last_atom);  
  }

/*      if (i == 0 || atoms[i].residue_number != atoms[i-1].residue_number)
      {
	
	  items[i].first_atom = atoms[i].atom_number;
	  items[i].last_atom = atoms[i-1].atom_number;   //tohle je spatne :)
	  printf("Residuum: % 5i %3s, indexy atomu: %3i %3i\n", atoms[i].residue_number, atoms[i].residue_name, items[i].first_atom, items[i].last_atom);
      }*/

}

int cteni(char soubor_cteni[]) //otevreni vstupniho souboru
{
  
char buf[BUF_SIZE] = "";
char s[30] = "";
  
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
  memset(buf, '\0', BUF_SIZE);
  if (fgets(buf, BUF_SIZE, f) == NULL)
    break;
  if (strncmp(buf, "ATOM", 4) == 0 || strncmp(buf, "HETATM", 6) == 0)
  {
    strncpy(atoms[count].record_name, buf, 6); //nacteni jmena zaznamu
    atoms[count].record_name[6] = '\0';
    
    strncpy(s, buf+6, 5); //nacteni cisla atomu
    s[5] = '\0';
    sscanf(s, "%d", &atoms[count].atom_number);
    
    strncpy(atoms[count].atom_name, buf+12, 4); //nacteni jmena atomu
    atoms[count].atom_name[4] = '\0';
    
    atoms[count].alt_loc = buf[16]; //nacteni alternativni pozice atomu
    
    strncpy(atoms[count].residue_name, buf+17, 3); //nacteni jmena residua
    atoms[count].residue_name[3] = '\0';
    
    atoms[count].chain_id = buf[21]; //nacteni identifikatoru proteinoveho retezce
    
    strncpy(s, buf+22, 4); //nacteni cisla residua
    s[4] = '\0';
    sscanf(s, "%d", &atoms[count].residue_number);
    
    atoms[count].i_code = buf[26]; //nacteni kodu indikujici vlozeni residua
    
    strncpy(s, buf+30, 8); //nacteni souradnice x
    s[8] = '\0';
    sscanf(s, "%f", &atoms[count].x);
    
    strncpy(s, buf+38, 8); //nacteni souradnice y
    s[8] = '\0';
    sscanf(s, "%f", &atoms[count].y);
    
    strncpy(s, buf+46, 8); //nacteni souradnice z
    s[8] = '\0';
    sscanf(s, "%f", &atoms[count].z);
    
    strncpy(s, buf+54, 6); //nacteni occupancy
    s[6] = '\0';
    sscanf(s, "%f", &atoms[count].occupancy);
    
    strncpy(s, buf+60, 6); //nacteni teplotniho faktoru
    s[6] = '\0';
    sscanf(s, "%f", &atoms[count].temp_factor);
    
    strncpy(atoms[count].element_name, buf+76, 2); //nacteni symbolu prvku
    atoms[count].element_name[2] = '\0';
    
    strncpy(atoms[count].formal_charge, buf+78, 2); //nacteni formalniho naboje
    atoms[count].formal_charge[2] = '\0';
    
    count++;
  }
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
      fprintf(f, "%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f%6.2f%6.2f          %2.2s%2.2s\n", atoms[n].record_name, atoms[n].atom_number, atoms[n].atom_name, atoms[n].alt_loc, atoms[n].residue_name, atoms[n].chain_id, atoms[n].residue_number, atoms[n].i_code, atoms[n].x, atoms[n].y, atoms[n].z, atoms[n].occupancy, atoms[n].temp_factor, atoms[n].element_name, atoms[n].formal_charge);
    } 
  fclose(f);
  return 0;
}

int main(int argc, char *argv[])  //ziska nazvy souboru jako parametry z prikazoveho radku
{
  char soubor_cteni[MAX] = "";
  char soubor_zapis[MAX] = "";
  
  if (argc > 1)
  {
    cteni(argv[1]);
    zapis(argv[2]);    
  }
  else //zepta se na nazvy souboru, kdyz nejsou zadany jako parametry
  {
    printf("Zadejte nazev souboru pro cteni: \n");
    scanf("%s", soubor_cteni);
    cteni(soubor_cteni);
    printf("Zadejte nazev souboru pro zapis: \n");
    scanf("%s", soubor_zapis);
    zapis(soubor_zapis);
  }
  residue();
  return 0; 
} 