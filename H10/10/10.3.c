#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <g2.h>
#include <g2_X11.h>
   
int main(int argc, char *argv[])
{ 
  int i = 0;
  int posun = 0;
  int y = 310;
  int x = 10;
  int radek = 1;
  int celkem = 1;
  int dev = 0;
  
  printf("Zadejte celkovy pocet segmentu:\n");
  scanf("%i", &celkem);
  
  printf("Zadejte pocet segmentu na jednom radku:\n");
  scanf("%i", &radek);
  getchar();
  
  dev = g2_open_X11(500, 320);
  g2_set_line_width (dev, 0);
  
  for (i = 0; i < celkem; i++)
  {
    if(i%2 == 0)
    {
      g2_pen(dev, 19);      
    }
    else
    {
      g2_pen(dev, 3);    
    }
    
    g2_filled_rectangle(dev, 10 + (posun * x), y, 20 + (posun * x), y - 10);
    posun++;
    
    if (posun == radek)
    {
       posun = 0;
       y = y - 15;
    }
  }
  
  getchar(); 
  g2_close(dev); 
  return 0; 
  }