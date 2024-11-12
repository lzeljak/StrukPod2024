#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _poly* position;
typedef struct _poly {
	int coeff;
	int exp;
	position next;
}poly;

position createElement(int, int);
position findPrev(position head, position P);
void insertSort(position head, const char* filePath);
void insertAfter(position A, position B);
void deleteElement(position head, position toDelete);
void printList(position head);
void addLists(position headA, position headB, position headC);
void multiplyLists(position headA, position headB, position headC);
void freeList(position head);



int main()
{
	poly headA = NULL;
	poly headB = NULL;
	poly headC = NULL;

	insertSort(&headA, "dat1.txt");
	insertSort(&headA, "dat2.txt");
	printList(&headA);
	printList(&headB);
	printf("\n");
	addLists(&headA, &headB, &headC);
	printList(&headC);
	freeList(&headC);
	multiplyLists(&headA, &headB, &headC);
	printList(&headC);
	freeList(&headC);

	freeList(&headA);
	freeList(&headB);


}

position createElement(int coeff, int exp)
{
	position newE = (position)malloc(sizeof(poly));
	if (newE == NULL) {
		printf("Error");
		return NULL;
	}
	newE->coeff = coeff;
	newE->exp = exp;
	newE->next = NULL;
	return newE;
}

position findPrev(position head, position P)
{
	position temp = head;
	while (temp->next = P)
		temp = temp->next;
	return temp;
}

void insertSort(position head, const char* filePath)
{
	position temp = head;
	int C, E, numBytes;
	char buffer[1024];
	char* ptr = buffer;
	FILE* file = fopen(filePath, "r");
	if (file = NULL) {
		printf("Error");
		return 1;
	}
	fgets(buffer, sizeof(buffer), file);
	if (sscanf(ptr, " %d %d %n", &C, &E, &numBytes) == 2) {
		position newElement = createElement(C, E);
		ptr += numBytes;
		while (temp->next && temp->exp < newElement->exp) {
			temp = temp->next;
		}
		if (temp && temp->exp != newElement->exp) {
			insertAfter(temp, newElement);
		}
		else {
			int resultCoeff = temp->coeff + newElement->coeff;
			if (resultCoeff == 0) {
				deleteElement(head, temp);
				free(newElement);
			}
			else
				temp->coeff = resultCoeff;
		}
	}
	else
		printf("Error");
	fclose(file);
}

void insertAfter(position A, position B)
{
	B->next = A->next;
	A->next = B;
}

void deleteElement(position head, position toDelete)
{
	position prev = findPrev(head, toDelete);
	prev->next = toDelete->next;
	free(toDelete);
}

void printList(position head)
{
	position temp = head->next;
	while (temp != NULL) {
		printf("%dx^%d ", temp->coeff, temp->exp);
		temp = temp->next;
	}
	printf("\n");
}

void addLists(position headA, position headB, position headC)
{
	position temp1 = headA->next;
	position temp2 = headB->next;
	position temp3 = headC;
	int tracker = 0;
	while (temp1 != NULL) {
		while (temp2 != NULL) {
			if (temp1->exp == temp2->exp) {
				tracker = 1;
				int resultCoeff = temp1->coeff + temp2->coeff;
				position newElement = createElement(resultCoeff, temp1->exp);
				insertAfter(temp3, newElement);
				temp3 = temp3->next;
				temp1 = temp1->next;
				if (temp1 == NULL && temp2 != NULL) {
					while (temp2 != NULL) {
						insertAfter(temp3, temp2);
						temp3 = temp3->next;
						temp2 = temp2->next;
					}
				}
			}
			else {
				tracker = 0;
				temp2 = temp2->next;
			}
		}
		if (tracker == 0) {
			insertAfter(temp3, temp1);
			temp3 = temp3->next;
			temp1 = temp1->next;
		}
	}
}

void multiplyLists(position headA, position headB, position headC)
{
	position temp1 = headA->next;
	position temp2 = headB->next;
	position temp3 = headC;
	while (temp1 != NULL) {
		temp2 = headB->next;
		while (temp2 != NULL) {
			int resultCoeff = temp1->coeff * temp2->coeff;
			int resultExp = temp1->exp + temp2->exp;
			position newElement = createElement(resultCoeff, resultExp);
			insertAfter(temp3, newElement);
			temp3 = temp3->next;
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
}

void freeList(position head)
{
	position temp = head;
	while (temp != NULL) {
		position next = temp->next;
		free(temp);
		temp = next;
	}
}