#include "stdafx.h"
#include "Cash.h"

Kasa::Kasa()
{
	next_ = nullptr;
	liczba_obsluzen_ = 0;
	aktualna_grupa_ = nullptr;
	id_kasjera_ = 0;
}

Kasa::~Kasa() = default;

void Kasa::UstawId(int id)
{
	id_kasjera_ = id;
}

void Kasa::UstawNastepna(Kasa* kasa)
{
	next_ = kasa;
}

void Kasa::PrzypiszGrupe(grupaKlientow* grupa)
{
	aktualna_grupa_ = grupa;
}

bool Kasa::SprawdzCzyNastepna()
{
	if (next_ != nullptr) return true;
	return false;
}

bool Kasa::SprawdzCzyGrupaPrzypisana()
{
	if(aktualna_grupa_!=nullptr) return true;
	return false;
}

void Kasa::AktualizujLiczbeObsluzen()
{
	liczba_obsluzen_++;
}

int Kasa::PodajLiczbeObsluzen()
{
	return liczba_obsluzen_;
}

int Kasa::PodajId()
{
	return id_kasjera_;
}

grupaKlientow* Kasa::ZwrocAktualnaGrupa()
{
	return aktualna_grupa_;
}

Kasa* Kasa::ZwrocNastepna()
{
	return next_;
}
