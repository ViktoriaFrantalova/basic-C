#include <stdio.h> // základná knižnica
#include <math.h>  // matematická knižnica
// program na riesenie kvadratickej rovnice
int main()
{ // určím si jednotlive parametre
    float a = 0.0, b = 0.0, c = 0.0;
    float discr = 0.0;
    float d = 0.0, e = 0.0;

    printf("Zadaj hodnity a, b, c oddelene medzerou: \n"); // spýtam sa na hodnoty parametra
    scanf("%f %f %f", &a, &b, &c); // načítanie zadanej hodnoty

    if (a == 0) // podmieka, ak parameter A patrí nule
    {
        printf("Koeficient a musi byt rozny od nuly. \n");  // potom vypíše hlášku
        return 0;                                          // predčasné ukončenie programu
    }

    discr = b * b - 4 * a * c; // vypočíta sa diskriminat podľa matematickej rovnice

    if (discr < 0) // podmienka, ak D je menší ako 0
    {
        printf("Diskriminat nema riesenie v obore realnych cisel. \n"); // potom vypíše hlášku
    }

    else if (discr == 0) // alebo ak D patrí nula
    {
        d = e = -b / (2 * a); // matimaticky výpočet pre jeden koreň
        printf("Diskriminat ma jeden koren %f\n", d); // potom sa vypíše hláška s jednym koreňom
    }
    else if (discr > 0) // alebo ak D je menšie ako nula
    {                   // matematicky výpočet oboch koreňou
        d = (-b + sqrt(discr)) / (2 * a);
        e = (-b - sqrt(discr)) / (2 * a);
        printf("Diskriminat ma dva korene, prvy je %f a druhy je %f\n", d, e); // potom sa vypiše hláška s oboma hodnotami koreňou
    }
    return 0; // koniec programu
}
