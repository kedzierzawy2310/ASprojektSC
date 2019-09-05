#include "stdafx.h"
/*
#pragma once
#include "Classes.h"
#include "Time Events.h"

//-------------------------------------------------------------------------------------------------- PÊTLA G£ÓWNA ----------------------------------------------------------------------------------------------------------------

int main()
{
	
	std::cout << "------------------------------------------ SYMULACJA CYFROWA - PROJEKT -------------------------------------------------" << std::endl;
	std::cout << "------------------------------------------- ROK AKADEMICKI 2018/2019 ---------------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "--------------------------------------------------- WYKONAL: -----------------------------------------------------------" << std::endl;
	std::cout << "---------------------------------------------- ADAM SAMORZEWSKI --------------------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------------------- SPECJALNOSC: ---------------------------------------------------------" << std::endl;
	std::cout << "-------------------------------------- TECHNOLOGIE MOBILNE I BEZPRZEWODOWE ---------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------------------ NUMER ALBUMU: ---------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------- 131133 -------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
	system("pause");

	Restauracja* restauracja = new Restauracja;
	Sala* salaRestauracji = new Sala;
	
	bool warunkowe=false;
	bool miejsca_zajete=false;
	grupaKlientow* pom_bufet = nullptr;
	Komunikat* obecne;
	grupaKlientow* klienci;
	ZdarzeniaCzasowe* nowaGrupa;
	ZdarzeniaCzasowe* alarm;
	ZdarzeniaCzasowe* powrotKierownika;
	ZdarzeniaCzasowe* zaserwowanoNapoje;
	ZdarzeniaCzasowe* zaserwowanoJedzenie;
	ZdarzeniaCzasowe* powrotZBufetu;
	ZdarzeniaCzasowe* dokonaniePlatnosci;
	Statystyki::Zlicz* zlicz;
	double zlicz_kolejka_sala;
	double zlicz_kolejka_kasy;
	double zlicz_czas_czekania_stolik;
	double zlicz_czas_czekania_obsluga;

	ZdarzeniaCzasowe::czas_systemowy = 0.0000000000;
	ZdarzeniaCzasowe::koniec_symulacji = 1000000.0000000000;

	//--------------------------------------------------------------------------- LISTÊ ZDARZEÑ NA OBIEKTY TYPU KOMUNIKAT -------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------- ODCZYTYWANIE CZASU WYKONYWANIA Z KOMUNIKATU komunikat->zdarzenie->czas_wykonania ---------------------------------------------------------------------------------

	nowaGrupa = new ZdarzeniaCzasowe(1);
	alarm = new ZdarzeniaCzasowe(8);
	Statystyki::liczba_wszystkich_klientow++;
	Statystyki::liczba_obecnych_klientow++;
	faza1 << Statystyki::liczba_obecnych_klientow << std::endl;
	faza2 << Statystyki::liczba_wszystkich_klientow << std::endl;
	
	ZdarzeniaCzasowe::dodaj((nowaGrupa)->komunikat);
	ZdarzeniaCzasowe::dodaj(alarm->komunikat);
	while (ZdarzeniaCzasowe::czas_systemowy < ZdarzeniaCzasowe::koniec_symulacji) {
		if(!ZdarzeniaCzasowe::komzdarzeniaCzasowe.empty()) obecne = ZdarzeniaCzasowe::komzdarzeniaCzasowe[ZdarzeniaCzasowe::komzdarzeniaCzasowe.size()-1];
		else continue;
		ZdarzeniaCzasowe::komzdarzeniaCzasowe.pop_back();
		ZdarzeniaCzasowe::czas_systemowy = obecne->czas_wykonania;
		obecne->zdarzenie->zdarzenie;
		obecne->zdarzenie->execute();
		delete obecne->zdarzenie;
		delete obecne;

		//-------------------------------------------------------------------------- PRZEGL¥D ZDARZEÑ WARUNKOWYCH ----------------------------------------------------------------------------------------------------------------

		warunkowe = false;
		while (warunkowe != true) {

		//-------------------------------------------------------------------------------- WEJŒCIE DO BUFETU ---------------------------------------------------------------------------------------------------------------------
			
			if (!Restauracja::kolejka_bufet.kolejka.empty())
			{
				klienci = Restauracja::kolejka_bufet.kolejka.front();
				if (Restauracja::bufet->buffet_size_-Restauracja::bufet->customer_number_>=klienci->wielkosc_grupy)
				{
					if (Restauracja::bufet_lista.kolejka.empty())
					{
						pom_bufet = klienci;
					}
					else
					{
						pom_bufet = Restauracja::bufet_lista.kolejka.front();
						while (pom_bufet->next!=nullptr)
						{
							pom_bufet = pom_bufet->next;
						}
						pom_bufet->next = klienci;
						klienci->previous = pom_bufet;
						pom_bufet = klienci;
					}
					powrotZBufetu = new ZdarzeniaCzasowe(7);
					ZdarzeniaCzasowe::dodaj(powrotZBufetu->komunikat);
					klienci->czas_opuszczenia_bufetu = powrotZBufetu->komunikat->czas_wykonania;
					Restauracja::bufet_lista.kolejka.push(klienci);
					Restauracja::bufet->customer_number_ = Restauracja::bufet->customer_number_ + klienci->wielkosc_grupy;
					Restauracja::kolejka_bufet.kolejka.pop();
					Statystyki::liczba_kolejka_do_bufetu--;
					std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << klienci->id_grupy << " weszla do bufetu" << std::endl;
					std::cout << ZdarzeniaCzasowe::czas_systemowy << " Obecny stan bufetu: " << Restauracja::bufet->customer_number_ << " z " << Restauracja::bufet->buffet_size_ << std::endl;
				}
				else std::cout << ZdarzeniaCzasowe::czas_systemowy <<" Grupa "<<klienci->id_grupy<<" oczekuje na wolne miejsce w bufecie (stan bufetu: "<< Restauracja::bufet->customer_number_ << "/" << Restauracja::bufet->buffet_size_ << ", wielkosc grupy: " << klienci->wielkosc_grupy << ")" << std::endl;
			}

		//----------------------------------------------------- PRZYDZIELANIE STOLIKÓW PRZEZ KIEROWNIKA SALI (METODA: £¥CZENIE STOLIKÓW) ----------------------------------------------------------------------------------------

			if (!Restauracja::kolejka_sala.kolejka.empty() && salaRestauracji->kierownikSali->wolnyKierownik == true)
			{
				miejsca_zajete = false;
				klienci = Restauracja::kolejka_sala.kolejka.front();
				salaRestauracji->kierownikSali->aktualnaGrupa = klienci;
				Stoliki* stolik2 = Sala::lista_stolikow2.front();
				Stoliki* stolik3 = Sala::lista_stolikow3.front();
				Stoliki* stolik4 = Sala::lista_stolikow4.front();
				Stoliki* stolik_cz_1 = nullptr;
				Stoliki* stolik_cz_2 = nullptr;
				if (klienci->wielkosc_grupy == 2 || klienci->wielkosc_grupy==1)
				{
					for (int i = 0; i < Sala::lista_stolikow2.size() - 1; i++)
					{
						if (stolik2->aktualna_grupa == nullptr)
						{
							salaRestauracji->kierownikSali->wolnyKierownik = false;
							stolik2->aktualna_grupa = klienci;
							if (stolik2->aktualna_grupa->czas_pojawienia_sie_na_sali != 0) {
								stolik2->aktualna_grupa->czas_dostania_stolika = ZdarzeniaCzasowe::czas_systemowy;
								zlicz = new Statystyki::Zlicz;
								zlicz->zlicz_czas_oczekiwania_stolik = stolik2->aktualna_grupa->czas_dostania_stolika - stolik2->aktualna_grupa->czas_pojawienia_sie_na_sali;
								if (Statystyki::Zlicz::first_stolik == nullptr)
								{
									Statystyki::Zlicz::first_stolik = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								else
								{
									Statystyki::Zlicz::pom_zlicz_stolik->next = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								Statystyki::count_stolik++;
							}
							if (!Restauracja::kolejka_sala.kolejka.empty()) Restauracja::kolejka_sala.kolejka.pop();
							Statystyki::liczba_kolejka_do_sali--;
							if (Statystyki::liczba_wszystkich_klientow >= faza_poczatkowa)
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
							}
							stolik2->wolnyStolik = false;
							miejsca_zajete = true;
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Przypisano grupe " << klienci->id_grupy << " do stolika " << stolik2->wielkoscStolika << "-osobowego" << std::endl;
							if (Sala::stoliki_do_obslugi.empty())
							{
								Sala::stoliki_do_obslugi.push(stolik2);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik2->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik2;
							}
							else
							{
								Sala::stolik_obs³uga->next_obs³uga = stolik2;
								Sala::stoliki_do_obslugi.push(stolik2);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << "Stolik grupy " << stolik2->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik2;
							}
							powrotKierownika = new ZdarzeniaCzasowe(2);
							ZdarzeniaCzasowe::dodaj(powrotKierownika->komunikat);
							break;
						}
						else
						{
							if(stolik2->next!=nullptr) stolik2 = stolik2->next;
							else break;
						}
					}
					for (int i = 0; i < Sala::lista_stolikow3.size() - 1; i++)
					{
						if (miejsca_zajete == true) break;
						if (stolik3->aktualna_grupa == nullptr)
						{
							salaRestauracji->kierownikSali->wolnyKierownik = false;
							stolik3->aktualna_grupa = klienci;
							if (stolik3->aktualna_grupa->czas_pojawienia_sie_na_sali != 0) {
								stolik3->aktualna_grupa->czas_dostania_stolika = ZdarzeniaCzasowe::czas_systemowy;
								zlicz = new Statystyki::Zlicz;
								zlicz->zlicz_czas_oczekiwania_stolik = stolik3->aktualna_grupa->czas_dostania_stolika - stolik3->aktualna_grupa->czas_pojawienia_sie_na_sali;
								if (Statystyki::Zlicz::first_stolik == nullptr)
								{
									Statystyki::Zlicz::first_stolik = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								else
								{
									Statystyki::Zlicz::pom_zlicz_stolik->next = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								Statystyki::count_stolik++;
							}
							if (!Restauracja::kolejka_sala.kolejka.empty()) Restauracja::kolejka_sala.kolejka.pop();
							Statystyki::liczba_kolejka_do_sali--;
							stolik3->wolnyStolik = false;
							miejsca_zajete = true;
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Przypisano grupe " << klienci->id_grupy << " do stolika " << stolik3->wielkoscStolika << "-osobowego" << std::endl;
							if (Sala::stoliki_do_obslugi.empty())
							{
								Sala::stoliki_do_obslugi.push(stolik3);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik3->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik3;
							}
							else
							{
								Sala::stolik_obs³uga->next_obs³uga = stolik3;
								Sala::stoliki_do_obslugi.push(stolik3);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik3->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik3;
							}
							powrotKierownika = new ZdarzeniaCzasowe(2);
							ZdarzeniaCzasowe::dodaj(powrotKierownika->komunikat);							
							break;
						}
						else
						{
							if (stolik3->next != nullptr) stolik3 = stolik3->next;
							else break;
						}
					}
					for (int i = 0; i < Sala::lista_stolikow4.size() - 1; i++)
					{
						if (miejsca_zajete == true) break;
						if (stolik4->aktualna_grupa == nullptr)
						{
							salaRestauracji->kierownikSali->wolnyKierownik = false;
							stolik4->aktualna_grupa = klienci;
							if (stolik4->aktualna_grupa->czas_pojawienia_sie_na_sali != 0) {
								stolik4->aktualna_grupa->czas_dostania_stolika = ZdarzeniaCzasowe::czas_systemowy;
								zlicz = new Statystyki::Zlicz;
								zlicz->zlicz_czas_oczekiwania_stolik = stolik4->aktualna_grupa->czas_dostania_stolika - stolik4->aktualna_grupa->czas_pojawienia_sie_na_sali;
								if (Statystyki::Zlicz::first_stolik == nullptr)
								{
									Statystyki::Zlicz::first_stolik = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								else
								{
									Statystyki::Zlicz::pom_zlicz_stolik->next = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								Statystyki::count_stolik++;
							}
							if (!Restauracja::kolejka_sala.kolejka.empty()) Restauracja::kolejka_sala.kolejka.pop();
							Statystyki::liczba_kolejka_do_sali--;
							stolik4->wolnyStolik = false;
							miejsca_zajete = true;
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Przypisano grupe " << klienci->id_grupy << " do stolika " << stolik4->wielkoscStolika << "-osobowego" << std::endl;
							if (Sala::stoliki_do_obslugi.empty())
							{
								Sala::stoliki_do_obslugi.push(stolik4);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik4->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik4;
							}
							else
							{
								Sala::stolik_obs³uga->next_obs³uga = stolik4;
								Sala::stoliki_do_obslugi.push(stolik4);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik4->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik4;
							}
							powrotKierownika = new ZdarzeniaCzasowe(2);
							ZdarzeniaCzasowe::dodaj(powrotKierownika->komunikat);							
							break;
						}
						else
						{
							if (stolik4->next != nullptr) stolik4 = stolik4->next;
							else
							{
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa o ID: " << klienci->id_grupy << " czeka na stolik" << std::endl;
								break;
							}
						}
					}
				}
				else if(klienci->wielkosc_grupy==3)
				{
					for (int i = 0; i < Sala::lista_stolikow3.size() - 1; i++)
					{
						if (stolik3->aktualna_grupa == nullptr)
						{
							salaRestauracji->kierownikSali->wolnyKierownik = false;
							stolik3->aktualna_grupa = klienci;
							if (stolik3->aktualna_grupa->czas_pojawienia_sie_na_sali != 0) {
								stolik3->aktualna_grupa->czas_dostania_stolika = ZdarzeniaCzasowe::czas_systemowy;
								zlicz = new Statystyki::Zlicz;
								zlicz->zlicz_czas_oczekiwania_stolik = stolik3->aktualna_grupa->czas_dostania_stolika - stolik3->aktualna_grupa->czas_pojawienia_sie_na_sali;
								if (Statystyki::Zlicz::first_stolik == nullptr)
								{
									Statystyki::Zlicz::first_stolik = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								else
								{
									Statystyki::Zlicz::pom_zlicz_stolik->next = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								Statystyki::count_stolik++;
							}
							if(!Restauracja::kolejka_sala.kolejka.empty()) Restauracja::kolejka_sala.kolejka.pop();
							Statystyki::liczba_kolejka_do_sali--;
							stolik3->wolnyStolik = false;
							miejsca_zajete = true;
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Przypisano grupe " << klienci->id_grupy << " do stolika " << stolik3->wielkoscStolika << "-osobowego" << std::endl;
							if (Sala::stoliki_do_obslugi.empty())
							{
								Sala::stoliki_do_obslugi.push(stolik3);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik3->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik3;
							}
							else
							{
								Sala::stolik_obs³uga->next_obs³uga = stolik3;
								Sala::stoliki_do_obslugi.push(stolik3);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik3->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik3;
							}
							powrotKierownika = new ZdarzeniaCzasowe(2);
							ZdarzeniaCzasowe::dodaj(powrotKierownika->komunikat);
							break;
						}
						else
						{
							if (stolik3->next != nullptr) stolik3 = stolik3->next;
							else break;
						}
					}
					for (int i = 0; i < Sala::lista_stolikow4.size() - 1; i++)
					{
						if (miejsca_zajete == true) break;
						if (stolik4->aktualna_grupa == nullptr)
						{
							salaRestauracji->kierownikSali->wolnyKierownik = false;
							stolik4->aktualna_grupa = klienci;
							if (stolik4->aktualna_grupa->czas_pojawienia_sie_na_sali != 0)
							{
								stolik4->aktualna_grupa->czas_dostania_stolika = ZdarzeniaCzasowe::czas_systemowy;
								zlicz = new Statystyki::Zlicz;
								zlicz->zlicz_czas_oczekiwania_stolik = stolik4->aktualna_grupa->czas_dostania_stolika - stolik4->aktualna_grupa->czas_pojawienia_sie_na_sali;
								if (Statystyki::Zlicz::first_stolik == nullptr)
								{
									Statystyki::Zlicz::first_stolik = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								else
								{
									Statystyki::Zlicz::pom_zlicz_stolik->next = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								Statystyki::count_stolik++;
							}
							if (!Restauracja::kolejka_sala.kolejka.empty()) Restauracja::kolejka_sala.kolejka.pop();
							Statystyki::liczba_kolejka_do_sali--;
							stolik4->wolnyStolik = false;
							miejsca_zajete = true;
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Przypisano grupe " << klienci->id_grupy << " do stolika " << stolik4->wielkoscStolika << "-osobowego" << std::endl;
							if (Sala::stoliki_do_obslugi.empty())
							{
								Sala::stoliki_do_obslugi.push(stolik4);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik4->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik4;
							}
							else
							{
								Sala::stolik_obs³uga->next_obs³uga = stolik4;
								Sala::stoliki_do_obslugi.push(stolik4);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik4->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik4;
							}
							powrotKierownika = new ZdarzeniaCzasowe(2);
							ZdarzeniaCzasowe::dodaj(powrotKierownika->komunikat);
							break;
						}
						else
						{
							if (stolik4->next != nullptr) stolik4 = stolik4->next;
							else break;
						}
					}
					for (int i = 0; i < Sala::lista_stolikow2.size() - 1; i++)
					{
						if (miejsca_zajete == true) break;
						if (stolik2->wolnyStolik==true)
						{
							stolik_cz_1 = stolik2;
							if(stolik2->next != nullptr) stolik2 = stolik2->next;
							for (int j = i+1; j < Sala::lista_stolikow2.size() - 1; i++)
							{
								if (stolik2->wolnyStolik == true)
								{
									stolik_cz_2 = stolik2;
									break;
								}
								else
								{
									if (stolik2->next != nullptr) stolik2 = stolik2->next;
									else
									{
										stolik_cz_1 = nullptr;
										std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa o ID: " << klienci->id_grupy << " czeka na stolik" << std::endl;
										break;
									}
								}
							}
							break;
						}
						else
						{
							if (stolik2->next != nullptr) stolik2 = stolik2->next;
							else
							{
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa o ID: " << klienci->id_grupy << " czeka na stolik" << std::endl;
								break;
							}
						}
					}
					if (stolik_cz_1 != nullptr && stolik_cz_2 != nullptr)
					{
						stolik_cz_2->dolaczony = true;
						stolik_cz_1->stolik_pomocniczy= stolik_cz_2;
						stolik_cz_2->stolik_pomocniczy = stolik_cz_1;
						stolik_cz_1->aktualna_grupa = klienci;
						stolik_cz_1->wolnyStolik = false;
						stolik_cz_2->wolnyStolik = false;
						salaRestauracji->kierownikSali->wolnyKierownik = false;
						if (stolik_cz_1->aktualna_grupa->czas_pojawienia_sie_na_sali != 0)
						{
							stolik_cz_1->aktualna_grupa->czas_dostania_stolika = ZdarzeniaCzasowe::czas_systemowy;
							zlicz = new Statystyki::Zlicz;
							zlicz->zlicz_czas_oczekiwania_stolik = stolik_cz_1->aktualna_grupa->czas_dostania_stolika - stolik_cz_1->aktualna_grupa->czas_pojawienia_sie_na_sali;
							if (Statystyki::Zlicz::first_stolik == nullptr)
							{
								Statystyki::Zlicz::first_stolik = zlicz;
								Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
							}
							else
							{
								Statystyki::Zlicz::pom_zlicz_stolik->next = zlicz;
								Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
							}
							Statystyki::count_stolik++;
						}
						if (!Restauracja::kolejka_sala.kolejka.empty()) Restauracja::kolejka_sala.kolejka.pop();
						Statystyki::liczba_kolejka_do_sali--;
						std::cout << ZdarzeniaCzasowe::czas_systemowy << " Przypisano grupe " << klienci->id_grupy << " do stolika laczonego (" << stolik_cz_1->wielkoscStolika << "+" << stolik_cz_2->wielkoscStolika <<")"<< std::endl;
						if (Sala::stoliki_do_obslugi.empty())
						{
							Sala::stoliki_do_obslugi.push(stolik_cz_1);
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik_cz_1->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
							Sala::stolik_obs³uga = stolik_cz_1;
						}
						else
						{
							Sala::stolik_obs³uga->next_obs³uga = stolik_cz_1;
							Sala::stoliki_do_obslugi.push(stolik_cz_1);
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik_cz_1->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
							Sala::stolik_obs³uga = stolik_cz_1;
						}
						powrotKierownika = new ZdarzeniaCzasowe(2);
						ZdarzeniaCzasowe::dodaj(powrotKierownika->komunikat);
					}
				}
				else
				{
					for (int i = 0; i < Sala::lista_stolikow4.size() - 1; i++)
					{
						if (stolik4->aktualna_grupa == nullptr)
						{
							salaRestauracji->kierownikSali->wolnyKierownik = false;
							stolik4->aktualna_grupa = klienci;
							if (stolik4->aktualna_grupa->czas_pojawienia_sie_na_sali != 0) 
							{
								stolik4->aktualna_grupa->czas_dostania_stolika = ZdarzeniaCzasowe::czas_systemowy;
								zlicz = new Statystyki::Zlicz;
								zlicz->zlicz_czas_oczekiwania_stolik = stolik4->aktualna_grupa->czas_dostania_stolika - stolik4->aktualna_grupa->czas_pojawienia_sie_na_sali;
								if (Statystyki::Zlicz::first_stolik == nullptr)
								{
									Statystyki::Zlicz::first_stolik = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								else
								{
									Statystyki::Zlicz::pom_zlicz_stolik->next = zlicz;
									Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
								}
								Statystyki::count_stolik++;
							}
							if (!Restauracja::kolejka_sala.kolejka.empty()) Restauracja::kolejka_sala.kolejka.pop();
							Statystyki::liczba_kolejka_do_sali--;
							stolik4->wolnyStolik = false;
							miejsca_zajete = true;
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Przypisano grupe " << klienci->id_grupy << " do stolika " << stolik4->wielkoscStolika << "-osobowego" << std::endl;
							if (Sala::stoliki_do_obslugi.empty())
							{
								Sala::stoliki_do_obslugi.push(stolik4);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik4->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik4;
							}
							else
							{
								Sala::stolik_obs³uga->next_obs³uga = stolik4;
								Sala::stoliki_do_obslugi.push(stolik4);
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik4->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
								Sala::stolik_obs³uga = stolik4;
							}
							powrotKierownika = new ZdarzeniaCzasowe(2);
							ZdarzeniaCzasowe::dodaj(powrotKierownika->komunikat);
							break;
						}
						else
						{
							if (stolik4->next != nullptr) stolik4 = stolik4->next;
							else break;
						}
					}
					for (int i = 0; i < Sala::lista_stolikow2.size() - 1; i++)
					{
						if (miejsca_zajete == true) break;
						if (stolik2->wolnyStolik == true)
						{
							stolik_cz_1 = stolik2;
							if (stolik2->next != nullptr) stolik2 = stolik2->next;
							for (int j = i + 1; j < Sala::lista_stolikow2.size() - 1; j++)
							{
								if (stolik2->wolnyStolik == true)
								{
									stolik_cz_2 = stolik2;
									miejsca_zajete = true;
									break;
								}
								else
								{
									if (stolik2->next != nullptr) stolik2 = stolik2->next;
									else break;
								}
							}
							for (int j = 0 ; j < Sala::lista_stolikow3.size() - 1; j++)
							{
								if (miejsca_zajete == true) break;
								if (stolik3->wolnyStolik == true)
								{
									stolik_cz_2 = stolik3;
									break;
								}
								else
								{
									if (stolik3->next != nullptr) stolik3 = stolik3->next;
									else
									{
										stolik_cz_1 = nullptr;
										break;
									}
								}
							}
							break;
						}
						else
						{
							if (stolik2->next != nullptr) stolik2 = stolik2->next;
							else break;
						}
					}
					for (int i = 0; i < Sala::lista_stolikow3.size() - 1; i++)
					{
						if (miejsca_zajete == true) break;
						if (stolik3->wolnyStolik == true)
						{
							stolik_cz_1 = stolik3;
							if (stolik3->next != nullptr) stolik3 = stolik3->next;
							for (int j = i + 1; j < Sala::lista_stolikow3.size() - 1; i++)
							{
								if (stolik3->wolnyStolik == true)
								{
									stolik_cz_2 = stolik3;
									break;
								}
								else
								{
									if (stolik3->next != nullptr) stolik3 = stolik3->next;
									else
									{
										stolik_cz_1 = nullptr;
										std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa o ID: " << klienci->id_grupy << " czeka na stolik" << std::endl;
										break;
									}
								}
							}
							break;
						}
						else
						{
							if (stolik3->next != nullptr) stolik3 = stolik3->next;
							else
							{
								std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa o ID: " << klienci->id_grupy << " czeka na stolik" << std::endl;
								break;
							}
						}
					}
					if (stolik_cz_1 != nullptr && stolik_cz_2 != nullptr)
					{
						stolik_cz_2->dolaczony = true;
						stolik_cz_1->stolik_pomocniczy = stolik_cz_2;
						stolik_cz_2->stolik_pomocniczy = stolik_cz_1;
						stolik_cz_1->aktualna_grupa = klienci;
						stolik_cz_1->wolnyStolik = false;
						stolik_cz_2->wolnyStolik = false;
						salaRestauracji->kierownikSali->wolnyKierownik = false;
						if (stolik_cz_1->aktualna_grupa->czas_pojawienia_sie_na_sali != 0)
						{
							stolik_cz_1->aktualna_grupa->czas_dostania_stolika = ZdarzeniaCzasowe::czas_systemowy;
							zlicz = new Statystyki::Zlicz;
							zlicz->zlicz_czas_oczekiwania_stolik = stolik_cz_1->aktualna_grupa->czas_dostania_stolika - stolik_cz_1->aktualna_grupa->czas_pojawienia_sie_na_sali;
							if (Statystyki::Zlicz::first_stolik == nullptr)
							{
								Statystyki::Zlicz::first_stolik = zlicz;
								Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
							}
							else
							{
								Statystyki::Zlicz::pom_zlicz_stolik->next = zlicz;
								Statystyki::Zlicz::pom_zlicz_stolik = zlicz;
							}
							Statystyki::count_stolik++;
						}
						if (!Restauracja::kolejka_sala.kolejka.empty()) Restauracja::kolejka_sala.kolejka.pop();
						Statystyki::liczba_kolejka_do_sali--;
						std::cout << ZdarzeniaCzasowe::czas_systemowy << " Przypisano grupe " << klienci->id_grupy << " do stolika laczonego (" << stolik_cz_1->wielkoscStolika << "+" << stolik_cz_2->wielkoscStolika << ")" << std::endl;
						if (Sala::stoliki_do_obslugi.empty())
						{
							Sala::stoliki_do_obslugi.push(stolik_cz_1);
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik_cz_1->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
							Sala::stolik_obs³uga = stolik_cz_1;
						}
						else
						{
							Sala::stolik_obs³uga->next_obs³uga = stolik_cz_1;
							Sala::stoliki_do_obslugi.push(stolik_cz_1);
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Stolik grupy " << stolik_cz_1->aktualna_grupa->id_grupy << " jest gotowy do obslugi" << std::endl;
							Sala::stolik_obs³uga = stolik_cz_1;
						}
						powrotKierownika = new ZdarzeniaCzasowe(2);
						ZdarzeniaCzasowe::dodaj(powrotKierownika->komunikat);
					}
				}
			}

		//--------------------------------------------------------------------------- OBS£UGA STOLIKÓW PRZEZ KELNERÓW (NAPOJE) ---------------------------------------------------------------------------------------------------------

			if (!salaRestauracji->lista_kelnerow.empty() && !Sala::stoliki_do_obslugi.empty())
			{
				Sala::kelner = salaRestauracji->lista_kelnerow.front();
				Sala::stolik = Sala::stoliki_do_obslugi.front();				
					
				for (int i = 0; i < salaRestauracji->lista_kelnerow.size(); i++)
				{
					if (Sala::stolik->aktualna_grupa != nullptr && Sala::stolik->napoje == false)
					{
						if (Sala::kelner->wolny_kelner == true)
						{
							if (Sala::stolik->aktualna_grupa->aktualnyKelner != nullptr) break;
							Sala::stolik->aktualna_grupa->aktualnyKelner = Sala::kelner;
							Sala::kelner->wolny_kelner = false;
							if (Sala::pom_stolik_napoje.empty()) 
							{
								Sala::stolik_napoje = Sala::stolik;
							}
							else
							{
								Sala::stolik_napoje->next_napoje = Sala::stolik;
								Sala::stolik_napoje = Sala::stolik;
							}
							Sala::pom_stolik_napoje.push(Sala::stolik);
							if (Sala::stolik->aktualna_grupa->czas_dostania_stolika != 0)
							{
								Sala::stolik->aktualna_grupa->czas_obslugi = ZdarzeniaCzasowe::czas_systemowy;
								zlicz = new Statystyki::Zlicz;
								zlicz->zlicz_czas_oczekiwania_obsluga = Sala::stolik->aktualna_grupa->czas_obslugi - Sala::stolik->aktualna_grupa->czas_dostania_stolika;
								if (Statystyki::Zlicz::first_obsluga == nullptr)
								{
									Statystyki::Zlicz::first_obsluga = zlicz;
									Statystyki::Zlicz::pom_zlicz_obsluga = zlicz;
								}
								else
								{
									Statystyki::Zlicz::pom_zlicz_obsluga->next = zlicz;
									Statystyki::Zlicz::pom_zlicz_obsluga = zlicz;
								}
								Statystyki::count_obsluga++;
							}
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << Sala::stolik->aktualna_grupa->id_grupy <<" oczekuje na napoje (kelner " << Sala::kelner->id_kelnera << ")" << std::endl;
							if (!Sala::stoliki_do_obslugi.empty())
							{
								Sala::stolik_do_usuwania = Sala::stoliki_do_obslugi.front();
								Sala::stolik_do_usuwania->next_obs³uga = nullptr;
								Sala::stoliki_do_obslugi.pop();
							}
							zaserwowanoNapoje = new ZdarzeniaCzasowe(3);
							ZdarzeniaCzasowe::dodaj(zaserwowanoNapoje->komunikat);
							if (Sala::kelner->next != nullptr && Sala::stolik->next_obs³uga != nullptr)
							{
								Sala::kelner = Sala::kelner->next;
								Sala::stolik = Sala::stolik->next_obs³uga;
							}
							else goto jedzenie;	
						}
						else
						{
							if (Sala::kelner->next != nullptr) Sala::kelner = Sala::kelner->next;
						}
					}
					else
					{
						if (Sala::stolik->next_obs³uga != nullptr) Sala::stolik = Sala::stolik->next_obs³uga;
						if (!Sala::stoliki_do_obslugi.empty()) Sala::stoliki_do_obslugi.pop();
					}
				}
			}

		//--------------------------------------------------------------------------- OBS£UGA STOLIKÓW PRZEZ KELNERÓW (DANIE G£ÓWNE) ---------------------------------------------------------------------------------------------------------

			jedzenie:
			if (!salaRestauracji->lista_kelnerow.empty() && !Sala::pom_stolik_jedzenie.empty())
			{
				Sala::kelner = salaRestauracji->lista_kelnerow.front();
				Sala::stolik = Sala::pom_stolik_jedzenie.front();

				for (int i = 0; i < salaRestauracji->lista_kelnerow.size(); i++)
				{
					if (Sala::stolik->aktualna_grupa != nullptr && Sala::stolik->napoje == true && Sala::stolik->jedzenie == false)
					{
						if (Sala::kelner->wolny_kelner == true)
						{
							if (Sala::stolik->aktualna_grupa->aktualnyKelner != nullptr) break;
							Sala::stolik->aktualna_grupa->aktualnyKelner = Sala::kelner;
							Sala::kelner->wolny_kelner = false;
							std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << Sala::stolik->aktualna_grupa->id_grupy << " oczekuje na jedzenie (kelner " << Sala::kelner->id_kelnera << ")" << std::endl;
							zaserwowanoJedzenie = new ZdarzeniaCzasowe(4);
							ZdarzeniaCzasowe::dodaj(zaserwowanoJedzenie->komunikat);
							if (Sala::kelner->next != nullptr && Sala::stolik->next_jedzenie != nullptr)
							{
								Sala::kelner = Sala::kelner->next;
								Sala::stolik = Sala::stolik->next_jedzenie;
							}
							else goto kasy;
						}
						else
						{
							if (Sala::kelner->next != nullptr) Sala::kelner = Sala::kelner->next;
						}
					}
					else
					{
						if (Sala::stolik->next_jedzenie != nullptr) Sala::stolik = Sala::stolik->next_jedzenie;
						if (!Sala::pom_stolik_jedzenie.empty()) Sala::pom_stolik_jedzenie.pop();
					}
				}
			}

		//------------------------------------------------------------------------------- OBS£UGA KLIENTÓW PRZEZ KASJERÓW --------------------------------------------------------------------------------------------------------

			kasy:
			if(!Restauracja::kolejka_kasy.kolejka.empty() && !Restauracja::listaKasjerow.empty())
			{
				Restauracja::kasjer = Restauracja::listaKasjerow.front();
				for (int i = 0; i < Restauracja::listaKasjerow.size(); i++) {
					if(!Restauracja::kolejka_kasy.kolejka.empty()) klienci = Restauracja::kolejka_kasy.kolejka.front();
					else goto koniec;
					if (Restauracja::kasjer->aktualnaGrupa == nullptr)
					{
						Restauracja::kasjer->aktualnaGrupa = klienci;
						Restauracja::kolejka_kasy.kolejka.pop();
						std::cout << ZdarzeniaCzasowe::czas_systemowy << " Grupa " << klienci->id_grupy << " dokonuje platnosci u kasjera " << Restauracja::kasjer->cashier_id_ << std::endl;
						Statystyki::liczba_kolejka_do_kasy--;
						dokonaniePlatnosci = new ZdarzeniaCzasowe(6);
						ZdarzeniaCzasowe::dodaj(dokonaniePlatnosci->komunikat);
						klienci->czas_placenia = dokonaniePlatnosci->komunikat->czas_wykonania;
						if (Restauracja::kasjer->next != nullptr) Restauracja::kasjer = Restauracja::kasjer->next;
						else
						{
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
							goto koniec;
						}
					}
					else
					{
						if (Restauracja::kasjer->next != nullptr) Restauracja::kasjer = Restauracja::kasjer->next;
						else
						{
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
							goto koniec;
						}
					}
				}
			}
			koniec:
			warunkowe = true;
		}
	}

	//-------------------------------------------------------------------------------------- STATYSTYKI SYMULACJI ----------------------------------------------------------------------------------------------------------------

	Restauracja::kasjer = Restauracja::listaKasjerow.front();
	Sala::kelner = Sala::lista_kelnerow.front();
	std::cout<< std::endl;
	std::cout << std::endl;
	std::cout << "Statystyki symulacji:" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//--------------------------------------------------------------------------------------- CZASY OCZEKIWANIA ------------------------------------------------------------------------------------------------------------------

	std::cout << "Czasy oczekiwania:" << std::endl;
	std::cout << std::endl;
	zlicz_czas_czekania_stolik = 0.0;
	zlicz_czas_czekania_obsluga = 0.0;
	Statystyki::Zlicz::pom_zlicz_stolik = Statystyki::Zlicz::first_stolik;
	for (int i = 0; i<Statystyki::count_stolik - 1; i++)
	{
		zlicz = Statystyki::Zlicz::pom_zlicz_stolik;
		czas_oczekiwania_stolik << Statystyki::Zlicz::pom_zlicz_stolik->zlicz_czas_oczekiwania_stolik << std::endl;
		zlicz_czas_czekania_stolik = zlicz_czas_czekania_stolik + Statystyki::Zlicz::pom_zlicz_stolik->zlicz_czas_oczekiwania_stolik;
		Statystyki::Zlicz::pom_zlicz_stolik = Statystyki::Zlicz::pom_zlicz_stolik->next;
		delete zlicz;
	}
	zlicz_czas_czekania_stolik = zlicz_czas_czekania_stolik / (Statystyki::count_stolik - 1);
	std::cout << "Sredni czas oczekiwania na stolik: " << zlicz_czas_czekania_stolik << std::endl;
	Statystyki::Zlicz::pom_zlicz_obsluga = Statystyki::Zlicz::first_obsluga;
	for (int i = 0; i<Statystyki::count_obsluga - 1; i++)
	{
		zlicz = Statystyki::Zlicz::pom_zlicz_obsluga;
		czas_oczekiwania_na_obsluge << Statystyki::Zlicz::pom_zlicz_obsluga->zlicz_czas_oczekiwania_obsluga << std::endl;
		zlicz_czas_czekania_obsluga = zlicz_czas_czekania_obsluga + Statystyki::Zlicz::pom_zlicz_obsluga->zlicz_czas_oczekiwania_obsluga;
		Statystyki::Zlicz::pom_zlicz_obsluga = Statystyki::Zlicz::pom_zlicz_obsluga->next;
		delete zlicz;
	}
	zlicz_czas_czekania_obsluga = zlicz_czas_czekania_obsluga / (Statystyki::count_obsluga - 1);
	std::cout << "Sredni czas oczekiwania na obsluge przez kelnera: " << zlicz_czas_czekania_obsluga << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//--------------------------------------------------------------------------------------- KOLEJKI KLIENTÓW -------------------------------------------------------------------------------------------------------------------

	std::cout << "Kolejki:" << std::endl;
	std::cout << std::endl;
	std::cout << "Stan kolejki do sali: " << Statystyki::liczba_kolejka_do_sali << std::endl;
	std::cout << "Stan kolejki do bufetu: " << Statystyki::liczba_kolejka_do_bufetu << std::endl;
	std::cout << "Stan kolejki do kasy: " << Statystyki::liczba_kolejka_do_kasy << std::endl;
	std::cout << std::endl;
	zlicz_kolejka_sala = 0.0;
	zlicz_kolejka_kasy = 0.0;
	Statystyki::Zlicz::pom_zlicz_sala = Statystyki::Zlicz::first_sala;
	for(int i = 0; i<Statystyki::count_sala-1; i++)
	{
		zlicz = Statystyki::Zlicz::pom_zlicz_sala;
		zlicz_kolejka_sala = zlicz_kolejka_sala + Statystyki::Zlicz::pom_zlicz_sala->zlicz_kolejka_sala;
		Statystyki::Zlicz::pom_zlicz_sala = Statystyki::Zlicz::pom_zlicz_sala->next;
		delete zlicz;
	}
	zlicz_kolejka_sala = zlicz_kolejka_sala / (Statystyki::count_sala - 1);
	std::cout << "Srednia dlugosc kolejki do sali: " << zlicz_kolejka_sala << std::endl;
	Statystyki::Zlicz::pom_zlicz_kasy = Statystyki::Zlicz::first_kasy;
	for (int i = 0; i<Statystyki::count_kasy - 1; i++)
	{
		zlicz = Statystyki::Zlicz::pom_zlicz_kasy;
		zlicz_kolejka_kasy = zlicz_kolejka_kasy + Statystyki::Zlicz::pom_zlicz_kasy->zlicz_kolejka_kasy;
		Statystyki::Zlicz::pom_zlicz_kasy = Statystyki::Zlicz::pom_zlicz_kasy->next;
		delete zlicz;
	}
	zlicz_kolejka_kasy = zlicz_kolejka_kasy / (Statystyki::count_kasy - 1);
	std::cout << "Srednia dlugosc kolejki do kasy: " << zlicz_kolejka_kasy << std::endl;

	//-------------------------------------------------------------------------------------------- ALARM --------------------------------------------------------------------------------------------------------------------------

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Alarm:" << std::endl;
	std::cout << std::endl;
	std::cout << "Liczba alarmow: "<< Statystyki::liczba_alarmow << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//--------------------------------------------------------------------------------------- KIEROWNIK SALI ----------------------------------------------------------------------------------------------------------------------

	std::cout << "Kierownik:" << std::endl;
	std::cout << std::endl;
	std::cout << "Kierownik obsluzyl: " << Sala::kierownikSali->liczba_obsluzen << " grup." << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//------------------------------------------------------------------------------------------- KELNERZY -----------------------------------------------------------------------------------------------------------------------

	std::cout << "Kelnerzy:" << std::endl;
	std::cout << std::endl;
	while(Sala::kelner!=nullptr)
	{
		std::cout << "Kelner " << Sala::kelner->id_kelnera << " obsluzyl: " << Sala::kelner->liczba_obsluzen << " grup." << std::endl;
		Sala::kelner = Sala::kelner->next;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	//------------------------------------------------------------------------------------------- KASJERZY -----------------------------------------------------------------------------------------------------------------------

	std::cout << "Kasy:" << std::endl;
	std::cout << std::endl;
	while (Restauracja::kasjer != nullptr)
	{
		std::cout << "Kasjer " << Restauracja::kasjer->cashier_id_ << " obsluzyl: " << Restauracja::kasjer->service_number_ << " grup." << std::endl;
		Restauracja::kasjer = Restauracja::kasjer->next;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	//------------------------------------------------------------------------------------------- USUWANIE ------------------------------------------------------------------------------------------------------------------------ 

	for(int i = 0; i<Sala::lista_kelnerow.size(); i++)
	{
		Sala::kelner = Sala::lista_kelnerow.front();
		Sala::lista_kelnerow.pop();
		delete Sala::kelner;
	}
	for (int i = 0; i<Sala::lista_stolikow2.size(); i++)
	{
		Sala::stolik = Sala::lista_stolikow2.front();
		if (Sala::stolik->aktualna_grupa != nullptr) delete Sala::stolik->aktualna_grupa;
		Sala::lista_stolikow2.pop();
		delete Sala::stolik;
	}	
	for (int i = 0; i<Sala::lista_stolikow3.size(); i++)
	{
		Sala::stolik = Sala::lista_stolikow3.front();
		if (Sala::stolik->aktualna_grupa != nullptr) delete Sala::stolik->aktualna_grupa;
		Sala::lista_stolikow3.pop();
		delete Sala::stolik;
	}
	for (int i = 0; i<Sala::lista_stolikow4.size(); i++)
	{
		Sala::stolik = Sala::lista_stolikow4.front();
		if (Sala::stolik->aktualna_grupa != nullptr) delete Sala::stolik->aktualna_grupa;
		Sala::lista_stolikow4.pop();
		delete Sala::stolik;
	}
	for (int i = 0; i<Restauracja::listaKasjerow.size(); i++)
	{
		Restauracja::kasjer = Restauracja::listaKasjerow.front();
		Restauracja::listaKasjerow.pop();
		delete Restauracja::kasjer;
	}
	for (int i = 0; i<Restauracja::bufet_lista.kolejka.size(); i++)
	{
		Restauracja::pom_kol = Restauracja::bufet_lista.kolejka.front();
		Restauracja::bufet_lista.kolejka.pop();
		delete Restauracja::pom_kol;
	}
	for (int i = 0; i<Restauracja::kolejka_bufet.kolejka.size(); i++)
	{
		Restauracja::pom_kol = Restauracja::kolejka_bufet.kolejka.front();
		Restauracja::kolejka_bufet.kolejka.pop();
		delete Restauracja::pom_kol;
	}
	for (int i = 0; i<Restauracja::kolejka_kasy.kolejka.size(); i++)
	{
		Restauracja::pom_kol = Restauracja::kolejka_kasy.kolejka.front();
		Restauracja::kolejka_kasy.kolejka.pop();
		delete Restauracja::pom_kol;
	}
	for (int i = 0; i<Restauracja::kolejka_sala.kolejka.size(); i++)
	{
		Restauracja::pom_kol = Restauracja::kolejka_sala.kolejka.front();
		Restauracja::kolejka_sala.kolejka.pop();
		delete Restauracja::pom_kol;
	}
	delete Restauracja::bufet;
	delete Sala::kierownikSali;
	delete salaRestauracji;
	delete restauracja;

	//-------------------------------------------------------------------------------------------- ZAPIS DANYCH ----------------------------------------------------------------------------------------------------------------

	for (int i = 0; i<Statystyki::losowanie_klienci.size(); i++) losowanie_klient << int(Statystyki::losowanie_klienci[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_bufet.size(); i++) losowanie_bufet << int(Statystyki::losowanie_bufet[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_konsumpcja.size(); i++) losowanie_konsumpcja << int(Statystyki::losowanie_konsumpcja[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_kasy.size(); i++) losowanie_kasy << int(Statystyki::losowanie_kasy[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_napoje.size(); i++) losowanie_napoje << int(Statystyki::losowanie_napoje[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_jedzenie.size(); i++) losowanie_jedzenie << int(Statystyki::losowanie_jedzenie[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_alarm.size(); i++) losowanie_alarm << int(Statystyki::losowanie_alarm[i]) << std::endl;

	system("pause");

	return 0;
}
*/