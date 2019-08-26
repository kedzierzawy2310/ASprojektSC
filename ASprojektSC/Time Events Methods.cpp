#include "stdafx.h"
#pragma once
#include "Time Events.h"

//------------------------------------------------------------------------------------------------- ZDARZENIA CZASOWE ------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------ DEKLARACJA U¯YWANYCH OBIEKTÓW I ZMIENNYCH KLAS DO IMPLEMENTACJI ZDARZEÑ CZASOWYCH I PÊTLI G£ÓWNEJ ----------------------------------------------------------------- 

int Statystyki::liczba_wszystkich_klientow;
int Statystyki::liczba_obecnych_klientow;
int Statystyki::liczba_kolejka_do_kasy;
int Statystyki::liczba_kolejka_do_bufetu;
int Statystyki::liczba_kolejka_do_sali;
int Statystyki::liczba_alarmow;
int Statystyki::count_sala;
int Statystyki::count_kasy;
int Statystyki::count_stolik;
int Statystyki::count_obsluga;
std::vector<double> Statystyki::losowanie_klienci;
std::vector<double> Statystyki::losowanie_bufet;
std::vector<double> Statystyki::losowanie_kasy;
std::vector<double> Statystyki::losowanie_konsumpcja;
std::vector<double> Statystyki::losowanie_napoje;
std::vector<double> Statystyki::losowanie_jedzenie;
std::vector<double> Statystyki::losowanie_alarm;
Statystyki::Zlicz* Statystyki::Zlicz::pom_zlicz_sala;
Statystyki::Zlicz* Statystyki::Zlicz::pom_zlicz_kasy;
Statystyki::Zlicz* Statystyki::Zlicz::pom_zlicz_stolik;
Statystyki::Zlicz* Statystyki::Zlicz::pom_zlicz_obsluga;
Statystyki::Zlicz* Statystyki::Zlicz::first_sala;
Statystyki::Zlicz* Statystyki::Zlicz::first_kasy;
Statystyki::Zlicz* Statystyki::Zlicz::first_stolik;
Statystyki::Zlicz* Statystyki::Zlicz::first_obsluga;
Kolejka Restauracja::klienci;
Kolejka Restauracja::bufet_lista;
std::queue<Kasa*> Restauracja::listaKasjerow;
Kolejka Restauracja::kolejka_bufet;
Kolejka Restauracja::kolejka_kasy;
Kolejka Restauracja::kolejka_sala;
std::queue<Kelner*> Sala::lista_kelnerow;
std::queue<Stoliki*> Sala::lista_stolikow2;
std::queue<Stoliki*> Sala::lista_stolikow3;
std::queue<Stoliki*> Sala::lista_stolikow4;
double ZdarzeniaCzasowe::czas_systemowy;
double ZdarzeniaCzasowe::koniec_symulacji;
int Bufet::liczbaOsob;
int Bufet::wielkoscBufetu;
Kierownik* Sala::kierownikSali;
std::queue<Stoliki*> Sala::pom_stolik_napoje;
std::queue<Stoliki*> Sala::pom_stolik_jedzenie;
std::queue<Stoliki*> Sala::pom_stolik_zjedzone;
std::queue<Stoliki*> Sala::stoliki_do_obslugi;
Bufet* Restauracja::bufet;
Kasa* Restauracja::kasjer;
grupaKlientow* Restauracja::pom_kol;
grupaKlientow* Restauracja::pom_kol_kasa;
grupaKlientow* Restauracja::pom_kol_buf;
Kelner* Sala::kelner;
Stoliki* Sala::stolik;
Stoliki* Sala::stolik_obs³uga;
Stoliki* Sala::stolik_zjedzone;
Stoliki* Sala::stolik_jedzenie;
Stoliki* Sala::stolik_napoje;
Stoliki* Sala::stolik_do_usuwania;
std::vector<Komunikat*> ZdarzeniaCzasowe::komzdarzeniaCzasowe;
double losuj(int rozklad);

//------------------------------------------------------------------------------------ METODA DODAWANIA ZDARZEÑ CZASOWYCH DO LISTY -----------------------------------------------------------------------------------------------

void ZdarzeniaCzasowe::dodaj(Komunikat* komunikat)
{
		for (int i = 0; i<komzdarzeniaCzasowe.size(); i++)
		{
			if (komzdarzeniaCzasowe[0] != nullptr && komunikat->czas_wykonania >= komzdarzeniaCzasowe[i]->czas_wykonania)
			{
				komzdarzeniaCzasowe.insert(komzdarzeniaCzasowe.begin() + i, komunikat); return;
			}
		}
	komzdarzeniaCzasowe.push_back(komunikat);
}


//----------------------------------------------------------------------------------------- KONSTRUKTOR KLASY ZDARZENIA CZASOWE --------------------------------------------------------------------------------------------------


ZdarzeniaCzasowe::ZdarzeniaCzasowe(int zdarzenie)
{
	this->zdarzenie=zdarzenie;
	this->komunikat = new Komunikat(this);
}

//--------------------------------------------------------------------------- METODA WYKONAWCZA - EXECUTE - ZDARZEÑ CZASOWYCH (WYBIERANIE ZDARZEÑ) -------------------------------------------------------------------------------

void ZdarzeniaCzasowe::execute()
{
	ZdarzeniaCzasowe* z;
	grupaKlientow * grupa;
	grupaKlientow* wlasciwa;
	Stoliki * stolik;
	Statystyki::Zlicz* zlicz;
	bool flaga;
	Stoliki* pom = nullptr;
	Stoliki* pom2 = nullptr;
	Stoliki* pom5 = nullptr;
	grupaKlientow* pom3 = nullptr;
	grupaKlientow* pom4 = nullptr;
	grupaKlientow* pom6 = nullptr;


	switch (this->zdarzenie)
	{

	//--------------------------------------------------------------------------------- POJAWIENIE SIÊ NOWEJ GRUPY KLIENTÓW W SYSTEMIE ------------------------------------------------------------------------------------------------

	case 1:
		grupa = new grupaKlientow;
		Statystyki::liczba_wszystkich_klientow++;
		Statystyki::liczba_obecnych_klientow++;
		faza1 << Statystyki::liczba_obecnych_klientow << std::endl;
		faza2 << Statystyki::liczba_wszystkich_klientow << std::endl;
		if (Statystyki::liczba_wszystkich_klientow>faza_poczatkowa)
		{
			kolejka_sala << Statystyki::liczba_kolejka_do_sali << std::endl;
			kolejka_kasa << Statystyki::liczba_kolejka_do_kasy << std::endl;
		}
		if (grupa->bufet == false) {
			if(Restauracja::kolejka_sala.kolejka.empty())
			{
				Restauracja::pom_kol = grupa;
			}
			else
			{
				Restauracja::pom_kol->next_kolejka = grupa;
				Restauracja::pom_kol = grupa;
			}
			Restauracja::kolejka_sala.kolejka.push(grupa);
			std::cout << ZdarzeniaCzasowe::czas_systemowy << " Dodano grupe o ID: " << grupa->id_grupy << " do kolejki do sali" << std::endl;
			Statystyki::liczba_kolejka_do_sali++;
			if(Statystyki::liczba_wszystkich_klientow>=faza_poczatkowa)
			{
				zlicz = new Statystyki::Zlicz;
				zlicz->zlicz_kolejka_sala = Statystyki::liczba_kolejka_do_sali;
				if (Statystyki::Zlicz::first_sala == nullptr)
				{
					Statystyki::Zlicz::pom_zlicz_sala = zlicz;
					Statystyki::Zlicz::first_sala = zlicz;
				}
				else
				{
					Statystyki::Zlicz::pom_zlicz_sala->next = zlicz;
					Statystyki::Zlicz::pom_zlicz_sala = zlicz;
				}
				Statystyki::count_sala++;

				grupa->czas_pojawienia_sie_na_sali = ZdarzeniaCzasowe::czas_systemowy;
			}
		}
		else {
			if (Restauracja::kolejka_bufet.kolejka.empty())
			{
				Restauracja::pom_kol_buf = grupa;
			}
			else
			{
				Restauracja::pom_kol_buf->next_kolejka = grupa;
				Restauracja::pom_kol_buf = grupa;
			}
			Restauracja::kolejka_bufet.kolejka.push(grupa);
			std::cout << ZdarzeniaCzasowe::czas_systemowy << " Dodano grupe o ID: " << grupa->id_grupy << " do kolejki do bufetu" << std::endl;
			Statystyki::liczba_kolejka_do_bufetu++;
		}
		z = new ZdarzeniaCzasowe(1);
		ZdarzeniaCzasowe::dodaj(z->komunikat);
		std::cout << ZdarzeniaCzasowe::czas_systemowy << " Zaplanowano nowa grupe klientow" << std::endl;
		break;

	//------------------------------------------------------------------------------------------- POWRÓT KIEROWNIKA SALI ---------------------------------------------------------------------------------------------------------

	case 2:
		Sala::kierownikSali->liczba_obsluzen++;
		Sala::kierownikSali->aktualnaGrupa = nullptr;
		Sala::kierownikSali->wolnyKierownik = true;
		std::cout << ZdarzeniaCzasowe::czas_systemowy << " Kierownik oczekuje na nastepna grupe" << std::endl;
		break;

	//---------------------------------------------------------------------------------------- PODANIE NAPOJÓW PRZEZ KELNERA -----------------------------------------------------------------------------------------------------

	case 3:
		if (!Sala::pom_stolik_napoje.empty())
		{
			stolik = Sala::pom_stolik_napoje.front();
			stolik->next_napoje = nullptr;
			Sala::pom_stolik_napoje.pop();

			stolik->napoje = true;
			std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << stolik->aktualna_grupa->id_grupy << " otrzymala napoje" << std::endl;
			stolik->aktualna_grupa->aktualnyKelner->liczba_obsluzen++;
			stolik->aktualna_grupa->aktualnyKelner->wolny_kelner = true;
			stolik->aktualna_grupa->aktualnyKelner = nullptr;
			if (Sala::pom_stolik_jedzenie.empty())
			{
				Sala::stolik_jedzenie = stolik;
			}
			else
			{
				Sala::stolik_jedzenie->next_jedzenie = stolik;
				Sala::stolik_jedzenie = stolik;
			}
			Sala::pom_stolik_jedzenie.push(stolik);
		}
		break;

	//---------------------------------------------------------------------------------------- PODANIE JEDZENIA PRZEZ KELNERA ----------------------------------------------------------------------------------------------------

	case 4:
		if (!Sala::pom_stolik_jedzenie.empty())
		{
			stolik = Sala::pom_stolik_jedzenie.front();
			stolik->next_jedzenie = nullptr;
			Sala::pom_stolik_jedzenie.pop();

			stolik->jedzenie = true;
			std::cout << ZdarzeniaCzasowe::czas_systemowy << " Podano posilek. Grupa " << stolik->aktualna_grupa->id_grupy << " zostala obsluzona" << std::endl;
			stolik->aktualna_grupa->aktualnyKelner->liczba_obsluzen++;
			stolik->aktualna_grupa->aktualnyKelner->wolny_kelner = true;
			stolik->aktualna_grupa->aktualnyKelner = nullptr;
			if (Sala::pom_stolik_zjedzone.empty())
			{
				Sala::stolik_zjedzone = stolik;
			}
			else
			{
				Sala::stolik_zjedzone->next_zjedzone = stolik;
				Sala::stolik_zjedzone = stolik;
			}
			Sala::pom_stolik_zjedzone.push(stolik);
			std::cout << ZdarzeniaCzasowe::czas_systemowy << " Rozpoczecie konsumpcji przez grupe " << stolik->aktualna_grupa->id_grupy << std::endl;
			z = new ZdarzeniaCzasowe(5);
			ZdarzeniaCzasowe::dodaj(z->komunikat);
		}
		break;

	//----------------------------------------------------------------------------- ZAKOÑCZENIE KONSUMPCJI PRZEZ KLIENTÓW JEDZ¥CYCH NA SALI --------------------------------------------------------------------------------------

	case 5:
		if (Sala::pom_stolik_zjedzone.empty()) break;
		stolik = Sala::pom_stolik_zjedzone.front();
		if (!Sala::pom_stolik_zjedzone.empty())
		{
			stolik->next_zjedzone = nullptr;
			Sala::pom_stolik_zjedzone.pop();
		}
		if (Restauracja::kolejka_kasy.kolejka.empty())
		{
			Restauracja::pom_kol_kasa = stolik->aktualna_grupa;
		}
		else
		{
			Restauracja::pom_kol_kasa->next_kolejka = stolik->aktualna_grupa;
			Restauracja::pom_kol_kasa = stolik->aktualna_grupa;
		}
		std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << stolik->aktualna_grupa->id_grupy << " zakonczyla konsumpcje" << std::endl;
		Restauracja::kolejka_kasy.kolejka.push(stolik->aktualna_grupa);
		std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << stolik->aktualna_grupa->id_grupy << " oczekuje w kolejce do kasy" << std::endl;
		Statystyki::liczba_kolejka_do_kasy++;
		if (Statystyki::liczba_wszystkich_klientow >= faza_poczatkowa)
		{
			zlicz = new Statystyki::Zlicz;
			zlicz->zlicz_kolejka_kasy = Statystyki::liczba_kolejka_do_kasy;
			if (Statystyki::Zlicz::first_kasy == nullptr)
			{
				Statystyki::Zlicz::pom_zlicz_kasy = zlicz;
				Statystyki::Zlicz::first_kasy = zlicz;
			}
			else
			{
				Statystyki::Zlicz::pom_zlicz_kasy->next = zlicz;
				Statystyki::Zlicz::pom_zlicz_kasy = zlicz;
			}
			Statystyki::count_kasy++;
		}
		stolik->aktualna_grupa = nullptr;
		stolik->wolnyStolik = true;
		stolik->jedzenie = false;
		stolik->napoje = false;
		if (stolik->stolik_pomocniczy != nullptr)
		{
			stolik->stolik_pomocniczy->dolaczony = false;
			stolik->stolik_pomocniczy->wolnyStolik = true;
			stolik->stolik_pomocniczy->stolik_pomocniczy = nullptr;
			stolik->stolik_pomocniczy = nullptr;
		}
		break;

	//----------------------------------------------------------------------------------- DOKONANIE P£ATNOŒCI PRZEZ GRUPÊ KLIENTÓW -----------------------------------------------------------------------------------------------

	case 6:
		Restauracja::kasjer = Restauracja::listaKasjerow.front();
		flaga = false;
		while (!flaga)
		{
			if (Restauracja::kasjer->aktualnaGrupa != nullptr && Restauracja::kasjer->aktualnaGrupa->czas_placenia == ZdarzeniaCzasowe::czas_systemowy) {
				grupa = Restauracja::kasjer->aktualnaGrupa;
				std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << grupa->id_grupy << " zaplacila za posilek (kasjer "<< Restauracja::kasjer->id_kasjera << ")" << std::endl;
				Restauracja::kasjer->liczba_obsluzen++;
				Restauracja::kasjer->aktualnaGrupa = nullptr;
				delete grupa;
				Statystyki::liczba_obecnych_klientow--;
				flaga = true;
			}
			else Restauracja::kasjer = Restauracja::kasjer->next;
		}
		break;

	//---------------------------------------------------------------------------------------- POWRÓT GRUPY KLIENTÓW Z BUFETU ----------------------------------------------------------------------------------------------------
	
	case 7:
		if(!Restauracja::bufet_lista.kolejka.empty())
		{
			grupa = Restauracja::bufet_lista.kolejka.front();
			flaga = false;
			while(!flaga)
			{
				if (grupa->czas_opuszczenia_bufetu == ZdarzeniaCzasowe::czas_systemowy)
				{
					wlasciwa = grupa;
					if (Restauracja::bufet_lista.kolejka.front() != wlasciwa)
					{
						if (wlasciwa->next != nullptr) 
						{
							wlasciwa->previous->next = wlasciwa->next;
							wlasciwa->next->previous = wlasciwa->previous;
						}
						wlasciwa->next = nullptr;
						if (Restauracja::bufet_lista.kolejka.back() == wlasciwa) wlasciwa->previous->next = nullptr;
						wlasciwa->previous = nullptr;
						grupa = Restauracja::bufet_lista.kolejka.front();
						while(Restauracja::bufet_lista.kolejka.size() != 0)
						{
							Restauracja::bufet_lista.kolejka.pop();
						}
						while (grupa != nullptr)
						{
							Restauracja::bufet_lista.kolejka.push(grupa);
							grupa = grupa->next;
						}
					}
					else
					{
						Restauracja::bufet_lista.kolejka.pop();
					}
					if (Restauracja::kolejka_kasy.kolejka.empty())
					{
						Restauracja::pom_kol_kasa = grupa;
					}
					else
					{
						Restauracja::pom_kol_kasa->next_kolejka = grupa;
						Restauracja::pom_kol_kasa = grupa;
					}
					std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << wlasciwa->id_grupy << " opuscila bufet" << std::endl;
					Restauracja::bufet->liczbaOsob = Restauracja::bufet->liczbaOsob - wlasciwa->wielkosc_grupy;
					std::cout << ZdarzeniaCzasowe::czas_systemowy << " Obecny stan bufetu: " << Restauracja::bufet->liczbaOsob << " z " << Restauracja::bufet->wielkoscBufetu << std::endl;
					Restauracja::kolejka_kasy.kolejka.push(wlasciwa);
					std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << wlasciwa->id_grupy << " oczekuje w kolejce do kasy" << std::endl;
					Statystyki::liczba_kolejka_do_kasy++;
					if (Statystyki::liczba_wszystkich_klientow >= faza_poczatkowa)
					{
						zlicz = new Statystyki::Zlicz;
						zlicz->zlicz_kolejka_kasy = Statystyki::liczba_kolejka_do_kasy;
						if (Statystyki::Zlicz::first_kasy == nullptr)
						{
							Statystyki::Zlicz::pom_zlicz_kasy = zlicz;
							Statystyki::Zlicz::first_kasy = zlicz;
						}
						else
						{
							Statystyki::Zlicz::pom_zlicz_kasy->next = zlicz;
							Statystyki::Zlicz::pom_zlicz_kasy = zlicz;
						}
						Statystyki::count_kasy++;
					}
					flaga = true;
				}
				else
				{
					if (grupa->next!=nullptr) grupa = grupa->next;
					else break;
				}
			}
		}
		break;

	//------------------------------------------------------------------------------------------------------- ALARM --------------------------------------------------------------------------------------------------------------

	case 8:
		std::cout << "ALARM POZAROWY!" << std::endl;
		if (Sala::stoliki_do_obslugi.size() > 0) {
			stolik = Sala::stoliki_do_obslugi.front();
			for (int i = 1; i <= Sala::stoliki_do_obslugi.size(); i++)
			{
				if (stolik->aktualna_grupa->alarm == true)
				{
					pom2 = stolik->next_obs³uga;
					stolik->next_obs³uga = nullptr;
					stolik->wolnyStolik = true;
					delete stolik->aktualna_grupa;
					stolik->aktualna_grupa = nullptr;
					if (stolik->stolik_pomocniczy != nullptr)
					{
						stolik->stolik_pomocniczy->stolik_pomocniczy = nullptr;
						stolik->stolik_pomocniczy->dolaczony = false;
						stolik->stolik_pomocniczy->wolnyStolik = true;
						stolik->stolik_pomocniczy = nullptr;
					}
					stolik = pom2;
					pom2 = nullptr;
				}
				else
				{
					if (pom == nullptr) {
						pom = stolik;
						stolik = stolik->next_obs³uga;
						pom->next_obs³uga = nullptr;
						pom5 = pom;
					}
					else
					{
						pom->next_obs³uga = stolik;
						pom = stolik;
						stolik = stolik->next_obs³uga;
						pom->next_obs³uga = nullptr;
					}
				}
			}
			while (Sala::stoliki_do_obslugi.size() != 0)
			{
				Sala::stoliki_do_obslugi.pop();
			}
			while (pom5 != nullptr)
			{
				Sala::stoliki_do_obslugi.push(pom5);
				if (pom5->next_obs³uga == nullptr) Sala::stolik_obs³uga = pom5;
				pom5 = pom5->next_obs³uga;
			}
		}
		pom = nullptr;
		if (Sala::pom_stolik_napoje.size() > 0) {
			stolik = Sala::pom_stolik_napoje.front();
			for (int i = 1; i <= Sala::pom_stolik_napoje.size(); i++)
			{
				if (stolik->aktualna_grupa->alarm == true)
				{
					pom2 = stolik->next_napoje;
					stolik->next_napoje = nullptr;
					stolik->wolnyStolik = true;
					stolik->aktualna_grupa->aktualnyKelner->wolny_kelner = true;
					stolik->aktualna_grupa->aktualnyKelner = nullptr;
					delete stolik->aktualna_grupa;
					stolik->aktualna_grupa = nullptr;
					if (stolik->stolik_pomocniczy != nullptr)
					{
						stolik->stolik_pomocniczy->stolik_pomocniczy = nullptr;
						stolik->stolik_pomocniczy->dolaczony = false;
						stolik->stolik_pomocniczy->wolnyStolik = true;
						stolik->stolik_pomocniczy = nullptr;
					}
					stolik = pom2;
					pom2 = nullptr;
				}
				else
				{
					if (pom == nullptr) {
						pom = stolik;
						stolik = stolik->next_napoje;
						pom->next_napoje = nullptr;
						pom5 = pom;
					}
					else
					{
						pom->next_napoje = stolik;
						pom = stolik;
						stolik = stolik->next_napoje;
						pom->next_napoje = nullptr;
					}
				}
			}
			while (Sala::pom_stolik_napoje.size() != 0)
			{
				Sala::pom_stolik_napoje.pop();
			}
			while (pom5 != nullptr)
			{
				Sala::pom_stolik_napoje.push(pom5);
				if (pom5->next_napoje == nullptr) Sala::stolik_napoje = pom5;
				pom5 = pom5->next_napoje;
			}
		}
		pom = nullptr;
		if (Sala::pom_stolik_jedzenie.size() > 0) {
			stolik = Sala::pom_stolik_jedzenie.front();
			for (int i = 1; i <= Sala::pom_stolik_jedzenie.size(); i++)
			{
				if (stolik->aktualna_grupa->alarm == true)
				{
					pom2 = stolik->next_jedzenie;
					stolik->napoje = false;
					stolik->next_jedzenie = nullptr;
					stolik->wolnyStolik = true;
					if (stolik->aktualna_grupa->aktualnyKelner != nullptr) {
						stolik->aktualna_grupa->aktualnyKelner->wolny_kelner = true;
						stolik->aktualna_grupa->aktualnyKelner = nullptr;
					}
					delete stolik->aktualna_grupa;
					stolik->aktualna_grupa = nullptr;
					if (stolik->stolik_pomocniczy != nullptr)
					{
						stolik->stolik_pomocniczy->stolik_pomocniczy = nullptr;
						stolik->stolik_pomocniczy->dolaczony = false;
						stolik->stolik_pomocniczy->wolnyStolik = true;
						stolik->stolik_pomocniczy = nullptr;
					}
					stolik = pom2;
					pom2 = nullptr;
				}
				else
				{
					if (pom == nullptr) {
						pom = stolik;
						stolik = stolik->next_jedzenie;
						pom->next_jedzenie = nullptr;
						pom5 = pom;
					}
					else
					{
						pom->next_jedzenie = stolik;
						pom = stolik;
						stolik = stolik->next_jedzenie;
						pom->next_jedzenie = nullptr;
					}
				}
			}
			while (Sala::pom_stolik_jedzenie.size() != 0)
			{
				Sala::pom_stolik_jedzenie.pop();
			}
			while (pom5 != nullptr)
			{
				Sala::pom_stolik_jedzenie.push(pom5);
				if (pom5->next_jedzenie == nullptr) Sala::stolik_jedzenie = pom5;
				pom5 = pom5->next_jedzenie;
			}
		}
		pom = nullptr;
		if (Sala::pom_stolik_zjedzone.size() > 0) {
			stolik = Sala::pom_stolik_zjedzone.front();
			for (int i = 1; i <= Sala::pom_stolik_zjedzone.size(); i++)
			{
				if (stolik->aktualna_grupa->alarm == true)
				{
					pom2 = stolik->next_zjedzone;
					stolik->napoje = false;
					stolik->jedzenie = false;
					stolik->next_zjedzone = nullptr;
					stolik->wolnyStolik = true;
					delete stolik->aktualna_grupa;
					stolik->aktualna_grupa = nullptr;
					if (stolik->stolik_pomocniczy != nullptr)
					{
						stolik->stolik_pomocniczy->stolik_pomocniczy = nullptr;
						stolik->stolik_pomocniczy->dolaczony = false;
						stolik->stolik_pomocniczy->wolnyStolik = true;
						stolik->stolik_pomocniczy = nullptr;
					}
					stolik = pom2;
					pom2 = nullptr;
				}
				else
				{
					if (pom == nullptr) {
						pom = stolik;
						stolik = stolik->next_zjedzone;
						pom->next_zjedzone = nullptr;
						pom5 = pom;
					}
					else
					{
						pom->next_zjedzone = stolik;
						pom = stolik;
						stolik = stolik->next_zjedzone;
						pom->next_zjedzone = nullptr;
					}
				}
			}
			while (Sala::pom_stolik_zjedzone.size() != 0)
			{
				Sala::pom_stolik_zjedzone.pop();
			}
			while (pom5 != nullptr)
			{
				Sala::pom_stolik_zjedzone.push(pom5);
				if (pom5->next_zjedzone == nullptr) Sala::stolik_zjedzone = pom5;
				pom5 = pom5->next_zjedzone;
			}
		}
		pom = nullptr;
		if (Restauracja::kolejka_sala.kolejka.size() > 0) {
			grupa = Restauracja::kolejka_sala.kolejka.front();
			for (int i = 1; i <= Restauracja::kolejka_sala.kolejka.size(); i++)
			{
				if (grupa->alarm == true)
				{
					pom3 = grupa;
					grupa = grupa->next_kolejka;
					delete pom3;
					pom3 = nullptr;
					Statystyki::liczba_kolejka_do_sali--;
				}
				else
				{
					if (pom4 == nullptr)
					{
						pom4 = grupa;
						grupa = grupa->next_kolejka;
						pom4->next_kolejka = nullptr;
						pom6 = pom4;
					}
					else
					{
						pom4->next_kolejka = grupa;
						pom4 = grupa;
						grupa = grupa->next_kolejka;
						pom4->next_kolejka = nullptr;
					}
				}
			}
			while (Restauracja::kolejka_sala.kolejka.size() != 0)
			{
				Restauracja::kolejka_sala.kolejka.pop();
			}
			while (pom6 != nullptr)
			{
				Restauracja::kolejka_sala.kolejka.push(pom6);
				if (pom6->next_kolejka == nullptr) Restauracja::pom_kol = pom6;
				pom6 = pom6->next_kolejka;
			}
		}
		pom4 = nullptr;
		if (Restauracja::kolejka_bufet.kolejka.size() > 0) {
			grupa = Restauracja::kolejka_bufet.kolejka.front();
			for (int i = 1; i <= Restauracja::kolejka_bufet.kolejka.size(); i++)
			{
				if (grupa->alarm == true)
				{
					pom3 = grupa;
					grupa = grupa->next_kolejka;
					delete pom3;
					pom3 = nullptr;
				}
				else
				{
					if (pom4 == nullptr)
					{
						pom4 = grupa;
						grupa = grupa->next_kolejka;
						pom4->next_kolejka = nullptr;
						pom6 = pom4;
					}
					else
					{
						pom4->next_kolejka = grupa;
						pom4 = grupa;
						grupa = grupa->next_kolejka;
						pom4->next_kolejka = nullptr;
					}
				}
			}
			while (Restauracja::kolejka_bufet.kolejka.size() != 0)
			{
				Restauracja::kolejka_bufet.kolejka.pop();
			}
			while (pom6 != nullptr)
			{
				Restauracja::kolejka_bufet.kolejka.push(pom6);
				if (pom6->next_kolejka == nullptr) Restauracja::pom_kol_buf = pom6;
				pom6 = pom6->next_kolejka;
			}
		}
		pom4 = nullptr;
		if (Restauracja::kolejka_kasy.kolejka.size() > 0) {
			grupa = Restauracja::kolejka_kasy.kolejka.front();
			for (int i = 1; i <= Restauracja::kolejka_kasy.kolejka.size(); i++)
			{
				if (grupa->alarm == true)
				{
					pom3 = grupa;
					grupa = grupa->next_kolejka;
					delete pom3;
					pom3 = nullptr;
					Statystyki::liczba_kolejka_do_kasy--;
				}
				else
				{
					if (pom4 == nullptr)
					{
						pom4 = grupa;
						grupa = grupa->next_kolejka;
						pom4->next_kolejka = nullptr;
						pom6 = pom4;
					}
					else
					{
						pom4->next_kolejka = grupa;
						pom4 = grupa;
						grupa = grupa->next_kolejka;
						pom4->next_kolejka = nullptr;
					}
				}
			}
			while (Restauracja::kolejka_kasy.kolejka.size() != 0)
			{
				Restauracja::kolejka_kasy.kolejka.pop();
			}
			while (pom6 != nullptr)
			{
				Restauracja::kolejka_kasy.kolejka.push(pom6);
				if (pom6->next_kolejka == nullptr) Restauracja::pom_kol_kasa = pom6;
				pom6 = pom6->next_kolejka;
			}
		}
		if (Statystyki::liczba_wszystkich_klientow >= faza_poczatkowa)
		{
			zlicz = new Statystyki::Zlicz;
			zlicz->zlicz_kolejka_kasy = Statystyki::liczba_kolejka_do_kasy;
			if (Statystyki::Zlicz::first_kasy == nullptr)
			{
				Statystyki::Zlicz::pom_zlicz_kasy = zlicz;
				Statystyki::Zlicz::first_kasy = zlicz;
			}
			else
			{
				Statystyki::Zlicz::pom_zlicz_kasy->next = zlicz;
				Statystyki::Zlicz::pom_zlicz_kasy = zlicz;
			}
			zlicz = new Statystyki::Zlicz;
			zlicz->zlicz_kolejka_sala = Statystyki::liczba_kolejka_do_sali;
			if (Statystyki::Zlicz::first_sala == nullptr)
			{
				Statystyki::Zlicz::pom_zlicz_sala = zlicz;
				Statystyki::Zlicz::first_sala = zlicz;
			}
			else
			{
				Statystyki::Zlicz::pom_zlicz_sala->next = zlicz;
				Statystyki::Zlicz::pom_zlicz_sala = zlicz;
			}
			Statystyki::count_sala++;
			Statystyki::count_kasy++;
		}
		pom4 = nullptr;
		if (Restauracja::bufet_lista.kolejka.size() > 0) {
			grupa = Restauracja::bufet_lista.kolejka.front();
			for (int i = 1; i <= Restauracja::bufet_lista.kolejka.size(); i++)
			{
				if (grupa->next != nullptr) pom3 = grupa->next;
				if (grupa->alarm == true)
				{
					if (Restauracja::bufet_lista.kolejka.front() != grupa)
					{
						if (grupa->next != nullptr)
						{
							grupa->previous->next = grupa->next;
							grupa->next->previous = grupa->previous;
						}
						grupa->next = nullptr;
						if (Restauracja::bufet_lista.kolejka.back() == grupa) grupa->previous->next = nullptr;
						grupa->previous = nullptr;
						pom4 = Restauracja::bufet_lista.kolejka.front();
						while (Restauracja::bufet_lista.kolejka.size() != 0)
						{
							Restauracja::bufet_lista.kolejka.pop();
						}
						while (pom4 != nullptr)
						{
							Restauracja::bufet_lista.kolejka.push(pom4);
							pom4 = pom4->next;
						}
					}
					else
					{
						Restauracja::bufet_lista.kolejka.pop();
					}
					Restauracja::bufet->liczbaOsob = Restauracja::bufet->liczbaOsob - grupa->wielkosc_grupy;
					delete grupa;
				}
				grupa = pom3;
			}
		}
		Statystyki::liczba_alarmow++;
		z = new ZdarzeniaCzasowe(8);
		ZdarzeniaCzasowe::dodaj(z->komunikat);
		std::cout << "KONIEC ALARMU" << std::endl;
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------------- KONSTRUKTOR KLASY KOMUNIKATÓW ZDARZEÑ CZASOWYCH --------------------------------------------------------------------------------------------

Komunikat::Komunikat(ZdarzeniaCzasowe* zdarzenie)
{
	this->zdarzenie = zdarzenie;
	czas_wykonania = losuj(this->zdarzenie->zdarzenie) + ZdarzeniaCzasowe::czas_systemowy;
}
