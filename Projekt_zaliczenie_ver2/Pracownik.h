#pragma once
#include <stdlib.h>


typedef struct {
	char numerSeryjny[7];
	char imie[15];
	char nazwisko[30];
	char stanowisko[20];
	char numerTelefonu[12];
	char wyplata[12];
}Pracownik;

char* Wyplata(char stanowisko[]);
Pracownik GenerujPracownikaZPliku(char rekord[], char separator);
Pracownik GenerujPracownika(char numerSeryjny[], char imie[], char nazwisko[], char stanowisko[], char numerTelefonu[], char wyplata[]);
