#include "stdafx.h"
#include "Tables.h"

Stoliki::Stoliki()
{
	aktualna_grupa_ = nullptr;
	wielkosc_stolika_ = 0;
	wolny_stolik_ = true;
	dolaczony_ = false;
	jedzenie_ = false;
	napoje_ = false;
	zjedzone_ = false;
	next_ = nullptr;
	next_obs³uga_ = nullptr;
	next_napoje_ = nullptr;
	next_jedzenie_ = nullptr;
	next_zjedzone_ = nullptr;
	stolik_pomocniczy_ = nullptr;
}

Stoliki::~Stoliki() = default;

void Stoliki::ZmienStatus(char c, bool b)
{
	switch(c)
	{
	case 'w':
		wolny_stolik_ = b;
		break;
	case 'd':
		dolaczony_ = b;
		break;
	case 'j':
		jedzenie_ = b;
		break;
	case 'n':
		napoje_ = b;
		break;
	case 'z':
		zjedzone_ = b;
		break;
	default:
		break;
	}
}

void Stoliki::UstawNastepny(Stoliki* stoliki)
{
	next_ = stoliki;
}

void Stoliki::UstawNastepnyObsluga(Stoliki* stoliki)
{
	next_obs³uga_ = stoliki;
}

void Stoliki::UstawNastepnyNapoje(Stoliki* stoliki)
{
	next_napoje_ = stoliki;
}

void Stoliki::UstawNastepnyJedzenie(Stoliki* stoliki)
{
	next_jedzenie_ = stoliki;
}

void Stoliki::UstawNastepnyZjedzone(Stoliki* stoliki)
{
	next_zjedzone_ = stoliki;
}

void Stoliki::PrzypiszGrupe(grupaKlientow* grupa)
{
	aktualna_grupa_ = grupa;
}

void Stoliki::PrzypiszPomocniczy(Stoliki* stoliki)
{
	stolik_pomocniczy_ = stoliki;
}

void Stoliki::NadajWielkosc(int i)
{
	wielkosc_stolika_ = i;
}

int Stoliki::PodajWielkosc()
{
	return wielkosc_stolika_;
}


bool Stoliki::SprawdzCzyNastepny()
{
	if (next_ != nullptr) return true;
	return false;
}

bool Stoliki::SprawdzCzyNastepnyObsluga()
{
	if (next_obs³uga_ != nullptr) return true;
	return false;
}

bool Stoliki::SprawdzCzyNastepnyNapoje()
{
	if (next_napoje_ != nullptr) return true;
	return false;
}

bool Stoliki::SprawdzCzyNastepnyJedzenie()
{
	if (next_jedzenie_ != nullptr) return true;
	return false;
}

bool Stoliki::SprawdzCzyZjedzone()
{
	if (next_zjedzone_ != nullptr) return true;
	return false;
}

bool Stoliki::SprawdzStatus(char c)
{
	switch (c)
	{
	case 'w':
		if(wolny_stolik_) return true;
		return false;
	case 'd':
		if(dolaczony_) return true;
		return false;
	case 'j':
		if(jedzenie_) return true;
		return false;
	case 'n':
		if(napoje_) return true;
		return false;
	case 'z':
		if(zjedzone_) return true;
		return false;
	default:
		break;
	}
}

grupaKlientow* Stoliki::ZwrocAktualnaGrupe()
{
	return aktualna_grupa_;
}

Stoliki* Stoliki::ZwrocPomocniczy()
{
	return stolik_pomocniczy_;
}

Stoliki* Stoliki::ZwrocNastepnyObsluga()
{
	return next_obs³uga_;
}

Stoliki* Stoliki::ZwrocNastepnyNapoje()
{
	return next_napoje_;
}

Stoliki* Stoliki::ZwrocNastepnyJedzenie()
{
	return next_jedzenie_;
}

Stoliki* Stoliki::ZwrocNastepnyZjedzone()
{
	return next_zjedzone_;
}

Stoliki* Stoliki::ZwrocNastepny()
{
	return next_;
}

bool Stoliki::SprawdzCzyGrupaPrzypisana()
{
	if (aktualna_grupa_ != nullptr) return true;
	return false;
}

bool Stoliki::SprawdzCzyPomocniczyPrzypisany()
{
	if (stolik_pomocniczy_ != nullptr) return true;
	return false;
}