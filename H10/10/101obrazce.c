#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

int main(int argc, char *argv[])
  {
    int dev = 0; //otevreni okna:
    dev = g2_open_X11(500, 320);
    g2_set_line_width(dev, 5);
    g2_pen(dev, 19);
    g2_line(dev, 10, 10, 60, 60); //kreslime cary
    g2_line(dev, 60, 10, 10, 60);
    
    //prazdny ctverec
    g2_pen(dev, 3);
    g2_rectangle(dev, 80, 60, 130, 10);
    
    //vyplneny ctverec
    g2_set_line_width(dev, 0);
    g2_pen(dev, 3);
    g2_filled_rectangle(dev, 150, 60, 200, 10);
    
    //prazdny kruh
    g2_set_line_width(dev, 7);
    g2_pen(dev, 7);
    g2_circle(dev, 245, 35, 25);
    
    //vyplneny kruh
    g2_set_line_width(dev, 0);
    g2_pen(dev, 7);
    g2_filled_circle(dev, 315, 35, 25);
    
    //trojbarevny prazdny kruh
    g2_set_line_width(dev, 5);
    g2_pen(dev, 19);
    g2_arc(dev, 385, 35, 25, 25, 0, 120);
    g2_pen(dev, 3);
    g2_arc(dev, 385, 35, 25, 25, 120, 240);
    g2_pen(dev, 25);
    g2_arc(dev, 385, 35, 25, 25, 240, 360);
    
    
    //trojbarevny plny kruh /vysece
    g2_set_line_width(dev, 0);
    g2_pen(dev, 19);
    g2_filled_arc(dev, 455, 35, 25, 25, 0, 120);
    g2_pen(dev, 3);
    g2_filled_arc(dev, 455, 35, 25, 25, 120, 240);
    g2_pen(dev, 25);
    g2_filled_arc(dev, 455, 35, 25, 25, 240, 360);
    
    //stridani dvoubarevnych kolecek
    int color1 = 0;
    int color2 = 0;
    int i = 0;
    int x = 20;
    int y = 50;
    color1 = g2_ink(dev, 1.0, 0.4, 0.35);
    color2 = g2_ink(dev, 0.5, 0.4, 1.0);
    for(i = 0; i<=7; i++)
      {
      g2_pen(dev, color1);
      g2_filled_circle(dev, x, 90, 10);
      g2_pen(dev, color2);
      g2_filled_circle(dev, y, 90, 10);
      x = x+60;
      y = y+60;
      }
      
    //blednuti jednobarevnych kolecek
    int color3 = 0;
    int j = 0;
    int z = 20;
    float a = 0.0;
    float b = 0.0;
    float c = 1.0;
    for(j = 0; j<=16; j++)
      {
      color3 = g2_ink(dev, a, b, c);  
      g2_pen(dev, color3);
      g2_filled_circle(dev, z, 130, 10);
      z = z+30;
      a = a + 0.06;
      b = b + 0.06;
      }
    
    //ztmavovani pruhu
    int color4 = 0;
    int k = 0;
    float u = 1.0;
    float v = 1.0;
    int o = 10;
    int p = 190;
    int q = 10;
    int r = 160;
    for(k = 0; k <=480; k++)
      {
      color4 = g2_ink(dev, 1.0, u, v);
      g2_pen(dev, color4);
      g2_line(dev, o, p, q, r);
      u = u - 0.0015;
      v = v - 0.0015;
      o = o + 1;
      q = q + 1;
      }
      
    //cary sbihajici se v centru - hvezdice
    g2_set_line_width(dev, 1);
    g2_pen(dev, 19);
    int ah = 235;
    int bh = 235;
    int ch = 300;
    int dh = 300;
    int e = 0;
    for(e = 0; e < 13; e++)
      {
      g2_line(dev, ah, bh, ch, dh);
      ah = ah + sin(500);
      bh = bh + sin(500);
      ch = ch + sin(500);
      dh = dh + sin(500); 
      }
      
    //modre paprsky
    int pocet = 0;
    printf("Zadejte pocet segmentu:\n");
    scanf("%i", &pocet);
    
    int dev = 0;
    dev = g2_open_X11(500, 320);
    g2_set_line_width(dev, 15);
    int posunA = 0;
    int posunB = 0;
    int posunC = 30;
    int posunD = 30;
    int i = 0;
    for(i = 0; i <= pocet/2; i++)
    {
      g2_pen(dev, 19);
      g2_arc(dev, 385, 50, 30, 30, posunA, posunB);
      g2_pen(dev, 3);
      g2_arc(dev, 385, 50, 30, 30, posunC, posunD);
      posunA = posunA + 30;
      posunC = posunD + 30;
     }
    
    
    //texty
    g2_pen(dev, 1);
    g2_set_font_size(dev, 24);
    g2_string(dev, 10, 280, "Tento text je napsany velikosti 24");
    
    g2_pen(dev, 1);
    g2_set_font_size(dev, 15);
    g2_string(dev, 10, 260, "Tento text je napsany velikosti 15");
    
    g2_pen(dev, 1);
    g2_set_font_size(dev, 12);
    g2_string(dev, 10, 245, "Tento text je napsany velikosti 12");
    
    g2_pen(dev, 1);
    g2_set_font_size(dev, 10);
    g2_string(dev, 10, 230, "Tento text je napsany velikosti 10");
    
    getchar();
    g2_close(dev);
    return 0; 
  }
  
  