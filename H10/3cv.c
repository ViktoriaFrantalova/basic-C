#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

// program, ktorý nakresli segmenty so striedajucou sa modrou a červenou farbou a celkový počet segmentov bude špecifikovaný N a v 1 riedku ich bude 30

int main(int argc, char *argv[])
{
    int i = 0;
    int posun = 0;
    int x = 10, y = 310;
    int riadok = 1;
    int spolu = 1;
    int win = 0;

    printf("Zadajte celkovy pocet segmentov: \n");
    scanf("%i", &spolu); // nacitanie hodnoty

    printf("Zadajte pocet segmentov na jednom riadku:\n");
    scanf("%i", &riadok); // nacitanie hodnoty
    getchar();

    win = g2_open_X11(500, 320); // velkost okna
    g2_set_line_width(win, 0);   // hrubka ciary

    for (i = 0; i <= spolu; i++)
    {
        if (i % 2 == 0)
        {                    // ak je parne
            g2_pen(win, 19); // cerveny
        }
        else
        {
            g2_pen(win, 3); // modry
        }

        g2_filled_rectangle(win, 10 + (posun * x), y, 20 + (posun * x), y - 10);
        posun++;

        if (posun == riadok)
        {
            posun = 0;
            y = y - 15;
        }
    }
    getchar();
    g2_close(win);
    return 0;
}