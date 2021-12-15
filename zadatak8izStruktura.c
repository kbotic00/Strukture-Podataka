#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct _stablo;
typedef struct _stablo* Position;
typedef struct _stablo {
	int num;
	Position left;
	Position right;
}stablo;
int inorder(Position current);
int postorder(Position current);
int preorder(Position current);
Position insert(Position current, Position q);
Position createelement(int number);
void find_op(Position current);
Position find(Position current, int trazi);
Position delete(Position current, int brisi);
Position findmax(Position current);




int inorder(Position current) {
	if (current == NULL)
		return 0;
	inorder(current->left);
	printf("%d", current->num);
	inorder(current->right);
	return 0;
}
int preorder(Position current) {
	if (current == NULL)
		return 0;
	printf("%d", current->num);
	preorder(current->left);
	preorder(current->right);
	return 0;
}
int postorder(Position current) {
	if (current == NULL)
		return 0;
	postorder(current->left);
	postorder(current->right);
	printf("%d", current->num);
	return 0;
}
Position insert(Position current, Position q) {
	if (current == NULL)
		return q;

	else if (current->num < q->num)
		current->right = insert(current->right, q);
	else if (current->num > q->num)
		current->left = insert(current->left, q);
	else
		free(q);

	return current;
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

int main()
{
	Position root = NULL;
	Position q;
	int brisi = 0;
	int odabir = 0;
	int broj = 0;


	do {

		printf("\nOdaberi \n 0-Unos elementa\n 1-Ispis postorder \n 2-Ispis inorder\n 3-Ispis preorder \n 4-Find\n 5-Delete\n 6-Kraj: ");
		scanf("%d", &odabir);
		switch (odabir) {
		case 0: 
			printf("Unesi broj koji zelis upisati: ");
			scanf("%d", &broj);
			q = createelement(broj);
			root = insert(root, q);
			break;
	
		case 1: 
			printf("\n Ispis postorder: ");
			postorder(root);
			break; 
		case 2: 
			printf("\n Ispis inorder: ");
			inorder(root);
			break;
		
		case 3: 
			printf("\n Ispis preorder: ");
			preorder(root);
			break;
		
		case 4: 
			find_op(root);
			break;
		
		case 5: 
			printf("Unesi broj koji zelis izbrisati:");
			scanf("%d", &brisi);
			delete(root, brisi);
			break;

		case 6:
			break;
		default:
			printf("Krivi unos");
			break;

		}
	} while (odabir != 6);
	return 0;
}
void find_op(Position current) {

	int trazi;
	Position vrijednost;
	printf("\n Upisite element koji trazite: ");
	scanf("%d", &trazi);
	vrijednost = find(current, trazi);

	if (vrijednost == NULL)
		printf("Taj broj ne postoji u stablu");
	else
		printf("Broj je pronaðen u stablu");
}

Position find(Position current, int trazi) {

	if (current == NULL)
		return NULL;
	else if (current->num > trazi)
		return find(current->left, trazi);
	else if (current->num < trazi)
		return find(current->right, trazi);
	return current;

}
Position findmax(Position current)
{
	if (NULL == current)
		return NULL;

	else if (current->right == NULL)
		return current;
	else
		return findmax(current->left);
}
Position delete(Position current, int brisi)
{
	if (NULL == current)
		printf("nema tog elementa");

	else if (current->num > brisi)
		current->left = delete(current->left, brisi);

	else if (current->num < brisi)
		current->right = delete(current->right, brisi);

	else {

		if (current->left != NULL && current->right != NULL)
		{
			Position temp = findmax(current->right);
			current->num = temp->num;
			current->right = delete(current->right, current->num);
		}
		else
		{
			Position temp = current;
			if (NULL == current->left)
				current = current->right;
			else
				current = current->left;
			free(temp);
		}

	}
	return current;
}
