#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

// program na vykreslenie kruhu so striedajúcimi sa modrými a červenými segmentmi(obdlžniky)

int main(int argc, char *argv[])
{
    int pocet = 0;
    int win = 0, i = 0;
    double x = 0.0;

    printf("Zadajte pocet segmentov: \n");
    scanf("%i", &pocet); // nacitanie hodnoty
    getchar();           // cakanie na vstup

    win = g2_open_X11(500, 320); // velkost okna
    g2_set_line_width(win, 15);  // hrubka ciary

    for (i = 0; i <= pocet; i++)
    {
        if (i % 2 == 0)
        {                   // ak je parne čislo modulo znamená zvyšok po delení
            g2_pen(win, 3); // modry
        }
        else
        {
            g2_pen(win, 19); // cerveny
        }
        x = 360 / pocet;
        g2_arc(win, 150, 150, 120, 120, (i - 1) * x, i * x);
    }
    getchar();
    g2_close(win); //zavretie okna
    return 0;
}