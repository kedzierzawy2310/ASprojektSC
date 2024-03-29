// ASprojektSC.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

/*
#pragma once
#include "Classes.h"
#include "Time Events.h"
#include <random>
#include <chrono>

//------------------------------------------------------------------------------------------- PARAMETRY GENERATORÓW -----------------------------------------------------------------------------------------------------------------

double mean_a = 650; //modyfikacja możliwa - 1500
double sigma_a = 10;	//modyyfikacja możliwa - 100
double mean_b = 2900;
double sigma_b = 80; //modyfikacja możliwa - 80
double mean_c = 4200;
double sigma_c = 50;
double lambda_kasy = 1 / 3000.0; //modyfikacja możliwa - 1/220
double lambda_konsumpcja = 1 / 2020.0;
double lambda_jedzenie = 1 / 3000.0; //modyfikacja możliwa - 1/2000
double lambda_napoje = 1 / 6000.0; //modyfikacja możliwa - 1/370

double prawd_grupy1 = 0.11 * 100;
double prawd_grupy2 = 0.33 * 100;
double prawd_grupy3 = 0.33 * 100;
double prawd_grupy4 = 0.23 * 100;
double prawd_alarmu = 0.70 * 100;

//------------------------------------------------------------------------------- DEFINICJA KONSTRUKTORÓW KLAS RESTAURACYJNYCH -------------------------------------------------------------------------------------------------------------

grupaKlientow::grupaKlientow(){ 
	aktualnyKelner = nullptr;
	next = nullptr;
	previous = nullptr;
	czas_opuszczenia_bufetu = 0;
	czas_dostania_stolika = 0;
	czas_pojawienia_sie_na_sali = 0;
	czas_obslugi = 0;
	this->id_grupy = Restauracja::klienci.kolejka.size();
	srand(time(NULL));
	wielkosc_grupy = rand() % 101;
	losowanie_wielkosci_grupy << wielkosc_grupy << std::endl;
	srand(time(NULL));
	alarmowe = rand() % 101;
	if (wielkosc_grupy <= prawd_grupy1) wielkosc_grupy = 1;
	else if (wielkosc_grupy > prawd_grupy1 && wielkosc_grupy <= prawd_grupy1 + prawd_grupy2) wielkosc_grupy = 2;
	else if (wielkosc_grupy > prawd_grupy1 + prawd_grupy2 && wielkosc_grupy <= prawd_grupy1 + prawd_grupy2 + prawd_grupy3) wielkosc_grupy = 3;
	else wielkosc_grupy = 4;
	if (alarmowe >= prawd_alarmu) alarm = false;
	else alarm = true;
	srand(time(NULL));
	int x = rand() % 100;
	if (x % 2 == 0) bufet = true;
	else bufet = false;
	Restauracja::klienci.kolejka.push(this);
}

grupaKlientow::~grupaKlientow() {
	if (ZdarzeniaCzasowe::czas_systemowy <= ZdarzeniaCzasowe::koniec_symulacji) std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << this->id_grupy << " opuscila lokal." << std::endl;
}

Bufet::Bufet() {
	customer_number_ = 0;
	buffet_size_ = 20;
}

Kierownik::Kierownik() {
	wolnyKierownik = true;
	aktualnaGrupa = nullptr;
	liczba_obsluzen = 0;
}

Kelner::Kelner() {
	id_kelnera = 0;
	wolny_kelner = true;
	next = nullptr;
	liczba_obsluzen = 0;
}

Kasa::Kasa() {
	cashier_id_ = Restauracja::listaKasjerow.size();
	aktualnaGrupa = nullptr;
	next = nullptr;
	service_number_ = 0;
}

Stoliki::Stoliki() {
	wielkoscStolika = 0;
	wolnyStolik = true;
	aktualna_grupa = nullptr;
	next = nullptr;
	dolaczony = false;
	jedzenie = false;
	napoje = false;
	zjedzone = false;
	stolik_pomocniczy = nullptr;
	next_jedzenie = nullptr;
	next_napoje = nullptr;
	next_obsługa = nullptr;
	next_zjedzone = nullptr;
}

Sala::Sala() {
	liczba_kelnerow = 13; //modyfikacja możliwa
	liczba_stolikow2_os = 8;
	liczba_stolikow3_os = 14;
	liczba_stolikow4_os = 4;

	pom1 = nullptr;
	pom2 = nullptr;
	pom3 = nullptr;
	pom4 = nullptr;
	
	stolik_zjedzone = nullptr;
	stolik_jedzenie = nullptr;
	stolik_do_usuwania = nullptr;
	stolik_napoje = nullptr;

	kierownikSali = new Kierownik;

	Kelner* kelner = new Kelner;
	kelner->id_kelnera = 1;
	pom1 = kelner;
	lista_kelnerow.push(kelner);
	
	Stoliki* stolik2 = new Stoliki;
	stolik2->wielkoscStolika = 2;
	pom2 = stolik2;
	lista_stolikow2.push(stolik2);
	
	Stoliki* stolik3 = new Stoliki;
	stolik3->wielkoscStolika = 3;
	pom3 = stolik3;
	lista_stolikow3.push(stolik3);
	
	Stoliki* stolik4 = new Stoliki;
	stolik4->wielkoscStolika = 4;
	pom4 = stolik4;
	lista_stolikow4.push(stolik4);
	
	for (int i = 2; i <= liczba_kelnerow; i++) {
		Kelner* k = new Kelner;
		k->id_kelnera = i;
		pom1->next = k;
		pom1 = k;
		lista_kelnerow.push(k);
	}
	for (int i = 2; i <= liczba_stolikow2_os; i++) {
		Stoliki* s = new Stoliki;
		s->wielkoscStolika = 2;
		pom2->next = s;
		pom2 = s;
		lista_stolikow2.push(s);
	}
	for (int i = 2; i <= liczba_stolikow3_os; i++) {
		Stoliki* s = new Stoliki;
		s->wielkoscStolika = 3;
		pom3->next = s;
		pom3 = s;
		lista_stolikow3.push(s);
	}
	for (int i = 2; i <= liczba_stolikow4_os; i++) {
		Stoliki* s = new Stoliki;
		s->wielkoscStolika = 4;
		pom4->next = s;
		pom4 = s;
		lista_stolikow4.push(s);
	}
}

Restauracja::Restauracja(){
	Kasa* kasa = new Kasa;
	kasa->cashier_id_ = 1;
	Kasa* pom = kasa;
	
	bufet = new Bufet;
	bufet->customer_number_ = 0;
	bufet->buffet_size_ = 20;
	liczbaKasjerow = 6;
	listaKasjerow.push(kasa);
	
	for (int i = 2; i <= liczbaKasjerow; i++) {
		Kasa* kas = new Kasa;
		kas->cashier_id_ = i;
		pom->next = kas;
		pom = kas;
		listaKasjerow.push(kas);
	}
}

//-------------------------------------------------------------------------------------------------- GENERATORY ------------------------------------------------------------------------------------------------------------------

double losuj(int rozklad) {

	double randomowa;
	std::default_random_engine gen;
	std::normal_distribution<double> rozklad_klient(mean_a, sigma_a); //ROZKŁAD NORMALNY - POJAWIENIE SIĘ KLIENTÓW
	std::normal_distribution<double> rozklad_bufet(mean_b, sigma_b); //ROZKŁAD  NORMALNY - CZAS W BUFECIE
	std::normal_distribution<double> rozklad_alarm(mean_c, sigma_c); //ROZKŁAD  NORMALNY - ALARM
	const std::exponential_distribution<double> rozklad_kasy(lambda_kasy); //ROZKŁAD WYKŁADNICZY - CZAS GRUPY KLIENTÓW PRZY KASIE
	const std::exponential_distribution<double> rozklad_konsumpcja(lambda_konsumpcja); //ROZKŁAD WYKŁADNICZY - CZAS KONSUMPCJI KLIENTÓW 
	const std::exponential_distribution<double> rozklad_jedzenie(lambda_jedzenie); //ROZKŁAD WYKŁADNICZY - CZAS OCZEKIWANIA NA DANIE GŁÓWNE
	const std::exponential_distribution<double> rozklad_napoje(lambda_napoje); //ROZKŁAD WYKŁADNICZY - CZAS OCZEKIWANIA NA NAPOJE

	//-------------------------------------------------------------------------------------------- WYBÓR ROZKŁADU ----------------------------------------------------------------------------------------------------------------

	gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
	switch (rozklad)
	{
		case 1:
			randomowa = abs(rozklad_klient(gen));
			Statystyki::losowanie_klienci.push_back(randomowa);
			break;
		case 2:
			randomowa = 10; //modyfikacja możliwa
			break;
		case 3:
			randomowa = abs(rozklad_napoje(gen));
			Statystyki::losowanie_napoje.push_back(randomowa);
			break;
		case 4:
			randomowa = abs(rozklad_jedzenie(gen));
			Statystyki::losowanie_jedzenie.push_back(randomowa);
			break;
		case 5:
			randomowa = abs(rozklad_konsumpcja(gen));
			Statystyki::losowanie_konsumpcja.push_back(randomowa);
			break;
		case 6:
			randomowa = abs(rozklad_kasy(gen));
			Statystyki::losowanie_kasy.push_back(randomowa);
			break;
		case 7:
			randomowa = abs(rozklad_bufet(gen));
			Statystyki::losowanie_bufet.push_back(randomowa);
			break;
		case 8:
			randomowa = abs(rozklad_alarm(gen));
			Statystyki::losowanie_alarm.push_back(randomowa);
			break;
		default:
			std::cout << ZdarzeniaCzasowe::czas_systemowy << " Nie mozna wybrac rozkladu" << std::endl;
			randomowa = abs(rand() % 100 + 1);
			break;
	}
	return randomowa;
}

//-------------------------------------------------------------------------- KONSTRUKTORY KLASY STATYCZNEJ I JEJ WEWNĘTRZNEJ KLASY ZLICZAJĄCEJ -----------------------------------------------------------------------------------

Statystyki::Statystyki()
{
	liczba_wszystkich_klientow = 0;
	liczba_obecnych_klientow = 0;
	liczba_alarmow = 0;
	count_sala = 0;
	count_kasy = 0;
	count_stolik = 0;
	count_obsluga = 0;
}

Statystyki::Zlicz::Zlicz()
{
	next = nullptr;
	zlicz_kolejka_sala = 0;
	zlicz_kolejka_kasy = 0;
	zlicz_czas_oczekiwania_obsluga = 0;
	zlicz_czas_oczekiwania_stolik = 0;
}

*/