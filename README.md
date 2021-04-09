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
