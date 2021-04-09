#include <stdio.h>
#include <math.h>
#include <stdlib.h> // musím vložiť túto knižnicu kvoli použitiu systemového príkazu system(príkaz)

// program, kt zapíše zoznam čisel od -5 po 10 + odpovedajúce hodnoty na obr.

int main() //vypise zoznam cisel s ich hodnotami
{
  FILE *f = NULL; // premenná typu FILE slúži k identifikácii súboru (f=názov mojej funkcie)
  int i = 0;

  f = fopen("./U4.txt", "w"); // otvorenie funkcie. názov+cesta k súboru
  // W = režim, kt. vytvorý nový súbor a otvorí ho pre zápis

  if (f == NULL) // kontrola
  {
    printf("Neda sa otvorit!\n");
    return 1;
  }

  fprintf(f, "Zoznam cisel a ich hodnoty\n");                       // zápis do funkcie, prvý parameter musí byť názov funkcie
  fprintf(f, "i,      i*i,    i*i*i,   exp(i),  sin(i), cos(i)\n"); // "ku konkrétnemu zadaniu"
  fprintf(f, "--------------------------------------------------\n");

  for (i = -5; i <= 10; i++)
  {
    fprintf(f, "%- 5i %5i %+8i %10.3f %- f %-+1.4f\n", i, i * i, i * i * i, exp(i), sin(i), cos(i));

    // FORMATOVANIE VÝSTUPU
    // %[príznaky][šírka][.presnost][modifikátor]konverzia]

    //Celé číslo, min. 5 zn., zarov. dolava, kladná č. na začiatku s medzerou = %- 5i
    //Celé číslo, min.5 znakov, zarov.doprava = %5i
    //Celé číslo, min.8 znakov, tiskne vždy znamienko + alebo - = %+8i
    //Desatinné číslo, min.10 znakov, 3 desatinné miesta, zarov.doprava = %10.3f
    //Desatinné číslo, zarov.dolava, kladné č.na začiatku s medzerou = %- f
    //Desatinné číslo, 4 desetinné miesta, zarov.dolava, tiskne vždy + alebo - Stlpce su naviac vždy oddelene jednou medzerou= %-+1.4f
  }

  system("code U4.txt"); // vyvolanie príkazu systému, kt. je interpretovaný shell systemom/príkaz sa zapisuje rovnako akoby sme ho písali do terminalu

  return 0;
}