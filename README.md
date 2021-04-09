# basic-C
Jazyk C je široko používaný pre tvorbu operačného systému, aplikačných programov, počítačových hier, programovovanie elektrických zariadení.
Tento jazyk patrí medzi tzv `kompilovacie jazyky`, t. j. po vytvorení súboru so zdrojovým kódom programu v C musíme spustiť `prekladač (kompilátor)`, kt. vygeneruje súbor so spustiteľním kódom

Zo syntaxi jazyka C vychádza C++, Java, C#, JavaScript, PHP C shell...

**Výhody:**
- vysoká výpočetná rýchlosť a pamaťová efektivita programu
možnosť nízkoúrovňových operácií pre priamu komunikáciu s hardwarom
- široká dostupnosť kvalitných prekladačov a knihovien

**Nevýhody:** 
- relativne zložitý jazyk
- nutnosť kompilácie zdrojového kódu po každej zmene programu

Spustenie súboru, kt. musí mať koncovku `.c`:
```
gcc -o spustitelny_súbor zdrojový_súbor
```

### Štruktúra programu v jazyku C
- všetky príkazy jazyka C sú zapísané vo funkciách
- program vždy začína funkciou `main()` a kód funkcie musí byť uzavretí v zložených zátvorkách `{}`
- každý príkaz je zakončený bodkočiarkou
- je `case-sensitiv`
- ukážka kódu, súbor `stdio.h` umožňuje používať funkciu `printf()` pre výstup na obrazovke

```c
#include <stdio.h>
int main()
{
    printf("Hello, World!\n"));
    return 0;
}
```

### Premenné
- každá premenná musí byť pred prvým použitím definovaná
- základné typy:
 - `int` celé čísla (integer)
 - `float` desatinné čísla (floating point number)
 - `char` znak (character)
- počiatočná hodnota premennej sa špecifikuje pomocou `=`

```c
int a, b, c;    // definujeme tri celociselne premenne a, b, c 
int d = 5;      // definujeme premennu d a inicializujeme ju hodnotou 5
float m, p;     // definujeme necelociselne premenne m a p
float g = 1.75; // definujeme premennu g a inicializujeme ju hodnotou 1.75
char z;         // definujeme znakovu promennu z
int teplota, vlhkost;  // meno premennej moze byt dlhsie nez jeden znak
int partial_charge3; // mozeme pouzivat pismena, cislice, podtrzitko, nie vsak medzeru
int MaxValue;      // daju sa pouzit i velka pismena
int maxValue;
```

### Konštanty
Konštanty sú číselé alebo znakové hodnoty, kt používame napr. pre priradenie hodnot premenným
- `celočíselné`
- `reálne`
- `znakové`

```c
int d = 5;    // inicializacia celociselnej premennej celociselnou konstantou
int a = 0, b = 0;  
float g = 1.75; // inicializacia realnej premennej realnou konstantou
float m = 0.0, n = 0.0;
char z = 'D';   // inicializacia znakovej premennej znakovou konstantou
```

### Aritmetické operátory
- `/`, `*`, `-`, `+`, `%`
- pre určenie priorít sa používaju zátvorky

```c
int a, b, c, d;  // definicia premennych a, b, c
a = 5;        // premenna a priradi hodnotu 5
b = 7;        // premenna b priradi hodnotu 7
c = 13;       // premenna c priradi hodnotu 13
d = a + b;    // premenna d priradi hodnotu suctu a plus b
d = a – b;
d = a * b;
d = a / b;    // POZOR!: delenie nulou sposobi okamzite ukoncenie programu
d = c % a;    // Zbytok po deleni cisla 13 cislom 5 co je 3
d = a + b / c;   // Prevedie se delenie b/c, potom sa pripocita a
d = (a + b) / c;  // Scita se a plus b a potom sa to vydeli c
```

### Funkcia `printf()` - výstup textu na obrazoku
Slúži k výpisu textu na obrazovku (terminál)
Miesto v texte, kde sa vypíše hodnota premenných sa špecifikuje pomocou formátových prvkov: 
  - `%i` pre premennú typu `int`
  - `%f` pre premennú typu `float`
  - `%c` pre premennú typu `char`
- špeciálny znak `\n` sposobý prechod na nový riadok

```c
int a = 3, b = 6, c = 9;
float m = 2.71, n = 14.3;
char c1 = 'D', c2 = 'j';

printf("Jednoduchy text\n");
printf("Cislo a ma hodnotu %i zatial co b je %i\n", a, b);
printf("Vypis celeho cisla %i a desetinneho cisla %f\n", c, m);
printf("Vypis dvoch znakov za sebou: %c%c\n", c1, c2);
```

### Použitie matematických funkcií
Pre sprístupnenie matematických funkcí musíme pridat na začiatok programu **#include <math.h>**
Pri kompilácii je potreba pridať matematicku knihovnu pomoco `-lm` (l ako library a m ako math)
```c
gcc -o mojprgogram mojprogram.c -lm
```
Najpoužívajnešie matematické funkcie:
`sqrt(x)` - odmocnina z x
`pow(x, y)` - x umocnena na y
`exp(x)` - e na x
`log(x)` - prirodzený logaritmus x
`cos(x)` - kosinus x
`sin(x)` - sinus x

```c
int n = 3;
float a = 7.3, b = 2.5, result = 0.0;

result = sqrt(a);
result = pow(a, n) + 7.4;
result = a + cos(b);
result = (sqrt(a) + sqrt(b)) / 2;
```

### Funkcia `scanf()` - čítanie vstupu z klávesnice
Slúži k získaniu vstupu z klávesnice
Prvým parametrom funkcie je fomátovací text, kt obsahuje jeden alebo viacerých formatovacích prvkov
Do formátovacieho textu sa nezadáva žiaden text, používaju sa iba formátovacie prvky
S pravdla je treba uživateľa vyzvat ku zadaniu hodnoty a preto sa volá naprv funkcia `printf()`
Za formátovací text funkcie `scanf()` zapíšeme toľko premenných, koľko bolo použitých formatovácich prvkov
POZOR !!! pred názovv premenných musíme vložiť znak `&`

```c
int a = 0;
float m = 0.0, n = 0.0;

printf("Zadej cele cislo a stiskni Enter: ");
scanf("%i", &a);
printf("Zadej dve desetinna cisla oddelena mezerou: ");
scanf("%f %f", &m, &n);
```

```c
int main()
{
  float a = 0.0, b = 0.0, c = 0.0;
  printf("Zadej A a B oddelene mezerou a stiskni Enter: ");
  scanf("%f %f", &a, &b);
  c = a + b;
  
  printf("Soucet %f a %f je %f\n", a, b, c);
  return 0;
}
```

### Príkaz podmienky `if`
Príkaz slúži k podmienenému prevedení príkazu
```c
 int a = 4, b = 0;
  
  if (a > 3)
    b = 10;     // Tento prikaz sa prevedie iba ak a je vacsie 3
  
    
  if (a > 8)
    b = 10;     // Tento prikaz sa prevedie iba ak a je vacsie 8
  else
    b = 0;      // Tento prikaz sa prevedie iba ak a nie je vacsie 8 
```

Pokiaľ je potreba vykonať viac ako jeden príkaz, tak sa používaju zložené zátvorky `{}`

```c
int a = 4, b = 0, c = 0, d = 0;
  
  if (a > 3)
  {
    b = 10;
    c = a + b;
  }
    
  if (a > 8)
  {
    b = 5; 
    c = a ­ b;
  }
  else
  {
    b = 7;      
    d = a + b
  }
```

### Logické operátory
Vyhodnocujú sa podľa priorit:
- najvačšia:
`<` - menší
`<=` - menší alebo rovný
`>` - vačší
`>=` - vačší alebo rovný
- menšia:
`==` - rovnosť
`!=` - nerovnosť
- najmenšia:
`||` - alebo (OR)
`&&` - a zároveň (AND)

Priority sa dajú ovplyvniť pomocou zátvoriek

```c
int a = 4, b = 5, c = 9;
char ch1 = 'A', ch2 = 'D';
  
if (a == 3)                // Jednoducha podmienka
if (a != 3)                // Jednoducha podmienka
if (b <= 3)                // Jednoducha podmienka
if (ch1 == 'B')            // Jednoducha podmienka 
if (ch1 != 'h')            // Jednoducha podmienka
if (a > 3 && b <= c)       // Trochu zlozitejsia podmienka
if ((a > 3) && (b <= c))   // Rovnaka podmienka ale s pouzitim zatvoriek
  
if (a > 3 || b != c && b <= c)   // Prioritu ma && pred ||
if (a > 3 || (b != c && b <= c)) // Rovnako s pouzitim zatvoriek
if ((a > 3 || b != c) && b <= c) // Tu zatvorky zmenily poradie vyhodnocovania
```

príklad: 
  Program načíta z klávesniice celé čísla a, b a vypíše, ktoré je vačšie
```c
int main()
{
  int a = 0, b = 0;
  printf("Zadaj A a B oddelene medzerou a stiskni Enter: ");
  scanf("%i %i", &a, &b);
  if (a == b)
  {
    printf("Vysledok: A je rovne B\n");
  }
  else
  {
    printf("Vysledok: A je rozne od B\n");
  }
  return 0;
}
```
