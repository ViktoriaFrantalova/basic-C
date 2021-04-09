#include <stdlib.h>
#include <stdio.h>
#include <g2.h>
#include <g2_X11.h>

int main(int argc, char *argv[])
{
  int i = 0;
  int dev = 0;
  int color1 = 0, color2 = 0, color3 = 0, color4 = 0;

  dev = g2_open_X11(500, 320); //otevre okno o velikosti 500x320

  //zkrizene cary
  g2_pen(dev, 19); //barva
  g2_set_line_width(dev, 5); //tloustka
  g2_line(dev, 10, 10, 60, 60); //souradnice
  g2_line(dev, 60, 10, 10, 60);

   //ctverec
  g2_pen(dev, 3);
  g2_rectangle(dev, 80, 60, 130, 10);

  //vyplneny ctverec
  g2_pen(dev, 3);
  g2_set_line_width(dev, 0);
  g2_filled_rectangle(dev, 150, 60, 200, 10);

  //kruznice
  g2_pen(dev, 7);
  g2_set_line_width(dev, 7);
  g2_circle(dev, 245, 35, 25);

  //vyplnena kruznice
  g2_set_line_width(dev, 0);
  g2_filled_circle(dev, 315, 35, 25);

  //kruhove usece
  g2_set_line_width(dev, 5);
  g2_pen(dev, 19); //cervena
  g2_arc(dev, 385, 35, 25, 25, 0, 120);
  g2_pen(dev, 3); //modra
  g2_arc(dev, 385, 35, 25, 25, 120, 240);
  g2_pen(dev, 25); //zluta
  g2_arc(dev, 385, 35, 25, 25, 240, 360);
  
  //vyplnene kruhove usece
  g2_set_line_width(dev, 0);
  g2_pen(dev, 19); //cervena
  g2_filled_arc(dev, 455, 35, 25, 25, 0, 120);
  g2_pen(dev, 3); //modra
  g2_filled_arc(dev, 455, 35, 25, 25, 120, 240);
  g2_pen(dev, 25); //zluta
  g2_filled_arc(dev, 455, 35, 25, 25, 240, 360);

  //vyplnene kruznice se stridajicimi se barvami
  color1 = g2_ink(dev, 1.0, 0.4, 0.35);
  color2 = g2_ink(dev, 0.5, 0.4, 1.0);
  int x1 = 20;
  int x2 = 50;

  for(i = 0; i <= 7; i++)
  {
    g2_pen(dev, color1);
    g2_filled_circle(dev, x1, 90, 10);
    g2_pen(dev, color2);
    g2_filled_circle(dev, x2, 90, 10);
    x1 = x1 + 60;
    x2 = x2 + 60;
  }

  //vyplnene kruznice s menicimi se barvami od modre po bilou
  float a = 0.0, b = 0.0;
  int j = 0, z = 20;

  for(j = 0; j < 16; j++)
  {
    g2_pen(dev, 1);
    g2_set_line_width(dev, 3);
    g2_circle(dev, z, 130, 10);
    color3 = g2_ink(dev, a, b, 1.0);
    g2_set_line_width(dev, 0);
    g2_pen(dev, color3);
    g2_filled_circle(dev, z, 130, 10);
    z = z + 30;
    a = a + 0.07;
    b = b + 0.07;
  }

  //pruh s barevnym prechodem
  int k = 0;
  float u = 1.0, v = 1.0;
  int o = 10, q = 10;
  g2_set_line_width(dev, 1);

  for(k = 0; k <= 480; k++)
    {
      color4 = g2_ink(dev, 1.0, u, v);
      g2_pen(dev, color4);
      g2_line(dev, o, 190, q, 160);
      u = u - 0.0015;
      v = v - 0.0015;
      o = o + 1;
      q = q + 1;
    }

  //cary sbihajici se v centru
  int n = 0, p = 350, r = 265, q = 30; 
  g2_pen(dev, 19);
  g2_set_line_width(dev, 1);

  for(n = 0; n <= 12; n++)
    {
      g2_line(dev, 350, 235, p, r);
      p = p + sin(0.5235); //+15
      r = q - cos(0.5235); //-4
    }

  //cary po okrajich kruznice
  


  //text
  g2_pen(dev, 1);
  g2_set_font_size(dev, 24);
  g2_string(dev, 10, 280, "Tento text je napsany velikosti 24");

  g2_set_font_size(dev, 15);
  g2_string(dev, 10, 260, "Tento text je napsany velikosti 15");

  g2_set_font_size(dev, 12);
  g2_string(dev, 10, 245, "Tento text je napsany velikosti 12");

  g2_set_font_size(dev, 10);
  g2_string(dev, 10, 230, "Tento text je napsany velikosti 10");

  getchar();
  g2_close(dev); //zavre okno
  return 0;
}
