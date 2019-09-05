#include "stdafx.h"
#include "Hall.h"

Sala::Sala()
{
	liczba_kelnerow_ = 13;
	liczba_stolikow2_os_ = 8;
	liczba_stolikow3_os_ = 14;
	liczba_stolikow4_os_ = 4;
	kierownik_sali_ = nullptr;

	Kelner* kelner = new Kelner;
	Stoliki* stoliki = new Stoliki;

	for (auto i = 1; i <= liczba_kelnerow_ - 1; i++) {
		kelner->UstawId(i);
		lista_kelnerow_.push(kelner);
		kelner->UstawNastepny(new Kelner);
		kelner = kelner->ZwrocNastepny();
	}
	lista_kelnerow_.push(kelner);

	for (auto i = 1; i <= liczba_stolikow2_os_ - 1; i++) {
		stoliki->NadajWielkosc(2);
		lista_stolikow2_.push(stoliki);
		wszystkie_stoliki_.push(stoliki);
		stoliki->UstawNastepny(new Stoliki);
		stoliki = stoliki->ZwrocNastepny();
	}
	stoliki->NadajWielkosc(2);
	lista_stolikow2_.push(stoliki);
	wszystkie_stoliki_.push(stoliki);

	stoliki = new Stoliki;
	for (auto i = 1; i <= liczba_stolikow3_os_ - 1; i++) {
		stoliki->NadajWielkosc(3);
		lista_stolikow3_.push(stoliki);
		wszystkie_stoliki_.push(stoliki);
		stoliki->UstawNastepny(new Stoliki);
		stoliki = stoliki->ZwrocNastepny();
	}
	stoliki->NadajWielkosc(3);
	lista_stolikow3_.push(stoliki);
	wszystkie_stoliki_.push(stoliki);

	stoliki = new Stoliki;
	for (auto i = 1; i <= liczba_stolikow4_os_ - 1; i++) {
		stoliki->NadajWielkosc(4);
		lista_stolikow4_.push(stoliki);
		wszystkie_stoliki_.push(stoliki);
		stoliki->UstawNastepny(new Stoliki);
		stoliki = stoliki->ZwrocNastepny();
	}
	stoliki->NadajWielkosc(4);
	lista_stolikow4_.push(stoliki);
	wszystkie_stoliki_.push(stoliki);
}

Sala::~Sala()
{
	while (wszystkie_stoliki_.size() != 0)
	{
		Stoliki* stoliki = wszystkie_stoliki_.front();
		if (stoliki->SprawdzCzyGrupaPrzypisana()) delete stoliki->ZwrocAktualnaGrupe();
		wszystkie_stoliki_.pop();
		delete stoliki;
	}
}

void Sala::PrzypiszKierownika(Kierownik* kierownik)
{
	kierownik_sali_ = kierownik;
}

void Sala::DodajDoObslugi(Stoliki* stoliki)
{
	stoliki_do_obslugi_.push(stoliki);
}

void Sala::UsunZObslugi()
{
	stoliki_do_obslugi_.pop();
}

void Sala::DodajDoNapojow(Stoliki* stoliki)
{
	pom_stolik_napoje_.push(stoliki);
}

void Sala::UsunZNapojow()
{
	pom_stolik_napoje_.pop();
}

void Sala::DodajDoJedzenia(Stoliki* stoliki)
{
	pom_stolik_jedzenie_.push(stoliki);
}

void Sala::UsunZJedzenia()
{
	pom_stolik_jedzenie_.pop();
}

void Sala::DodajDoZjedzonych(Stoliki* stoliki)
{
	pom_stolik_zjedzone_.push(stoliki);
}

void Sala::UsunZeZjedzonych()
{
	pom_stolik_zjedzone_.pop();
}

void Sala::UsunZeWszystkich()
{
	wszystkie_stoliki_.pop();
}

void Sala::UsunZListyKelnerow()
{
	lista_kelnerow_.pop();
}

int Sala::podajRozimar2()
{
	return lista_stolikow2_.size();
}

std::queue<Kelner*> Sala::WskazListeKelnera()
{
	return lista_kelnerow_;
}

std::queue <Stoliki*> Sala::WskazListe2()
{
	return lista_stolikow2_;
}

std::queue <Stoliki*> Sala::WskazListe3()
{
	return lista_stolikow3_;
}

std::queue <Stoliki*> Sala::WskazListe4()
{
	return lista_stolikow4_;
}

std::queue <Stoliki*> Sala::WskazListeDoObslugi()
{
	return stoliki_do_obslugi_;
}

std::queue <Stoliki*> Sala::WskazListeNapoje()
{
	return pom_stolik_napoje_;
}

std::queue <Stoliki*> Sala::WskazListeJedzenie()
{
	return pom_stolik_jedzenie_;
}

std::queue <Stoliki*> Sala::WskazListeZjedzone()
{
	return pom_stolik_zjedzone_;
}

std::queue<Stoliki*> Sala::WskazListeWszystkie()
{
	return wszystkie_stoliki_;
}

