#define _CRT_SECURE_NO_WARNINGS
#include "BazaPracownikow.h"
#include "Struktura.h"
#include <stdio.h>
#include <stdlib.h>

int BazaPracownikow() {
	int wybor=0;
	system("cls");
	puts("----------BAZA PRACOWNIKOW----------\n");
	puts("1. Wyswietl liste");
	puts("2. Wyjscie z programu (powrot do menu).\n");
	wybor = WalidatorWyboru(1, 3);
	if (wybor == 1)
	{
		int stan = 0;
		do
		{
			stan = WyswietlListe();
		} while (stan != 3);
	}
	else {
		return 0;
	}


}

void DodajPracownika(Pracownik* dynamicznaListaPracownikow, int iloscRekordow) {
	Pracownik* nowaDynamicznaListaPracownikow = realloc(dynamicznaListaPracownikow, (iloscRekordow + 1) * sizeof(Pracownik));
	char numerSeryjny[7];
	char imie[15];
	char nazwisko[30];
	char stanowisko[20];
	char numerTelefonu[12];

	system("cls");
	puts("----------BAZA PRACOWNIKOW----------\n\n");
	puts("Podaj dane: ");

	printf("Numer seryjny [format: 00-000]: ");
	scanf("%s[0,1,2,3,4,5,6,7,8,9,-]", &numerSeryjny);

	printf("Imie: ");
	scanf("%s", &imie);

	printf("Nazwisko: ");
	scanf("%s", &nazwisko);

	printf("Stanowisko: ");
	scanf("%s", &stanowisko);

	printf("Numer telefonu [format: 000-000-000]: ");
	scanf("%s[0,1,2,3,4,5,6,7,8,9,-]", &numerTelefonu);


	Pracownik pracownik = GenerujPracownika(numerSeryjny, imie, nazwisko, stanowisko, numerTelefonu);
	nowaDynamicznaListaPracownikow[iloscRekordow] = pracownik;

	for (int j = 0; j < iloscRekordow+1; j++)
	{
		printf("1.Numer seryjny: %s\n", nowaDynamicznaListaPracownikow[j].numerSeryjny);
		printf("2.Imie: %s\n", nowaDynamicznaListaPracownikow[j].imie);
		printf("3.Nazwisko: %s\n", nowaDynamicznaListaPracownikow[j].nazwisko);
		printf("4.Stanowisko: %s\n", nowaDynamicznaListaPracownikow[j].stanowisko);
		printf("5.Numer telefonu: %s\n", nowaDynamicznaListaPracownikow[j].numerTelefonu);
	}
	
	FILE* bazaPracownikow = fopen("BazaPracownikow.txt", "w");

	for (int i = 0; i < iloscRekordow+1; i++)

	{
		fprintf(bazaPracownikow, "%s,%s,%s,%s,%s\n", nowaDynamicznaListaPracownikow[i].numerSeryjny, nowaDynamicznaListaPracownikow[i].imie, nowaDynamicznaListaPracownikow[i].nazwisko, nowaDynamicznaListaPracownikow[i].stanowisko, nowaDynamicznaListaPracownikow[i].numerTelefonu);
	}
	fclose(bazaPracownikow);
	free(nowaDynamicznaListaPracownikow);
	system("cls");
	puts("----------BAZA PRACOWNIKOW----------\n\n");
	puts("Dodano pracownika");
}

void UsunPracownika(Pracownik* dynamicznaListaPracownikow, int iloscRekordow) {
	int numerUsunietegoRekordu, indeks1 = 0, indeks2 = 0, rozmiarZmodyfikowanejTablicy = iloscRekordow - 1;
	Pracownik* zmodyfikowanaDynamicznaListaPracownikow = malloc( rozmiarZmodyfikowanejTablicy * sizeof(Pracownik));
	FILE* bazaPracownikow;

	do
	{
		printf("Podaj numer rekordu do usuniecia: ");
		scanf("%d", &numerUsunietegoRekordu);

		if (numerUsunietegoRekordu < 1 || numerUsunietegoRekordu > iloscRekordow) puts("ERROR: Rekord o takim numerze nie istnieje.");
		else break;
	} while (true);

	while (indeks1 < rozmiarZmodyfikowanejTablicy)
	{
		if (indeks2 == numerUsunietegoRekordu - 1)
		{
			indeks2++;
			continue;
		}
		zmodyfikowanaDynamicznaListaPracownikow[indeks1] = dynamicznaListaPracownikow[indeks2];
		indeks1++;
		indeks2++;
	}

	bazaPracownikow = fopen("BazaPracownikow.txt", "w");

	for (int j = 0; j < rozmiarZmodyfikowanejTablicy; j++)
	{
		fprintf(bazaPracownikow, "%s,%s,%s,%s,%s\n", zmodyfikowanaDynamicznaListaPracownikow[j].numerSeryjny, zmodyfikowanaDynamicznaListaPracownikow[j].imie, zmodyfikowanaDynamicznaListaPracownikow[j].nazwisko, zmodyfikowanaDynamicznaListaPracownikow[j].stanowisko, zmodyfikowanaDynamicznaListaPracownikow[j].numerTelefonu);
	}
	free(zmodyfikowanaDynamicznaListaPracownikow);
	free(dynamicznaListaPracownikow);
	fclose(bazaPracownikow);

	system("cls");
	puts("----------BAZA PRACOWNIKOW----------\n\n");
	printf("Usunieto rekord o numerze: %d", numerUsunietegoRekordu);
}

int WyswietlListe() {
	system("cls");
	puts("----------BAZA PRACOWNIKOW----------\n\n");
	int iloscRekordowWBazie = IloscRekordowWBazie("BazaPracownikow.txt");


	if (iloscRekordowWBazie == 0) puts("Baza jest pusta.\n");
	else
	{
		FILE* bazaPracownikow = fopen("BazaPracownikow.txt", "r");
		Pracownik* dynamicznaListaPracownikow = malloc(iloscRekordowWBazie * sizeof(Pracownik));
		int linijka = 0;
		char string[100];

		while (fgets(string, 100, bazaPracownikow))
		{
			Pracownik pracownik = GenerujPracownikaZPliku(string, ',');
			dynamicznaListaPracownikow[linijka] = pracownik;
			linijka++;
		}
		fclose(bazaPracownikow);

		int numerRekordu = 1;
		for (int rekord = 0; rekord < iloscRekordowWBazie; rekord++)
		{
			printf("NUMER REKORDU: %d\n", numerRekordu);
			printf("1.Numer seryjny: %s\n", dynamicznaListaPracownikow[rekord].numerSeryjny);
			printf("2.Imie: %s\n", dynamicznaListaPracownikow[rekord].imie);
			printf("3.Nazwisko: %s\n", dynamicznaListaPracownikow[rekord].nazwisko);
			printf("4.Stanowisko: %s\n", dynamicznaListaPracownikow[rekord].stanowisko);
			printf("Numer telefonu: %s\n", dynamicznaListaPracownikow[rekord].numerTelefonu);
			puts("\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			numerRekordu++;
		}
		puts("|1. Dodaj pracownika | 2. Usun rekord | 3. Wyjscie");
		
		int wybor = WalidatorWyboru(1, 4);


		if (wybor == 1)
		{
			DodajPracownika(dynamicznaListaPracownikow, iloscRekordowWBazie);			
			return 1;
			
		}
		else if (wybor == 2) {
			UsunPracownika(dynamicznaListaPracownikow, iloscRekordowWBazie);
		}
		else  {
			return 3;
		}

	}
	


}

int IloscRekordowWBazie(char nazwaBazy[]) {	
	FILE* baza;
	baza = fopen(nazwaBazy, "r");
	if (baza == NULL)
	{
		printf("ERROR: Nie udalo sie otworzyc %s.\n", nazwaBazy);
		return -1;
	} 
	else
	{
		int iloscLinii = 0;
		char linia[100];
		while (fgets(linia, sizeof(linia), baza)) iloscLinii++;
		fclose(baza);
		return iloscLinii;
	}

}




