#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

#define MAX_ATOMS 100000
#define MAX_RES 10000
#define BUFFLEN 100
#define RESD_TYPES_COUNT 21

char outname[BUFFLEN];
char readfile[BUFFLEN];
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
}PDBATOM;

typedef struct
{
  int start;
  int end;
  char residue_name[4];
  int residue_number;
  int numero;
}RES;

typedef struct
{
   char code3[4]; // three-letter code
   char code1; // one-letter code
   double color_r;
   double color_g;
   double color_b;
   int numero;
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

PDBATOM atoms[MAX_ATOMS];
int atom_count = 0;

RES residues[MAX_RES];
int residue_count=0;

void init()
{
  int i=0;
  for(i=0; i<MAX_ATOMS; i++)
  {
    memset(atoms[i].record_name, '\0', 7);
    atoms[i].atom_number=0;
    memset(atoms[i].atom_name, '\0', 5);
    atoms[i].alt_loc='\0';
    memset(atoms[i].residue_name, '\0', 4);
    atoms[i].chain_id='\0';
    atoms[i].residue_number=0;
    atoms[i].i_code='\0';
    atoms[i].x=0.0;
    atoms[i].y=0.0;
    atoms[i].z=0.0;
    atoms[i].occupancy=0.0;
    atoms[i].temp_factor=0.0;
    memset(atoms[i].element_name, '\0', 3);
    memset(atoms[i].formal_charge, '\0', 3);
    atoms[i].is_occupancy=0;
    atoms[i].is_temp_factor=0;
  }
  for(i=0; i< MAX_RES; i++)
  {
    residues[i].start=0;
    residues[i].end=0;
    memset(residues[i].residue_name, '\0', 4);
    residues[i].residue_number=0;
  }
}

int readPDBfile(char readfile[BUFFLEN])
{
  FILE *pdbfile = NULL;
  char buff[BUFFLEN];
  char s[BUFFLEN];
  
  memset(buff, '\0', BUFFLEN);
  memset(s, '\0', BUFFLEN);
  
  pdbfile=fopen(readfile, "r");
  
  if(pdbfile==NULL)
  {
    printf("Failed to load file.\n");
    return 1;
  }
  
  atom_count=0;
  
  while(feof(pdbfile) == 0)
  {
    if (atom_count >= MAX_ATOMS)
    {
      printf("File too big!\n");
      return 1;
    }
    /*if (atom_count >= 20)
    {
    break;
  }*/
    
    if(fgets(buff, BUFFLEN, pdbfile)==NULL)
      break;
    
    if ((strncmp(buff, "ATOM", 4) == 0))
    {
      strncpy(atoms[atom_count].record_name, buff, 6);
      atoms[atom_count].record_name[6]='\0';
      
      strncpy(s, buff+6, 5);
      s[5]='\0';
      sscanf(s, "%d", &atoms[atom_count].atom_number);
      
      strncpy(atoms[atom_count].atom_name, buff+12, 4);
      atoms[atom_count].atom_name[4]='\0';
      
      atoms[atom_count].alt_loc = buff[16];
      
      strncpy(atoms[atom_count].residue_name, buff+17, 3);
      atoms[atom_count].residue_name[3]='\0';
      
      atoms[atom_count].chain_id = buff[21];
      
      strncpy(s, buff+22, 4);
      s[4]='\0';
      sscanf(s, "%d", &atoms[atom_count].residue_number);
      
      atoms[atom_count].i_code = buff[26];
      
      strncpy(s, buff+30, 8);
      s[8]='\0';
      sscanf(s, "%lf", &atoms[atom_count].x);
      
      strncpy(s, buff+38, 8);
      s[8]='\0';
      sscanf(s, "%lf", &atoms[atom_count].y);
      
      strncpy(s, buff+46, 8);
      s[8]='\0';
      sscanf(s, "%lf", &atoms[atom_count].z);
      
      strncpy(s, buff+54, 6);
      s[6]='\0';
      if (sscanf(s, "%lf", &atoms[atom_count].occupancy) > 0)
      {
        atoms[atom_count].is_occupancy = 1;
      } else atoms[atom_count].is_occupancy = 0;
      
      strncpy(s, buff+60, 6);
      s[6]='\0';
      if (sscanf(s, "%lf", &atoms[atom_count].temp_factor) > 0)
      {
        atoms[atom_count].is_temp_factor = 1;
      } else atoms[atom_count].is_temp_factor = 0;
      
      strncpy(s, buff+76,  2);
      s[2]='\0';
      sscanf(s, "  %s  ", atoms[atom_count].element_name);
      
      strncpy(atoms[atom_count].formal_charge, buff+78, 2);
      atoms[atom_count].formal_charge[2]='\0';
      
      
      atom_count++;
    }
  }
  
  fclose(pdbfile);
  return 0;
}

int outputPDBfile(char outname[BUFFLEN])
{
  FILE *outputPDB = NULL;
  int i=0;
  
  outputPDB=fopen(outname, "w");
  if(outputPDB==NULL)
  {
    printf("Failed to load output file.\n");
    return 1;
  }
  
  for(i=0; i<atom_count; i++)
  {
    fprintf(outputPDB, "%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f", 
            atoms[i].record_name, atoms[i].atom_number, atoms[i].atom_name, 
            atoms[i].alt_loc, atoms[i].residue_name, atoms[i].chain_id, 
            atoms[i].residue_number, atoms[i].i_code, 
            atoms[i].x, atoms[i].y, atoms[i].z);
    
    if (atoms[i].is_occupancy == 1)
    {
      fprintf(outputPDB, "%6.2f", atoms[i].occupancy);
    } else 
    {
      fprintf(outputPDB, "      ");
    }
    if (atoms[i].is_temp_factor == 1)
    {
      fprintf(outputPDB, "%6.2f", atoms[i].temp_factor);
    } else 
    {
      fprintf(outputPDB, "      ");
    }
    
    fprintf(outputPDB, "          %2.2s%2.2s\n", 
            atoms[i].element_name, atoms[i].formal_charge);
    //printf("%s %s\n", atoms[i].element_name, atoms[i].formal_charge);
    //printf("%s", atoms[i].element_name);
  }
  
  fclose(outputPDB);
  return 0;
}

int detectResidues()
{
  int i=0;
  int last = 0;
  
  while(i<atom_count)
  {
    if(residue_count>MAX_RES)
    {
      printf("Too many residues.\n");
      return 1;
    }
    
    if(atoms[i].residue_number > last)
    {
      residues[residue_count].start = i;
      strcpy(residues[residue_count].residue_name, atoms[i].residue_name);
      residues[residue_count].residue_number = atoms[i].residue_number;
      i++;
      last = atoms[i].residue_number;
      while((atoms[i].residue_number == last))
        i++;
      residues[residue_count].end = i-1;
      residue_count++;
    }
    //printf("%i %i\n", atoms[i].residue_number, last);
  }
  
  residues[residue_count-1].end = atom_count;
  
  /*for(i=0; i<residue_count; i++)
  {
    printf("%.3i %.3i %s %.2i\n", residues[i].start, residues[i].end, residues[i].residue_name, residues[i].residue_number);
  ;}*/
  return 0;
}
/*void coloring()
{
   int i=0;
   int j=0;
   for(i=0; i<residue_count; i++)
   {
      for(j=0; j<RESD_TYPES_COUNT; j++)
      {
         if(strcmp(residues[i].residue_name, residue_types[j].code3)==0)
         {
            residues[i].numero=j;
            //printf("%i %s %i %s\n", residues[i].numero, residues[i].residue_name, j, residue_types[j].code3);
         }
      }
   }
   int dev = 0;
   double x = 0.0;
   getchar();
   dev = g2_open_X11(300, 300);
   g2_set_line_width (dev, 15);
   for (i=0; i<=residue_count; i++)
   {
      g2_pen(dev, g2_ink(dev, residue_types[residues[i].numero].color_r,residue_types[residues[i].numero].color_g,
             residue_types[residues[i].numero].color_b));
      x=360.0/(residue_count-1);
      g2_arc(dev, 150, 150, 120, 120,(i-1)*x, i*x);
   }
   getchar();
   g2_close(dev);
}*/
//gcc -o ukol ukol01.11.c -std=c99 -pedantic -I/home/martinp/libg2/include -L/home/martinp/libg2/ -lg2 -lX11 -lm
/*void GeomCentre()
{
  int i=0, j=0;
  int length=0;
  double centre[3]={0.0, 0.0, 0.0};
  
  int debug[BUFFLEN];
  int debug_count=0;
  
  for(i=0; i<residue_count; i++)
  {
    length=0;
    debug_count=0;
    memset(debug, 0, BUFFLEN);
    printf("%-3i %s\n", residues[i].residue_number, residues[i].residue_name);
    for(j=residues[i].start; j<=residues[i].end; j++)
    {
      if(strcmp("H", atoms[j].element_name) != 0)
      {
        centre[0] += atoms[j].x;
        centre[1] += atoms[j].y;
        centre[2] += atoms[j].z;
        length++;
        
        debug[debug_count]=atoms[j].atom_number;
        debug_count++;
        printf("%8.3f %8.3f %8.3f\n", atoms[j].x, atoms[j].y, atoms[j].z);
      }
    }
    centre[0]=centre[0]/length;
    centre[1]=centre[1]/length;
    centre[2]=centre[2]/length;
    printf("\n");
    printf("%8.3f %8.3f %8.3f\n", centre[0], centre[1], centre[2]);
    
    //printf("%i\n ",length);
    
    for(j=0; j<debug_count; j++)
    {
      printf(" %3i", debug[j]);
    }
    printf("\n");
    printf("________________________\n");
  }
  
}
// gcc -o ukol ukol01.11.c -std=c99 -pedantic -I/home/martinp/libg2/include -L/home/martinp/libg2/ -lg2 -lX11 -lm

void Backbone()
{
  int i=0, j=0;
  int length=0;
  int was=0;
  int numbers[BUFFLEN];
  for(i=0; i<residue_count; i++)
  {
    memset(numbers, 0, BUFFLEN);
    length=0;
    was=0;
    for(j=residues[i].start; j<=residues[i].end; j++)
    {
      if ((strstr(atoms[j].atom_name, "N ")!=NULL)||(strstr(atoms[j].atom_name, "CA")!=NULL)
        ||(strstr(atoms[j].atom_name, "C ")!=NULL)||(strstr(atoms[j].atom_name, "O ")!=NULL))
      {
        numbers[length]=atoms[j].atom_number;
        length++;
        was=1;
      }
    }
    if(was==1)
    {
      printf("%-3i %s ", residues[i].residue_number, residues[i].residue_name);
      for(j=0; j<length; j++)
      printf("%3i ", numbers[j]);
      printf("\n");
    }
  }
}*/

void carbons_alpha()
{
   int i=0,j=0;
   int alpha_count=0;
   double CA[3][MAX_RES];
   double dist=0.0;
  
   for(i=0; i<3; i++) memset(CA[i], 0.0, MAX_RES);
  
   for(i=0; i<residue_count; i++)
   {
      for(j=residues[i].start; j<=residues[i].end; j++)
      {
         if(strstr(atoms[j].atom_name, "CA")!=NULL)
         {
            CA[0][alpha_count]=atoms[j].x;
            CA[1][alpha_count]=atoms[j].y;
            CA[2][alpha_count]=atoms[j].z;
            alpha_count++;
         }
      }
   }
  
   for(i=0; i<alpha_count; i++)
   {
      printf("%3i %s :   ", residues[i].residue_number, residues[i].residue_name);
      for(j=i; j<alpha_count; j++)
      {
         dist=sqrt(pow(CA[0][i]-CA[0][j], 2) + pow(CA[1][i]-CA[1][j], 2) + pow(CA[2][i]-CA[2][j], 2));
         if((dist>5.0) && (dist<8.0))
         {
            printf("	%3i %s = %f Angstrom\n",residues[j].residue_number, residues[j].residue_name, dist);
         }
      }
      printf("\n");
   }
  
  
}

int main()
{
  init();
  scanf("%s %s", readfile, outname);
  readPDBfile(readfile);
  outputPDBfile(outname);
  detectResidues();
  //GeomCentre();
  //printf("______________________\n___________________\n");
  //Backbone();
  //printf("______________________\n___________________\n");
  //printf("______________________\n___________________\n");
  carbons_alpha();
 // coloring();
    return EXIT_SUCCESS;

} 
