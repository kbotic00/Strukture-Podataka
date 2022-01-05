#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX_SIZE (50)
#define MAX_LINE (1028)
//STABLO-DRZAVE //LISTA-GRADOVI U DRZAVI
struct _lista;
typedef struct _lista* LPos;
typedef struct _lista {
	char grad[50];
	int broj_stan;
	LPos next;
}lista;

struct _stablo;
typedef struct _stablo* SPos;
typedef struct _stablo {
	char drzava[50];
	SPos right;
	SPos left;
	LPos root;
}stablo;

LPos creategrad(char* imegrada, int broj_st);
SPos createdrzava(char* imedrzave);
int Ispisdrzava(SPos current);
SPos Unesidrzavu(SPos current, SPos new);
int Unosgradova(SPos stablo, char* drzava, char* imedrzave);
LPos sortirajgrad(LPos current, LPos new);
int InsertAfter(LPos position, LPos newPerson);
SPos finddrzava(SPos stablo, char* drzava);
int IspisGradovi(LPos lis);
int trazigrad(SPos p, char* imeDrzave, int stanovnici);

LPos creategrad(char* imegrada, int broj_st) {
	LPos newel = NULL;
	newel = (LPos)malloc(sizeof(lista));

	if (!newel) {
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(newel->grad, imegrada);
	newel->next = NULL;

	return newel;
}
SPos createdrzava(char* imedrzave) {

	SPos newel = NULL;
	newel = (SPos)malloc(sizeof(stablo));

	if (!newel) {
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(newel->drzava, imedrzave);
	newel->left = NULL;
	newel->right = NULL;
	newel->root = NULL;

	return newel;
}


int main() {

	FILE* dat = NULL;
	char imedrzave[MAX_SIZE];
	char drzavadat[MAX_SIZE];
	char imetrazenedrzave[20];
	int stanovnici = 0;
	int prvi = 1;
	SPos drzave = NULL;
	SPos new;

	dat = fopen("drzave.txt", "r");
	if (!dat)
		return -1;

	while (!feof(dat)) {
		fscanf(dat, "%s %s", imedrzave, drzavadat);
		new = createdrzava(imedrzave);
		drzave = Unesidrzavu(drzave, new);
		Unosgradova(drzave, imedrzave, drzavadat);
	}
	fclose(dat);
	Ispisdrzava(drzave);


	char imetrazenedrzave[20];
	int stanovnici = 0;

	printf("Unesite ime trazene drzave ");
	scanf("%s", imetrazenedrzave);
	printf("Minimalan broj stanovnika po gradu: ");
	scanf("%d", &stanovnici);
	trazigrad(root, imeDrzave, stanovnici);

	return 0;
}
SPos Unesidrzavu(SPos current, SPos new) {
	if (current == NULL)
		return new;

	else if (strcmp(current->drzava, new->drzava) < 0)
		current->right = Unesidrzavu(current->right, new);
	else if (strcmp(current->drzava, new->drzava) > 0)
		current->left = Unesidrzavu(current->left, new);
	else
		free(new);

	return current;
}

int Ispisdrzava(SPos current)
{
	if (current == NULL)
		return 0;
	Ispisdrzava(current->left);
	printf("%s\n", current->drzava);
	Ispisdrzava(current->right);
	return 0;
}

int IspisGradovi(LPos lis)
{
	while (lis != NULL)
	{
		printf("%s %d\n", list->grad, list->broj_stan);
		list = list->next;
	}
	return 0;
}
int Unosgradova(SPos stablo, char* drzava, char* imedrzave)
{
	FILE* dat = NULL;
	char imegrada[MAX_SIZE];
	int broj_stan;
	LPos new;
	SPos find;

	dat = fopen("drzave.txt", "r");
	if (!dat)
		return -1;

	while (!feof(dat)) {
		fscanf(dat, "%s %d", imegrada, &broj_stan);
		new = creategrad(imegrada, broj_stan);
		find = finddrzava(stablo, drzava);
		sortirajgrad(find->root, new);
	}

	fclose(dat);
	return 1;
}
LPos sortirajgrad(LPos current, LPos new) {

	while (current != NULL && (current->broj_stan < new->broj_stan))
	{
		current = current->next;
	}
	if (current == NULL) {
		strcpy(current->grad, new->grad);
		current->broj_stan = new->broj_stan;
	}
	else
		InsertAfter(current, new);
	return EXIT_SUCCESS;

}
int InsertAfter(LPos position, LPos newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}
SPos finddrzava(SPos stablo, char* imedrzava) {

	SPos temp = stablo;

	if (stablo == NULL)
		return NULL;

	if (strcmp(stablo->drzava, imedrzava) < 0)
		temp = finddrzava(stablo->right, imedrzava);

	else if (strcmp(stablo->drzava, imedrzava) < 0)
		temp = finddrzava(stablo->left, imedrzava);

	return temp;
}

int trazigrad(SPos p, char* imeDrzave, int stanovnici)
{
	SPos drzava = NULL;
	SPol gradp = NULL;
	int broj = 0;

	drzava = finddrzava(p, imeDrzave);
	if (drzava == NULL)
	{
		printf("ta drzava nije u datoteci !\n");
		return 0;
	}
	gradp = drzava->grad;

	if (gradp == NULL)
	{
		printf("Nema gradova u toj drzavi\n");
		return 0;
	}

	gradp = gradp->next;
	while (gradp != NULL)
	{
		if (gradp->stanovnici >= stanovnici)
		{
			printf("%s\n", gradp->ime);
			broj = 1;
		}
		else break;
		gradp = gradp->next;
	}
	if (broj == 0)
		printf("Nema nijedan takav grad s takvim brojem vecim stanovnika!\n");

	return 0;
}