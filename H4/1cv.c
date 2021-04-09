#include <stdio.h>
// program, kt načíta od uživateľa text, program vypíše počet znakov, potom vypíše časť zadaného textu počnúcť 6. znakom a následne prvých 5 znakov (napr. kočkopes najprv "pes" potom "kočko")
int main()
{
  int i;              // Počet znakov v reťazci
  char str[20] = " "; // Prázdny reťazec

  printf("Napis nejake slovo: %s\n", str);
  scanf("%19s", &str); // lebo posledný znak je \0

  for (i = 0; str[i] != '\0'; i++) // cyklus zisteniu počtu znakov v reťazci
    printf("Pocet znakov v retazci je: %i\n", i);
  printf("%s\n", str + 5); // vypíše slovo až od 6 znaku

  str[5] = '\0';       // po 5 znaku to ukončí
  printf("%s\n", str); // vypíše prvých 5 znakov

  return 0;
}