#pragma once
#include "Classes.h"

//----------------------------------------------------------------------------------- DEKLARACJA KLASY KOMUNIKAT�W ZDARZE� CZASOWYCH -----------------------------------------------------------------------------------------------

class Komunikat
{
public:
	double czas_wykonania;
	ZdarzeniaCzasowe* zdarzenie;
	Komunikat(ZdarzeniaCzasowe*);
};

//----------------------------------------------------------------------------------------- DEKLARACJA KLASY ZDARZE� CZASOWYCH -----------------------------------------------------------------------------------------------------

class ZdarzeniaCzasowe
{
public:
	int zdarzenie;
	Komunikat* komunikat;

	ZdarzeniaCzasowe(int zdarzenie);
	virtual void execute();
	static double czas_systemowy;
	double podajCzasZdarzenia();
	static std::vector<Komunikat*> komzdarzeniaCzasowe; //WEKTOR KOMUNIKAT�W ZDARZE� CZASOWYCH
	
	static void dodaj(Komunikat* komunikat);
};

//------------------------------------------------------------------- DEKLARACJA PLIK�W STATYSTYCZNYCH DO WYZNACZENIA FAZY POCZ�TKOWEJ UK�ADU SYMULACYJNEGO ------------------------------------------------------------------------

static std::ofstream faza1("Faza.txt");
static std::ofstream faza2("Faza-x.txt");



