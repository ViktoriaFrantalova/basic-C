#include <stdio.h>
#define SIZE 4
// program kt spocita sucin dvoch n-dimenzionalnych vekorov
int main()
{
    int i = 0;
    float va[SIZE] = {0.0};
    float vb[SIZE] = {0.0};
    float vc = 0.0;

    printf("Zadajte %i suradnice prveho vektoru:\n", SIZE);
    for (i = 0; i < SIZE; i++)
        scanf("%f", &va[i]);

    printf("Zadajte %i suradnice druheho vektoru:\n", SIZE);
    for (i = 0; i < SIZE; i++)
        scanf("%f", &vb[i]);

    for (i = 0; i < SIZE; i++)
    {
        vc = vc + (va[i] * vb[i]);
    }

    printf("Skalarny sucin vektorov je: %f \n", vc);
    return 0;
}
