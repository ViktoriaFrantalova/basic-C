#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

int main(int argc, char *argv[])
  {
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
     
    getchar();
    g2_close(dev);
    return 0; 
  }