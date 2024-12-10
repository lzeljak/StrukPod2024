#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _articlesList* PositionArt;
typedef struct _receipt* PositionRec;

typedef struct _articlesList {
	char article[50];
	int quantity;
	double price;
	PositionArt next;
}articlesList;

typedef struct _receipt {
	int year, month, day;
	articlesList articlesHead;
	PositionRec next;
}receipt;

PositionRec createReceipt(char*);
PositionArt createArticle(char*, int, double);
bool compareDates(PositionRec, PositionRec);
bool compareStrings(PositionArt, PositionArt);
void readFile(char*, PositionRec);
void insertSortRec(PositionRec, PositionRec);
void insertSortArt(PositionArt, PositionArt);
void searchByName(char*, PositionRec);
void printList(PositionRec);
void freeList(PositionRec);



int main()
{
	receipt head;
	head.next = NULL;
	readFile("C:\\Users\\PC\\Desktop\\racuni.txt", &head);
	printList(&head);
	printf("Koji artikl zelite pretraziti?\n");
	char line[50];
	scanf("%s", line);
	searchByName(line, &head);
	freeList(&head);
}



PositionRec createReceipt(char* filePath)
{
	PositionRec newReceipt = (PositionRec)malloc(sizeof(receipt));
	if (newReceipt == NULL) {
		printf("Error creating receipt");
		return NULL;
	}
	FILE* file = fopen(filePath, "r");
	if (file == NULL) {
		printf("Error opening file in receipt");
		return NULL;
	}
	int year, month, day, quantity;
	double price;
	char article[50], line[50];
	fgets(line, sizeof(line), file);
	if (sscanf(line, "%4d-%2d-%2d", &year, &month, &day) == 3) {
		newReceipt->year = year;
		newReceipt->month = month;
		newReceipt->day = day;
	}
	else {
		printf("Error reading date");
		return NULL;
	}
	newReceipt->articlesHead.next = NULL;
	newReceipt->next = NULL;
	while (fgets(line, sizeof(line), file)) {
		if (sscanf(line, "%s %d %lf", article, &quantity, &price) == 3) {
			PositionArt temp = createArticle(article,quantity, price);
			insertSortArt(&newReceipt->articlesHead, temp);
		}
		else {
			printf("Error reading articles");
			return NULL;
		}
	}
	fclose(file);
	return newReceipt;
}

PositionArt createArticle(char* article, int quantity, double price)
{
	PositionArt newArticle = (PositionArt)malloc(sizeof(articlesList));
	if (newArticle == NULL) {
		printf("Error creating article");
		return NULL;
	}
	strcpy(newArticle->article, article);
	newArticle->quantity = quantity;
	newArticle->price = price;
	newArticle->next = NULL;
	return newArticle;
}

bool compareDates(PositionRec A, PositionRec B)
{
	if (A->year < B->year)
		return true;
	else if (A->month < B->month && A->year==B->year)
		return true;
	else if (A->day < B->day && A->month==B->month && A->year==B->year)
		return true;
	else
		return false;
}

bool compareStrings(PositionArt A, PositionArt B)
{
	return strcmp(A->article, B->article) > 0;
}

void readFile(char* filePath, PositionRec head) {
	FILE* file = fopen(filePath, "r");
	if (file == NULL) {
		printf("Error opening main file");
		return;
	}
	char line[50];
	while (fgets(line, sizeof(line), file)) {
		line[strcspn(line, "\n")] = '\0';
		PositionRec temp=createReceipt(line);
		insertSortRec(head, temp);
	}
	fclose(file);
}

void insertSortRec(PositionRec head, PositionRec P)
{
	PositionRec temp = head;
	while (temp->next != NULL && !compareDates(temp->next, P))
		temp = temp->next;
	P->next = temp->next;
	temp->next = P;
}

void insertSortArt(PositionArt head, PositionArt P)
{
	PositionArt temp = head;
	while (temp->next != NULL && !compareStrings(temp->next, P))
		temp = temp->next;
	P->next = temp->next;
	temp->next = P;
}

void searchByName(char* article, PositionRec head)
{
	int totalQuantity=0;
	double totalPrice=0;
	PositionRec temp = head->next;
	while (temp != NULL) {
		PositionArt tempArt = temp->articlesHead.next;
		while(tempArt!=NULL){
			if (!strcmp(tempArt->article, article)) {
				totalQuantity += tempArt->quantity;
				totalPrice = tempArt->price * totalQuantity;
			}
			tempArt = tempArt->next;
		}
		temp = temp->next;
	}
	printf("Artikla %s ukupno je prodano %d komada za %.2lf eura\n", article, totalQuantity, totalPrice);
}

void printList(PositionRec head)
{
	PositionRec temp = head->next;
	while (temp != NULL) {
		printf("Na dan %d.%d.%d. prodano je:\n", temp->day, temp->month, temp->year);
		PositionArt tempArt = temp->articlesHead.next;
		while (tempArt != NULL) {
			printf("%s, %d komada po %.2lf eura\n", tempArt->article, tempArt->quantity, tempArt->price);
			tempArt = tempArt->next;
		}
		printf("\n");
		temp = temp->next;
	}
}

void freeList(PositionRec head)
{
	PositionRec temp = head->next;
	while (temp != NULL) {
		PositionArt tempArt = temp->articlesHead.next;
		while (tempArt != NULL) {
			PositionArt nextArt = tempArt->next;
			free(tempArt);
			tempArt = nextArt;
		}
		PositionRec next = temp->next;
		free(temp);
		temp = next;
	}
}