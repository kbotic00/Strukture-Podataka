#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX_SIZE (50)

struct _stablo;
typedef struct _stablo* Position;
typedef struct _stablo {
	int num;
	Position left;
	Position right;
}stablo;

struct _lista;
typedef struct _lista* Pos;
typedef struct _lista {
	int number;
	Pos next;
}lista;

int inorder(Position current);
int inorderlista(Position current, Pos position);
Position insert(Position current, Position q);
Position createelement(int number);
int replace(Position current);
int PrintList(Pos first);
Pos Createel(int broj);
int InsertAfter(Pos position, Pos newel);
int InsertiontoFile(Pos second, Pos first, char* imeDatoteke);

int main()
{
	Position roota = NULL;
	Position rootc = NULL;
	Position q;
	int niz1[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	time_t t;
	int nepotrebni;
	lista Head1= {.number= 0};
	Pos p1= &Head1;
	lista Head2= { .number = 0 };
	Pos p = &Head2;
	char nazivdat[MAX_SIZE] = "zadatak.txt";

	srand((unsigned)time(&t));

	for (int i = 0; i < 10; i++)
	{
		q = createelement(niz1[i]);
		roota = insert(roota, q);
	}

	printf("\nProvjera ispis stabla inorder: ");
	inorder(roota);
	printf("\nProvjera ispis liste: ");
	inorderlista(roota,p1);
	PrintList(p1->next);

	nepotrebni=replace(roota);
	printf("\nProvjera ispis stabla inorder: ");
	inorder(roota);
	printf("\nProvjera ispis liste: ");
	inorderlista(roota,p);
	PrintList(p->next);

	InsertiontoFile(p,p1, nazivdat);

	for (int i = 0; i < 10; i++)
	{
		niz1[i] = rand() % (89 + 1 - 11) + 11;
		q = createelement(niz1[i]);
		rootc = insert(rootc, q);
	}

	printf("\nProvjera ispis inorder: ");
	inorder(rootc);

	

    return 0;
}
Position createelement(int number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(stablo));
	if (!newElement)
	{
		printf("Can't allocate memory");
		return NULL;
	}

	newElement->num = number;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}
Position insert(Position current, Position q) {
	if (current == NULL)
		return q;

	else if (current->num <= q->num)
		current->left = insert(current->left, q);
	else if (current->num > q->num)
		current->right = insert(current->right, q);

	return current;
}
int inorder(Position current) {
	if (current == NULL)
		return 0;
	inorder(current->left);
	printf("%d ", current->num);
	inorder(current->right);
	return 0;
}
int inorderlista(Position current, Pos position) {
	Pos newel = NULL;

	if (current == NULL)
		return 0;

	inorderlista(current->left,position);

	newel = Createel(current->num);
	InsertAfter(position, newel);

	inorderlista (current->right,position);
	return 0;
}
int replace(Position current) {

	int temp = 0;

	if (current->left==NULL && current->right==NULL)
	{
		temp = current->num;
		current->num = 0;
		return temp;
	}
	else if (current->left!=NULL && current->right==NULL)
	{
		temp = current->num;
		current->num = replace(current->left);
		temp = temp + current->num;
		return temp;
	}

	else if(current->left==NULL && current->right!=NULL)
	{
		temp = current->num;
		current->num = replace(current->right);
		temp =temp + current->num;
		return temp;
	}
	else 
	{
		temp = current->num;
		current->num = replace(current->left) + replace(current->right);
		temp = temp + current->num;
		return temp;
	}

	return current->num;

}
int PrintList(Pos first)
{
	Pos temp = first; //ne dirati ono sta smo slali u f-ju
	while (temp)
	{
		printf("%d ", temp->number);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Pos Createel(int broj)
{
	Pos newel = NULL;
	newel = (Pos)malloc(sizeof(lista));

	if (!newel) {
		perror("Can't allocate memory!\n");
		return 0;
	}

	newel->number = broj;
	newel->next = NULL;

	return newel;
}

int InsertAfter(Pos position, Pos newel)
{
	while (position->next)
		position = position->next;

	newel->next = position->next;
	position->next = newel;

	return EXIT_SUCCESS;
}
int InsertiontoFile(Pos second, Pos first, char* imeDatoteke) {
	FILE* dat = NULL;
	Pos temp = first;
	Pos temp2 = second;
	dat = fopen(imeDatoteke, "w");
	if (!dat)
		return -1;

	while (temp) {
		if (temp != first)
			fprintf(dat, "%d ", temp->number);
		temp = temp->next;
	}
	fprintf(dat, "\n");
	while (temp2) {
		if (temp2 != second)
			fprintf(dat, "%d ", temp2->number);
		temp2 = temp2->next;
	}
	fclose(dat);
	return 0;
}
