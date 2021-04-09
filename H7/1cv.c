#include <stdio.h>
#include <math.h>

// riesenie kvadratickej rovnice pomocou funkcii a ukazovatelov

int kvadr_rovnica(float a, float b, float c, float *p_d, float *p_e)
{ // ukazovatele ako parametry
    // *p_d - dereferečný operátor, kt uvádzame pred názov ukazovatela prem. aby sme zistili obsah premennej nachádzajucej na adrese uloženú v ukazovateli
    float discr = 0.0;
    discr = b * b - 4 * a * c;

    if (discr < 0)
    {
        return 0;
    }

    else if (discr == 0)
    {
        *p_d = *p_e = -b / (2 * a);
        return 1; // existuje jeden koren
    }
    else if (discr > 0)
    {
        *p_d = (-b + sqrt(discr)) / (2 * a);
        *p_e = (-b - sqrt(discr)) / (2 * a);
        return 2; // navratova hodnota ak exsituju 2 korene
    }
}

int main()
{
    float a = 0.0, b = 0.0, c = 0.0;
    float discr = 0.0;
    float d = 0.0, e = 0.0;
    int n = 0; // pocet korenov

    printf("Zadaj hodnity a, b, c oddelene medzerou: \n");
    scanf("%f %f %f", &a, &b, &c);

    if (a == 0)
    {
        printf("Koeficient a musi byt rozny od nuly. \n");
        return 0;
    }

    n = kvadr_rovnica(a, b, c, &d, &e); // retenčný operátor & uvádzame pred názov premennej kt. adresu chceme zistiť

    if (n == 0)
    {
        printf("Rovnica nema riesenie v obore realnych cisel. \n");
    }

    else if (n == 1)
    {
        printf("Diskriminat ma jeden koren %f\n", d);
    }
    else if (n == 2)
    {
        printf("Diskriminat ma dva korene, prvy je %f a druhy je %f\n", d, e);
    }
    return 0;
}
