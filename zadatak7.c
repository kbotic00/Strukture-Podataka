#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _stablo;
typedef struct _stablo* Position;
typedef struct _stablo {
    char name[15];
    Position child;
    Position sibling;
}stablo;

struct _stog;
typedef struct _stog* Pos;
typedef struct _stog {
    Position adresa;
    Pos next;
}stog;

Position createne(char* ime);
Position insert(Position current, Position ne);
int ispis(Position current);
int push(Pos head, Position adresa);
Pos CreateStackElement(Position adressa);
int InsertAfter(Pos position, Pos newElement);
Position find(Position current, char* name);
Position pop(Pos current);

int ispis(Position current) {
    Position temp = current->child;
    while (temp != NULL)
    {
        printf("\n %s", temp->name);
        temp = temp->sibling;
    }
    return 1;
}
Position createne(char* ime)
{
    Position ne=NULL;
    ne = (Position)malloc(sizeof(stablo));
    if (!ne)
        return NULL;
    strcpy(ne->name,ime);
    ne->child = NULL;
    ne->sibling = NULL;
    return ne;
}

Position insert(Position current, Position ne) {
    if (!current)
        return ne;
    if (strcmp(current->name, ne->name) < 0)
        current->sibling = insert(current->sibling, ne);
    else if (strcmp(current->name, ne->name) > 0) {
        ne->sibling = current;
        return ne;
    }
    return current;
}
int push(Pos head, Position adr) {
    Pos newElement = NULL;
    newElement = CreateStackElement(adr);
    if (!newElement) {
        return -1;
    }

    InsertAfter(head, newElement);
    return 1;
    
}
Pos CreateStackElement(Position adressa) {
    Pos newElement = NULL;
    newElement = (Pos)malloc(sizeof(stog));
    if (!newElement)
    {
        printf("Can't allocate memory");
        return NULL;
    }

    newElement->adresa = adressa;
    newElement->next = NULL;

    return newElement;
}

int InsertAfter(Pos position, Pos newElement) {
    newElement->next = position->next;
    position->next = newElement;

    return 1;
}
Position pop(Pos current)
{
    Pos temp= NULL;
    Position trazena = NULL;

    temp = current->next;
    current->next = temp->next;

    trazena = temp->adresa;
    free(temp);

    return trazena;
}
Position find(Position current, char* name)
{
    Position child = current->child;

    if (current == NULL)
        printf("Direktorij je prazan");


    while (child!=NULL && strcmp(child->name, name)!= 0)
        child = child->sibling;

    return child;
}

int main() {

    stablo c = { .name = "C", .child = NULL, .sibling = NULL };
    Position current = &c;

    stog s = {.adresa=current,.next=NULL};
    Pos sroot = &s;

    Position new;
    int odabir;
    char ime[15];

    do {

        printf("Upisite odabir: \n");
        printf("\n 1 - md  \n 2 - cd dir  \n 3 - cd ..  \n 4 - dir  \n 5 - izlaz: \n");
        scanf("%d", &odabir);
        Position temp;

        switch (odabir) {
        case 1:
            printf("Unesite ime novog direktorija");
            scanf("%s", ime);
            new=createne(ime);
            current->child = insert(current->child, new);
            break;
        case 2:
            printf("Unesite ime direktorija");
            scanf("%s", ime);
            temp = find(current, ime);
            if (temp == NULL)
                printf("Nepostoji element s takvim imenom (%s)\n", ime);
            else {
                push(sroot, temp);
            }
            current = temp;
            printf("Elementi direktorija (%s):", ime);
            ispis(current);
            break;
        case 3:
            current = pop(sroot);
            break;
        case 4:
            printf("Elementi direktorija (%s):", current->name);
            ispis(current);
            break;
        case 5:
            break;
        default:
            printf("Krivi unos");
            break;
        }
    } while (odabir != 5);
    return 0;
}