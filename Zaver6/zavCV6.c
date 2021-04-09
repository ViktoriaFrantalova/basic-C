/* Viktória Galliková, jar 2019
-----------------------------------------------------
program, ktorý spočítá vzdialenosti C-alfa uhlíkových
atomov residuí od centra molekuly a naviac načita z PDB
suboru informacie o sekundárnej strukture (alfa-šroubovicích a beta-listech). Potom zobrazí graf reprezentující vzdálenost Calfa atomov od centra s vyznačením alfa-helixom a beta-listu */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>
#define MAXPOLE 100000
#define BUF_SIZE 1000

typedef struct
{ //definicia struktury residui
  int prvy_atom;
  int posledny_atom;
  int cisloresidua;
  char menoresidua[4];
  int type;
  int ca;
  double distance;
  int motivType;
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

double stred_x = 0.0;
double stred_y = 0.0;
double stred_z = 0.0;

typedef struct
{
  int first_residue;
  int last_residue;
  int type;
} SECONDARY_MOTIV;

SECONDARY_MOTIV motiv[MAXPOLE];
int pocet_motiv = 0;

#define RESD_TYPES_COUNT 21
typedef struct
{
  char code3[4]; // three­letter code
  char code1;    // one­letter code
  double color_r;
  double color_g;
  double color_b;
} RESIDUE_TYPE;

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

void getMotiv()
{
  for (int i = 0; i <= pocet_resid; i++) // pre kazde resid
  {
    for (int j = 0; j < pocet_motiv; j++) // kazdeho motivu
    {
      if (motiv[j].first_residue <= resid[i].cisloresidua && motiv[j].last_residue >= resid[i].cisloresidua)
      {                                     // ci nemam cislo medzi first a last vratane
        resid[i].motivType = motiv[j].type; // ak ano uloz typ inak nic
      }
    }
  }
}

int getType(char *menoresidua) // nastavuje typ podla mena pre farby
{
  for (int i = 0; i < RESD_TYPES_COUNT; i++) // prechadza vsetky typy a ten tkory je spravny ulozi
  {
    if (strcmp(menoresidua, residue_types[i].code3) == 0)
    {
      return i;
    }
  }
  return -1;
}

double distance(RESIDUE resid)
{
  return sqrt(pow(stred_x - atoms[resid.ca].x, 2) + pow(stred_y - atoms[resid.ca].y, 2) + pow(stred_z - atoms[resid.ca].z, 2)); // vzdialenost dvoch bodov v 3d
}

void center() // vypocita tazisko celeho proteinu
{
  int g = 0;
  int q = 0;
  double sucet_x = 0;
  double sucet_y = 0;
  double sucet_z = 0;
  int pocet = 0;
  for (g = 0; g <= pocet_resid; g++)
  {
    for (q = resid[g].prvy_atom; q <= resid[g].posledny_atom; q++)
    {
      sucet_x += atoms[q].x;
      sucet_y += atoms[q].y;
      sucet_z += atoms[q].z;
      pocet++;
    }
  }
  stred_x = sucet_x / pocet;
  stred_y = sucet_y / pocet;
  stred_z = sucet_z / pocet;
}

void caGet() // nastavi vsetkym residuam ich alfa uhlik
{
  for (int i = 0; i <= pocet_resid; i++) // pre kazde resid...
  {
    for (int j = resid[i].prvy_atom; j <= resid[i].posledny_atom; j++) // ...pre kazdy jeho atom...
    {
      if (strcmp(" CA ", atoms[j].menoatomu) == 0) // ..najdi alfa...
      {
        resid[i].ca = j; // ...a uloz
      }
    }
  }
}

void distanceGet() // nastavi kazdemu residuu jeho vzdialenost od taziska
{
  for (int i = 0; i <= pocet_resid; i++) // pre kazdy resid
  {
    resid[i].distance = distance(resid[i]);
  }
}

int residue()
{ //vypise informacie o residuach
  int n = 0;

  for (n = 0; n < pocet_atomov; n++)
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
      resid[pocet_resid].motivType = 0; // ked vytvoris resid tak nema motiv
      pocet_resid++;

      resid[pocet_resid].cisloresidua = atoms[n].cisloresidua;
      strcpy(resid[pocet_resid].menoresidua, atoms[n].menoresidua);
      resid[pocet_resid].prvy_atom = n;
    }
    else
    {
      resid[pocet_resid].posledny_atom = n; //index posledniho atomu
      resid[pocet_resid].type = getType(atoms[n].menoresidua);
      resid[pocet_resid].motivType = 0; // ked vytvoris resid tak nema motiv
    }
  }
  center();      // tazisko
  caGet();       // uhliky
  distanceGet(); // vzdialenosti
  getMotiv();    // nastavi motivy
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

    if (strncmp(buf, "ATOM", 4) == 0)
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

    if (strncmp(buf, "HELIX", 5) == 0) // najdem HELIX
    {                                  // vytvaram novy motiv
      motiv[pocet_motiv].type = 1;     // typ helix
      strncpy(s, buf + 22, 4);         // podla navodu cast riadku s prvym residuom
      s[4] = '\0';
      sscanf(s, "%d", &motiv[pocet_motiv].first_residue);

      strncpy(s, buf + 34, 4); // podla navodu cast riadku s poslednym residuom
      s[4] = '\0';
      sscanf(s, "%d", &motiv[pocet_motiv].last_residue);
      pocet_motiv++; // zvys pocet motivov
    }

    if (strncmp(buf, "SHEET", 5) == 0) // najdem SHEET
    {                                  // rovnako ako HELIX
      motiv[pocet_motiv].type = 2;
      strncpy(s, buf + 23, 4);
      s[4] = '\0';
      sscanf(s, "%d", &motiv[pocet_motiv].first_residue);

      strncpy(s, buf + 34, 4);
      s[4] = '\0';
      sscanf(s, "%d", &motiv[pocet_motiv].last_residue);
      pocet_motiv++;
    }
  }
  fclose(f);
  return 0;
}

double getMaxDistance() // zisti najvacsiu vzdialenost od taziska
{
  double m = resid[0].distance;          // max je prva
  for (int i = 0; i <= pocet_resid; i++) // pre kazdy resid
  {
    if (m < resid[i].distance) // ak je max mensia ako aktualna
    {
      m = resid[i].distance; // nastav max na aktualnu
    }
  }
  return m; // vrat max
}

int vypvzdialenost(double dis, double max)
{
  return (-175 / max * dis + 175); // linerna funkcia pre tvorenie krivky
  // 175 pretoze to je velkost tabulky
}

void kresli(char *subor) // vykreslenie funkci
{
  int dev = 0;
  int sirka = 1500;
  int vyska = 1000;
  double maxDistance = getMaxDistance();

  dev = g2_open_X11(sirka, vyska);
  g2_set_line_width(dev, 0);

  // nadpis
  g2_pen(dev, 1);            // čierna
  g2_set_font_size(dev, 25); // veľkosť
  g2_string(dev, 25, vyska - 25, "Vzdialenosť C-alfa atomu residui od ťažiska s vyznačenými sekundarnými motívmi.");

  // aHelixy
  g2_pen(dev, g2_ink(dev, 1.0, 0.4, 0.35)); // slabo cervena
  g2_filled_rectangle(dev, 75, vyska - 400, 175, vyska - 425);
  g2_pen(dev, 1);
  g2_string(dev, 200, vyska - 425, "Alfa helixy");

  //B listy
  g2_pen(dev, g2_ink(dev, 0.5, 0.4, 1.0)); // slabo modra
  g2_filled_rectangle(dev, 375, vyska - 400, 475, vyska - 425);
  g2_pen(dev, 1);
  g2_string(dev, 500, vyska - 425, "Beta listy");

  g2_pen(dev, g2_ink(dev, residue_types[0].color_r, residue_types[0].color_g, residue_types[0].color_b));
  g2_filled_rectangle(dev, 75, vyska - 475, 150, vyska - 500);
  g2_pen(dev, 1);
  g2_string(dev, 175, vyska - 500, residue_types[0].code3);

  // legenda
  int horiskok = 200; // horizontalny po ose x
  int verskok = 0;    // 37, vertikálny po ose y
  for (int i = 1; i < RESD_TYPES_COUNT; i++)
  {
    g2_pen(dev, g2_ink(dev, residue_types[i].color_r, residue_types[i].color_g, residue_types[i].color_b)); // intenzita farieb červenej, zelenej, modrej

    g2_filled_rectangle(dev, 75 + horiskok * ((i - 1) % 5), vyska - (512 + verskok), 150 + horiskok * ((i - 1) % 5), vyska - (537 + verskok));

    g2_pen(dev, 1);
    g2_string(dev, 175 + horiskok * ((i - 1) % 5), vyska - (537 + verskok), residue_types[i].code3);

    if (i != 1 && ((i - 1) % 5) == 4)
    {
      verskok += 37;
    }
  }

  char retazec[MAXPOLE] = "";
  sprintf(retazec, "%.1f", maxDistance);
  g2_pen(dev, 1);
  g2_string(dev, 25, vyska - 75, retazec);
  g2_string(dev, 25, vyska - 275, "0.0");

  double posun = (sirka - 150) / (pocet_resid + 1);
  for (int i = 0; i <= pocet_resid; i++)
  {
    switch (resid[i].motivType)
    {
    case 0:
      g2_pen(dev, 0);
      break;
    case 1:
      g2_pen(dev, g2_ink(dev, 1.0, 0.4, 0.35));
      break;
    case 2:
      g2_pen(dev, g2_ink(dev, 0.5, 0.4, 1.0));
      break;
    }
    g2_filled_rectangle(dev, 75 + i * posun, vyska - 75, 75 + posun * (i + 1), vyska - 250);
    g2_pen(dev, g2_ink(dev, residue_types[resid[i].type].color_r, residue_types[resid[i].type].color_g, residue_types[resid[i].type].color_b));
    g2_filled_rectangle(dev, 75 + i * posun, vyska - 255, 75 + posun * (i + 1), vyska - 280);

    // vykreslenie škály. každá 5. pika
    if (i % 5 == 0)
    {
      g2_pen(dev, 1);
      g2_line(dev, 83 + i * posun, vyska - 275, 83 + i * posun, vyska - 285);
      if (i % 10 == 0)
      {
        retazec[0] = '\0';
        sprintf(retazec, "%d", i);
        g2_string(dev, 75 + i * posun, vyska - 310, retazec);
      }
    }
  }
  // vykreslenie krivky
  g2_set_line_width(dev, 2);
  g2_pen(dev, 7); // zelena
  for (int i = 0; i < pocet_resid; i++)
  {
    g2_line(dev, 75 + i * posun, vyska - (75 + vypvzdialenost(resid[i].distance, maxDistance)), 75 + posun * (i + 1), vyska - (75 + vypvzdialenost(resid[i + 1].distance, maxDistance)));
  }

  g2_pen(dev, 1);
  g2_set_line_width(dev, 5);
  g2_rectangle(dev, 75, vyska - 75, 75 + posun * (pocet_resid + 1), vyska - 250);
  g2_set_line_width(dev, 1);
  // vypis názvuxpoužitého suboru
  g2_pen(dev, 1);
  retazec[0] = '\0';
  strcpy(retazec, "PDB soubor: ");
  strcat(retazec, subor);
  g2_string(dev, 25, 50, retazec);
  getchar();
  g2_close(dev);
}

int main(int argc, char *argv[])
{ //ziska nazvy suboru ako parametre z prikazoveho radku
  if (argc != 2)
  {
    printf("Zly pocet parametrov!\n");
    return 1;
  }
  nacitanie(argv[1]);
  residue();
  kresli(argv[1]);
  return 0;
}
