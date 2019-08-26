#pragma once
#include "Classes.h"

//----------------------------------------------------------------------------------- DEKLARACJA KLASY KOMUNIKATÓW ZDARZEÑ CZASOWYCH -----------------------------------------------------------------------------------------------

class Komunikat
{
public:
	double czas_wykonania;
	ZdarzeniaCzasowe* zdarzenie;
	Komunikat(ZdarzeniaCzasowe*);
};

//----------------------------------------------------------------------------------------- DEKLARACJA KLASY ZDARZEÑ CZASOWYCH -----------------------------------------------------------------------------------------------------

class ZdarzeniaCzasowe
{
public:
	int zdarzenie;
	Komunikat* komunikat;

	ZdarzeniaCzasowe(int zdarzenie);
	virtual void execute();
	static double czas_systemowy;
	double podajCzasZdarzenia();
	static std::vector<Komunikat*> komzdarzeniaCzasowe; //WEKTOR KOMUNIKATÓW ZDARZEÑ CZASOWYCH
	
	static void dodaj(Komunikat* komunikat);
};

//------------------------------------------------------------------- DEKLARACJA PLIKÓW STATYSTYCZNYCH DO WYZNACZENIA FAZY POCZ¥TKOWEJ UK£ADU SYMULACYJNEGO ------------------------------------------------------------------------

static std::ofstream faza1("Faza.txt");
static std::ofstream faza2("Faza-x.txt");



