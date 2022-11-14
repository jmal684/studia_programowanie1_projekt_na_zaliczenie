#define _CRT_SECURE_NO_WARNINGS
#include "Pracownik.h"
#include <stdio.h>
#include <string.h>

Pracownik GenerujPracownikaZPliku(char rekord[], char separator) {
	Pracownik pracownik;
	int indeks = 1;
	char* informacja;
	char separatory[] = { separator, "\n" };
	char kopia[100];
	strcpy(kopia, rekord);
	informacja = strtok(kopia, separatory);
	while (informacja != NULL)
	{
		switch (indeks)
		{
		case 1:
			strcpy(pracownik.numerSeryjny, informacja);
			break;
		case 2:
			strcpy(pracownik.imie, informacja);
			break;
		case 3:
			strcpy(pracownik.nazwisko, informacja);
			break;
		case 4:
			strcpy(pracownik.stanowisko, informacja);
			break;
		case 5:
			strcpy(pracownik.numerTelefonu, informacja);
			break;
		default:
			break;
		}
		informacja = strtok(NULL, separatory);
		indeks++;
	}


	return pracownik;
}

Pracownik GenerujPracownika(char numerSeryjny[], char imie[], char nazwisko[], char stanowisko[], char numerTelefonu[]) {
	Pracownik pracownik;
	strcpy(pracownik.numerSeryjny, numerSeryjny);
	strcpy(pracownik.imie, imie);
	strcpy(pracownik.nazwisko, nazwisko);
	strcpy(pracownik.stanowisko, stanowisko);
	strcpy(pracownik.numerTelefonu, numerTelefonu);

	return pracownik;
}
