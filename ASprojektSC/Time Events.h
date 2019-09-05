#pragma once
#include "stdafx.h"
/*
#pragma once
#include "Classes.h"

//----------------------------------------------------------------------------- DEKLARACJA KLASY KOMUNIKATÓW ZDARZEÑ CZASOWYCH -------------------------------------------------------------------------------

class Komunikat
{
public:
	double czas_wykonania;
	ZdarzeniaCzasowe* zdarzenie;
	Komunikat(ZdarzeniaCzasowe* zdarzenia);
};

//----------------------------------------------------------------------------------- DEKLARACJA KLASY ZDARZEÑ CZASOWYCH ------------------------------------------------------------------------------------- 

class ZdarzeniaCzasowe
{
public:
	int zdarzenie;
	static double czas_systemowy;
	static double koniec_symulacji;
	Komunikat* komunikat;
	static std::vector<Komunikat*> komzdarzeniaCzasowe;
	
	ZdarzeniaCzasowe(int zdarzenie);
	virtual ~ZdarzeniaCzasowe() = default;
	static void dodaj(Komunikat* komunikat);
	virtual void execute();
};

//----------------------------------------------------------------- DEKLARACJA PLIKÓW DANYCH NIEZBÊDNYCH DO WYZNACZENIA FAZY POCZ¥TKOWEJ ---------------------------------------------------------------------

static std::ofstream faza1("Faza.txt");
static std::ofstream faza2("Faza-x.txt");
static std::ofstream losowanie_klient("Losowanie_klient.txt");
static std::ofstream losowanie_bufet("Losowanie_bufet.txt");
static std::ofstream losowanie_konsumpcja("Losowanie_konsumpcja.txt");
static std::ofstream losowanie_kasy("Losowanie_kasy.txt");
static std::ofstream losowanie_napoje("Losowanie_napoje.txt");
static std::ofstream losowanie_jedzenie("Losowanie_jedzenie.txt");
static std::ofstream losowanie_alarm("Losowanie_alarm.txt");
static std::ofstream losowanie_wielkosci_grupy("Losowanie_wielkosci_grupy.txt");
static std::ofstream kolejka_sala("D³ugoœæ_kolejki_do_sali.txt");
static std::ofstream kolejka_kasa("D³ugoœæ_kolejki_do_kasy.txt");
static std::ofstream czas_oczekiwania_stolik("Czas_oczekiwania_na_stolik.txt");
static std::ofstream czas_oczekiwania_na_obsluge("Czas_oczekiwania_na_obs³ugê.txt");
*/