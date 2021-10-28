#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (50)

// greska create person mislimm
struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
Position FindBySurname(Position first,char*surname);
Position FindBefore(Position first,Position position);
int DeleteAfter(Position head, char* surname);

int main(int argc, char** argv)
{
    Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
    Position p = &Head;
    Position find=NULL;
    int odabir=0;
    int temp=1;
    char name[MAX_SIZE]={0};
    char surname[MAX_SIZE]={0};
    int birthyear=0;
    
    while(temp){
    printf("ODABERITE:\n 1-dodati novi element na početak liste \n 2-ispisati listu\n 3-dodati novi element na kraj liste\n 4-pronaći element po prezimenu\n 5-obrisati element\n 6-kraj odabira\n");
    scanf("%d",&odabir);
    if(odabir==1){
        printf("Unesite podatke za novi element:\n Ime: ");
        scanf("%s", name);
        printf("\n Prezime:");
        scanf("%s", surname);
        printf("\n Godina rođenja:");
        scanf("%d", &birthyear);
        PrependList(p, name, surname, birthyear);
    }
    else if(odabir==2){
        PrintList(p->next);
    }
    else if(odabir==3){
        printf("Unesite podatke za novi element:\n Ime: ");
        scanf("%s", name);
        printf("\n Prezime:");
        scanf("%s", surname);
        printf("\n Godina rođenja:");
        scanf("%d", &birthyear);
        AppendList(p, name, surname, birthyear);
    }
    else if(odabir==4){
        printf("Unesite prezime traženog elementa: ");
        scanf("%s", surname);
        find=FindBySurname(p->next,surname);
        if(find==0){
            printf("Nije nađena osoba tog prezimena");
        }
        else printf("Tražena osoba:\n Ime: %s \n Prezime: %s \n Godina Rođenja: %d",find->name, find->surname, find->birthYear);
        
    }
    else if(odabir==5){
        printf("Unesite prezime traženog elementakojeg zelite izbrisati: ");
        scanf("%s", surname);
        DeleteAfter(p,surname);
        
    }
    else if(odabir==6){
        temp=0;
        printf("Kraj");
    }
    else printf("Krivi unos");
    }
    return 0;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson = CreatePerson(name, surname, birthYear);

    if (!newPerson) {
    //perror("Can't allocate memory!\n");
    return -1;
    }

    InsertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

int PrintList(Position first)
{
    Position temp = first; //ne dirati ono sta smo slali u f-ju
    while (temp)
    {
        printf("Name: %s, surname: %s, birth year: %d\n", temp->name, temp->surname, temp->birthYear);
        temp= temp->next;
    }

    return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;
    newPerson=(Position)malloc(sizeof(Person));

    if (!newPerson) {
        perror("Can't allocate memory!\n");
        return 0;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
    Position temp = head;
    while (temp->next){
    temp = temp->next;
    }
    return temp;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;
    Position last = NULL;

    newPerson = CreatePerson(name, surname, birthYear);

    if (!newPerson) {
    //perror("Can't allocate memory!\n");
    return -1;
    }

    last = FindLast(head);
    InsertAfter(last, newPerson);

    return EXIT_SUCCESS;
}

Position FindBySurname(Position first, char* surname)
{
    Position temp = first;
    while(temp){
        if (strcmp(temp->surname, surname) == 0)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

Position FindBefore(Position first,Position position)
{
    Position temp=first;
    while(temp->next!=position){
       temp=temp->next;
    }
    return temp;
}
int DeleteAfter(Position head, char* surname)
{
   Position find=NULL;
   Position before=NULL;
   
   find=FindBySurname(head->next,surname);
   
   before=FindBefore(head,find);
   before->next=find->next;
   
   return EXIT_SUCCESS;
}
