#pragma once
#include "Customer Group.h"

class Kierownik {
	grupaKlientow * aktualna_grupa_;
	bool wolny_kierownik_;
	int liczba_obsluzen_;
public:
	Kierownik();
	virtual ~Kierownik();
	void PrzypiszGrupe(grupaKlientow* grupa);
	void UstawStatus(bool b);
	void AktualizujLiczbeObsluzen();
	bool SprawdzCzyGrupaPrzypisana();
	bool SprawdzCzyWolny();
	int PodajLiczbeObsluzen();
};
