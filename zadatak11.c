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

struct _hashTab;
typedef struct _lista* Lista;
typedef struct _hashTab* hashT;
typedef struct _hashTab
{
	int velTab;
	Lista* hashLista;
}hashTab;


Position createelement(char* ime, int broj);
Pos Createel(char* ime);
int InsertAfter(Pos position, Pos newPerson);
int Sortiranje(Pos first, Pos newperson);
Position insert(Position current, Position q);
int citycompare(Position current, Position q);
int Unosizdatd(hashT, char* imedatoteke);
int Unos(Pos new, char* drzavadat);
int Ispis(hashT);
int ispisGrad(Position p);
Pos traziDrzavu(Pos p, char* ime);
int traziGrad(Position p, int broj);
int key(char* V);
hashT InicijalizacijaTbalice(int velTab);
int hashunos(hashT h, char* drzava, char* drzavadat);

hashT InicijalizacijaTablice(int velTab)
{
	hashT H;
	int i;

	H = (hashT)malloc(sizeof(hashTab));
	if (H = NULL) {
		printf("Greska kod inicijalizacije memorije!");
		exit(0);
	}
	H->velTab = velTab;
	H->hashLista = (Pos*)malloc(sizeof(Pos) * H->velTab);
	if (H->hashLista == NULL) {
		printf("Greska kod inicijalizacije memorije !");
		exit(0);
	}

	for (i = 0; i < velTab; i++)
		H->hashLista[i] = NULL;

	return H;

}

int key(char* V)
{
	int HashV = 0;
	int brojac = 0;
	printf("\n hash %s=  ", V);
	while (brojac != 5) {
		printf("+%d", *V);
		HashV += *V++;
		brojac++;
	}

	return HashV % 11;
}

int hashunos(hashT H, char* drzava, char* drzavadat) {
	Pos newEl = NULL;
	Pos current = NULL;
	int kljuc = key(drzava);

	newEl = Createel(drzava);

	if (newEl == NULL)
		return -1;

	Unos(newEl, drzavadat);


	if (!H->hashLista[kljuc])
		H->hashLista[kljuc] = newEl;
	else {
		current = H->hashLista[kljuc];
		while (current->next != NULL && strcmp(current->next->drzava, drzava) < 0)
			current = current->next;
		newEl->next = current->next;
		current->next = newEl;
	}
	return 0;
}

int main()
{
	//lista Head = { .drzava = "", .next = NULL, .root = NULL };
	//Pos pp = &Head;
	char imeDrzave[20];
	int broj = 0;
	Pos p;
	hashT  Hash = NULL;
	Hash = InicijalizacijaTablice(11);	//inicjalizacija 



	char datoteka[] = "drzave.txt";
	Unosizdatd(Hash, datoteka);
	Ispis(Hash);

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
	printf("\nGradovi %s sa vise od %d stanovnika:\n", p->drzava, broj);
	traziGrad(p->root, broj);*/


	return 0;
}

int Unosizdatd(hashT H, char* imedatoteke)
{
	FILE* dat = NULL;
	char imedrzave[MAX_SIZE] = { 0 };
	char drzavadat[MAX_SIZE] = { 0 };
	lista tempp = { .drzava = "", .root = NULL, .next = NULL };
	Pos new = &tempp;
	int hash_broj = 0;

	dat = fopen(imedatoteke, "r");
	if (!dat)
		return -1;


	while (!feof(dat)) {
		fscanf(dat, "%s %s\n", imedrzave, drzavadat);
		hashunos(H, imedrzave, drzavadat);

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
	char imegrada[MAX_SIZE] = "";
	int brojstanovnika = 0;
	//Position newg;

	dat = fopen(drzavadat, "r");
	if (!dat)
		return -1;

	while (!feof(dat)) {
		fscanf(dat, "%s %d", imegrada, &brojstanovnika);
		Position newg = createelement(imegrada, brojstanovnika);
		new->root = insert(new->root, newg);
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

	while (head->next != NULL && strcmp(head->next->drzava, newElement->drzava) < 0)
	{
		head = head->next;
	}

	InsertAfter(head, newElement);
	return EXIT_SUCCESS;
}

int Ispis(hashT H)
{
	Lista L = NULL;
	for (int i = 0; i < H->velTab; i++) {
		L = H->hashLista[i];
		if (L != NULL) {
			while (L != NULL) {
				printf("Drzava: %s\n", L->drzava);
				printf(" Grad:                Broj Stanovnika:\n");
				ispisGrad(L->root);
				L = L->next;
			}
		}
	}
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

/*Pos traziDrzavu(Pos p, char* ime)
{
	while (p != NULL)
	{
		if (strcmp(p->drzava, ime) == 0)
			return p;
		p = p->next;
	}
	return p;
}
*/
int traziGrad(Position p, int broj) {
	if (p == NULL)
		return 0;
	traziGrad(p->left, broj);
	if (p->broj_stan >= broj)
		printf(" %s %d\n", p->grad, p->broj_stan);
	traziGrad(p->right, broj);

	return 0;
}