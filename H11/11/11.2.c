#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

#define MAX 100000
#define BUF_SIZE 10000
#define BUFFLEN 100
#define RESD_TYPES_COUNT 21

//vypise informace o crambinu do souboru a pomoci g2 knihovny zobrazi residua formou barevnych segmentu

typedef struct
{
   char code3[4]; //tripismenny kod
   char code1; //jednopismenny kod
   double color_r; //cervena slozka
   double color_g; //zelena slozka
   double color_b; //modra slozka
   int residue_type;
} RESIDUE_TYPE;

RESIDUE_TYPE residue_types[RESD_TYPES_COUNT] =
{
   {"UNK", 'X', 153/255.0, 153/255.0, 153/255.0, 1},
   {"ALA", 'A', 204/255.0, 255/255.0, 255/255.0, 2},
   {"ARG", 'R', 230/255.0, 6/255.0, 6/255.0, 3},
   {"ASN", 'N', 255/255.0, 153/255.0, 0/255.0, 4},
   {"ASP", 'D', 255/255.0, 204/255.0, 153/255.0, 5},
   {"CYS", 'C', 0/255.0, 255/255.0, 255/255.0, 6},
   {"GLN", 'Q', 255/255.0, 102/255.0, 0/255.0, 7},
   {"GLU", 'E', 255/255.0, 204/255.0, 0/255.0, 8},
   {"GLY", 'G', 0/255.0, 255/255.0, 0/255.0, 9},
   {"HIS", 'H', 255/255.0, 255/255.0, 153/255.0, 10},
   {"ILE", 'I', 0/255.0, 0/255.0, 128/255.0, 11},
   {"LEU", 'L', 51/255.0, 102/255.0, 255/255.0, 12},
   {"LYS", 'K', 198/255.0, 6/255.0, 0/255.0, 13},
   {"MET", 'M', 153/255.0, 204/255.0, 255/255.0, 14},
   {"PHE", 'F', 0/255.0, 204/255.0, 255/255.0, 15},
   {"PRO", 'P', 255/255.0, 255/255.0, 0/255.0, 16},
   {"SER", 'S', 204/255.0, 255/255.0, 153/255.0, 17},
   {"THR", 'T', 0/255.0, 255/255.0, 153/255.0, 18},
   {"TRP", 'W', 204/255.0, 153/255.0, 255/255.0, 19},
   {"TYR", 'Y', 204/255.0, 255/255.0, 204/255.0, 20},
   {"VAL", 'V', 0/255.0, 0/255.0, 255/255.0, 0}
};

typedef struct //definice struktury residui
{
  int first_atom;
  int last_atom;
  int residue_number;
  char residue_name[4];
  int residue_type;
} RESIDUE;
RESIDUE items[BUF_SIZE];
int residue_count = 0;

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
int atom_count = 0;

int count; //pocet radku souboru

void init()
{
  int i = 0;
  for(i = 0; i < MAX; i++)
  {
    memset(atoms[i].record_name, '\0', 7);
    atoms[i].atom_number = 0;
    memset(atoms[i].atom_name, '\0', 5);
    atoms[i].alt_loc = '\0';
    memset(atoms[i].residue_name, '\0', 4);
    atoms[i].chain_id = '\0';
    atoms[i].residue_number = 0;
    atoms[i].i_code = '\0';
    atoms[i].x = 0.0;
    atoms[i].y = 0.0;
    atoms[i].z = 0.0;
    atoms[i].occupancy = 0.0;
    atoms[i].temp_factor = 0.0;
    memset(atoms[i].element_name, '\0', 3);
    memset(atoms[i].formal_charge, '\0', 3);
  }
  for(i = 0; i < BUF_SIZE; i++)
  {
    items[i].first_atom = 0;
    items[i].last_atom = 0;
    memset(items[i].residue_name, '\0', 4);
    items[i].residue_number = 0;
  }
}

int cteni(char soubor_cteni[BUFFLEN]) //otevreni vstupniho souboru
{
  FILE *f = NULL;
  char buf[BUFFLEN];
  char s[BUFFLEN];
  
  memset(buf, '\0', BUFFLEN);
  memset(s, '\0', BUFFLEN);

  f = fopen(soubor_cteni, "r"); //otevre soubor pro cteni
  if (f == NULL) //kontrola souboru
    {
      printf("Nelze otevrit vstupni soubor!\n");
      return 1;
    }
   
  while (feof(f) == 0)
  {
    if (count >= MAX) //kontrola velikosti pole
    {
      printf("Soubor je prilis velky!\n");
      return 1;
    }
  
    if (fgets(buf, BUFFLEN, f) == NULL)
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
      fprintf(f, "%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f%6.2f%6.2f          %2.2s%2.2s\n",
	      atoms[n].record_name, atoms[n].atom_number, atoms[n].atom_name,
	      atoms[n].alt_loc, atoms[n].residue_name, atoms[n].chain_id, atoms[n].residue_number,
	      atoms[n].i_code, atoms[n].x, atoms[n].y, atoms[n].z, atoms[n].occupancy, atoms[n].temp_factor,
	      atoms[n].element_name, atoms[n].formal_charge);
    } 
  fclose(f);
  return 0;
}

int residue() //vypise info o residuich
{
  int i = 0;
  int itemCount = 0;	//citac jednotlivych polozek zaznamu

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
    
 return 0;
}

void draw()
{
  int dev = 0;
  int i = 0;
  int y = 460; 
  int x1 = 20, x2 = 35; 
  int p = 0;
  char s[2] = {'\0'};
  
  dev = g2_open_X11(500, 500);
  g2_set_line_width(dev, 18);
  
  for(i = 0; i < residue_count; i++)
  {
    p++;
    g2_pen(dev, g2_ink(dev,
           residue_types[items[i].residue_type].color_r,
           residue_types[items[i].residue_type].color_g,
           residue_types[items[i].residue_type].color_b)
          );
    
    g2_line(dev, x1, y, x2, y);
    g2_set_font_size(dev, 12);
    
    if (items[i].residue_type == 10)
      g2_pen(dev, 0);
    else
      g2_pen(dev, 1);
      s[0] = residue_types[items[i].residue_type].code1;
      s[1] = '\0';
    
    if (items[i].residue_type == 13)
      g2_string(dev, x1+2, y-4, s);
    else if (items[i].residue_type == 10)
      g2_string(dev, x1+5, y-4, s);
    else
      g2_string(dev, x1+3, y-4, s);
      x1 = x1+15; 
      x2 = x2+15;
    
    if (p != 0 && (p % 30) == 0)
      {
	y = y - 36;
	x1 = 20;
	x2 = 35;
      }    
  }
  getchar();
  getchar(); 
  g2_close(dev);
}

void center() //pocita geometricky stred atomu pro kazde residuum
{
  int i = 0;
  int j = 0;
  int atomCount = 0; //geom. stred residua na zaklade poctu jeho atomu
  char testChar[] = "H"; //hledany znak
  float soucet_x = 0, soucet_y = 0, soucet_z = 0; //pomocne promenne pro soucet souradnic
  float stred_x = 0, stred_y = 0, stred_z = 0; //hodnoty geometrickeho stredu atomu
  
  for (i = 0; i < residue_count; i++)
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
}

void protein() //vyhledava atomy ktere tvori pater proteinu
{
     int i = 0, j = 0, length = 0, was = 0, numbers[BUFFLEN];
          
    for (i = 0; i <= residue_count; i++)
      {
	memset(numbers, 0, BUFFLEN);
	length = 0;
	was = 0;
	for (j = items[i].first_atom; j <= items[i].last_atom; j++)
	{
	  if ((strstr(atoms[j].atom_name, " N  ") != NULL) || (strstr(atoms[j].atom_name, " CA ") != NULL) || (strstr(atoms[j].atom_name, " C  ") != NULL) || (strstr(atoms[j].atom_name, " O  ") != NULL)) 
	  {
	    numbers[length]=atoms[j].atom_number;
	    length++;
	    was=1;	    
	  }                    
	}
	if(was==1)
	{
	  printf("Cisla atomu tvoricich peptidickou pater proteinu pro residuum % 5i %3s:\n", items[i].residue_number, items[i].residue_name);
	  for(j=0; j < length; j++)
	   printf("%3i ", numbers[j]);
	   printf("\n");
	}
      }
}

void carbons_alpha()
{
   int i = 0,j = 0;
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
	      printf("%3i %s = %f Angstrom ||", items[j].residue_number, items[j].residue_name, dist);
	  }
      }
      printf("\n");
   }  
}


int main(int argc, char *argv[])  //ziska nazvy souboru jako parametry z prikazoveho radku
{
  init();
  
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
  //center();
  //protein();
  //carbons_alpha();
  draw();
  
  return 0; 
} 