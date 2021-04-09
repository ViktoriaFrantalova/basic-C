#include <stdio.h>
#include <string.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>
#define MAXPOLE 100000
#define BUF_SIZE 1000
//program, ktory vypise informacie o crambine do subora

typedef struct
{ //definice struktury residui
  int prvy_atom;
  int posledny_atom;
  int cisloresidua;
  char menoresidua[4];
  int type;
} RESIDUE;
RESIDUE resid[MAXPOLE];
int pocet_resid = 0;

typedef struct
{ // definicia struktury
  char nazovzaznamu[7];
  int cisloatomu;
  char menoatomu[5];
  char alt_loc;
  char chain_id; // identifikator proteinoveho retazca 21
  char i_code;   // kod indikujuci vlozenie residua 26
  double hodnota;
  double tepelny_faktor;
  char menoresidua[4];
  int cisloresidua;
  double x, y, z; // suradnice
  char symbolprvku[3];
  char formal_naboj[3];
} ATOM;

ATOM atoms[MAXPOLE];  //pole struktur
int pocet_atomov = 0; //pocet riadkov suboru

#define RESD_TYPES_COUNT 21
typedef struct
{
  char code3[4]; // three­letter code
  char code1;    // one­letter code
  double color_r;
  double color_g;
  double color_b;
} RESIDUE_TYPE;

// konkretne zadané farbi v suradniciach pre jednotlivé AMK
RESIDUE_TYPE residue_types[RESD_TYPES_COUNT] =
    {
        {"UNK", 'X', 153 / 255.0, 153 / 255.0, 153 / 255.0},
        {"ALA", 'A', 204 / 255.0, 255 / 255.0, 255 / 255.0},
        {"ARG", 'R', 230 / 255.0, 6 / 255.0, 6 / 255.0},
        {"ASN", 'N', 255 / 255.0, 153 / 255.0, 0 / 255.0},
        {"ASP", 'D', 255 / 255.0, 204 / 255.0, 153 / 255.0},
        {"CYS", 'C', 0 / 255.0, 255 / 255.0, 255 / 255.0},
        {"GLN", 'Q', 255 / 255.0, 102 / 255.0, 0 / 255.0},
        {"GLU", 'E', 255 / 255.0, 204 / 255.0, 0 / 255.0},
        {"GLY", 'G', 0 / 255.0, 255 / 255.0, 0 / 255.0},
        {"HIS", 'H', 255 / 255.0, 255 / 255.0, 153 / 255.0},
        {"ILE", 'I', 0 / 255.0, 0 / 255.0, 128 / 255.0},
        {"LEU", 'L', 51 / 255.0, 102 / 255.0, 255 / 255.0},
        {"LYS", 'K', 198 / 255.0, 6 / 255.0, 0 / 255.0},
        {"MET", 'M', 153 / 255.0, 204 / 255.0, 255 / 255.0},
        {"PHE", 'F', 0 / 255.0, 204 / 255.0, 255 / 255.0},
        {"PRO", 'P', 255 / 255.0, 255 / 255.0, 0 / 255.0},
        {"SER", 'S', 204 / 255.0, 255 / 255.0, 153 / 255.0},
        {"THR", 'T', 0 / 255.0, 255 / 255.0, 153 / 255.0},
        {"TRP", 'W', 204 / 255.0, 153 / 255.0, 255 / 255.0},
        {"TYR", 'Y', 204 / 255.0, 255 / 255.0, 204 / 255.0},
        {"VAL", 'V', 0 / 255.0, 0 / 255.0, 255 / 255.0}};

int getType(char *menoresidua)
{ // funkcia
  for (int i = 0; i < RESD_TYPES_COUNT; i++)
  {
    if (strcmp(menoresidua, residue_types[i].code3) == 0)
    {
      return i; // ak sa vráti 0, reťazce sú totožné
    }
  }
  return -1;
}

int residue()
{ //vypise informacie o residuach
  int n = 0;

  for (n = 0; n < pocet_atomov; n++) // pre každý atom
  {
    if (n == 0)
    { // som na prvom riadku
      resid[pocet_resid].cisloresidua = atoms[n].cisloresidua;
      strcpy(resid[pocet_resid].menoresidua, atoms[n].menoresidua);
      resid[pocet_resid].prvy_atom = n;
    }
    else if (resid[pocet_resid].cisloresidua != atoms[n].cisloresidua)
    {
      resid[pocet_resid].posledny_atom = n - 1; //index posledniho atomu
      resid[pocet_resid].type = getType(atoms[n].menoresidua);
      pocet_resid++;

      resid[pocet_resid].cisloresidua = atoms[n].cisloresidua;
      strcpy(resid[pocet_resid].menoresidua, atoms[n].menoresidua);
      resid[pocet_resid].prvy_atom = n;
    }
    else
    {
      resid[pocet_resid].posledny_atom = n; //index posledniho atomu
      resid[pocet_resid].type = getType(atoms[n].menoresidua);
    }
  }
  return 0;
}

int nacitanie(char subor_nacitania[])
{ // otvorenie vstupneho suboru
  char buf[BUF_SIZE] = "";
  char s[30] = "";
  FILE *f = NULL;
  f = fopen(subor_nacitania, "r"); // nacitanie suboru

  if (f == NULL)
  { // kontrola suboru
    printf("Neda sa otvorit subor!\n");
    return 1;
  }

  while (feof(f) == 0)
  {
    if (pocet_atomov >= MAXPOLE)
    { //kontrola velikosti pole
      printf("Male pole!\n");
      break;
    }
    memset(buf, '\0', BUF_SIZE);         // zapise n(BUF_SIZE) znakov c(\0) na miesto urcene ukazovatelom s(buf)
    if (fgets(buf, BUF_SIZE, f) == NULL) // nacita 1 riadok zo suboru f do retazca buf dokial nenarazí na znak koiec riadku/suboru
      break;

    if (strncmp(buf, "ATOM", 4) == 0 || strncmp(buf, "HETATM", 6) == 0)
    {
      strncpy(atoms[pocet_atomov].nazovzaznamu, buf, 6); //nacitanie mena zaznamu, skopiruje dany pocet znakov
      atoms[pocet_atomov].nazovzaznamu[6] = '\0';        // na koniec musime zapisat nulu

      strncpy(s, buf + 6, 5); // nacitanie cisla atomu
      s[5] = '\0';
      sscanf(s, "%d", &atoms[pocet_atomov].cisloatomu);

      strncpy(atoms[pocet_atomov].menoatomu, buf + 12, 4); // nacitanie mena atomu skopiruje 4 znaky od pozicie 12
      atoms[pocet_atomov].menoatomu[4] = '\0';

      atoms[pocet_atomov].alt_loc = buf[16]; //nacitanie alternativnej pozicii

      strncpy(atoms[pocet_atomov].menoresidua, buf + 17, 3); //nacitanie mena residua
      atoms[pocet_atomov].menoresidua[3] = '\0';

      atoms[pocet_atomov].chain_id = buf[21]; // nacitanie identifikatoru proteinu

      strncpy(s, buf + 22, 4); // nacitanie cisla residua
      s[4] = '\0';
      sscanf(s, "%d", &atoms[pocet_atomov].cisloresidua);

      atoms[pocet_atomov].i_code = buf[26]; // nacitanie kodu indikujucu vlozenie residua

      strncpy(s, buf + 30, 8); //nacitanie souradnice x
      s[8] = '\0';
      sscanf(s, "%lf", &atoms[pocet_atomov].x);

      strncpy(s, buf + 38, 8); //nacitanie souradnice y
      s[8] = '\0';
      sscanf(s, "%lf", &atoms[pocet_atomov].y);

      strncpy(s, buf + 46, 8); //nacitanie souradnice z
      s[8] = '\0';
      sscanf(s, "%lf", &atoms[pocet_atomov].z);

      strncpy(s, buf + 54, 6); //nacitanie hodnoty
      s[6] = '\0';
      sscanf(s, "%lf", &atoms[pocet_atomov].hodnota);

      strncpy(s, buf + 60, 6); //nacitanie teplotneho faktoru
      s[6] = '\0';
      sscanf(s, "%lf", &atoms[pocet_atomov].tepelny_faktor);

      strncpy(atoms[pocet_atomov].symbolprvku, buf + 76, 2); //nacitanie symbolu prvku
      atoms[pocet_atomov].symbolprvku[2] = '\0';

      strncpy(atoms[pocet_atomov].formal_naboj, buf + 78, 2); //nacitanie formalneho naboja
      atoms[pocet_atomov].formal_naboj[2] = '\0';

      pocet_atomov++;
    }
  }
  fclose(f);
  return 0;
}

int zapis(char subor_zapisu[])
{ // otvorenie vystupneho suboru a zapis hodnot do suboru
  FILE *fout = NULL;
  int i = 0;
  fout = fopen(subor_zapisu, "w"); // otvori subor pre zapis hodnot

  if (fout == NULL)
  { // kontrola
    printf("Neda sa otvorit subor!\n");
    return 1;
  }

  for (i = 0; i < pocet_atomov; i++)
  {
    fprintf(fout, "%-6.6s %5d %-4.4s %3s %4d %8.3f %8.3f %8.3f %2.2s\n", atoms[i].nazovzaznamu, atoms[i].cisloatomu, atoms[i].menoatomu, atoms[i].menoresidua, atoms[i].cisloresidua, atoms[i].x, atoms[i].y, atoms[i].z, atoms[i].symbolprvku);
  }

  fclose(fout);
  return 0;
}

int kruh()
{ // funkcia na vykreslenie kruhu s počtom residuit
  int win = 0;
  win = g2_open_X11(500, 320); // velkost okna
  g2_set_line_width(win, 15);  // hrubka ciary
  getchar();
  double x = 0.0;

  for (int i = 0; i < pocet_resid; i++)
  {
    g2_pen(win, g2_ink(win, residue_types[resid[i].type].color_r, residue_types[resid[i].type].color_g, residue_types[resid[i].type].color_b));
    g2_arc(win, 150, 150, 120, 120, x, x + 360.0 / pocet_resid);
    x += 360.0 / pocet_resid;
  }
  getchar();
  g2_close(win);
  return 0;
}

int main(int argc, char *argv[])
{ //ziska nazvy suboru ako parametre z prikazoveho radku
  char subor_nacitania[MAXPOLE] = "";
  char subor_zapisu[MAXPOLE] = "";

  if (argc > 1)
  {
    nacitanie(argv[1]);
    zapis(argv[2]);
  }
  else
  { //spyta sa na nazvy suborou, ked nebudu zadane ako parametre
    printf("Zadajte nazov suboru pre nacitanie: \n");
    scanf("%s", subor_nacitania);
    nacitanie(subor_nacitania);
    printf("Zadajte nazov suboru pre zapis: \n");
    scanf("%s", subor_zapisu);
    zapis(subor_zapisu);
  }
  residue();
  kruh();
  return 0;
}
