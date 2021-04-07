#include <stdio.h>
// program na scitanie cisel
int main()
{
  int n; //pocet zadanych cisel
  float a = 0.0, b = 0.0, c = 0.0, d = 0.0, e = 0.0;
  float suma = 0.0;

  printf("Zadaj pocet zadanych cisel (max 5): $i\n");
  scanf("%i", &n);

  if ((n < 2) || (n > 5))
  {
    printf("Pocet zadanych cisel musi byt v intervale <2,5>. \n");
    return 0;
  }

  if (n == 2)
  {
    suma = a + b;
    printf("suma dvoch cisel je: %f \n", suma);
  }

  if (n == 3)
  {
    suma = a + b + c;
    printf("suma troch cisel je: %f \n", suma);
  }

  if (n == 4)
  {
    suma = a + b + c + d;
    printf("suma styroch cisel je: %f \n", suma);
  }

  if (n == 5)
  {
    suma = a + b + c + d + e;
    printf("suma piatich cisel je: %f \n", suma);
  }
  return 0;
}
