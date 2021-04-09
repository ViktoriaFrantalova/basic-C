#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
#include <errno.h>

#define MAX_ATOMS 20000
#define MAX_RESIDUES 10000
#define BUF_SIZE 100
#define RESD_TYPES_COUNT 21

typedef struct
{
  char record_name[7];
  int atom_number;
  char atom_name[5];
  char alt_loc;
  char residue_name[4];
  char chain_id;
  int residue_number;
  char i_code;
  double x;
  double y;
  double z;
  double occupancy;
  double temp_factor;
  char element_name[3];
  char formal_charge[3];
  int is_occupancy;
  int is_temp_factor;
} ATOM;

typedef struct
{
  char residue_name[4];
  int residue_number;
  int first_atom;
  int last_atom;
  int is_specified;
  int residue_type;
} RESIDUE;
char filename_input[200] = "crambin_noal.pdb";
  char filename_output[200] = "vysledek.pdb";
typedef struct
{
  char code3[4]; // threeletter code
  char code1; // oneletter code
  double color_r;
  double color_g;
  double color_b;
} RESIDUE_TYPE;

RESIDUE_TYPE residue_types[RESD_TYPES_COUNT] =
{                                                //prirazene indexy
  {"UNK", 'X', 153/255.0, 153/255.0, 153/255.0}, //0
  {"ALA", 'A', 204/255.0, 255/255.0, 255/255.0}, //1
  {"ARG", 'R', 230/255.0, 6/255.0, 6/255.0},     //2
  {"ASN", 'N', 255/255.0, 153/255.0, 0/255.0},   //3
  {"ASP", 'D', 255/255.0, 204/255.0, 153/255.0}, //4
  {"CYS", 'C', 0/255.0, 255/255.0, 255/255.0},   //5
  {"GLN", 'Q', 255/255.0, 102/255.0, 0/255.0},   //6
  {"GLU", 'E', 255/255.0, 204/255.0, 0/255.0},   //7
  {"GLY", 'G', 0/255.0, 255/255.0, 0/255.0},     //8
  {"HIS", 'H', 255/255.0, 255/255.0, 153/255.0}, //9
  {"ILE", 'I', 0/255.0, 0/255.0, 128/255.0},     //10
  {"LEU", 'L', 51/255.0, 102/255.0, 255/255.0},  //11
  {"LYS", 'K', 198/255.0, 6/255.0, 0/255.0},     //12
  {"MET", 'M', 153/255.0, 204/255.0, 255/255.0}, //13
  {"PHE", 'F', 0/255.0, 204/255.0, 255/255.0},   //14
  {"PRO", 'P', 255/255.0, 255/255.0, 0/255.0},   //15
  {"SER", 'S', 204/255.0, 255/255.0, 153/255.0}, //16
  {"THR", 'T', 0/255.0, 255/255.0, 153/255.0},   //17
  {"TRP", 'W', 204/255.0, 153/255.0, 255/255.0}, //18
  {"TYR", 'Y', 204/255.0, 255/255.0, 204/255.0}, //19
  {"VAL", 'V', 0/255.0, 0/255.0, 255/255.0}      //20
};

ATOM atoms[MAX_ATOMS];
RESIDUE residues[MAX_RESIDUES];
int atoms_count = 0;
int residues_count = 0;
//int h = 0, w = 0;
char file_name_input[1000] = "\0";


void init_variables()
{
  int i = 0;
  for (i = 0; i < MAX_ATOMS; i++)
  {
    atoms[i].record_name[0] = '\0';
    atoms[i].atom_number = 0;
    atoms[i].atom_name[0] = '\0';
    atoms[i].alt_loc = '\0';
    atoms[i].residue_name[0] = '\0';
    atoms[i].chain_id = '\0';
    atoms[i].residue_number = 0;
    atoms[i].i_code = '\0';
    atoms[i].x = 0.0;
    atoms[i].y = 0.0;
    atoms[i].z = 0.0;
    atoms[i].occupancy = 0.0;
    atoms[i].temp_factor = 0.0;
    atoms[i].element_name[0] = '\0';
    atoms[i].formal_charge[0] = '\0';
    atoms[i].is_occupancy = 0;
    atoms[i].is_temp_factor = 0;
  }
  
  for (i = 0; i < MAX_RESIDUES; i++)
  {
    residues[i].residue_name[0] = '\0';
    residues[i].residue_number = 0;
    residues[i].first_atom = 0;
    residues[i].last_atom = 0;
    residues[i].is_specified = 0;
    residues[i].residue_type = 0;
  }
}

/*int read_config_file(char filename_input[])
{
  char buf[BUF_SIZE] = {'\0'};
  //char s[30] = {'\0'};
  char record_name[100] = {'\0'};
  char *start_read = NULL;
  char *stop_read = NULL;
  int i = 0, j = 0, n = 0;
  int resd_num = 0;             // Budou se do ni nacitat cisla residui ze seznamu RESIDUES_LIST
  int previous_resd_num = -1;   // Zde ulozime cislo predesleho residua v pripade nacitani intervalu (napr. 5 - 12)
  //char c = ' ', c_previous = ',';
  
  
  FILE *fconf = NULL;
  
  fconf = fopen(filename_input, "r");
  if (fconf == NULL)
  {
    printf("Nelze otevrit konfiguracni soubor!\n");
    if (errno != 0)
      printf(" Error explanation: %s\n",
             strerror(errno));
    return 1;
  }
  
  while (!feof(fconf))  // Nacitame soubor, dokud neni konec souboru
  {
		//for (i = 0; i < RESD_TYPES_COUNT; i++) printf("%s\n", residue_types[i].residue_name);
    // Nacteme radek souboru    
    if (fgets(buf, BUF_SIZE, fconf) == NULL)
      break; 
    start_read = strchr(buf, '=');      // Zjistime jestli radek obsahuje '=' a pokud ano, ukazatel na nej nejbude v start_read
    if (start_read == NULL)
      continue;                        // Pokud radek neobsahuje '=' nebudeme ho dale zpracovavat    
    // Nasledujici nacita retezec az po znak '=' nebo bily znak
    // Zacatek textu muze predchazet libovolny pocet bilych znaku (proto davame mezeru na zacatku form. retezce)
    n = sscanf(buf, " %99[^= \t\n]", record_name);         
    if (n < 1)
      continue;    // Na radku se nenachazi zadny pocatecni retezec takze v jeho zpracovani nepokracujeme
    if (strcmp(record_name, "INPUT_FILE") == 0) //Nacteni vstupniho souboru
    {
      start_read++;
      stop_read = buf + strlen(buf);
      sscanf(start_read, "%s", file_name_input);
			//printf("Nacteno %s \n", file_name_input);
      continue;
    }
    if (strcmp(record_name, "WINDOW_SIZE") == 0) //Nastaveni velikosti okna
    {
      start_read++;
      stop_read = buf + strlen(buf);
      sscanf(start_read, "%i , %i", &w, &h);
			//printf("Nacteny rozmery %i x %i\n", w, h);
      continue;
    }
    if (strcmp(record_name, "RESIDUE_LIST") == 0) //Pro vyber rezidui
    {
			//printf("Nactena rezidua: ");
      start_read++;            // Chceme ancitat od pozice az za znakem '=' (start_read puvodne ukazuje na pozici znaku '=')
      stop_read = buf + strlen(buf);
      // Nacitame cisla residui, zacneme od pozice za znakem '=' coz je (start_read + 1)
      for ( ; start_read < stop_read; start_read++)
      {
        n = sscanf(start_read, "%d", &resd_num);   // Nacteme celociselnou hodnotu residua
        if (n < 1) 
          break;              // Pokud se nenacetlo cisla residua jme bud nakonci radku nebo je na radku chyba
        // Nasledne vypiseme residua od "previous_resd_num" do "resd_num", pokud vsak nebyl specifikovan interval,
        // musime nastavit "previous_resd_num = resd_num", pak se cyklus projde jen jednou        
        if (previous_resd_num < 0)
          previous_resd_num = resd_num;   // Timto zajistime, ze nasledujici cyklus se projde jen jednou s hodnotou "resd_num"
        else 
          previous_resd_num++;   // Provedeme inkrementaci, protoze "previous_resd_num" jsme jiz zpracovali pri minulem pruchodu
        for (i = previous_resd_num; i <= resd_num; i++)
        {
          // Prohledavame vsechna residua jestli nekter z nich ma cislo rovne i
          for (j = 0; j < residues_count; j++)
          {
            if (residues[j].residue_number == i)
              residues[j].is_specified = 1;
          }
        }uloha2: 11.2.c
	gcc -o 11.2 11.2.c -std=c99 -Wall -pedantic -lg2 -lgd -lX11 -lm

        while (*start_read != ',' && *start_read != '-' && start_read < stop_read) 
          start_read++;        
        if (*start_read == '-')
          previous_resd_num = resd_num;
        else
          previous_resd_num = -1;
				   
				//printf("%d, ", resd_num);  
      }
			//printf("\n");
    }
  }
  
  //fclose(fconf);
  if (fclose(fconf) == EOF)
  {
    printf("Error closing the file %s\n",
           filename_input);
    if (errno != 0)
      printf(" Explanation: %s\n",
             strerror(errno));
    return 1;
  }
  fconf = NULL;
  return 0;
}*/

int read_input_file()
{
  char buf[BUF_SIZE] = {'\0'};
  char s[30] = {'\0'};
  FILE *fin = NULL;
  fin = fopen(filename_input, "r");
  if (fin == NULL)
  {
    printf("Nelze otevrit vstupni soubor!\n");
    if (errno != 0)
      printf(" Error explanation: %s\n",
             strerror(errno));
    return 1;
  }
  
  while (feof(fin) == 0)
  {
    if (atoms_count >= MAX_ATOMS)
    {
      printf("Velikost pole neni dostatecna!\n");
      return 1;
    }
    
    memset(buf, '\0', BUF_SIZE);
    if (fgets(buf, BUF_SIZE, fin) == NULL)
      break;
    if (strncmp(buf, "ATOM", 4) == 0 || strncmp(buf, "HETATM", 6) == 0)
    {
      {
        strncpy(atoms[atoms_count].record_name, buf, 6);
        atoms[atoms_count].record_name[6] = '\0';
        // Nacteni cisla atomu
        strncpy(s, buf+6, 5);
        s[5] = '\0';
        sscanf(s, "%d", &atoms[atoms_count].atom_number);
        // Jmeno atomu jednoduse zkopirujeme 4 znaky
        // od pozice 13 (cisl. od 1), tj, 12 (cisl. od 0)
        strncpy(atoms[atoms_count].atom_name, buf+12, 4);
        atoms[atoms_count].atom_name[4] = '\0'; 
        // Retezec musime zakoncit '\0'
        // Alternativni pozice
        atoms[atoms_count].alt_loc = buf[16];
        // Jmeno rezidua
        strncpy(atoms[atoms_count].residue_name, buf+17, 3);
        atoms[atoms_count].residue_name[3] = '\0';
        // Ukazka nacteni identifikatoru proteinoveho retezce jednoduse
        // zkopirujeme 1 znak z pozice 22 (cislovano od 1), tj. 21 (cislovano od 0)
        atoms[atoms_count].chain_id = buf[21];
        // Ukazka nacteni cisla residua z pozice 23 â 26 (cislovano od 1)
        strncpy(s, buf+22, 4); // Do s kopirujeme 4 znaky od pozice 22 (cisl. od 0)
        s[4] = '\0'; // Retezec musime zakoncit '\0'
        sscanf(s, "%d", &atoms[atoms_count].residue_number);
        // Nacteni kodu indikujici vlozeni rezidua
        atoms[atoms_count].i_code = buf[26];
        // Nacitani souradnice x
        strncpy(s, buf+30, 8);
        s[8] = '\0';
        sscanf(s, "%lf", &atoms[atoms_count].x);
        // Nacitani souradnice y
        strncpy(s, buf+38, 8);
        s[8] = '\0';
        sscanf(s, "%lf", &atoms[atoms_count].y);
        // Nacitani souradnice z
        strncpy(s, buf+46, 8);
        s[8] = '\0';
        sscanf(s, "%lf", &atoms[atoms_count].z);
        // Nacitani occupancy
        strncpy(s, buf+54, 6);
        s[6] = '\0';
        if (strncmp(s, "      ", 6) != 0)
          {
            sscanf(s, "%lf", &atoms[atoms_count].occupancy);
            atoms[atoms_count].is_occupancy = 1; // 
          }
        else
          atoms[atoms_count].is_occupancy = 0;
        // Nacitani teplotniho faktoru
        strncpy(s, buf+60, 6);
        s[6] = '\0';
        if (strncmp(s, "      ", 6) != 0)
        {
          sscanf(s, "%lf", &atoms[atoms_count].temp_factor);
          atoms[atoms_count].is_temp_factor = 1; //
        }
        else
          atoms[atoms_count].is_temp_factor = 0;
        // Nacteni symbolu prvku
        strncpy(atoms[atoms_count].element_name, buf+76, 2);
        atoms[atoms_count].element_name[2] = '\0';
        // Nacteni formalniho naboje
        strncpy(atoms[atoms_count].formal_charge, buf+78, 2);
        atoms[atoms_count].formal_charge[2] = '\0';
        
        //Testovaci vypis nacitani
        /*printf("%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f", atoms[atoms_count].record_name, atoms[atoms_count].atom_number, atoms[atoms_count].atom_name, atoms[atoms_count].alt_loc,  atoms[atoms_count].residue_name, atoms[atoms_count].chain_id, atoms[atoms_count].residue_number, atoms[atoms_count].i_code, atoms[atoms_count].x, atoms[atoms_count].y, atoms[atoms_count].z);
    
        if (atoms[atoms_count].is_occupancy == 1)
          printf("%6.2f", atoms[atoms_count].occupancy);
        else
          printf("      ");
     
        if (atoms[atoms_count].is_temp_factor == 1)
          printf("%6.2f", atoms[atoms_count].temp_factor);
        else
          printf("      ");
    
        printf("          ");
    
        printf("%2.2s%2.2s\n", atoms[atoms_count].element_name, atoms[atoms_count].formal_charge);
        
        if (atoms_count > 15) break;*/ 
        
        
        atoms_count++;
      }
    }
    
    /*fscanf(fin, "%6s %i %4s %3s %i %lf %lf %lf %2s", atoms[atoms_count].record_name, &atoms[atoms_count].atom_number, atoms[atoms_count].atom_name, atoms[atoms_count].residue_name, &atoms[atoms_count].residue_number, &atoms[atoms_count].x, &atoms[atoms_count].y, &atoms[atoms_count].z, atoms[atoms_count].element_name);
    atoms_count++;*/
  }
  
  
  //fclose(fin);
  
  if (fclose(fin) == EOF)
  {
    printf("Error closing the file %s\n",
           file_name_input);
    if (errno != 0)
      printf(" Explanation: %s\n",
             strerror(errno));
    return 1;
  }
  
  fin = NULL;
  return 0;
}

int set_residues()
{
  int i = 0, j = 0;
  int previous_residue_number = -1;
  //int atom_first = 0;
  //int atom_last = 0;
  /*for (i = 0; i < atoms_count; i++)
  {
  if ((atoms[i].residue_number != atoms[i-1].residue_number) || i == 0)
  {
      //printf ("%-3s %3i  %-4s %3i\n", atoms[i].residue_name, atoms[i].residue_number, atoms[i].atom_name, atoms[i].atom_number);
  residues[i].first_atom = i+1;
  residues[i].residue_number = atoms[i].residue_number;
  strncpy (residues[i].residue_name, atoms[i].residue_name, 3);
  residues[i].residue_name[3] = '\0';
}
  if ((atoms[i].residue_number != atoms[i+1].residue_number) || i == atoms_count)
  {
      //printf ("%-3s %3i  %-4s %3i\n", atoms[i].residue_name, atoms[i].residue_number, atoms[i].atom_name, atoms[i].atom_number);
  residues[i].last_atom = i+1;
  residues_count++;
}
}
  //Testovaci vypis:
  for (i = 0; i < residues_count; i++)
  {
  printf("%i %s %i %i\n", residues[i].residue_number, residues[i].residue_name, residues[i].first_atom, residues[i].last_atom);
}*/
  for (i = 0; i < atoms_count; i++)
  {
    if (previous_residue_number != atoms[i].residue_number)
    {      
      if (residues_count == MAX_RESIDUES)
      {
        printf("Soubor obsahuje vice residui nez je maximalni pripustny pocet (%i)\n", MAX_RESIDUES);
        break;
      }
      if (residues_count > 0)
        residues[residues_count-1].last_atom = i-1;      
      residues[residues_count].first_atom = i;      
      // Zkopirujeme nazev residua
      strncpy(residues[residues_count].residue_name, atoms[i].residue_name, 3);
      residues[residues_count].residue_name[3] = '\0';          
      residues[residues_count].residue_number = atoms[i].residue_number;       
      residues_count++;
      previous_residue_number = atoms[i].residue_number;
			
    }
  }
  residues[residues_count-1].last_atom = atoms_count - 1;
  
  // Oznaceni typu rezidui
  for (i = 0; i < residues_count; i++)
  {
    for (j = 0; j < RESD_TYPES_COUNT; j++)
    {
      if (strcmp(residue_types[j].code3, residues[i].residue_name) == 0)
      {
        residues[i].residue_type = j;
      }
    } 
  }
  
  //Kontrolni vypis
  /*for (i = 0; i < residues_count; i++)
  {
    printf("%d %.3s %c %d\n", residues[i].residue_number, residues[i].residue_name, residue_types[residues[i].residue_type].code1, residues[i].residue_type);
}*/
  //Prirazuje se mi to spravne
    

  return 0;
}

void draw()
{
  int dev = 0;
  int i = 0;
  int y = 460; //0.93877551*h
  int x1 = 20, x2 = 35; //x1 = 0.040816327*w, x2 = 0.071428571*w
  int p = 0;
  char s[2] = {'\0'};
  
  dev = g2_open_X11(500, 500);
  g2_set_line_width(dev, 18);
  
  for(i = 0; i < residues_count; i++)
  {
    p++;
    /*if((i%2) == 0)
      g2_pen(dev, 3);
    else
    g2_pen(dev, 19);*/
    g2_pen(dev, g2_ink(dev,
           residue_types[residues[i].residue_type].color_r,
           residue_types[residues[i].residue_type].color_g,
           residue_types[residues[i].residue_type].color_b)
          );
    
    //g2_arc(dev, h/2, w/2, rad, rad, i*360.0/residues_count, 360.0/residues_count + i*360.0/residues_count);
    
    g2_line(dev, x1, y, x2, y);
    g2_set_font_size(dev, 12);
    if (residues[i].residue_type == 10)
      g2_pen(dev, 0);
    else
      g2_pen(dev, 1);
    s[0] = residue_types[residues[i].residue_type].code1;
    s[1] = '\0';
    if (residues[i].residue_type == 13)
      g2_string(dev, x1+2, y-4, s);
    else if (residues[i].residue_type == 10)
      g2_string(dev, x1+5, y-4, s);
    else
      g2_string(dev, x1+3, y-4, s);
    x1 = x1+15; //
    x2 = x2+15;
    
    if (p != 0 && (p % 30) == 0)
    {
      y = y - 36;
      x1 = 20;
      x2 = 35;
      
      //printf("%d\n", y);
    }
    
  }
  
  
  
  getchar();
  getchar(); // Ceka se na vstup znaku z klavesnice
  g2_close(dev);
}

/*void calculate_geometric_center()
{
  int i = 0, j = 0, n = 0, count_H = 0; // n je pocet atomu v reziduu
  double x = 0.0, y = 0.0, z = 0.0;
  char s[3] = {'\0'};
  printf("Geometricke stredy rezidui:\n");
  for (i = 0; i < residues_count; i++)
  {
    count_H = 0;
    for (j = residues[i].first_atom; j <= residues[i].last_atom; j++)
    {
      sscanf(atoms[j].element_name, "%2s", s);
      if (s[0] == 'H')
        count_H++;
      else
      {
        x += atoms[j].x;
        y += atoms[j].y;
        z += atoms[j].z;
      }
    }
    n = (residues[i].last_atom - residues[i].first_atom + 1) - count_H;
    x = x/n;
    y = y/n;
    z = z/n;
    printf("%i %.3s %lf %lf %lf\n", residues[i].residue_number, residues[i].residue_name, x, y, z);
  } 
}

void find_backbone()
{
  int i = 0; //j = 0;
  char s[5] = {'\0'};
  printf("Atomy peptidicke patere rezidui:\n");
  for (i = 0; i < atoms_count; i++)
  {
    sscanf(atoms[i].atom_name, "%4s", s);
      if (strcmp(s, "N") == 0)
        printf("%i %.3s %i %s\n", atoms[i].residue_number, atoms[i].residue_name, atoms[i].atom_number, atoms[i].atom_name);
      else if (strcmp(s, "CA") == 0)
        printf("%i %.3s %i %s\n", atoms[i].residue_number, atoms[i].residue_name, atoms[i].atom_number, atoms[i].atom_name);
      else if (strcmp(s, "C") == 0)
        printf("%i %.3s %i %s\n", atoms[i].residue_number, atoms[i].residue_name, atoms[i].atom_number, atoms[i].atom_name);
      else if (strcmp(s, "O") == 0)
        printf("%i %.3s %i %s\n", atoms[i].residue_number, atoms[i].residue_name, atoms[i].atom_number, atoms[i].atom_name);
  }
}*/

int save_output_file(char filename_output[])
{
  int i = 0, j = 0;
  FILE *fout = NULL;
  
  //Testovaci vypis residui:
  for (i = 0; i < residues_count; i++)
    printf("%.3s %i: %i %i %i\n", residues[i].residue_name, residues[i].residue_number, 
           residues[i].first_atom, residues[i].last_atom, residues[i].is_specified);
  
  fout = fopen(filename_output, "w");
  if (fout == NULL)
  {
    printf("Nelze otevrit vystupni soubor!\n");
    return 1;
  }
  
  for (j = 0; j < residues_count; j++)
  {
    if (residues[j].is_specified == 1)
    {
      //Kontrolni vypis
      printf("%i %.3s\n", residues[j].residue_number, residues[j].residue_name);
      for (i = residues[j].first_atom; i < residues[j].last_atom; i++)
      {
        fprintf(fout, "%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f", atoms[i].record_name, atoms[i].atom_number, atoms[i].atom_name, atoms[i].alt_loc,  atoms[i].residue_name, atoms[i].chain_id, atoms[i].residue_number, atoms[i].i_code, atoms[i].x, atoms[i].y, atoms[i].z);
    
        if (atoms[i].is_occupancy == 1)
          fprintf(fout, "%6.2f", atoms[i].occupancy);
        else
          fprintf(fout, "      ");
     
        if (atoms[i].is_temp_factor == 1)
          fprintf(fout, "%6.2f", atoms[i].temp_factor);
        else
          fprintf(fout, "      ");
    
        fprintf(fout, "          ");
    
        fprintf(fout, "%2.2s%2.2s\n", atoms[i].element_name, atoms[i].formal_charge);
    
    
    
      }
    }
  }
  
  fclose(fout);
  fout = NULL;
  return 0;
}




  
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Nebylo zadano jmeno souboru!\n");
    return EXIT_FAILURE;
  }
  /*else if (argc < 3)
  {
    printf("Chybi jmeno vystupniho souboru!\n");
    return EXIT_FAILURE;
} */
  
  init_variables();
  
 // if (read_config_file(argv[1]) != 0)
   // return EXIT_FAILURE;
  
  if (read_input_file() != 0)
    return EXIT_FAILURE;
  
  set_residues();
  draw();
  
  /*if (read_config_file(argv[1]) != 0)
  return EXIT_FAILURE;*/
  
  /*if (save_output_file(argv[2]) != 0)
  return EXIT_FAILURE;*/
  
  
  //calculate_geometric_center();
  //find_backbone();
  
  return EXIT_SUCCESS;
}
