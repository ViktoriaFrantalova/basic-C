#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
#define MAX 1000000
#define RESD_TYPES_COUNT 21

int a=0, b=0;
int count=0;
int residues_count=0;
int width=0, height=0;
double distance=0.0;
char filename[100]={'\0'}; 
typedef struct
{
  char jmeno_zaznamu[7];
  int poradove_cislo;
  char jmeno_atomu[5];
  char alternativni_pozice;
  char jmeno_residua[4];
  char identifikator;
  int poradove_cislo_residua;
  char kod;
  double x; 
  double y;
  double z;
  double occupancy;
  double teplotni_faktor;
  char symbol_prvku[3];
  char formalni_naboj[3];
}ATOM;
  ATOM atoms[MAX];
  
typedef struct
{
  int prvni_atom;
  int posledni_atom;
  int poradove_cislo_residua;
  char jmeno_residua[4];
  int restype;
}RESIDUE;
RESIDUE residue[10000];
  
typedef struct
{
  int cislo;
  char code3[4]; // three-letter code
  char code1; // one-letter code
  double color_r;
  double color_g;
  double color_b;
} RESIDUE_TYPE;
RESIDUE_TYPE residue_type[RESD_TYPES_COUNT]=
{
  {0, "UNK", 'X', 153/255.0, 153/255.0, 153/255.0},
  {1, "ALA", 'A', 204/255.0, 255/255.0, 255/255.0},
  {2, "ARG", 'R', 230/255.0, 6/255.0, 6/255.0},
  {3, "ASN", 'N', 255/255.0, 153/255.0, 0/255.0},
  {4, "ASP", 'D', 255/255.0, 204/255.0, 153/255.0},
  {5, "CYS", 'C', 0/255.0, 255/255.0, 255/255.0},
  {6, "GLN", 'Q', 255/255.0, 102/255.0, 0/255.0},
  {7, "GLU", 'E', 255/255.0, 204/255.0, 0/255.0},
  {8, "GLY", 'G', 0/255.0, 255/255.0, 0/255.0},
  {9, "HIS", 'H', 255/255.0, 255/255.0, 153/255.0},
  {10, "ILE", 'I', 0/255.0, 0/255.0, 128/255.0},
  {11, "LEU", 'L', 51/255.0, 102/255.0, 255/255.0},
  {12, "LYS", 'K', 198/255.0, 6/255.0, 0/255.0},
  {13, "MET", 'M', 153/255.0, 204/255.0, 255/255.0},
  {14, "PHE", 'F', 0/255.0, 204/255.0, 255/255.0},
  {15, "PRO", 'P', 255/255.0, 255/255.0, 0/255.0},
  {16, "SER", 'S', 204/255.0, 255/255.0, 153/255.0},
  {17, "THR", 'T', 0/255.0, 255/255.0, 153/255.0},
  {18, "TRP", 'W', 204/255.0, 153/255.0, 255/255.0},
  {19, "TYR", 'Y', 204/255.0, 255/255.0, 204/255.0},
  {20, "VAL", 'V', 0/255.0, 0/255.0, 255/255.0}
};

  
int promenne()
{ 
  int i=0;
  for(i=0;i<MAX;i++)
  {
    atoms[i].jmeno_zaznamu[0]='\0';
    atoms[i].poradove_cislo=0;
    atoms[i].jmeno_atomu[0]='\0';
    atoms[i].alternativni_pozice='\0';
    atoms[i].jmeno_residua[0]='\0';
    atoms[i].identifikator='\0';
    atoms[i].poradove_cislo_residua=0;
    atoms[i].kod='\0';
    atoms[i].x=0.0;
    atoms[i].y=0.0;
    atoms[i].z=0.0;
    atoms[i].occupancy=0.0;
    atoms[i].teplotni_faktor=0.0;
    atoms[i].symbol_prvku[0]='\0';
    atoms[i].formalni_naboj[0]='\0';
  }
  for(i=0;i<10000;i++)
  {
    residue[i].prvni_atom=0;
    residue[i].posledni_atom=0;
    residue[i].poradove_cislo_residua=0;
    residue[i].jmeno_residua[0]='\0';
    residue[i].restype=0;
  };
  return EXIT_SUCCESS;
}

int config()
{
  char str[MAX]={'\0'};
  char tr[MAX]={'\0'};
  FILE *h=NULL;
  h = fopen("/home/tbouchal/cecko/c", "r");
  if (h== NULL)
  {
    printf ("Cannot open file1!\n");
    return EXIT_FAILURE;
  }
  while (feof(h)==0)
  {
    if (fgets(str, MAX, h)==NULL)
      break;
    sscanf(str, "%49[^ =]", tr);
    if (strcmp(tr, "INPUT_FILE")==0)
      sscanf(str, "%*[^ =] = %99s", filename);
    if (strcmp(tr, "WINDOW_SIZE")==0)
      sscanf(str, "%*[^ =] = %i , %i", &width, &height);
    if (strcmp(tr, "DISTANCE")==0)
      sscanf(str, "%*[^ =] = %lf", &distance);

  }
  fclose(h);
  h=NULL;
  return EXIT_SUCCESS;
}

int openf()
{
  char buf[MAX]={'\0'};
  char s[9]={'\0'};
  char *p_s=NULL;
  char *q_s=NULL;
  FILE *f=NULL;
  f = fopen(filename, "r");
  if (f== NULL)
  {
    printf ("Cannot open file2!\n");
    return EXIT_FAILURE;
  }
  while (feof(f)==0)
  {
    memset(buf, '\0', MAX);
    if (fgets(buf, MAX, f)== NULL)
      break;
    if (strncmp(buf, "ATOM", 4)==0 || strncmp(buf, "HETATM", 6)==0)
    {
      strncpy(atoms[count].jmeno_zaznamu, buf,6);
      atoms[count].jmeno_zaznamu[6]='\0';
      
      strncpy(s, buf+6, 5);
      s[5]='\0';
      sscanf(s, "%d", &atoms[count].poradove_cislo);
      
      strncpy(atoms[count].jmeno_atomu, buf+12 , 4);
      atoms[count].jmeno_atomu[4]='\0';
      
      atoms[count].alternativni_pozice=buf[16];

      strncpy(atoms[count].jmeno_residua, buf+17 ,3);
      atoms[count].jmeno_residua[3]='\0';
      
      atoms[count].identifikator=buf[21];
      
      strncpy(s, buf+22, 4);
      s[4]='\0';
      sscanf(s, "%d", &atoms[count].poradove_cislo_residua);
      
      atoms[count].kod=buf[26];
      
      strncpy(s, buf+30, 8);
      s[8]='\0';
      sscanf(s, "%lf", &atoms[count].x);
      
      strncpy(s, buf+38, 8);
      s[8]='\0';
      sscanf(s, "%lf", &atoms[count].y);
      
      strncpy(s, buf+46, 8);
      s[8]='\0';
      sscanf(s, "%lf", &atoms[count].z);
      
      strncpy(s, buf+54, 6);
      s[6]='\0';
      p_s=strstr(s,".");
      if (p_s == NULL)
      a=0;
      else if(p_s != NULL)
      {
	a=1;
	sscanf(s,"%lf", &atoms[count].occupancy);
      }
      
      strncpy(s, buf+60, 6);
      s[6]='\0';
      q_s=strstr(s,".");
      if (q_s == NULL)
	b=0;
      else if(q_s != NULL)
      {
	b=1;
	sscanf(s, "%lf", &atoms[count].teplotni_faktor);
      }
      
      strncpy(atoms[count].symbol_prvku, buf+76 ,2);
      atoms[count].symbol_prvku[2]='\0';
      
      strncpy(atoms[count].formalni_naboj, buf+78 ,2);
      atoms[count].formalni_naboj[2]='\0';
      
      count++;
    }
  }
  fclose(f);
  f=NULL;
  return EXIT_SUCCESS;

}

int openg()
{ int i=0;
  int l=0;
  FILE *g=NULL;
  g= fopen("/home/tbouchal/cecko/c/brb.pdb", "w");
  if (g== NULL)
  {
    printf ("Cannot open file4!\n");
    return EXIT_FAILURE;
  }
  l=count-1;
  for (i=0 ;i<=l;i++)
  { if(a==1 && b==1)
    {fprintf(g, "%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f%6.2f%6.2f          %2.2s%2.2s\n",
	     atoms[i].jmeno_zaznamu, atoms[i].poradove_cislo, atoms[i].jmeno_atomu,
	     atoms[i].alternativni_pozice, atoms[i].jmeno_residua, atoms[i].identifikator, 
	     atoms[i].poradove_cislo_residua, atoms[i].kod, atoms[i].x, atoms[i].y, atoms[i].z,
	     atoms[i].occupancy, atoms[i].teplotni_faktor, atoms[i].symbol_prvku, atoms[i].formalni_naboj);
    }
    if(a==0 && b==0)
    {fprintf(g, "%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f                      %2.2s%2.2s\n",
	     atoms[i].jmeno_zaznamu, atoms[i].poradove_cislo, atoms[i].jmeno_atomu,
	     atoms[i].alternativni_pozice, atoms[i].jmeno_residua, atoms[i].identifikator, 
	     atoms[i].poradove_cislo_residua, atoms[i].kod, atoms[i].x, atoms[i].y, atoms[i].z,
	     atoms[i].symbol_prvku, atoms[i].formalni_naboj);
    }
   else if(a==1 && b==0)
    {fprintf(g, "%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f%6.2f                %2.2s%2.2s\n",
	     atoms[i].jmeno_zaznamu, atoms[i].poradove_cislo, atoms[i].jmeno_atomu,
	     atoms[i].alternativni_pozice, atoms[i].jmeno_residua, atoms[i].identifikator, 
	     atoms[i].poradove_cislo_residua, atoms[i].kod, atoms[i].x, atoms[i].y, atoms[i].z,
	     atoms[i].occupancy, atoms[i].symbol_prvku, atoms[i].formalni_naboj);
    }
    else if(a==0 && b==1)
    {fprintf(g, "%-6.6s%5d %-4.4s%c%-3.3s %c%4d%c   %8.3f%8.3f%8.3f      %6.2f          %2.2s%2.2s\n",
	     atoms[i].jmeno_zaznamu, atoms[i].poradove_cislo, atoms[i].jmeno_atomu,
	     atoms[i].alternativni_pozice, atoms[i].jmeno_residua, atoms[i].identifikator, 
	     atoms[i].poradove_cislo_residua, atoms[i].kod, atoms[i].x, atoms[i].y, atoms[i].z,
	     atoms[i].teplotni_faktor, atoms[i].symbol_prvku, atoms[i].formalni_naboj);
    }
  }
  fclose(g);
  g=NULL;
  return EXIT_SUCCESS;

}
int res()
{ int i=0;
  int j=0;
  int l=0;
  l=count-1;
  int aktualni_residuum =-1;
  for (i=0 ;i<=l;i++) 
  {
    if (atoms[i].poradove_cislo_residua != aktualni_residuum)
    { aktualni_residuum = atoms[i].poradove_cislo_residua;
    residue[j].prvni_atom=atoms[i].poradove_cislo;
    residue[j].poradove_cislo_residua=atoms[i].poradove_cislo_residua;
    snprintf(residue[j].jmeno_residua, MAX, atoms[i].jmeno_residua );
    if(aktualni_residuum >1)
    {residue[j].posledni_atom=atoms[i-1].poradove_cislo;}
    j++;
    }
    residues_count=j;
  }
  return EXIT_SUCCESS;
}

void coloring()
{
  int i=0;
  int j=0;
  for(i=0; i<residues_count; i++)
  {
    for(j=0; j<RESD_TYPES_COUNT; j++)
    {
      if(strcmp(residue[i].jmeno_residua, residue_type[j].code3)==0)
      {
        residue[i].restype=j;
      }
    }
  }
  int dev=0, pocet=0, k=0;
  double podil=0;
  double x1, x2, y1, y2;
  char text[2]={'\0'};
  j=0;
  podil=residues_count/30;
  dev = g2_open_X11 (530, 320);
  for(y1=310; y1>=10; y1=y2-10)
  {
    i=0;
    for(x1=10;x1<=490;x1=x2)
    {  
      y2=y1-10;
      x2=x1+480/30;

        g2_pen(dev, g2_ink(dev, residue_type[residue[k].restype].color_r,residue_type[residue[k].restype].color_g,
               residue_type[residue[k].restype].color_b));
        g2_filled_rectangle(dev,x1,y1,x2,y2);
        text[0]=residue_type[residue[k].restype].code1;
        text[1]='\0';
        if(residue_type[residue[k].restype].cislo==11 ||residue_type[residue[k].restype].cislo==10 || residue_type[residue[k].restype].cislo==20)
        {
        g2_pen(dev, 0);
        g2_string(dev, x1, y2, text);
        }
        else
        {
          g2_pen(dev, 1);
          g2_string(dev, x1, y2, text);
        }
        i++;
        k++;
      pocet++;
      if (i==30)
        break;
      
      if (pocet==residues_count)
        break;
      
    }
    j++;
    if(j==podil+1)
      break;
  }

  getchar();
  g2_close(dev);
}

int main()
{ 
  promenne();
  config();
  openf();
  openg();
  res();
  coloring();
  return EXIT_SUCCESS;
}


