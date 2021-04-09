#include <stdio.h>
// program, kt načíta od uživateľa jedno slovo a vypíše ho od zadu
int main()
{
    int j = 0;           // pomocna premenna
    int i = 0;           // Počet znakov v prvom reťazci
    char str1[20] = " "; // prvý reťazec
    char str2[20] = " "; // druhý pomocný reťazec

    printf("Napis nejake slovo: ");
    scanf("%19s", str1);

    for (i = 0; str1[i] != '\0'; i++) // cyklus zisteniu počtu znakov v reťazci

        for (j = 0; j <= i; j++)
        { // cyklus priradujuci znaky pola
            str2[j] = str1[i - j];
        }
    str2[i + 1] = '\0';
    printf("Vase slovo obratene je: %s\n", str2);

    return 0;
}