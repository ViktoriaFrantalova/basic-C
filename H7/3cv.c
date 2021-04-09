#include <stdio.h>
#include <string.h>
#define MAXPOLE 10000
// nacita retazec ako parameter a preda ho roznym funkciam

int funkcia(char retazec[])
{
    char s1[MAXPOLE] = "";
    char s2[MAXPOLE] = "";
    char s3[MAXPOLE] = "";
    int dlzka1 = 0;
    int dlzka2 = 0;

    dlzka1 = strlen(retazec); // funcia na zistovanie dlzku retazca
    printf("Dlzka retazca je: %i\n", dlzka1);

    strncpy(s1, retazec, 5); // funkcia na zkopirovanie reťazca
    s1[4] = '\0';            // prvé 4 znaky

    strncpy(s2, retazec + 10, 6); // zkopiruje 6 znakov od 9.znaku
    s1[6] = '\0';
    printf("Extrahovane retazce s1 a s2 su: %s, %s\n", s1, s2);

    if (strncmp(s1, s2, 4) == 0) // funkcia porovnáva iba prvých n teda v mojom prípade 4 znaky medzi dvoma reťazcami si a s2
    {
        printf("Retazce s1 a s2 maju prve 4 znaky totozne\n");
    }
    else
    {
        printf("Retazce s1 a s2 maju prve 4 znaky rozdielne\n");
    }

    strcpy(s3, s1); // spoji retazce, skopíruje reťazec s1 do s3, na koniec sa dá 0
    strcat(s3, s2); // pridá reťazec s2 na koniec reťazca s3 a pridá 0

    printf("Spojeny retazec s3: %s\n", s3);

    dlzka2 = strlen(s3); // zistuje dlzku spojeneneho retazca
    printf("Dlzka retazca s3 je: %i\n", dlzka2);
}
int main(int argc, char *argv[])
{ // použijeme ak chceme spracovať parametre predané programu na prikazovom riadku
    // argument argc - obs. počet parametrov predaných programu na príkazovom riadku zvečšený o 1
    // argument argv je pole ukazovatelov na reťazce, každý prok poľa odpovedá jednému predanému parametru
    // prvá hodnota v argv je vždy názov a cesta programu tak ako boly uvedene na prikazovom riadku
    char retazec[MAXPOLE] = "";
    if (argc > 1)
    {                     //nacita parametr z prikazoveho riadku
        funkcia(argv[1]); //preda ho ako argument funkcii
    }
    else
    {
        printf("Zadejte retezec: \n"); // bez parametru se spýta na retezec
        scanf("%s", retazec);
        funkcia(retazec);
    }
}
