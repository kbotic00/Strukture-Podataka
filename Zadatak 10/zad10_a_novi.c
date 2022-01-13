#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX_SIZE (50)
#define MAX_LINE (1028)

struct _stablo;
typedef struct _stablo* Position;
typedef struct _stablo {
	char grad[50];
	int broj_stan;
	Position left;
	Position right;
}stablo;

struct _lista;
typedef struct _lista* Pos;
typedef struct _lista {
	char drzava[50];
	Pos next;
	Position root;
}lista;

Position createelement(char* ime, int broj);
Pos Createel(char* ime);
int InsertAfter(Pos position, Pos newPerson);
int Sortiranje(Pos first, Pos newperson);
Position insert(Position current, Position q);
int citycompare(Position current, Position q);
int Unosizdatd(Pos p, char* imedatoteke);
int Unos(Pos new, char* drzavadat);
int Ispis(Pos pp);
int ispisGrad(Position p);
Pos traziDrzavu(Pos p, char* ime);
int traziGrad(Position p, int broj);


int main()
{
	lista Head = { .drzava = "", .next = NULL, .root = NULL };
	Pos pp = &Head;
	char imeDrzave[20];
	int broj = 0;
	Pos p;

	char datoteka[]="drzave.txt";
	Unosizdatd(pp, datoteka);
	Ispis(pp);

	/*printf("\nUnesite ime drzave");
	scanf("%s", imeDrzave);
	p= traziDrzavu(pp->next, imeDrzave);
	if (p== NULL)
	{
		printf("Nepostoji!\n");
		return 0;
	}
	printf("Minimalan broj stanovnika: ");
	scanf("%d", &broj);
	printf("\nGradovi te drzave sa vise od %d stanovnika:\n", broj);
	traziGrad(pp->root, broj);*/


	return 0;
}

int Unosizdatd(Pos p, char* imedatoteke)
{
	FILE* dat = NULL;
	char imedrzave[MAX_SIZE]= {0};
	char drzavadat[MAX_SIZE]= {0};
	lista tempp = {.drzava = "", .root = NULL, .next = NULL};
    Pos new = &tempp;
 
	dat = fopen(imedatoteke, "r");
	if (!dat)
		return -1;


	while (!feof(dat)) {
		fscanf(dat, "%s %s\n", imedrzave, drzavadat);
		new = Createel(imedrzave);
		Unos(new, drzavadat);
		Sortiranje(p, new);
	}

	fclose(dat);
	return EXIT_SUCCESS;
}


Pos Createel(char* ime)
{
	Pos newel = NULL;
	newel = (Pos)malloc(sizeof(lista));

	if (!newel) {
		perror("Can't allocate memory!\n");
		return 0;
	}

	strcpy(newel->drzava, ime);
	newel->next = NULL;
	newel->root = NULL;
	return newel;
}

int Unos(Pos new, char* drzavadat) {

	FILE* dat = NULL;
	char imegrada[MAX_SIZE]="";
	int brojstanovnika=0;
	//Position newg;

	dat = fopen(drzavadat, "r");
	if (!dat)
		return -1;

	while (!feof(dat)) {
		fscanf(dat, "%s %d", imegrada, &brojstanovnika);
		Position newg = createelement(imegrada, brojstanovnika);
		new->root=insert(new->root, newg);
	}

	fclose(dat);
	return EXIT_SUCCESS;
}
Position createelement(char* ime, int broj)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(stablo));
	if (!newElement)
	{
		printf("Can't allocate memory");
		return NULL;
	}
	strcpy(newElement->grad, ime);
	newElement->broj_stan = broj;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}
int InsertAfter(Pos position, Pos newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}
Position insert(Position current, Position q)
{
	if (current == NULL)
		return q;

	else if (current->broj_stan > q->broj_stan)
		current->right = insert(current->right, q);
	else if (current->broj_stan < q->broj_stan)
		current->left = insert(current->left, q);
	else if (current->broj_stan == q->broj_stan)
		citycompare(current, q);
	else
		free(q);

	return current;
}

int citycompare(Position current, Position q)
{
	if (strcmp(current->grad, q->grad) > 0) {
		current->left = insert(current->left, q);
	}
	if (strcmp(current->grad, q->grad) < 0) {
		current->right = insert(current->right, q);
	}
	return EXIT_SUCCESS;
}

int Sortiranje(Pos head, Pos newElement)
{

    while( head -> next != NULL && strcmp(head -> next -> drzava, newElement -> drzava) < 0 )
    { 
        head = head -> next;
    }

    InsertAfter(head,newElement);
    return EXIT_SUCCESS;
}

int Ispis(Pos pp)
{
    pp=pp->next;
	printf("Ispis drzava i gradova :\n");
	while (pp != NULL)
	{
		printf("  %s\n", pp->drzava);
		ispisGrad(pp->root);
		pp = pp->next;
	}
	return 0;
}

int ispisGrad(Position p)
{
	if (p == NULL)
		return 0;
	ispisGrad(p->left);
	printf("%s\n", p->grad);
	ispisGrad(p->right);
	return 0;
}

Pos traziDrzavu(Pos p, char* ime)
{
	while (p != NULL)
	{
		if (strcmp(p->drzava, ime) == 0)
			return p;
		p = p->next;
	}
	return p;
}

int traziGrad(Position p, int broj)
{
	if (p == NULL)
		return 0;
	traziGrad(p->left, broj);
	if (p->broj_stan >= broj)
		printf(" %s %d\n", p->grad, p->broj_stan);
	traziGrad(p->right, broj);
	return 0;
}
