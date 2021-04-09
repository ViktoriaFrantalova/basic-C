#include <stdio.h>
#define SIZE 3
// nedokončeny program, ktorý vynásobí 2 matice o 3 riadkoch a 3 stlpcoxh
int main()
{
    int i = 0;
    int j = 0;
    float ma[SIZE][SIZE][SIZE] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    float mb[SIZE][SIZE][SIZE] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    float mc[SIZE][SIZE][SIZE] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};

    printf("Zadajte prvy riadok prvej matice:\n");
    scanf("%f %f %f", &ma[0], &ma[1], &ma[2]);

    printf("Zadajte druhy riadok prvej matice:\n");
    scanf("%f %f %f", &ma[0], &ma[1], &ma[2]);

    printf("Zadajte treti riadok prvej matice:\n");
    scanf("%f %f %f", &ma[0], &ma[1], &ma[2]);

    printf("Zadajte prvy riadok druhej matice:\n");
    scanf("%f %f %f", &mb[0], &mb[1], &mb[2]);

    printf("Zadajte druhy riadok druhej matice:\n");
    scanf("%f %f %f", &mb[0], &mb[1], &mb[2]);

    printf("Zadajte treti riadok druhej matice:\n");
    scanf("%f %f %f", &mb[0], &mb[1], &mb[2]);

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            mc[i] = ma[0] * mb[0] + ma[1] * mb[] * mb[i] * [j]
        }
    }

    printf("Sucin dvoch matic je: ");
    for (i = 0; i < SIZE; i++)
    {
        printf("%f, ", mc[i][j]);

        printf("\n");
        return 0;
    }
}
