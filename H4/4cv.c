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
    // %[příznaky][šířka][.přesnost][modifikátor]konverze]

    //Celé číslo, min. 5 zn., zarov. doleva, kladná č. na začátku s mezerou = %- 5i
    //Celé číslo, min.5 znaků, zarov.doprava = %5i
    //Celé číslo, min.8 znaků, tiskne vždy znaménko + nebo - = %+8i
    //Desetinné číslo, min.10 znaků, 3 desetinná místa, zarov.doprava = %10.3f
    //Desetinné číslo, zarov.doleva, kladná č.na začátku s mezerou = %- f
    //Desetinné číslo, 4 desetinná místa, zarov.doleva, tiskne vždy + nebo - Sloupce jsou navíc vždy ddělěny jednou mezerou= %-+1.4f
  }

  system("code U4.txt"); // vyvolanie príkazu systému, kt. je interpretovaný shell systemom/príkaz sa zapisuje rovnako akoby sme ho písali do terminalu

  return 0;
}