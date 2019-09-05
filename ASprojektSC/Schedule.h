#pragma once
#include "Time Events 2.h"

class Harmonogram
{
	double czas_systemowy_;
	double koniec_symulacji_;
	std::vector<ZdarzeniaCzasowe*> zdarzenia_czasowe_;
public:
	Harmonogram();
	void dodaj(ZdarzeniaCzasowe* zdarzenia);
	void usuñ();
	void AktualizujCzasSystemowy(ZdarzeniaCzasowe* zdarzenia);
	double PodajCzasSystemowy();
	double PodajKoniecSymulacji();
	std::vector<ZdarzeniaCzasowe*> ZarzadzajZdarzeniami();
};
