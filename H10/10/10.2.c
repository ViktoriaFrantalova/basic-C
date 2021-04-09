#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

int main(int argc, char *argv[])
  {
    int pocet = 0;
    printf("Zadejte pocet segmentu:\n"); //ziskani poctu segmentu
    scanf("%i", &pocet);
    getchar();
    
    int dev = 0;
    dev = g2_open_X11(500, 320);
    
    double x = 0.0;
    int i = 0;
    
    g2_set_line_width(dev, 15);
    
    for(i = 0; i <= pocet; i++)
    {
      if(i%2 == 0)
      {
	g2_pen(dev, 3);
      }
      else
      {
	g2_pen(dev, 19);
      }
      x = 360/pocet;     
      g2_arc(dev, 150, 150, 120, 120,(i-1)*x, i*x);
     }
     
    getchar();
    g2_close(dev);
    return 0; 
  }