#include "Struktura.h"
#include "BazaPracownikow.h"
#include "GwiazdaGra.h"
#include <stdio.h>

int MenuGlowne() {
	int wybor;
	system("cls");
	puts("----------SPIS PROGRAMOW----------\n");
	puts("1. Baza danych pracownikow");
	puts("2. Gdzie jest gwiazdka?");
	puts("3. Wyjscie");
	
	wybor = WalidatorWyboru(1, 3);
	if (wybor == 1)
	{
		int status = 1;
		do
		{
			status = BazaPracownikow();
		} while (status != 0);
	}
	else if(wybor == 2)
	{
		int status = 1;
		do
		{
			status = GwiazdaGra();
		} while (status!=0);
	}
	else
	{
		return 3;
	}


}
int WalidatorWyboru(const int poczatekZakresu, const int koniecZakresu) {
	int wybor;
	do
	{
		printf("-> ");
		scanf_s("%d", &wybor);
		if (wybor < poczatekZakresu || wybor > koniecZakresu) puts("ERROR: Nie ma opcji o takim numerze.");
		else break;
	} while (1==1);
	return wybor;
}