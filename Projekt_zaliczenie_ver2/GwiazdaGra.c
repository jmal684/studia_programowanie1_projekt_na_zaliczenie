#define _CRT_SECURE_NO_WARNINGS
#define BLU   "\x1B[34m"
#define GRN   "\x1B[32m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#include "GwiazdaGra.h"
#include "Struktura.h"
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<windows.h>

int GwiazdaGra() {
	int wybor; 
	int status = 1;
	system("cls");
	puts("----------GDZIE JEST GWIAZA----------\n");

	puts("1. Graj");
	puts("2. Instrukcja");
	puts("3. Wyjscie");

	wybor = WalidatorWyboru(1, 3);
	if (wybor == 1)
	{
		
		do
		{
			status = Graj();
		} while (status != 0);

	}
	else if (wybor == 2)
	{
		Instrukcja();

	}
	else
	{
		return 0;
	}
	

}

int Graj() {
	char plansza[10][10];
	char wiadomoscRzad[10] = "";
	char wiadomoscKolumna[10] = "";
	char kierunek = 'a';
	char gracz = '%';
	char pole = '*';

	const int wielkosc = 10;
	int proby = 0;
	int lokalizacjaGraczaRzad = 3, lokalizacjaGraczaKolumna = 4;
	int zaznaczenieRzad = 3, zaznaczenieKolumna = 4;
	int gwiazdkaLokalizacjaRzad = 1, gwiazadkaLokalizacjaKolumna = 1;
	int czyGra = true;
	int wybor = 0;

	time_t t;
	srand((unsigned)time(&t));


	for (int i = 0; i < wielkosc; i++)
	{
		for (int j = 0; j < wielkosc; j++)
		{
			
			plansza[i][j] = pole;
		}
	}

	do
	{
		//Przywrocenie planszy do stanu poczatkowego
		strcpy(wiadomoscRzad, "-");
		strcpy(wiadomoscKolumna, "-");
		plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = pole;
		lokalizacjaGraczaRzad = 3;
		lokalizacjaGraczaKolumna = 4;
		plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = gracz;
		
		//Losowanie pozycji gwiazdki
		gwiazdkaLokalizacjaRzad = rand() % 10;
		gwiazadkaLokalizacjaKolumna = rand() % 10;

		while (true)
		{
			system("cls");
			//Wyswietlenie planszy
			for (int i = 0; i < wielkosc; i++)
			{
				for (int j = 0; j < wielkosc; j++)
				{
					if (plansza[i][j] == pole)
					{
						printf(BLU" %c " RESET, plansza[i][j]);
					}
					else
					{
						printf(WHT" %c ", plansza[i][j]);
					}

				}
				puts(" ");
			}

			//Wyswietlenie danych na temat lokalizacji gracza, gwiazdy oraz informacji odnosnie sterowania
			printf("\nGWIAZDA: (%s, %s)", wiadomoscRzad, wiadomoscKolumna);
			printf("\nPozycja gracza (%d, %d)\n", lokalizacjaGraczaRzad, lokalizacjaGraczaKolumna);
			puts("\nSTEROWANIE: W - gora, S - dol, A - lewo, D - prawo, E - sprawdz czy jest gwiazda, Q - Wyjscie");

			
			kierunek = _getch();

			//Sterowanie graczem
			if (kierunek == 'w')
			{
				plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = pole;
				lokalizacjaGraczaRzad -= 1;
				if (lokalizacjaGraczaRzad < 0)
				{
					lokalizacjaGraczaRzad = 9;
				}
				plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = gracz;
			}
			else if (kierunek == 's') {
				plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = pole;
				lokalizacjaGraczaRzad += 1;
				if (lokalizacjaGraczaRzad > 9)
				{
					lokalizacjaGraczaRzad = 0;
				}
				plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = gracz;
			}
			else if (kierunek == 'a') {
				plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = pole;
				lokalizacjaGraczaKolumna -= 1;
				if (lokalizacjaGraczaKolumna < 0)
				{
					lokalizacjaGraczaKolumna = 9;
				}
				plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = gracz;
			}
			else if (kierunek == 'd') {
				plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = pole;
				lokalizacjaGraczaKolumna += 1;
				if (lokalizacjaGraczaKolumna > 9)
				{
					lokalizacjaGraczaKolumna = 0;
				}
				plansza[lokalizacjaGraczaRzad][lokalizacjaGraczaKolumna] = gracz;
			}
			else if (kierunek == 'e')
			{
				if (lokalizacjaGraczaRzad == gwiazdkaLokalizacjaRzad && lokalizacjaGraczaKolumna == gwiazadkaLokalizacjaKolumna)
				{
					puts(GRN "\nWYGRANA" RESET);
					break;
				}

				if (lokalizacjaGraczaRzad > gwiazdkaLokalizacjaRzad)
				{

					strcpy(wiadomoscRzad, "Za DUZO");
				}
				else if (lokalizacjaGraczaRzad < gwiazdkaLokalizacjaRzad) {
					strcpy(wiadomoscRzad, "Za MALO");
				}

				if (lokalizacjaGraczaKolumna > gwiazadkaLokalizacjaKolumna) {

					strcpy(wiadomoscKolumna, "Za DUZO");
				}
				else if (lokalizacjaGraczaKolumna < gwiazadkaLokalizacjaKolumna) {
					strcpy(wiadomoscKolumna, "Za MALO");
				}
			}
			else if (kierunek == 'q')
			{
				break;
			}
			Sleep(20);

		}

		//Menu koncowe
		puts("----------------");
		puts("Zakonczono gre. 1. Zagraj ponownie, 2. Wyjdz");
		wybor = WalidatorWyboru(1, 2);
		if (wybor == 2)
		{
			czyGra = false;
		}
		

	} while (czyGra == true);

	return 0;
}

void Instrukcja() {
	system("cls");
	puts("----------GDZIE JEST GWIAZA----------\n");

	puts("Zadaniem gracza jest odnalezienie gwiazdy, która jest ukryta na jednym z pol planszy. Pod plansza wyswietlone sa informacje");
	puts("na temat wspolrzednych lokalizacji gracza, oraz jak bardzo odlegle sa one od wspolrzednych gwiazdki.\n");
	puts("Przyklad:");
	puts("Gwiazda: (Za MALO, Za DUZO)");
	puts("Pozycja gracza: (9,2)");
	puts("Gracz otrzymal informacje, ze numer rzedu jest za maly oraz, ze numer kolumny jest za duzy.");
	system("pause");
}
