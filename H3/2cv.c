#include <stdio.h>
// program, ktory po zadani dvoch 3-dimenzionalnom vektorov vypíše ich sučin
int main()
{
  float va[3] = {0.0, 0.0, 0.0};
  float vb[3] = {0.0, 0.0, 0.0};
  float vc[3] = {0.0, 0.0, 0.0};

  printf("Zadajte prvy vektor:\n");
  scanf("%f %f %f", &va[0], &va[1], &va[2]);

  printf("Zadajte druhy vektor:\n");
  scanf("%f %f %f", &vb[0], &vb[1], &vb[2]);

  vc[0] = va[1] * vb[2] - va[2] * vb[1];
  vc[1] = va[2] * vb[0] - va[0] * vb[2];
  vc[2] = va[0] * vb[1] - va[1] * vb[0];

  printf("Sucin vektorov je:  %f, %f, %f\n", vc[0], vc[1], vc[2]);

  return 0;
}
