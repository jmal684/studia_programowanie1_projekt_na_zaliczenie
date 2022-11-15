#define _CRT_SECURE_NO_WARNINGS
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#include "BazaPracownikow.h"
#include "Struktura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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
		} while (stan != 4);
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
	char wyplata[12];
	
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

	strcpy(wyplata, Wyplata(stanowisko));
	

	Pracownik pracownik = GenerujPracownika(numerSeryjny, imie, nazwisko, stanowisko, numerTelefonu, wyplata);
	nowaDynamicznaListaPracownikow[iloscRekordow] = pracownik;

	for (int j = 0; j < iloscRekordow+1; j++)
	{
		printf("1.Numer seryjny: %s\n", nowaDynamicznaListaPracownikow[j].numerSeryjny);
		printf("2.Imie: %s\n", nowaDynamicznaListaPracownikow[j].imie);
		printf("3.Nazwisko: %s\n", nowaDynamicznaListaPracownikow[j].nazwisko);
		printf("4.Stanowisko: %s\n", nowaDynamicznaListaPracownikow[j].stanowisko);
		printf("5.Numer telefonu: %s\n", nowaDynamicznaListaPracownikow[j].numerTelefonu);
		printf("6 Wyplata: %s", wyplata);
	}
	
	FILE* bazaPracownikow = fopen("BazaPracownikow.txt", "w");

	for (int i = 0; i < iloscRekordow+1; i++)

	{
		fprintf(bazaPracownikow, "%s,%s,%s,%s,%s,%s\n", nowaDynamicznaListaPracownikow[i].numerSeryjny, nowaDynamicznaListaPracownikow[i].imie, nowaDynamicznaListaPracownikow[i].nazwisko, nowaDynamicznaListaPracownikow[i].stanowisko, nowaDynamicznaListaPracownikow[i].numerTelefonu, nowaDynamicznaListaPracownikow[i].wyplata);
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
		fprintf(bazaPracownikow, "%s,%s,%s,%s,%s,%s\n", zmodyfikowanaDynamicznaListaPracownikow[j].numerSeryjny, zmodyfikowanaDynamicznaListaPracownikow[j].imie, zmodyfikowanaDynamicznaListaPracownikow[j].nazwisko, zmodyfikowanaDynamicznaListaPracownikow[j].stanowisko, zmodyfikowanaDynamicznaListaPracownikow[j].numerTelefonu, zmodyfikowanaDynamicznaListaPracownikow[j].wyplata);
	}
	free(zmodyfikowanaDynamicznaListaPracownikow);
	free(dynamicznaListaPracownikow);
	fclose(bazaPracownikow);

	system("cls");
	puts("----------BAZA PRACOWNIKOW----------\n\n");
	printf("Usunieto rekord o numerze: %d", numerUsunietegoRekordu);
}

char * OdczytajWyplaty() {
	int indeks = 1;
	char wyplatyLista[4][12];
	FILE* wyplaty;
	char* informacja;
	char separatory[] = { ',', "\n" };
	char kopia[100];
	char string[100];
	char kierownikWyplata[12] = "6000";
	char projektantWyplata[12] = "5000";
	char sekretarkaWyplata[12] = "3000";
	char doradcaWyplata[12] = "7000";

	wyplaty = fopen("wyplaty.txt", "r");
	fscanf(wyplaty, "%[^\n]", string);
	strcpy(kopia, string);
	informacja = strtok(kopia, separatory);
	while (informacja != NULL)
	{
		switch (indeks)
		{
		case 1:
			strcpy(wyplatyLista[0], informacja);			
			break;
		case 2:
			strcpy(wyplatyLista[1], informacja);
			strcpy(projektantWyplata, informacja);
			break;
		case 3:
			strcpy(wyplatyLista[2], informacja);			
			break;
		case 4:
			strcpy(wyplatyLista[3], informacja);			
			break;
		default:
			break;
		}
		informacja = strtok(NULL, separatory);
		indeks++;
	}
	fclose(wyplaty);
	free(informacja);
	return wyplatyLista;
}

void ModyfikujWyplaty(Pracownik* dynamicznaListaPracownikow, int iloscRekordow) {
	int czyAnulowano = false;
	char listaWyplat[4][12];
	char stanowisko[15];
	char nowaWyplata[12];
	char wybor;
	FILE* bazaWyplat;
	
	system("cls");
	puts("----------BAZA PRACOWNIKOW----------\n\n");
	memcpy(listaWyplat, OdczytajWyplaty(), 4 * 12);
	while (true)
	{
		printf("\n\nPodaj grupe dla ktorej chcesz zmienic wyplate (sekretarka, projektant, kierownik, doradca): ");
		scanf("%s", &stanowisko);
		printf("Nowa wyplata: ");
		scanf("%s", &nowaWyplata);


		switch (stanowisko[0])
		{
		case 's':
			printf("Zmieniono wyplate dla: %s, z ", stanowisko);
			printf(RED"%s"RESET, listaWyplat[0]);
			printf(" PLN na ");
			printf(GRN"%s"RESET, nowaWyplata);
			printf(" PLN\n");
			strcpy(listaWyplat[0], nowaWyplata);
			break;
		case 'p':
			printf("Zmieniono wyplate dla: %s, z ", stanowisko);
			printf(RED"%s"RESET, listaWyplat[1]);
			printf(" PLN na ");
			printf(GRN"%s"RESET, nowaWyplata);
			printf(" PLN\n");
			strcpy(listaWyplat[1], nowaWyplata);
			break;
		case 'k':
			printf("Zmieniono wyplate dla: %s, z ", stanowisko);
			printf(RED"%s"RESET, listaWyplat[2]);
			printf(" PLN na ");
			printf(GRN"%s"RESET, nowaWyplata);
			printf(" PLN\n");
			strcpy(listaWyplat[2], nowaWyplata);
			break;
		case 'd':
			printf("Zmieniono wyplate dla: %s, z ", stanowisko);
			printf(RED"%s"RESET, listaWyplat[3]);
			printf(" PLN na ");
			printf(GRN"%s"RESET, nowaWyplata);
			printf(" LN\n");;
			strcpy(listaWyplat[3], nowaWyplata);
			break;
		default:
			break;
		}
		printf("q - Wprowadz kolejna zmiane | e - Zatwierdz wszystkie zmiany | r - anuluj wszystkie zmiany :");
		wybor = _getch();
		if (wybor == 'e') break;
		else if (wybor == 'r') {
			czyAnulowano = true;
			break;
		}
	}
	

	
	if (czyAnulowano == false){
	
		bazaWyplat = fopen("wyplaty.txt", "w");
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)fprintf(bazaWyplat, "%s,", listaWyplat[i]);
			else fprintf(bazaWyplat, "%s", listaWyplat[i]);

		}
		fclose(bazaWyplat);
		for (int i = 0; i < iloscRekordow; i++)
		{
			if (dynamicznaListaPracownikow[i].stanowisko[0] == 's')
			{
				strcpy(dynamicznaListaPracownikow[i].wyplata, listaWyplat[0]);
			}
			else if (dynamicznaListaPracownikow[i].stanowisko[0] == 'p')
			{
				strcpy(dynamicznaListaPracownikow[i].wyplata, listaWyplat[1]);
			}
			else if (dynamicznaListaPracownikow[i].stanowisko[0] == 'k')
			{
				strcpy(dynamicznaListaPracownikow[i].wyplata, listaWyplat[2]);
			}
			else {
				strcpy(dynamicznaListaPracownikow[i].wyplata, listaWyplat[3]);
			}
		}
		FILE* bazaPracownikow = fopen("BazaPracownikow.txt", "w");

		for (int i = 0; i < iloscRekordow; i++)

		{
			fprintf(bazaPracownikow, "%s,%s,%s,%s,%s,%s\n", dynamicznaListaPracownikow[i].numerSeryjny, dynamicznaListaPracownikow[i].imie, dynamicznaListaPracownikow[i].nazwisko, dynamicznaListaPracownikow[i].stanowisko, dynamicznaListaPracownikow[i].numerTelefonu, dynamicznaListaPracownikow[i].wyplata);
		}
		fclose(bazaPracownikow);
		free(dynamicznaListaPracownikow);
		puts("\nPomyslnie wprowadzono zmiany");
		system("pause");
	}
	else
	{
		puts("\nAnulowano wprowadzanie zmian. Powrot do menu...");
		system("pause");
	}
	

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
			printf("5.Numer telefonu: %s\n", dynamicznaListaPracownikow[rekord].numerTelefonu);
			printf("6. Wyplata: ");
			printf(GRN"%s"RESET, dynamicznaListaPracownikow[rekord].wyplata);
			printf(" PLN");
			puts("\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			numerRekordu++;
		}
		puts("|1. Dodaj pracownika | 2. Usun rekord | 3. Modyfikuj wyplaty |4. Wyjscie");
		
		int wybor = WalidatorWyboru(1, 4);


		if (wybor == 1)
		{
			DodajPracownika(dynamicznaListaPracownikow, iloscRekordowWBazie);			
			return 1;
			
		}
		else if (wybor == 2) {
			UsunPracownika(dynamicznaListaPracownikow, iloscRekordowWBazie);
		}
		else if (wybor == 3) {
			ModyfikujWyplaty(dynamicznaListaPracownikow, iloscRekordowWBazie);
		}
		else  {
			return 4;
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




