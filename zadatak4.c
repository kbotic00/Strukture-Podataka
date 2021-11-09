#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_LINE (1024)

struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
    int koef;
    int eks;
    Position next;
} Polinom;

int OpenFile(Position p1, Position p2);// radi i uredna je i gotova 
int ReadLine(char* linija, Position p);//radi i uredna je i gotova,cita elemente iz linije koja joj je poslana i poziva funkciju za sortirani ulaz i poziv valja
int PrintList(Position p); //ista kao i u zadatak 3
Position CreateElement(int koeficijent, int eksponent); //radiii ostale isto rade 
Position FindPrevious(Position head, Position position);
int InsertSorted(Position p,Position newel); 
int InsertAfter(Position position, Position newel);
int Delete(Position position,Position deleting);
int Zbroji(Position add,Position p1, Position p2);
int Pomnozi(Position multi, Position p1, Position p2);

int main() 
{
    Polinom head1 = { .koef = 0,.eks = 0, .next = NULL };
    Polinom head2 = { .koef = 0,.eks = 0, .next = NULL };
    Polinom head3 = { .koef = 0,.eks = 0, .next = NULL };
    Polinom head4 = { .koef = 0,.eks = 0, .next = NULL };

    Position p1 = &head1;
    Position p2 = &head2;
    Position add = &head3;
    Position multi = &head4;


    OpenFile(p1,p2);

    printf("\n Ispis 1.polinoma: ");
    PrintList(p1->next);
    printf("\n Ispis 2.polinoma: ");
    PrintList(p2->next);

    printf("\n Zbroj polinoma p1 i p2: ");
    Zbroji(add,p1->next, p2->next);
    PrintList(add->next);

    printf("\n Umnozak polinoma p1 i p2: ");
    Pomnozi(multi,p1->next, p2->next);
    PrintList(multi->next);
    printf("\n");



}
int OpenFile(Position p1, Position p2) //otvara datoteku i salje linije za stvoriti p1 vezanu listu i p2 vezanu listu
{
    FILE* dat;
    char naziv[50]= { 0 };
    char buffer[MAX_LINE] = { 0 };
    printf("\nUnesi ime datoteke :");
    scanf(" %s", naziv);

    dat = fopen(naziv, "r");
    if (!dat)
        return -1;

    fgets(buffer, MAX_LINE, dat);
    ReadLine(buffer, p1);

    fgets(buffer, MAX_LINE, dat);
    ReadLine(buffer, p2);

    fclose(dat);
    return EXIT_SUCCESS;
}
int ReadLine(char* linija, Position p) //cita elemente iz linije koja joj je poslana i poziva funkciju za sortirani ulaz i poziv valja
{
    char* temp = linija;
    int ppomak = 0, upomak = 0, status = 1;
    Position newel = NULL;

    int koef = 0, eks = 0;
    while (strlen(temp + upomak) > 0) {
        sscanf(temp+upomak, " %d %d %n", &koef, &eks, &ppomak);
        upomak += ppomak;//printf("%d %d\n", koef, eks);
        if (koef != 0) {
            newel = CreateElement(koef, eks);
            InsertSorted(p, newel);
        }
    }
    return EXIT_SUCCESS;
}
Position CreateElement(int koeficijent, int eksponent) 
{
    Position newel = NULL;
    newel = (Position)malloc(sizeof(Polinom));
    if (!newel) {
        perror("Can't allocate memory!\n");
        return NULL;
    }
    
    newel->koef = koeficijent;
    newel->eks = eksponent;
    newel->next = NULL;
    return newel;
}
int PrintList(Position p)
{
    Position temp = p;
    while (temp)
    {
        printf("%dx^(%d) ", temp->koef, temp->eks);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}
int InsertAfter(Position position, Position newel)
{
    newel->next = position->next;
    position->next = newel;

    return EXIT_SUCCESS;
}
int Delete(Position position, Position deleting)
{
    Position previousElement= FindPrevious(position, deleting);
    previousElement->next = deleting->next;

    return EXIT_SUCCESS;
}

int InsertSorted(Position head, Position newel)
{
    Position temp = head->next;
    Position previous = NULL;
    int nkoef = 0;

    while (temp!=NULL && (newel->eks) < (temp->eks))
            temp = temp->next;

    if (temp!=NULL && (newel->eks == temp->eks))
        {
            nkoef=temp->koef +newel->koef;
            if (nkoef == 0)
            {
                free(newel);
                Delete(head, temp);
            }
            else
                temp->koef = nkoef;
        }

     else
        {
            previous = FindPrevious(head, temp);
            InsertAfter(previous, newel);
        }
    return EXIT_SUCCESS;
}
Position FindPrevious(Position head, Position position)
{
    Position previous = head;
    while (previous->next != position)
        previous = previous->next;

    return previous;
}
int Zbroji(Position add,Position p1, Position p2) 
{
    Position newel = NULL;
    Position temp = NULL;

    while (p1 && p2) {
        if (p1->eks == p2->eks) {
            newel = CreateElement(p1->koef + p2->koef, p1->eks);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->eks > p2->eks) {
            newel = CreateElement(p1->koef, p1->eks);
            p1 = p1->next;
        }
        else {
            newel = CreateElement(p2->koef, p2->eks);
            p2 = p2->next;
        }
        InsertSorted(add, newel);
    }
    if (p1 && !p2)
        temp = p1;
    else
        temp = p2;

    while (temp) {
        newel = CreateElement(temp->koef, temp->eks);
        InsertSorted(add, newel);
        temp = temp->next;

    }
    return EXIT_SUCCESS;
}
int Pomnozi(Position multi,Position p1, Position p2) 
{
    Position newel = NULL;
    Position k2 = p2;

    for (p1; p1 != NULL; p1 = p1->next) {
        k2 = p2;
        for (k2; k2 != NULL; k2 = k2->next) {
            newel = CreateElement(p1->koef * k2->koef, p1->eks + k2->eks);
            InsertSorted(multi, newel);
        }
    }
    return EXIT_SUCCESS;
}
