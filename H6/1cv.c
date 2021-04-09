#include <stdio.h>

// program, ktory po zadani dvoch 3-dimenzionalnom vektorov vypíše ich sučin
// pre reprezentáciu vektorov použijeme štruktúry

int main()
{
  typedef struct
  { // struktúry slúžia ku zoskúpeniu niekoľkých premenných rôznych typov
    float x;
    float y;
    float z;
  } VECTOR_3D;
  // inicializácia vektorov
  VECTOR_3D v1 = {0.0, 0.0, 0.0};
  VECTOR_3D v2 = {0.0, 0.0, 0.0};
  VECTOR_3D vsuc = {0.0, 0.0, 0.0};

  printf("Zadajte suradnice 1. vektoru: ");
  scanf("%f %f %f", &v1.x, &v1.y, &v1.z);

  printf("Zadajte suradnice 2. vektoru: ");
  scanf("%f %f %f", &v2.x, &v2.y, &v2.z);
  // k jednotlivým premenným pristupuje cez bodku
  //jméno_struktury.jméno_proměnné
  vsuc.x = v1.y * v2.z - v1.z * v2.y;
  vsuc.y = v1.z * v2.x - v1.x * v2.z;
  vsuc.z = v1.x * v2.y - v1.y * v2.x;

  printf("Sucin vektorov je: %f, %f, %f\n", vsuc.x, vsuc.y, vsuc.z);

  return 0;
}