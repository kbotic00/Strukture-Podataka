#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SIZE (64)

struct _Person;
typedef struct _Person *Position;
typedef struct _Person
{
  char name[MAX_SIZE];
  char surname[MAX_SIZE];
  int birthYear;
  Position next;
} Person;

//1a dodaje osobu na pocetak liste
int addStart (Position head);
//1c dodaje osobu na kraj liste
int addEnd(Position head);

//a pomocno dodaje iza
int insertAfter (Position position, Position newPerson);
//  pomocno dodaje ispred
int insertBefore(Position head,Position searched);

//  kreira osobu s njenim podatcima
Position createPerson ();
//b ispis
int printList (Position head);
//d traži osobu po prezimenu
Position findPerson(Position head,char *find);
//e brise osobu iz liste
int deletePerson(Position head,char *find);
//e pomocno traziti osobu prije

Position findBefore(Position head,Position searched);
//a dodaje osobu iza neke osobe

int addAfter(Position head,char* searched);
//b dodaje osobu ispred neke osobe
int addBefore(Position head,char* searched);
//b pom dodaje ispred

int insertBefore(Position head,Position searched){
    Position find=NULL;
    Position newPerson=NULL;
    
    newPerson=createPerson();

    find=findBefore(head,searched);
    if(find!=NULL)
        insertAfter(find,newPerson);
    return EXIT_SUCCESS;

}
int addBefore(Position head,char* searched){
  
    Position find=NULL;
    
 
    find=findPerson(head,searched);
    
    if(find!=NULL)
        insertBefore(head,find);
    else printf("greska");
    return EXIT_SUCCESS;
}
    
int addAfter(Position head,char* searched){
    Position newPerson=NULL;
    Position find=NULL;
    
    newPerson=createPerson();
    
    find=findPerson(head,searched);
    if(find!=NULL)
        insertAfter(find,newPerson);
    else printf("greska");
    
    return EXIT_SUCCESS;
}

Position findBefore(Position head,Position searched)
{
   Position temp=NULL;
   while(temp!=NULL)
   {
       if(temp->next == searched)
            return temp;
        temp = temp->next;
   }
}
int deletePerson(Position head,char *searched){
    Position find=NULL;
    Position before=NULL;
    
    find=findPerson(head->next,searched);
    before=findBefore(head,find);
    if(before!=NULL)
        before->next=find->next;
    else 
        return -2;
    return EXIT_SUCCESS;
}

Position findPerson(Position head,char *find)
{
    Position temp=head;

    while(temp){
        if(strcmp(temp->surname,find)==0)
            return temp;
        temp=temp->next;
    }
    
    return NULL;
}
int addEnd(Position head)
{
    Position temp=head;
    Position newPerson = NULL;
    newPerson = createPerson();
    while(temp->next)
        temp=temp->next;
    insertAfter (temp,newPerson);
    return EXIT_SUCCESS;
}
int printList (Position head)
{
  Position temp = head;
  while (temp)
    {
      printf ("Ime: %s Prezime: %s Godina Rođenja: %d \n", temp->name,temp->surname, temp->birthYear);
      temp = temp->next;
    }

  return EXIT_SUCCESS;
}

int addStart (Position head)
{
  Position newPerson = NULL;

  newPerson = createPerson();
  insertAfter (head, newPerson);

  return EXIT_SUCCESS;
}

int insertAfter (Position position, Position newPerson)
{
  newPerson->next = position->next;
  position->next = newPerson;

  return EXIT_SUCCESS;
}

Position createPerson ()
{
  Position newPerson = NULL;
  newPerson = (Position) malloc (sizeof (Person));
  if (!newPerson)
    {
      perror ("Can't allocate memory");
      return NULL;
    }
  char name[MAX_SIZE] = { 0 };
  char surname[MAX_SIZE] = { 0 };
  int birthYear = 0;

  printf ("Unesite podatke za novu osobu \n Ime: ");
  scanf (" %s", name);
  printf (" Prezime: ");
  scanf (" %s", surname);
  printf (" Godina rođenja: ");
  scanf ("%d", &birthYear);

  strcpy (newPerson->name,name);
  strcpy (newPerson->surname,surname);
  newPerson->birthYear = birthYear;
  newPerson->next = NULL;

  return newPerson;

}

int main ()
{
    Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
    Position p = &Head;
    Position find= NULL;
    char searchedSurname[MAX_SIZE]={0};
    int odabir = 0;
    int flag = 1;
    while (flag){
        printf("Odaberite:\n 0-Kraj \n 1-Dodavanje elementa na pocetak\n 2-Ispis liste\n 3-Dodavanje elementa na kraj\n"
                " 4-Pronaći element po prezimenu\n 5-Obrisati određeni element\n 6-Dodati novi element iza određenog"
                "\n 7-Dodati novi element ispred određenog");
        scanf ("%d", &odabir);
        
        switch (odabir){
            case 1:
                addStart(p);
                break;
            case 2:
                printList(p->next);
                break;
            case 3:
                addEnd(p);
                break;
            case 4:{
                printf("Unesite prezime tražene osobe: ");
                scanf("%s",searchedSurname);
                find=findPerson(p->next,searchedSurname);
                if(find){
                    printf("Tražena osoba je: %s %s,%d \n",find->name,find->surname,find->birthYear);
                }
                else printf("Ne postoji osoba s tim prezimenom u listi");
                break;
            }
            case 5:{
                printf("Unesite prezime osobe koju želite izbrisati: ");
                scanf("%s",searchedSurname);
                deletePerson(p->next,searchedSurname);
                break;
            }
            case 6:{
                printf("Unesite prezime osobe iza koje zelite unijeti novi element: ");
                scanf("%s",searchedSurname);
                addAfter(p->next,searchedSurname);
                break;
            }
            case 7:{
                printf("Unesite prezime osobe ispred koje zelite unijeti novi element: ");
                scanf("%s",searchedSurname);
                addBefore(p,searchedSurname);
                break;
            }
            default:{
                printf("Kraj!");
                flag=0;
                break;
            }
        }
	
    }
}
