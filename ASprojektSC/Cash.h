#pragma once
#include "Customer Group.h"

class Kasa {
	int liczba_obsluzen_;
	int id_kasjera_;
	grupaKlientow* aktualna_grupa_;
	Kasa* next_;
public:
	Kasa();
	virtual ~Kasa();
	void UstawId(int id);
	void UstawNastepna(Kasa* kasa);
	void PrzypiszGrupe(grupaKlientow* grupa);
	bool SprawdzCzyNastepna();
	bool SprawdzCzyGrupaPrzypisana();
	void AktualizujLiczbeObsluzen();
	int PodajLiczbeObsluzen();
	int PodajId();
	grupaKlientow* ZwrocAktualnaGrupa();
	Kasa* ZwrocNastepna();
};
