// Projekt_zaliczenie_ver2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Struktura.h"
#include "GwiazdaGra.h"


int main()
{
    int status = 1;
	do
	{
		status = MenuGlowne();
	} while (status!=3);	
}


