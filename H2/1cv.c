#include <stdio.h>
// program, ktory vypise cisla od 1 po zadanu hodnotu
int main()
{

    int max = 0, value = 1;

    printf("Zadaj maximalnu hodnotu:\n");
    scanf("%i", &max);
    printf("Hodnoty su:");

    while (value <= max)
    {
        printf(" %i, ", value);
        value = value + 1;
    }

    printf("\n");
    return 0;
}
