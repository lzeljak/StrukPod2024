#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _num* position;
typedef struct _num {
	double number;
	position next;
}num;

void read(position, const char*);
void push(position, double);
double pop(position);
bool isEmpty(position);


int main()
{
	const char* filePath = "C:\\Users\\PC\\Desktop\\postfix.txt";
	num head;
	head.number = 0;
	head.next = NULL;
	read(&head, filePath);
}

void read(position head, const char* filePath)
{
	FILE* file = fopen(filePath, "r");
	if (file == NULL) {
		printf("Error reading file!");
		return;
	}
	int numBytes;
	double k, operand1, operand2, result;
	char op='\0';
	char buffer[1024];
	char* ptr;
	fgets(buffer, sizeof(buffer), file);
	ptr = buffer;
	while (*ptr!='\0') {
		if (sscanf(ptr, "%lf %n", &k, &numBytes) == 1) {
			ptr = ptr + numBytes;
			push(head, k);
		}
		else if (sscanf(ptr, "%c %n", &op, &numBytes) == 1) {
			ptr = ptr + numBytes;
			operand2 = pop(head);
			operand1 = pop(head);
			if (op == '+')
				result = operand1 + operand2;
			else if (op == '-')
				result = operand1 - operand2;
			else if (op == '*')
				result = operand1 * operand2;
			else if (op == '/' && operand2 != 0)
				result = operand1 / operand2;
			else
				printf("Error proccessing operands!");
			push(head, result);
		}
	}
	double finalResult = pop(head);
	if (isEmpty(head))
		printf("Final result is: %lf", finalResult);
	else
		printf("Error");
}



void push(position head, double n)
{
	position P = (position)malloc(sizeof(num));
	if (P == NULL) {
		printf("Error allocating memory");
		exit(1);
	}
	P->number = n;
	P->next = head->next;
	head->next = P;
}

double pop(position head)
{
	double value;
	if (isEmpty(head)) {
		printf("Error, nothing to pop!");
		exit(1);
	}
	else {
		position toPop = head->next;
		head->next = toPop->next;
		value = toPop->number;
		free(toPop);
		return value;
	}
}

bool isEmpty(position head)
{
	if (head->next == NULL)
		return true;
	else
		return false;
}