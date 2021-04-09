#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//vypise cisla a ich mocniny + zobrazi graf mocnin
// program, kt. do súboru zapíše zoznam čísel 1-20 a ich druhé mocniny tak, že na každom riadku bude číslo a za ním jeho druhá mocnina
// + vytvorý súbor s príkazom pre gnuplot, zavolá gnuplot a zobrazí sa graf mocnin

int main()
{
  int i = 0, moc = 0;
  FILE *f = NULL, *fgnuplot = NULL;

  f = fopen("U5.txt", "w"); //vytvori soubor v mocninami

  if (f == NULL)
  {
    printf("Nedá sa otvoriť!\n");
    return 1;
  }

  for (i = 1; i <= 20; i++)
  {
    moc = i * i;
    fprintf(f, "%i %i\n", i, moc); //vypise cislo a jeho mocninu
  }

  fclose(f); //ukončenie používania súboru sa ukončí touto funkciou

  fgnuplot = fopen("gnuplot.cmd", "w"); //vytvori soubor v gnuplote
  if (fgnuplot == NULL)
  {
    printf("Nedá sa otvoriť!\n");
    return 1;
  }

  fprintf(fgnuplot, "plot \"mocniny.dat\" using 1:2\npause -1 \"Hit return\"\n"); //príkázy pre gnuplot

  fclose(fgnuplot);              //zavrie súbor príkazov pre gnuplot
  system("gnuplot gnuplot.cmd"); //zavola gnuplot a zobrazi graf

  return 0;
}