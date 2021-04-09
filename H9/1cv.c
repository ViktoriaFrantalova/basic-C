#include <stdio.h>
#include <string.h>
#define MAXPOLE 100000
#define BUF_SIZE 1000
//program, ktory vypise informacie o crambine do subora

typedef struct
{ //definice struktury residui
  int prvy_atom;
  int posledny_atom;
  int cisloresidua;
  char menoresidua[4];
} RESIDUE;
RESIDUE resid[MAXPOLE];

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

ATOM atoms[MAXPOLE]; //pole struktur
int pocet = 0;       //pocet riadkov suboru

int residue()
{ //vypise informacie o residuach
  int n = 0;
  int pocet_resid = 0;

  for (n = 0; n < pocet; n++)
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
      pocet_resid++;                            //nove residuum - zvysuje cislo indexu pro polozky vypisu

      resid[pocet_resid].cisloresidua = atoms[n].cisloresidua;
      strcpy(resid[pocet_resid].menoresidua, atoms[n].menoresidua);
      resid[pocet_resid].prvy_atom = n;
    }
    else
    {
      resid[pocet_resid].posledny_atom = n; //index posledniho atomu
    }
  }
  for (n = 0; n <= pocet_resid; n++)
  {
    printf("Residium: %4d  %-3.3s, indexy atomu: %3d, %3d\n", resid[n].cisloresidua, resid[n].menoresidua, resid[n].prvy_atom, resid[n].posledny_atom);
  }
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
    if (pocet >= MAXPOLE)
    { //kontrola velikosti pole
      printf("Male pole!\n");
      break;
    }
    memset(buf, '\0', BUF_SIZE);         // zapise n(BUF_SIZE) znakov c(\0) na miesto urcene ukazovatelom s(buf)
    if (fgets(buf, BUF_SIZE, f) == NULL) // nacita 1 riadok zo suboru f do retazca buf dokial nenarazí na znak koiec riadku/suboru
      break;

    if (strncmp(buf, "ATOM", 4) == 0 || strncmp(buf, "HETATM", 6) == 0)
    {
      strncpy(atoms[pocet].nazovzaznamu, buf, 6); //nacitanie mena zaznamu, skopiruje dany pocet znakov
      atoms[pocet].nazovzaznamu[6] = '\0';        // na koniec musime zapisat nulu

      strncpy(s, buf + 6, 5); // nacitanie cisla atomu
      s[5] = '\0';
      sscanf(s, "%d", &atoms[pocet].cisloatomu);

      strncpy(atoms[pocet].menoatomu, buf + 12, 4); // nacitanie mena atomu skopiruje 4 znaky od pozicie 12
      atoms[pocet].menoatomu[4] = '\0';

      atoms[pocet].alt_loc = buf[16]; //nacitanie alternativnej pozicii

      strncpy(atoms[pocet].menoresidua, buf + 17, 3); //nacitanie mena residua
      atoms[pocet].menoresidua[3] = '\0';

      atoms[pocet].chain_id = buf[21]; // nacitanie identifikatoru proteinu

      strncpy(s, buf + 22, 4); // nacitanie cisla residua
      s[4] = '\0';
      sscanf(s, "%d", &atoms[pocet].cisloresidua);

      atoms[pocet].i_code = buf[26]; // nacitanie kodu indikujucu vlozenie residua

      strncpy(s, buf + 30, 8); //nacitanie souradnice x
      s[8] = '\0';
      sscanf(s, "%lf", &atoms[pocet].x);

      strncpy(s, buf + 38, 8); //nacitanie souradnice y
      s[8] = '\0';
      sscanf(s, "%lf", &atoms[pocet].y);

      strncpy(s, buf + 46, 8); //nacitanie souradnice z
      s[8] = '\0';
      sscanf(s, "%lf", &atoms[pocet].z);

      strncpy(s, buf + 54, 6); //nacitanie hodnoty
      s[6] = '\0';
      sscanf(s, "%lf", &atoms[pocet].hodnota);

      strncpy(s, buf + 60, 6); //nacitanie teplotneho faktoru
      s[6] = '\0';
      sscanf(s, "%lf", &atoms[pocet].tepelny_faktor);

      strncpy(atoms[pocet].symbolprvku, buf + 76, 2); //nacitanie symbolu prvku
      atoms[pocet].symbolprvku[2] = '\0';

      strncpy(atoms[pocet].formal_naboj, buf + 78, 2); //nacitanie formalneho naboja
      atoms[pocet].formal_naboj[2] = '\0';

      pocet++;
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

  for (i = 0; i < pocet; i++)
  {
    fprintf(fout, "%-6.6s %5d %-4.4s %3s %4d %8.3f %8.3f %8.3f %2.2s\n", atoms[i].nazovzaznamu, atoms[i].cisloatomu, atoms[i].menoatomu, atoms[i].menoresidua, atoms[i].cisloresidua, atoms[i].x, atoms[i].y, atoms[i].z, atoms[i].symbolprvku);
  }

  fclose(fout);
  return 0;
}

int main(int argc, char *argv[])
{ //ziska nazvy suboru ako parametre z prikazoveho riadku
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
  return 0;
}
