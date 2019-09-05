#include "stdafx.h"
#include "Customer Group.h"
#include <iostream>
#include <ctime>

grupaKlientow::grupaKlientow()
{
	aktualny_kelner_ = nullptr;
	next_ = nullptr;
	previous_ = nullptr;
	next_kolejka_ = nullptr;
	czas_opuszczenia_bufetu_ = 0;
	czas_dostania_stolika_ = 0;
	czas_pojawienia_sie_na_sali_ = 0;
	czas_obslugi_ = 0;
	srand(time(NULL));
	wielkosc_grupy_ = rand() % 101;
	//losowanie_wielkosci_grupy << wielkosc_grupy << std::endl;
	srand(time(NULL));
	alarmowe_ = rand() % 101;
	if (wielkosc_grupy_ <= prawd_grupy1_) wielkosc_grupy_ = 1;
	else if (wielkosc_grupy_ > prawd_grupy1_ && wielkosc_grupy_ <= prawd_grupy1_ + prawd_grupy2_) wielkosc_grupy_ = 2;
	else if (wielkosc_grupy_ > prawd_grupy1_ + prawd_grupy2_ && wielkosc_grupy_ <= prawd_grupy1_ + prawd_grupy2_ + prawd_grupy3_) wielkosc_grupy_ = 3;
	else wielkosc_grupy_ = 4;
	if (alarmowe_ >= prawd_alarmu_) alarm_ = false;
	else alarm_ = true;
	srand(time(NULL));
	auto x = rand() % 100;
	if (x % 2 == 0) bufet_ = true;
	else bufet_ = false;
}

grupaKlientow::~grupaKlientow() = default;

void grupaKlientow::UstawNastepnaKolejka(grupaKlientow* grupa)
{
	next_kolejka_ = grupa;
}

void grupaKlientow::UstawNastepna(grupaKlientow* grupa)
{
	next_ = grupa;
}

void grupaKlientow::UstawPoprzednia(grupaKlientow* grupa)
{
	previous_ = grupa;
}

void grupaKlientow::zeruj()
{
	next_ = nullptr;
	previous_ = nullptr;
	next_kolejka_ = nullptr;
}

void grupaKlientow::UstawId(Statystyki* statystyki)
{
	id_grupy_ = statystyki->PodajLiczbeWszystkichUtworzonych();
}

void grupaKlientow::UstawCzasOpuszczeniaBufetu(double czas)
{
	czas_opuszczenia_bufetu_ = czas;
}

void grupaKlientow::UstawCzasPlacenia(double czas)
{
	czas_placenia_ = czas;
}

void grupaKlientow::UstawCzasPojawieniaSieNaSali(double czas)
{
	czas_pojawienia_sie_na_sali_ = czas;
}

void grupaKlientow::UstawCzasDostaniaStolika(double czas)
{
	czas_dostania_stolika_ = czas;
}

void grupaKlientow::UstawCzasObslugi(double czas)
{
	czas_obslugi_ = czas;
}

void grupaKlientow::PrzypiszKelnera(Kelner* kelner)
{
	aktualny_kelner_ = kelner;
}

bool grupaKlientow::SprawdzCzyNastepna()
{
	if(next_!=nullptr) return true;
	return false;
}

bool grupaKlientow::SprawdzCzyPoprzednia()
{
	if (previous_ != nullptr) return true;
	return false;
}

bool grupaKlientow::SprawdzCzyNastepnaKolejka()
{
	if (next_kolejka_ != nullptr) return true;
	return false;
}

bool grupaKlientow::SprawdzCzyBufet()
{
	if (bufet_) return true;
	return false;
}

bool grupaKlientow::SprawdzCzyAlarm()
{
	if (alarm_) return true;
	return false;
}

bool grupaKlientow::SprawdzCzyKelnerPrzypisany()
{
	if (aktualny_kelner_ != nullptr) return true;
	return false;
}

int grupaKlientow::PodajId()
{
	return id_grupy_;
}

int grupaKlientow::PodajWielkosc()
{
	return wielkosc_grupy_;
}

double grupaKlientow::PodajCzasPlacenia()
{
	return czas_placenia_;
}

double grupaKlientow::PodajCzasOpuszczeniaBufetu()
{
	return czas_opuszczenia_bufetu_;
}

double grupaKlientow::PodajCzasPojawieniaSieNaSali()
{
	return czas_pojawienia_sie_na_sali_;
}

grupaKlientow* grupaKlientow::ZwrocNastepny()
{
	return next_;
}

grupaKlientow* grupaKlientow::ZwrocPoprzedni()
{
	return previous_;
}

grupaKlientow* grupaKlientow::ZwrocNastepnyKolejka()
{
	return next_kolejka_;
}

double grupaKlientow::PodajCzasDostaniaStolika()
{
	return czas_dostania_stolika_;
}

double grupaKlientow::PodajCzasObslugi()
{
	return czas_obslugi_;
}

Kelner* grupaKlientow::ZwrocAktualnegoKelnera()
{
	return aktualny_kelner_;
}

