#include "stdafx.h"
#include "Manager.h"

Kierownik::Kierownik()
{
	aktualna_grupa_ = nullptr;
	liczba_obsluzen_ = 0;
	wolny_kierownik_ = true;
}

Kierownik::~Kierownik() = default;

void Kierownik::PrzypiszGrupe(grupaKlientow* grupa)
{
	aktualna_grupa_ = grupa;
}

void Kierownik::AktualizujLiczbeObsluzen()
{
	liczba_obsluzen_++;
}

void Kierownik::UstawStatus(bool b)
{
	wolny_kierownik_ = b;
}

bool Kierownik::SprawdzCzyGrupaPrzypisana()
{
	if (aktualna_grupa_ != nullptr) return true;
	return false;
}

bool Kierownik::SprawdzCzyWolny()
{
	if (wolny_kierownik_) return true;
	return false;
}

int Kierownik::PodajLiczbeObsluzen()
{
	return liczba_obsluzen_;
}