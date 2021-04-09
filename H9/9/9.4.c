#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 100000
#define BUF_SIZE 10000
//vypise informace o crambinu do souboru

typedef struct //definice struktury residui
{
  int first_atom;
  int last_atom;
  int residue_number;
  char residue_name[4];
} RESIDUE;
RESIDUE items[MAX];
int residue_count = 0;//pocet residui

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
  int i = 0;
  int itemCount = 0; //citac jednotlivych polozek zaznamu

  for (i = 0; i < count; i++)
    {
      if (i == 0) 
	{
	  items[itemCount].residue_number = atoms[i].residue_number;
	  strcpy(items[itemCount].residue_name, atoms[i].residue_name);
	  items[itemCount].first_atom = i;	
	}
	  else if (items[itemCount].residue_number != atoms[i].residue_number) 
	{
	  items[itemCount].last_atom = i-1; //index posledniho atomu
	  itemCount++;	//nove residuum - zvysuje cislo indexu pro polozky vypisu
	  
	  items[itemCount].residue_number = atoms[i].residue_number;
	  strcpy(items[itemCount].residue_name, atoms[i].residue_name);
	  items[itemCount].first_atom = i;
	 }
	else
	{
	  items[itemCount].last_atom = i; //index posledniho atomu
	 }
      residue_count = itemCount;
    }
 /* for (i = 0;i <= itemCount; i++)
  {
    printf("Residuum: % 5i %3s, indexy atomu: %3i %3i\n", items[i].residue_number, items[i].residue_name, items[i].first_atom, items[i].last_atom);
  }*/
}

/*int center() //pocita geometricky stred atomu pro kazde residuum
{
  int i = 0;
  int j = 0;
  int atomCount = 0; //geom. stred residua na zaklade poctu jeho atomu
  char testChar[] = "H"; //hledany znak
  float soucet_x = 0, soucet_y = 0, soucet_z = 0; //pomocne promenne pro soucet souradnic
  float stred_x = 0, stred_y = 0, stred_z = 0; //hodnoty geometrickeho stredu atomu
  
  for (i = 0; i < residueCount; i++)
   {
     soucet_x = 0;
     soucet_y = 0;
     soucet_z = 0;
     stred_x = 0;
     stred_y = 0;
     stred_z = 0;
     atomCount = 0;
     
     for (j = items[i].first_atom; j <= items[i].last_atom; j++)
      {
	if (strstr(atoms[j].element_name, testChar) == 0)
	  {
	    soucet_x = soucet_x + atoms[j].x; //soucet x-ovych souradnic
	    soucet_y = soucet_y + atoms[j].y; //soucet y-ovych souradnic
	    soucet_z = soucet_z + atoms[j].z; //soucet z-ovych souradnic
	    atomCount++;
	  }
      }
      stred_x = soucet_x / atomCount; //vypocet geom. stredu pro x
      stred_y = soucet_y / atomCount; //vypocet geom. stredu pro y
      stred_z = soucet_z / atomCount; //vypocet geom. stredu pro z
    
      printf("Residuum: % 5i %3s, center: %.2f %.2f %.2f\n", items[i].residue_number, items[i].residue_name, stred_x, stred_y, stred_z);
     
    } 
}*/

void carbons_alpha() //vyhleda residua, jejichz vzdalenost C-alpha atomu je > 5 a < 8 Angstromu
{
   int i = 0, j = 0;
   int alpha_count = 0;
   double CA[3][BUF_SIZE];
   double dist = 0.0;
  
   for(i = 0; i < 3; i++) memset(CA[i], 0.0, BUF_SIZE);
  
   for(i = 0; i < residue_count; i++)
   {
      for(j = items[i].first_atom; j <= items[i].last_atom; j++)
      {
         if(strstr(atoms[j].atom_name, "CA") != NULL)
         {
            CA[0][alpha_count] = atoms[j].x;
            CA[1][alpha_count] = atoms[j].y;
            CA[2][alpha_count] = atoms[j].z;
            alpha_count++;
         }
      }
   }
  
   for(i = 0; i < alpha_count; i++)
   {
      printf("%3i %s :   ", items[i].residue_number, items[i].residue_name);
      
      for(j = i; j < alpha_count; j++)
      {
         dist = sqrt(pow(CA[0][i]-CA[0][j], 2) + pow(CA[1][i]-CA[1][j], 2) + pow(CA[2][i]-CA[2][j], 2));
         if((dist > 5.0) && (dist < 8.0))
	  {
	      printf("	%3i %s = %f Angstrom\n", items[j].residue_number, items[j].residue_name, dist);
	  }
      }
      printf("\n");
   }  
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
  carbons_alpha();
  
  //center();
  //protein();
  
  return 0; 
} 