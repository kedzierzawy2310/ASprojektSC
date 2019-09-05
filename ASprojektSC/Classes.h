#pragma once

#include "stdafx.h"
/*
#include <queue>
#include <iostream>
#include <vector>
#include <fstream>

class ZdarzeniaCzasowe;

static int faza_poczatkowa = 66;

//--------------------------------------------------------------------------------------------- DEKLARACJA KLAS RESTAURACYJNYCH --------------------------------------------------------------------------------------------------

class Kelner {
public:
	int liczba_obsluzen;
	int id_kelnera;
	bool wolny_kelner;
	Kelner* next;

	Kelner();
};

class grupaKlientow {
public:
	int wielkosc_grupy;
	int id_grupy;
	int alarmowe;
	bool bufet;
	bool alarm;
	double czas_opuszczenia_bufetu;
	double czas_placenia;
	double czas_pojawienia_sie_na_sali;
	double czas_dostania_stolika;
	double czas_obslugi;
	Kelner* aktualnyKelner;
	grupaKlientow* next;
	grupaKlientow* previous;
	grupaKlientow* next_kolejka;

	grupaKlientow(); 
	~grupaKlientow();
};

class Bufet {
public:
	static int customer_number_;
	static int buffet_size_;

	Bufet();
};

class Kierownik {
public:
	grupaKlientow* aktualnaGrupa;
	bool wolnyKierownik;
	int liczba_obsluzen;

	Kierownik();
};

class Kasa {
public:
	int service_number_;
	int cashier_id_;
	grupaKlientow* aktualnaGrupa;
	Kasa* next;

	Kasa();
};

class Stoliki {
public:
	grupaKlientow* aktualna_grupa;
	int wielkoscStolika;
	bool wolnyStolik;
	bool dolaczony;
	bool jedzenie;
	bool napoje;
	bool zjedzone;
	Stoliki* next;
	Stoliki* next_obs³uga;
	Stoliki* next_napoje;
	Stoliki* next_jedzenie;
	Stoliki* next_zjedzone;
	Stoliki* stolik_pomocniczy;

	Stoliki();
};


class Kolejka
{
public:
	std::queue<grupaKlientow*> kolejka;
};

class Sala {
public:
	int liczba_kelnerow;
	int liczba_stolikow2_os;
	int liczba_stolikow3_os;
	int liczba_stolikow4_os;

	static Kierownik* kierownikSali;
	static std::queue <Kelner*> lista_kelnerow;
	static std::queue <Stoliki*> pom_stolik_napoje;
	static std::queue <Stoliki*> pom_stolik_zjedzone;
	static std::queue <Stoliki*> pom_stolik_jedzenie;
	static std::queue <Stoliki*> lista_stolikow2;
	static std::queue <Stoliki*> lista_stolikow3;
	static std::queue <Stoliki*> lista_stolikow4;
	static std::queue <Stoliki*> stoliki_do_obslugi;

	static Kelner* kelner;
	static Stoliki* stolik;
	static Stoliki* stolik_obs³uga;
	static Stoliki* stolik_zjedzone;
	static Stoliki* stolik_jedzenie;
	static Stoliki* stolik_do_usuwania;
	static Stoliki* stolik_napoje;

	Kelner* pom1;
	Stoliki* pom2;
	Stoliki* pom3;
	Stoliki* pom4;

	Sala();
};

class Restauracja {
public:
	static Kolejka klienci;
	static Kolejka kolejka_sala;
	static Kolejka kolejka_bufet;
	static Kolejka kolejka_kasy;
	static Kolejka bufet_lista;
	static std::queue <Kasa*> listaKasjerow;
	int liczbaKasjerow;
	static Bufet* bufet;
	static Kasa* kasjer;
	static grupaKlientow* pom_kol;
	static grupaKlientow* pom_kol_kasa;
	static grupaKlientow* pom_kol_buf;
	
	Restauracja();
};

//--------------------------------------------------------------------------- DEKLARACJA KLASY STATYSTYCZNEJ I JEJ WEWNÊTRZNEJ KLASY ZLICZAJ¥CEJ -------------------------------------------------------------------------------------------------------------

class Statystyki
{
public:
	static int liczba_wszystkich_klientow;
	static int liczba_obecnych_klientow;
	static int liczba_kolejka_do_kasy;
	static int liczba_kolejka_do_sali;
	static int liczba_kolejka_do_bufetu;
	static int liczba_alarmow;
	static int count_sala;
	static int count_kasy;
	static int count_stolik;
	static int count_obsluga;
	static std::vector<double> losowanie_klienci;
	static std::vector<double> losowanie_bufet;
	static std::vector<double> losowanie_konsumpcja;
	static std::vector<double> losowanie_jedzenie;
	static std::vector<double> losowanie_napoje;
	static std::vector<double> losowanie_kasy;
	static std::vector<double> losowanie_alarm;

	Statystyki();
	class Zlicz
	{
	public:
		Zlicz* next;
		static Zlicz* first_sala;
		static Zlicz* first_kasy;
		static Zlicz* first_stolik;
		static Zlicz* first_obsluga;
		static Zlicz* pom_zlicz_sala;
		static Zlicz* pom_zlicz_kasy;
		static Zlicz* pom_zlicz_stolik;
		static Zlicz* pom_zlicz_obsluga;
		int zlicz_kolejka_sala;
		int zlicz_kolejka_kasy;
		double zlicz_czas_oczekiwania_stolik;
		double zlicz_czas_oczekiwania_obsluga;
		Zlicz();
	};
};

*/
