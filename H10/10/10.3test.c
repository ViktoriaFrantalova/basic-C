#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>

int main(int argc, char *argv[])
  {
    int dev = 0;
    int i = 1;
    int j = 0;
    int y = 490;
    int x = 10;
    int pocet = 1, radek = 1;
    printf("Zadejte celkovy pocet segmentu:\n");
    scanf("%i", &pocet);    
    
    printf("Zadejte pocet segmentu na jednom radku:\n");
    scanf("%i", &radek);
    getchar();
    
    dev = g2_open_X11(500, 320);
    
    g2_set_line_width(dev, 0);
    
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
      g2_filled_rectangle(dev, 10 + (j * x), y, 20 + (j * x), y - 10);
    
      j++;
      if (j == radek)
      {
       j = 0;
       y = y - 15;
      }
     }
    getchar();
    g2_close(dev);
return 0; 
  }