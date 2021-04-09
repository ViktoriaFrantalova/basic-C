#include <stdio.h>

// funkcia na zmenu hodnot dvoch celociselnych premennych

void hod_zmena(int *p_a, int *p_b)
{ // funkcia ukazvatelov
    int temp = 0;
    temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;
    // zamena hodnot
}

int main()
{
    int a = 0, b = 0;
    printf("Zadaj hodnoty a, b oddelene medzerou: \n"); // zadanie premennych
    scanf("%d %d", &a, &b);                             // nacitanie premennych

    hod_zmena(&a, &b); // volanie funkcie

    printf("Zmena hodnot: a sa teraz = %i a b sa = %i", a, b); // vypis
    return 0;
}
