#include "stdafx.h"
#pragma once
#include "Conditional Events.h"
#include <iostream>

//------------------------------------------------------------------------------------------ PÊTLA G£ÓWNA -------------------------------------------------------------------------------------------------------------------

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
	auto sala = new Sala;
	Kierownik* kierownik = new Kierownik;
	Bufet* bufet = new Bufet;
	Harmonogram* harmonogram = new Harmonogram;
	Statystyki* statystyki = new Statystyki;

	ZdarzenieWarunkowe* warunkowe;
	//faza1 << Statystyki::liczba_obecnych_klientow << std::endl;
	//faza2 << Statystyki::liczba_wszystkich_klientow << std::endl;

	//--------------------------------------------------------------------------- LISTÊ ZDARZEÑ NA OBIEKTY TYPU KOMUNIKAT -------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------- ODCZYTYWANIE CZASU WYKONYWANIA Z KOMUNIKATU komunikat->zdarzenie->czas_wykonania ---------------------------------------------------------------------------------

	nowaGrupa* nowa_grupa = new nowaGrupa(restauracja, harmonogram, statystyki);
	harmonogram->dodaj(nowa_grupa);

	alarm* wlacz_alarm = new alarm(restauracja, sala, bufet, harmonogram, statystyki);
	harmonogram->dodaj(wlacz_alarm);

	while (statystyki->PodajLiczbeWszystkichObsluzonych() < 1500)
	{
		auto czasowe = harmonogram->ZarzadzajZdarzeniami()[harmonogram->ZarzadzajZdarzeniami().size() - 1];
		harmonogram->usuñ();
		harmonogram->AktualizujCzasSystemowy(czasowe);
		czasowe->execute();
		delete czasowe;

		//-------------------------------------------------------------------------- PRZEGL¥D ZDARZEÑ WARUNKOWYCH ----------------------------------------------------------------------------------------------------------------

	
		//------------------------------------------------------------------------------- WEJŒCIE DO BUFETU ----------------------------------------------------------------------------------------------------------------------

		if (!restauracja->ZarzadzajKolejkaDoBufetu().SprawdzCzyPusta())
		{
			warunkowe = new wejscieDoBufetu(restauracja, bufet, harmonogram, statystyki);
			warunkowe->execute();
			delete warunkowe;
		}

		//----------------------------------------------------- PRZYDZIELANIE STOLIKÓW PRZEZ KIEROWNIKA SALI (METODA: £¥CZENIE STOLIKÓW) ----------------------------------------------------------------------------------------

		if (!restauracja->ZarzadzajKolejkaDoSali().SprawdzCzyPusta() && kierownik->SprawdzCzyWolny())
		{
			warunkowe = new przypisanieStolika(restauracja, sala, kierownik, harmonogram, statystyki);
			warunkowe->execute();
			delete warunkowe;
		}

		//-------------------------------------------------------------------- OBS£UGA STOLIKÓW PRZEZ KELNERÓW (NAPOJE) ---------------------------------------------------------------------------------------------------------

		if (!sala->WskazListeKelnera().empty() && !sala->WskazListeDoObslugi().empty())
		{
			warunkowe = new obslugaNapoje(sala, harmonogram, statystyki);
			warunkowe->execute();
			delete warunkowe;
		}

		//------------------------------------------------------------------ OBS£UGA STOLIKÓW PRZEZ KELNERÓW (DANIE G£ÓWNE) ------------------------------------------------------------------------------------------------------

		if (!sala->WskazListeKelnera().empty() && !sala->WskazListeJedzenie().empty())
		{
			warunkowe = new obslugaJedzenie(restauracja, sala, harmonogram, statystyki);
			warunkowe->execute();
			delete warunkowe;
		}

		//------------------------------------------------------------------------- OBS£UGA KLIENTÓW PRZEZ KASJERÓW --------------------------------------------------------------------------------------------------------------

		if (!restauracja->ZarzadzajKolejkaDoKasy().SprawdzCzyPusta() && !restauracja->ZwrocListeKasjerow().empty())
		{
			warunkowe = new placenie(restauracja, harmonogram, statystyki);
			warunkowe->execute();
			delete warunkowe;
		}		
	}

	//-------------------------------------------------------------------------------------- STATYSTYKI SYMULACJI ----------------------------------------------------------------------------------------------------------------

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Statystyki symulacji:" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//--------------------------------------------------------------------------------------- CZASY OCZEKIWANIA ------------------------------------------------------------------------------------------------------------------

	std::cout << "Czasy oczekiwania:" << std::endl;
	std::cout << std::endl;

	std::cout << "Sredni czas oczekiwania na stolik: " << statystyki->PodajSumaCzasowStolik()/statystyki->PodajCounterStoliki() << std::endl;
	std::cout << "Sredni czas oczekiwania na obsluge przez kelnera: " << statystyki->PodajSumaCzasowObsluga()/statystyki->PodajCounterObsluga() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//--------------------------------------------------------------------------------------- KOLEJKI KLIENTÓW -------------------------------------------------------------------------------------------------------------------

	std::cout << "Kolejki:" << std::endl;
	std::cout << std::endl;
	std::cout << "Stan kolejki do sali: " << restauracja->ZarzadzajKolejkaDoSali().SprawdzRozmiar() << std::endl;
	std::cout << "Stan kolejki do bufetu: " << restauracja->ZarzadzajKolejkaDoBufetu().SprawdzRozmiar() << std::endl;
	std::cout << "Stan kolejki do kasy: " << restauracja->ZarzadzajKolejkaDoKasy().SprawdzRozmiar() << std::endl;
	std::cout << std::endl;

	std::cout << "Srednia dlugosc kolejki do sali: " << statystyki->PodajSumeKolejkiSala()/statystyki->PodajSumaCzasowSala() << std::endl;
	std::cout << "Srednia dlugosc kolejki do kasy: " << statystyki->PodajSumeKolejkiKasy()/statystyki->PodajSumaCzasowKasy() << std::endl;

	//-------------------------------------------------------------------------------------------- ALARM --------------------------------------------------------------------------------------------------------------------------

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Alarm:" << std::endl;
	std::cout << std::endl;
	std::cout << "Liczba alarmow: " << statystyki->PodajLiczbeAlarmow() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//-------------------------------------------------------------------------------------------- BUFET --------------------------------------------------------------------------------------------------------------------------

	std::cout << "Bufet:" << std::endl;
	std::cout << std::endl;
	std::cout << "Stan bufetu: " << bufet->PodajLiczbeOsob() << "/" << bufet->PodajWielkoscBufetu() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//------------------------------------------------------------------------------------------- KLIENCI -------------------------------------------------------------------------------------------------------------------------

	std::cout << "Klienci:" << std::endl;
	std::cout << std::endl;
	std::cout << "Liczba wszystkich grup klientow: " << statystyki->PodajLiczbeWszystkichUtworzonych() << std::endl;
	std::cout << "Liczba wszystkich obsluzonych grup klientow: " << statystyki->PodajLiczbeWszystkichObsluzonych() << std::endl;
	std::cout << "Liczba wszystkich grup klientow w bufecie: " << statystyki->PodajLiczbeWszystkichBufet() << "/" << statystyki->PodajWB() << std::endl;
	std::cout << "Liczba wszystkich grup klientow na sali: " << statystyki->PodajLiczbeWszystkichSala() << "/" << statystyki->PodajWS() << std::endl;
	std::cout << "Liczba wszystkich grup klientow, ktore opuscily podczas alarmu pozarowego: " << statystyki->PodajLiczbeWszystkichAlarm() << " (w tym "<< statystyki->PodajAlarmKolejki() << " z kolejek)" <<std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//--------------------------------------------------------------------------------------- KIEROWNIK SALI ----------------------------------------------------------------------------------------------------------------------

	std::cout << "Kierownik:" << std::endl;
	std::cout << std::endl;
	std::cout << "Kierownik obsluzyl: " << kierownik->PodajLiczbeObsluzen() << " grup." << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	//------------------------------------------------------------------------------------------- KELNERZY -----------------------------------------------------------------------------------------------------------------------

	std::cout << "Kelnerzy:" << std::endl;
	std::cout << std::endl;
	while (sala->WskazListeKelnera().size() != 0)
	{
		Kelner* kelner = sala->WskazListeKelnera().front();
		std::cout << "Kelner " << kelner->PodajId() << " obsluzyl: " << kelner->PodajLiczbeObsluzen() << " grup." << std::endl;
		kelner->UstawNastepny(nullptr);
		sala->UsunZListyKelnerow();
		delete kelner;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	//------------------------------------------------------------------------------------------- KASJERZY -----------------------------------------------------------------------------------------------------------------------

	std::cout << "Kasy:" << std::endl;
	std::cout << std::endl;
	while (restauracja->ZwrocListeKasjerow().size() != 0)
	{
		Kasa* kasjer = restauracja->ZwrocListeKasjerow().front();
		std::cout << "Kasjer " << kasjer->PodajId() << " obsluzyl: " << kasjer->PodajLiczbeObsluzen() << " grup." << std::endl;
		kasjer->UstawNastepna(nullptr);
		restauracja->UsunZListyKasjerow();
		if (kasjer->SprawdzCzyGrupaPrzypisana()) delete kasjer->ZwrocAktualnaGrupa();
		delete kasjer;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	//------------------------------------------------------------------------------------------- USUWANIE ------------------------------------------------------------------------------------------------------------------------ 

	delete kierownik;
	delete bufet;
	delete sala;
	delete restauracja;
	delete statystyki;
	delete harmonogram;

	//-------------------------------------------------------------------------------------------- ZAPIS DANYCH ----------------------------------------------------------------------------------------------------------------
	/*
	for (int i = 0; i<Statystyki::losowanie_klienci.size(); i++) losowanie_klient << int(Statystyki::losowanie_klienci[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_bufet.size(); i++) losowanie_bufet << int(Statystyki::losowanie_bufet[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_konsumpcja.size(); i++) losowanie_konsumpcja << int(Statystyki::losowanie_konsumpcja[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_kasy.size(); i++) losowanie_kasy << int(Statystyki::losowanie_kasy[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_napoje.size(); i++) losowanie_napoje << int(Statystyki::losowanie_napoje[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_jedzenie.size(); i++) losowanie_jedzenie << int(Statystyki::losowanie_jedzenie[i]) << std::endl;
	for (int i = 0; i<Statystyki::losowanie_alarm.size(); i++) losowanie_alarm << int(Statystyki::losowanie_alarm[i]) << std::endl;
	*/
	system("pause");

	return 0;
}