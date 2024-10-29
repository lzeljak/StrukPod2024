#include<stdio.h>
#include<stdlib.h>
#define max_bod 60
#define ERROR 1
#define _CRT_SECURE_NO_WARNINGS

struct student {
	char ime[50];
	char prez[50];
	float bod;
};

FILE* otvori(const char* filePath)
{
	FILE* file = fopen(filePath, "r");          // Otvara datoteku
	if (file == NULL) {                         // Provjerava je li otvaranje uspjelo
		printf("Greska pri otvaranju datoteke");
		return NULL;
	}
	return file;
}

float postotak(float bod)
{
	return bod / max_bod * 100; // Vraca postotak
}

int izbroj_retke(FILE* file)
{
	int brojac = 0;
	char line[1024];
	while (fgets(line, sizeof(line), file) != NULL) // Za svaki redak s podacima povecava brojac
		brojac++;
	rewind(file); // Vraca datoteku na pocetak nakon citanja
	return brojac;
}


int main()
{
	const char* filePath = "studenti.txt"; // Definira mjesto datoteke

	FILE* file = otvori(filePath);

	int i, broj_redaka = izbroj_retke(file);

	struct student* studenti;
	studenti = (struct student*)malloc(broj_redaka * sizeof(struct student)); // Alocira memoriju prema broju redaka
	if (studenti == NULL) {                                                   // Provjerava je li alokacija uspjela
		printf("Greska pri alociranju memorije");
		return ERROR;
	}

	for (i = 0;i < broj_redaka;i++) {
		fscanf(file, "%s %s %f", studenti[i].ime, studenti[i].prez, &studenti[i].bod);
		printf("%s %s %f %f\n", studenti[i].ime, studenti[i].prez, studenti[i].bod, postotak(studenti[i].bod));
	}

	free(studenti);
	fclose(file);
	return 0;
}