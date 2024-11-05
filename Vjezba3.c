#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _person* position;
typedef struct _person {
	char fname[50];
	char lname[50];
	int birth_year;
	position next;
}person;

position createPerson(char* name, char* lastname, int year);
position findLast(position head);
position findByLastName(position head, char* lastname);
position findPrev(position head, position P);
FILE* openFileWrite(const char* filePath);
FILE* openFileRead(const char* filePath);
void writeList(position head, const char* filePath);
void readList(position head, const char* filePath);
void sort(position head);
void addBegin(position head, char* name, char* lastname, int year);
void addEnd(position head, char* name, char* lastname, int year);
void insertAfter(position head, char* name, char* lastname, int year, char* baselastname);
void insertBefore(position head, char* name, char* lastname, int year, char* baselastname);
void delete(position head, char* lastname);
void print(position head);
void freeList(position head);



int main()
{
	const char* filePath = "C:\\Users\\PC\\Desktop\\datoteka.txt";
	person head;
	*head.fname = '\0';
	*head.lname = '\0';
	head.birth_year = 0;
	head.next = NULL;

	addBegin(&head, "Ana", "Jukic", 2005);
	addBegin(&head, "Ante", "Ivic", 2003);
	addEnd(&head, "Ive", "Matic", 2004);
	print(&head);
	insertAfter(&head, "Marko", "Horvat", 1998, "Ivic");
	insertBefore(&head, "Mate", "Milanovic", 2001, "Matic");
	print(&head);
	delete(&head, "Matic");
	print(&head);
	sort(&head);
	print(&head);

	freeList(&head);
	return 0;
}



position createPerson(char* name, char* lastname, int year)
{
	position newPerson = (position)malloc(sizeof(person));
	if (newPerson == NULL) {
		printf("Error");
		return NULL;
	}

	strncpy(newPerson->fname, name, sizeof(newPerson->fname));
	strncpy(newPerson->lname, lastname, sizeof(newPerson->lname));
	newPerson->birth_year = year;
	newPerson->next = NULL;

	return newPerson;
}

position findLast(position head)
{
	position temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

position findByLastName(position head, char* lastname)
{
	position temp = head;

	while (temp != NULL) {
		if (strcmp(temp->lname, lastname) == 0) {
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

position findPrev(position head, position P)
{
	position temp = head;

	while (temp->next != P) {
		temp = temp->next;
	}

	return temp;
}

FILE* openFileWrite(const char* filePath)
{
	FILE* file = fopen(filePath, "w");
	if (file = NULL) {
		printf("Error");
		return NULL;
	}

	return file;
}

FILE* openFileRead(const char* filePath)
{
	FILE* file = fopen(filePath, "r");
	if (file = NULL) {
		printf("Error");
		return NULL;
	}

	return file;
}

void writeList(position head, const char* filePath)
{
	FILE* file = openFileWrite(filePath);
	position temp = head;

	while (temp != NULL) {
		fprintf(file, "%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
		temp = temp->next;
	}
	fclose(file);
}

void readList(position head, const char* filePath)
{
	FILE* file = openFileRead(filePath);
	position temp = head;
	char string1[50], string2[50], line[1024];
	int int1;

	while (fgets(line, sizeof(line), file) != NULL) {
		if (sscanf(line, "%s %s %d", string1, string2, &int1) == 3) {
			position P = createPerson(string1, string2, int1);
			P->next = temp->next;
			temp->next = P;
			temp = temp->next;
		}
	}
	fclose(file);
}

void sort(position head)
{
	position current = head;
	bool swapped = true;

	if (!current->next || !current->next->next) {
		return;
	}

	while (swapped) {
		swapped = false;
		while (strcmp(current->next->lname, current->next->next->lname) > 0) {
			position first = current->next;
			position second = current->next->next;
			first->next = second->next;
			second->next = first;
			current->next = second;
		}
		current = current->next;
	}
}

void addBegin(position head, char* name, char* lastname, int year)
{
	position P = createPerson(name, lastname, year);

	P->next = head->next;
	head->next = P;
}

void addEnd(position head, char* name, char* lastname, int year)
{
	position P = createPerson(name, lastname, year);
	position last = findLast(head);

	P->next = last->next;
	last->next = P;
}

void insertAfter(position head, char* name, char* lastname, int year, char* baselastname)
{
	position P = createPerson(name, lastname, year);
	position base = findByLastName(head, baselastname);

	P->next = base->next;
	base->next = P;
}

void insertBefore(position head, char* name, char* lastname, int year, char* baselastname)
{
	position P = createPerson(name, lastname, year);
	position base = findByLastName(head, baselastname);
	position prev = findPrev(head, base);

	P->next = prev->next;
	prev->next = P;
}

void delete(position head, char* lastname)
{
	position toDelete = findByLastName(head, lastname);
	position prev = findPrev(head, toDelete);

	prev->next = toDelete->next;
	free(toDelete);
}

void print(position head)
{
	position temp = head;

	while (temp != NULL) {
		if (temp->birth_year != 0) {
			printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	printf("\n");
}

void freeList(position head)
{
	position temp = head;
	position next;

	while (temp != NULL) {
		next = temp->next;
		free(temp);
		temp = next;
	}
}