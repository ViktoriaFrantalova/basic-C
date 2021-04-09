#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

// program, ktory vytvory rozne graficke geometricke tvary a textove polia

int main(int argc, char *argv[])
{
    int i = 0;
    int win = 0;
    int color1 = 0, color2 = 0, color3 = 0, color4 = 0; // cervena farba

    win = g2_open_X11(500, 320); // Otvorime okno o tejto velkosti

    // červené X
    g2_pen(win, 19);              // kreslenie cervenou farbou
    g2_set_line_width(win, 5);    // hrubka čiary
    g2_line(win, 10, 10, 60, 60); // suradnice 1. ciary
    g2_line(win, 60, 10, 10, 60); // suradnice 2. ciary

    // modry stvorec obrys
    g2_pen(win, 3);                     // modra farba
    g2_set_line_width(win, 5);          // hrubka čiary
    g2_rectangle(win, 80, 60, 130, 10); // suradnice obdlznika

    // plny modry storec
    g2_pen(win, 3);
    g2_set_line_width(win, 0);
    g2_filled_rectangle(win, 150, 60, 200, 10); // vyplnený obdlžník

    // zeleny kruh obrys
    g2_pen(win, 7); // zelena farba
    g2_set_line_width(win, 7);
    g2_circle(win, 245, 35, 25); // kruh, suradnice stredu a posledne cislo je polomer r

    // plny zeleny kruh
    g2_pen(win, 7);
    g2_set_line_width(win, 0);
    g2_filled_circle(win, 315, 35, 25); // vyplneny

    // tri kruhove farebne usecky
    g2_set_line_width(win, 5);
    g2_pen(win, 19);                        // cervena farba
    g2_arc(win, 385, 35, 25, 25, 0, 120);   // kruhova vyseč
    g2_pen(win, 3);                         // modra farba
    g2_arc(win, 385, 35, 25, 25, 120, 240); // kruhova vyseč
    g2_pen(win, 25);                        // zlta farba
    g2_arc(win, 385, 35, 25, 25, 240, 360); // kruhova vyseč

    // tri vyplnene kruhove vysece
    g2_set_line_width(win, 0);
    g2_pen(win, 19);                        // cervena farba
    g2_arc(win, 455, 35, 25, 25, 0, 120);   // kruhova vyseč, posledné dve h. počiatočný a koncový uhol
    g2_pen(win, 3);                         // modra farba
    g2_arc(win, 455, 35, 25, 25, 120, 240); // kruhova vyseč
    g2_pen(win, 25);                        // zlta farba
    g2_arc(win, 455, 35, 25, 25, 240, 360); // kruhova vyseč

    // 16 vyplnenych kruhov striedajuce farby
    color1 = g2_ink(win, 1.0, 0.4, 0.35); // intenzita farieb červenej, zelenej, modrej
    color2 = g2_ink(win, 0.5, 0.4, 1.0);
    int x1 = 20;
    int x2 = 50;

    for (i = 0, i < 8, i++)
    {
        g2_pen(win, color1);
        g2_filled_circle(win, x1, 90, 10);
        g2_pen(win, color2);
        g2_filled_circle(win, x2, 90, 10);
        x1 = x1 + 60; // posun po osi x
        x2 = x2 + 60;
    }

    //16 vyplnenych kruznic blebnucej  farby
    float a = 0.0, b = 0.0;
    int j = 0, z = 20;

    for (j = 0; j <= 16; j++)
    {
        g2_pen(win, 1);            // čierna farba
        g2_set_line_width(win, 3); // obrys

        color3 = g2_ink(win, a, b, 1.0); // modrá - funkcia na tienovanie
        // g2_set_line_width(win, 0);
        g2_pen(win, color3); //
        g2_filled_circle(win, z, 130, 10);
        z = z + 30;   // posun po x suradnici
        a = a + 0.07; // lebo max hodnota 1 a chcem 16 kruhov 1/16= 0,0625
        b = b + 0.07;
    }

    //pas s farebnym prechodem
    float c = 1.0;
    int k = 0, d = 10;
    g2_set_line_width(win, 1);

    for (k = 0; k < 480; k++)
    {
        color4 = g2_ink(win, 1.0, c, c);
        g2_pen(win, color4);
        g2_line(win, d, 190, d, 160);
        c = c - 0.0015; // tienovanie
        d = d + 1;      // posun po ose x
    }

    //ciary sbiehajice sa v centre
    g2_pen(win, 19);           // cervena
    g2_set_line_width(win, 1); // nastavenie širky ciary v pixeloch
    for (int i = 0; i < 360, i += 30)
        g2_line(win, 350, 235, 350 + 30.0 * cos(i / 180.0 * 3.144), 235 + 30.0 * sin(i / 180.0 * 3.144));

    //ciary po okrajoch kruznice
    g2_pen(win, 3); // modra farba
    g2_set_line_width(win, 3);
    for (int i = 0; i < 360; i += 30)
    {
        g2_line(win, 430 + 20.0 * cos(i / 180.0 * 3.144), 235 + 20.0 * sin(i / 180.0 * 3.144), 430 + 30.0 * cos(i / 180.0 * 3.144), 235 + 30.0 * sin(i / 180.0 * 3.144));
    }

    //teXtove polia
    g2_pen(win, 1);
    g2_set_font_size(win, 24); // velkost pisma
    g2_string(win, 10, 280, "Tento text je pisany velkostou 24");

    g2_set_font_size(win, 15);
    g2_string(win, 10, 260, "Tento text je pisany velkostou 15");

    g2_set_font_size(win, 12);
    g2_string(win, 10, 245, "Tento text je pisany velkostou 12");

    g2_set_font_size(win, 10);
    g2_string(win, 10, 230, "Tento text je pisany velkostou 10");

    getchar();
    g2_close(win); // Zavrieme okno
    return 0;
}
