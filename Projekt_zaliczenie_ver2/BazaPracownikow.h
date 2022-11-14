#pragma once
#include "Pracownik.h"
#include "Struktura.h"
#include <stdio.h>



int BazaPracownikow();

int WyswietlListe();

int IloscRekordowWBazie(char nazwaBazy[]);

void DodajPracownika(Pracownik* dynamicznaListaPracownikow, int iloscRekordow);

void UsunPracownika(Pracownik* dynamicznaListaPracownikow, int iloscRekordow);