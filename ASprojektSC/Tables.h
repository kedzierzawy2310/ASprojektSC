#pragma once
#include "Customer Group.h"

class Stoliki {
	grupaKlientow * aktualna_grupa_;
	int wielkosc_stolika_;
	bool wolny_stolik_;
	bool dolaczony_;
	bool jedzenie_;
	bool napoje_;
	bool zjedzone_;
	Stoliki* next_;
	Stoliki* next_obs³uga_;
	Stoliki* next_napoje_;
	Stoliki* next_jedzenie_;
	Stoliki* next_zjedzone_;
	Stoliki* stolik_pomocniczy_;

public:
	Stoliki();
	virtual ~Stoliki();
	void ZmienStatus(char c, bool b);
	void UstawNastepny(Stoliki* stoliki);
	void UstawNastepnyObsluga(Stoliki* stoliki);
	void UstawNastepnyNapoje(Stoliki* stoliki);
	void UstawNastepnyJedzenie(Stoliki* stoliki);
	void UstawNastepnyZjedzone(Stoliki* stoliki);
	void PrzypiszGrupe(grupaKlientow* grupa);
	void PrzypiszPomocniczy(Stoliki* stoliki);
	void NadajWielkosc(int i);
	int PodajWielkosc();
	bool SprawdzCzyGrupaPrzypisana();
	bool SprawdzCzyPomocniczyPrzypisany();
	bool SprawdzCzyNastepny();
	bool SprawdzCzyNastepnyObsluga();
	bool SprawdzCzyNastepnyNapoje();
	bool SprawdzCzyNastepnyJedzenie();
	bool SprawdzCzyZjedzone();
	bool SprawdzStatus(char c);
	grupaKlientow* ZwrocAktualnaGrupe();
	Stoliki* ZwrocPomocniczy();
	Stoliki* ZwrocNastepnyObsluga();
	Stoliki* ZwrocNastepnyNapoje();
	Stoliki* ZwrocNastepnyJedzenie();
	Stoliki* ZwrocNastepnyZjedzone();
	Stoliki* ZwrocNastepny();
};
