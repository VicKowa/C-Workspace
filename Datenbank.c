#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clrscr() printf("\e[1;1H\e[2J")
#define MAX_DATASETS 50
// importe

// Methode für eine linie aus -
char print_65_dash_line()
{
    int i;
    for (i = 0; i < 150; i++)
    {
        printf("-");
    }
    printf("\n");
    return 0;
}
// enum anrede
typedef enum
{
    Herr = 22,
    Frau = 33
} Anrede;

typedef struct
{
    Anrede anrede;
    char *vorn;
    char *nachn;
    char *str;
    int postl;
    char *ort;
} Person;

typedef struct
{
    int size;
    Person data[MAX_DATASETS];

} Datenbank;

Person *createPerson();
void menu(Datenbank datenbank);
void printPerson(Person *per, int i);
void removePerson(Datenbank datenbank);
void printDatenbank(Datenbank datenbank);
int main();

Person *createPerson()
{
    int buff;
    char buffer[100];
    Person *temp = malloc(sizeof(Person));

    clrscr();
    printf("Anrede? 1: Herr, 2: Frau \n");
    scanf("%d", &buff);
    fflush(stdin);
    if (buff > 2 || buff < 0)
    {
        createPerson();
    }
    else if (buff == 1)
    {
        temp->anrede = Herr;
    }
    else if (buff == 2)
    {
        temp->anrede = Frau;
    }

    printf("Vorname? \n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    temp->vorn = strdup(buffer);
    fflush(stdin);
    // printf("%s", temp->vorn);

    printf("Nachname? \n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    temp->nachn = strdup(buffer);
    fflush(stdin);
    // printf("%s", buffer);

    printf("Straße? \n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    temp->str = strdup(buffer);
    fflush(stdin);

    printf("Postleitzahl? \n");
    scanf("%d", &buff);
    temp->postl = buff;
    fflush(stdin);

    printf("Ort? \n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    temp->ort = strdup(buffer);
    fflush(stdin);

    return temp;
}

void menu(Datenbank datenbank)
{
    int input;
    int size = datenbank.size;
    Person *temp;

    clrscr();
    printf("%c", print_65_dash_line());
    printf("Datenbank Menu : \n");
    printf("%c", print_65_dash_line());
    printf("Eintrag hinzufügen :\t\t1\n");
    printf("Eintrag entfernen :\t\t2\n");
    printf("Daten ansehen :\t\t\t3\n");
    printf("Exit :\t\t\t\t4\n");
    printf("%c", print_65_dash_line());

    scanf("%d", &input);
    fflush(stdin);
    if (input == 1)
    {
        clrscr();
        temp = createPerson();
        if (temp != NULL)
        {
            datenbank.data[size].anrede = temp->anrede;
            datenbank.data[size].nachn = temp->nachn;
            datenbank.data[size].ort = temp->ort;
            datenbank.data[size].postl = temp->postl;
            datenbank.data[size].vorn = temp->vorn;
            datenbank.data[size].str = temp->str;
            datenbank.size++;
        }
        menu(datenbank);
    }
    else if (input == 2)
    {   
        if(size > 0) {
            clrscr();
            removePerson(datenbank);
        } else {
            menu(datenbank);
        }
    }
    else if (input == 3)
    {
        clrscr();
        printDatenbank(datenbank);
    }
    else if (input == 4)
    {
        exit(0);
    }
}

int main()
{
    Datenbank datenbank;
    datenbank.size = 0;
    menu(datenbank);
    return 0;
}

void printDatenbank(Datenbank datenbank)
{
    Person *per;
    int input;

    clrscr();
    printf("%c\n", print_65_dash_line());
    printf("%c\n", print_65_dash_line());
    printf("Index\t\tAnrede\t\tVorname\t\tNachname\t\tStraße\t\tPostleitzahl\t\tOrt\t\t\n");
    printf("%c\n", print_65_dash_line());

    for (int i = 0; i < datenbank.size; i++)
    {
        per = &datenbank.data[i];
        if (per->postl != 0)
        {
            printPerson(per, i);
            printf("%c\n", print_65_dash_line());
        }
    }

    printf("Hauptmenu:\t\t1\n");
    scanf("%d", &input);
    fflush(stdin);

    if (input == 1)
    {
        menu(datenbank);
    }
}

void removePerson(Datenbank datenbank)
{
    int i;

    printf("Welcher Eintrag soll gelöscht werden?\n");
    printf("Abbrechen :\t\t -1");
    scanf("%d", &i);
    fflush(stdin);
    if(i < 0) {
        menu(datenbank);
    } else {
        datenbank.data[i].postl = 0;
        menu(datenbank);
    }
    
}

void printPerson(Person *per, int i)
{
    printf("%d\t\t", i);

    if (per->anrede == 22)
    {
        printf("Herr\t\t");
    }
    else if (per->anrede == 33)
    {
        printf("Frau\t\t");
    }

    printf("%s\t\t", per->vorn);
    printf("%s\t\t", per->nachn);
    printf("%s\t\t", per->str);
    printf("%d\t\t", per->postl);
    printf("%s\t\t\n", per->ort);
}
