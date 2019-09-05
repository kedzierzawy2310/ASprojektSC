#include "stdafx.h"
#include "Time Events 2.h"
#include "Customer Group.h"
#include <iostream>
#include <random>
#include <chrono>
#include "Schedule.h"

ZdarzeniaCzasowe::ZdarzeniaCzasowe()
{
	
}

ZdarzeniaCzasowe::~ZdarzeniaCzasowe() = default;

void ZdarzeniaCzasowe::execute(){}


void ZdarzeniaCzasowe::UstawRozklad(int i)
{
	rozklad_ = i;
}

double ZdarzeniaCzasowe::PodajCzasWykonania()
{
	return czas_wykonania_;
}

void ZdarzeniaCzasowe::UstawCzasWykonania(Harmonogram* harmonogram)
{
	czas_wykonania_ = losuj(rozklad_, harmonogram) + harmonogram->PodajCzasSystemowy();
}

double ZdarzeniaCzasowe::losuj(int rozklad, Harmonogram* harmonogram)
{
	double randomowa;
	std::default_random_engine gen;
	std::normal_distribution<double> rozklad_klient(mean_a_, sigma_a_); //ROZK£AD NORMALNY - POJAWIENIE SIÊ KLIENTÓW
	std::normal_distribution<double> rozklad_bufet(mean_b_, sigma_b_); //ROZK£AD  NORMALNY - CZAS W BUFECIE
	std::normal_distribution<double> rozklad_alarm(mean_c_, sigma_c_); //ROZK£AD  NORMALNY - ALARM
	const std::exponential_distribution<double> rozklad_kasy(lambda_kasy_); //ROZK£AD WYK£ADNICZY - CZAS GRUPY KLIENTÓW PRZY KASIE
	const std::exponential_distribution<double> rozklad_konsumpcja(lambda_konsumpcja_); //ROZK£AD WYK£ADNICZY - CZAS KONSUMPCJI KLIENTÓW 
	const std::exponential_distribution<double> rozklad_jedzenie(lambda_jedzenie_); //ROZK£AD WYK£ADNICZY - CZAS OCZEKIWANIA NA DANIE G£ÓWNE
	const std::exponential_distribution<double> rozklad_napoje(lambda_napoje_); //ROZK£AD WYK£ADNICZY - CZAS OCZEKIWANIA NA NAPOJE

																			   //-------------------------------------------------------------------------------------------- WYBÓR ROZK£ADU ----------------------------------------------------------------------------------------------------------------

	gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
	switch (rozklad)
	{
	case 1:
		randomowa = abs(rozklad_klient(gen));
		//Statystyki::losowanie_klienci.push_back(randomowa);
		break;
	case 2:
		randomowa = 10; //modyfikacja mo¿liwa
		break;
	case 3:
		randomowa = abs(rozklad_napoje(gen));
		//Statystyki::losowanie_napoje.push_back(randomowa);
		break;
	case 4:
		randomowa = abs(rozklad_jedzenie(gen));
		//Statystyki::losowanie_jedzenie.push_back(randomowa);
		break;
	case 5:
		randomowa = abs(rozklad_konsumpcja(gen));
		//Statystyki::losowanie_konsumpcja.push_back(randomowa);
		break;
	case 6:
		randomowa = abs(rozklad_kasy(gen));
		//Statystyki::losowanie_kasy.push_back(randomowa);
		break;
	case 7:
		randomowa = abs(rozklad_bufet(gen));
		//Statystyki::losowanie_bufet.push_back(randomowa);
		break;
	case 8:
		randomowa = abs(rozklad_alarm(gen));
		//Statystyki::losowanie_alarm.push_back(randomowa);
		break;
	default:
		std::cout << harmonogram->PodajCzasSystemowy() << " Nie mozna wybrac rozkladu" << std::endl;
		randomowa = abs(rand() % 100 + 1);
		break;
	}
	return randomowa;
}

int ZdarzeniaCzasowe::PodajRozklad()
{
	return rozklad_;
}

nowaGrupa::nowaGrupa(Restauracja* restauracja, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
	UstawRozklad(1);
	UstawCzasWykonania(harmonogram_);
}

void nowaGrupa::execute()
{
	grupaKlientow* grupa = new grupaKlientow;
	statystyki_->AktualizujLiczbeWszystkichUtworzonych();
	grupa->UstawId(statystyki_);
	//Statystyki::liczba_wszystkich_klientow++;
	//Statystyki::liczba_obecnych_klientow++;
	//faza1 << Statystyki::liczba_obecnych_klientow << std::endl;
	//faza2 << Statystyki::liczba_wszystkich_klientow << std::endl;
	//if (Statystyki::liczba_wszystkich_klientow>faza_poczatkowa)
	//{
		//kolejka_sala << Statystyki::liczba_kolejka_do_sali << std::endl;
		//kolejka_kasa << Statystyki::liczba_kolejka_do_kasy << std::endl;
	//}

	if (!grupa->SprawdzCzyBufet()) {
		if (restauracja_->ZarzadzajKolejkaDoSali().SprawdzCzyPusta())
		{
			restauracja_->PrzypiszPomKol(grupa);
		}
		else
		{
			restauracja_->PodajPomKol()->UstawNastepnaKolejka(grupa);
			restauracja_->PrzypiszPomKol(grupa);
		}
		restauracja_->DodajDoKolejkiSala(grupa);
		statystyki_->AktualizujWS();
		std::cout << harmonogram_->PodajCzasSystemowy() << " Dodano grupe o ID: " << grupa->PodajId() << " do kolejki do sali" << std::endl;
		
		if (!statystyki_->SprawdzCzyPierwszySala())
		{
			statystyki_->PrzypiszCzasWagowySala(harmonogram_->PodajCzasSystemowy() - statystyki_->PodajCzasOstatniegoPomiaruSala());
			statystyki_->PrzypiszCzasOstatniegoPomiaruSala(harmonogram_->PodajCzasSystemowy());
			statystyki_->AktualizujSumeCzasowSala(statystyki_->PodajCzasWagowySala());
			statystyki_->ZsumujKolejkaSala(statystyki_->PodajLiczbeKolejkaSala() * statystyki_->PodajCzasWagowySala());
			statystyki_->AktualizujLiczbeKolejkaSala(restauracja_->ZarzadzajKolejkaDoSali().SprawdzRozmiar());
		}
		else
		{
			statystyki_->PrzypiszCzasOstatniegoPomiaruSala(harmonogram_->PodajCzasSystemowy());
			statystyki_->ZmienStatusPierwszegoSala(false);
			statystyki_->AktualizujLiczbeKolejkaSala(restauracja_->ZarzadzajKolejkaDoSali().SprawdzRozmiar());
		}
		grupa->UstawCzasPojawieniaSieNaSali(harmonogram_->PodajCzasSystemowy());
		
	}
	else {
		if (restauracja_->ZarzadzajKolejkaDoBufetu().SprawdzCzyPusta())
		{
			restauracja_->PrzypiszPomKolBuf(grupa);
		}
		else
		{
			restauracja_->PodajPomKolBuf()->UstawNastepnaKolejka(grupa);
			restauracja_->PrzypiszPomKolBuf(grupa);
		}
		restauracja_->DodajDoKolejkiBufet(grupa);
		statystyki_->AktualizujWB();
		std::cout << harmonogram_->PodajCzasSystemowy() << " Dodano grupe o ID: " << grupa->PodajId() << " do kolejki do bufetu" << std::endl;
		//Statystyki::liczba_kolejka_do_bufetu++;
	}
	nowaGrupa* nowa_grupa = new nowaGrupa(restauracja_, harmonogram_, statystyki_);
	harmonogram_->dodaj(nowa_grupa);
	std::cout << harmonogram_->PodajCzasSystemowy() << " Zaplanowano nowa grupe klientow" << std::endl;
}

powrotKierownika::powrotKierownika(Kierownik* kierownik, Harmonogram* harmonogram)
{
	kierownik_ = kierownik;
	harmonogram_ = harmonogram;
	UstawRozklad(2);
	UstawCzasWykonania(harmonogram_);
}

void powrotKierownika::execute()
{
	kierownik_->AktualizujLiczbeObsluzen();
	kierownik_->PrzypiszGrupe(nullptr);
	kierownik_->UstawStatus(true);
	std::cout << harmonogram_->PodajCzasSystemowy() << " Kierownik oczekuje na nastepna grupe" << std::endl;
}

podanieNapojow::podanieNapojow(Sala* sala, Harmonogram* harmonogram)
{
	sala_ = sala;
	harmonogram_ = harmonogram;
	UstawRozklad(3);
	UstawCzasWykonania(harmonogram_);
}

void podanieNapojow::execute()
{
	Stoliki* stolik = nullptr;
	if (!sala_->WskazListeNapoje().empty())
	{
		stolik = sala_->WskazListeNapoje().front();
		sala_->WskazListeNapoje().front()->UstawNastepnyNapoje(nullptr);
		sala_->UsunZNapojow();

		stolik->ZmienStatus('n',true);
		std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " otrzymala napoje" << std::endl;
		stolik->ZwrocAktualnaGrupe()->ZwrocAktualnegoKelnera()->AktualizujLiczbeObsluzen();
		stolik->ZwrocAktualnaGrupe()->ZwrocAktualnegoKelnera()->UstawStatus(true);
		stolik->ZwrocAktualnaGrupe()->PrzypiszKelnera(nullptr);
		if (!sala_->WskazListeJedzenie().empty())
		{
			sala_->WskazListeJedzenie().back()->UstawNastepnyJedzenie(stolik);
		}
		sala_->DodajDoJedzenia(stolik);
	}
}

podanieDan::podanieDan(Restauracja* restauracja, Sala* sala, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	sala_ = sala;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
	UstawRozklad(4);
	UstawCzasWykonania(harmonogram_);

}

void podanieDan::execute()
{
	if (!sala_->WskazListeJedzenie().empty())
	{
		auto stolik = sala_->WskazListeJedzenie().front();
		stolik->UstawNastepnyJedzenie(nullptr);
		sala_->UsunZJedzenia();

		stolik->ZmienStatus('j',true);
		std::cout << harmonogram_->PodajCzasSystemowy() << " Podano posilek. Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " zostala obsluzona" << std::endl;
		stolik->ZwrocAktualnaGrupe()->ZwrocAktualnegoKelnera()->AktualizujLiczbeObsluzen();
		stolik->ZwrocAktualnaGrupe()->ZwrocAktualnegoKelnera()->UstawStatus(true);
		stolik->ZwrocAktualnaGrupe()->PrzypiszKelnera(nullptr);
		if (!sala_->WskazListeZjedzone().empty())
		{
			sala_->WskazListeZjedzone().back()->UstawNastepnyZjedzone(stolik);
		}
		sala_->DodajDoZjedzonych(stolik);
		std::cout << harmonogram_->PodajCzasSystemowy() << " Rozpoczecie konsumpcji przez grupe " << stolik->ZwrocAktualnaGrupe()->PodajId() << std::endl;
		koniecKonsumpcji* koniec_konsumpcji = new koniecKonsumpcji(restauracja_, sala_, harmonogram_, statystyki_);
		harmonogram_->dodaj(koniec_konsumpcji);
	}
}

powrotZBufetu::powrotZBufetu(Restauracja* restauracja, Bufet* bufet, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	bufet_ = bufet;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
	UstawRozklad(7);
	UstawCzasWykonania(harmonogram_);
}

void powrotZBufetu::execute()
{
	if (!restauracja_->ZarzadzajListaBufetu().SprawdzCzyPusta())
	{
		auto grupa = restauracja_->ZarzadzajListaBufetu().WskazPierwszy();
		auto flaga = false;
		while (!flaga)
		{
			if (grupa->PodajCzasOpuszczeniaBufetu() == harmonogram_->PodajCzasSystemowy())
			{
				auto wlasciwa = grupa;
				if (restauracja_->ZarzadzajListaBufetu().WskazPierwszy() != wlasciwa)
				{
					if (wlasciwa->SprawdzCzyNastepna())
					{
						wlasciwa->ZwrocPoprzedni()->UstawNastepna(wlasciwa->ZwrocNastepny());
						wlasciwa->ZwrocNastepny()->UstawPoprzednia(wlasciwa->ZwrocPoprzedni());
					}
					wlasciwa->UstawNastepna(nullptr);
					if (restauracja_->ZarzadzajListaBufetu().WskazOstatni() == wlasciwa) wlasciwa->ZwrocPoprzedni()->UstawNastepna(nullptr) ;
					wlasciwa->UstawPoprzednia(nullptr);
					grupa = restauracja_->ZarzadzajListaBufetu().WskazPierwszy();
					while (restauracja_->ZarzadzajListaBufetu().SprawdzRozmiar() != 0)
					{
						restauracja_->UsunZBufetu();
					}
					while (grupa != nullptr)
					{
						restauracja_->DodajDoBufetu(grupa);
						grupa = grupa->ZwrocNastepny();
					}
				}
				else
				{
					restauracja_->UsunZBufetu();
				}
				if (restauracja_->ZarzadzajKolejkaDoKasy().SprawdzCzyPusta())
				{
					restauracja_->PrzypiszPomKolKas(grupa);
				}
				else
				{
					restauracja_->PodajPomKolKas()->UstawNastepnaKolejka(grupa);
					restauracja_->PrzypiszPomKolKas(grupa);
				}
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << wlasciwa->PodajId() << " opuscila bufet" << std::endl;
				bufet_->AktualizujBufet(wlasciwa, '-');
				std::cout << harmonogram_->PodajCzasSystemowy() << " Obecny stan bufetu: " << bufet_->PodajLiczbeOsob() << " z " << bufet_->PodajWielkoscBufetu() << std::endl;
				restauracja_->DodajDoKolejkiKasy(wlasciwa);
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << wlasciwa->PodajId() << " oczekuje w kolejce do kasy" << std::endl;
				if (!statystyki_->SprawdzCzyPierwszyKasy())
				{
					statystyki_->PrzypiszCzasWagowyKasy(harmonogram_->PodajCzasSystemowy() - statystyki_->PodajCzasOstatniegoPomiaruKasy());
					statystyki_->PrzypiszCzasOstatniegoPomiaruKasy(harmonogram_->PodajCzasSystemowy());
					statystyki_->AktualizujSumeCzasowKasy(statystyki_->PodajCzasWagowyKasy());
					statystyki_->ZsumujKolejkaKasy(statystyki_->PodajLiczbeKolejkaKasy() * statystyki_->PodajCzasWagowyKasy());
					statystyki_->AktualizujLiczbeKolejkaKasy(restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar());
				}
				else
				{
					statystyki_->PrzypiszCzasOstatniegoPomiaruKasy(harmonogram_->PodajCzasSystemowy());
					statystyki_->ZmienStatusPierwszegoKasy(false);
					statystyki_->AktualizujLiczbeKolejkaKasy(restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar());
				}
				flaga = true;
			}
			else
			{
				if (grupa->SprawdzCzyNastepna()) grupa = grupa->ZwrocNastepny();
				else break;
			}
		}
	}
}

alarm::alarm(Restauracja* restauracja, Sala* sala, Bufet* bufet, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	sala_ = sala;
	bufet_ = bufet;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
	UstawRozklad(8);
	UstawCzasWykonania(harmonogram_);
}

void alarm::execute()
{
	Stoliki* stolik;
	Stoliki* pom = nullptr;
	Stoliki* pom2 = nullptr;
	Stoliki* pom5 = nullptr;
	grupaKlientow* pom3 = nullptr;
	grupaKlientow* pom4 = nullptr;
	grupaKlientow* pom6 = nullptr;
	grupaKlientow* grupa;

	std::cout << "ALARM POZAROWY!" << std::endl;
	std::cout << "OBSLUGA" << std::endl;
	if (sala_->WskazListeDoObslugi().size() > 0) {
		stolik = sala_->WskazListeDoObslugi().front();
		for (auto i = 1; i <= sala_->WskazListeDoObslugi().size(); i++)
		{
			if (stolik->ZwrocAktualnaGrupe()->SprawdzCzyAlarm())
			{
				pom2 = stolik->ZwrocNastepnyObsluga();
				stolik->UstawNastepnyObsluga(nullptr);
				stolik->ZmienStatus('w', true);
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " opuscila lokal." << std::endl;
				delete stolik->ZwrocAktualnaGrupe();
				statystyki_->AktualizujLiczbeWszystkichAlarm();
				stolik->PrzypiszGrupe(nullptr);
				if (stolik->SprawdzCzyPomocniczyPrzypisany())
				{
					stolik->ZwrocPomocniczy()->PrzypiszPomocniczy(nullptr);
					stolik->ZwrocPomocniczy()->ZmienStatus('d', false);
					stolik->ZwrocPomocniczy()->ZmienStatus('w', true);
					stolik->PrzypiszPomocniczy(nullptr);
				}
				stolik = pom2;
				pom2 = nullptr;
			}
			else
			{
				if (pom == nullptr) {
					pom = stolik;
					stolik = stolik->ZwrocNastepnyObsluga();
					pom->UstawNastepnyObsluga(nullptr);
					pom5 = pom;
				}
				else
				{
					pom->UstawNastepnyObsluga(stolik);
					pom = stolik;
					stolik = stolik->ZwrocNastepnyObsluga();
					pom->UstawNastepnyObsluga(nullptr);
				}
			}
		}
		while (sala_->WskazListeDoObslugi().size() != 0)
		{
			sala_->UsunZObslugi();
		}
		while (pom5 != nullptr)
		{
			sala_->DodajDoObslugi(pom5);
			//if (!pom5->sprawdzCzyNastepnyObsluga()) obsluga = pom5;
			pom5 = pom5->ZwrocNastepnyObsluga();
		}
	}
	pom = nullptr;
	std::cout << "NAPOJE" << std::endl;
	if (sala_->WskazListeNapoje().size() > 0) {
		stolik = sala_->WskazListeNapoje().front();
		for (auto i = 1; i <= sala_->WskazListeNapoje().size(); i++)
		{
			if (stolik->ZwrocAktualnaGrupe()->SprawdzCzyAlarm())
			{
				pom2 = stolik->ZwrocNastepnyNapoje();
				stolik->UstawNastepnyNapoje(nullptr);
				stolik->ZmienStatus('w', true);
				stolik->ZwrocAktualnaGrupe()->ZwrocAktualnegoKelnera()->UstawStatus(true);
				stolik->ZwrocAktualnaGrupe()->PrzypiszKelnera(nullptr);
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " opuscila lokal." << std::endl;
				delete stolik->ZwrocAktualnaGrupe();
				statystyki_->AktualizujLiczbeWszystkichAlarm();
				stolik->PrzypiszGrupe(nullptr);
				if (stolik->SprawdzCzyPomocniczyPrzypisany())
				{
					stolik->ZwrocPomocniczy()->PrzypiszPomocniczy(nullptr);
					stolik->ZwrocPomocniczy()->ZmienStatus('d', false);
					stolik->ZwrocPomocniczy()->ZmienStatus('w', true);
					stolik->PrzypiszPomocniczy(nullptr);
				}
				stolik = pom2;
				pom2 = nullptr;
			}
			else
			{
				if (pom == nullptr) {
					pom = stolik;
					stolik = stolik->ZwrocNastepnyNapoje();
					pom->UstawNastepnyNapoje(nullptr);
					pom5 = pom;
				}
				else
				{
					pom->UstawNastepnyNapoje(stolik);
					pom = stolik;
					stolik = stolik->ZwrocNastepnyNapoje();
					pom->UstawNastepnyNapoje(nullptr);
				}
			}
		}
		while (sala_->WskazListeNapoje().size() != 0)
		{
			sala_->UsunZNapojow();
		}
		while (pom5 != nullptr)
		{
			sala_->DodajDoNapojow(pom5);
			//if (pom5->next_napoje == nullptr) Sala::stolik_napoje = pom5;
			pom5 = pom5->ZwrocNastepnyNapoje();
		}
	}
	pom = nullptr;
	std::cout << "JEDZENIE" << std::endl;
	if (sala_->WskazListeJedzenie().size() > 0) {
		stolik = sala_->WskazListeJedzenie().front();
		for (auto i = 1; i <= sala_->WskazListeJedzenie().size(); i++)
		{
			if (stolik->ZwrocAktualnaGrupe()->SprawdzCzyAlarm())
			{
				pom2 = stolik->ZwrocNastepnyJedzenie();
				stolik->ZmienStatus('n',false);
				stolik->UstawNastepnyJedzenie(nullptr);
				stolik->ZmienStatus('w', true);
				if (stolik->ZwrocAktualnaGrupe()->SprawdzCzyKelnerPrzypisany()) 
				{
					stolik->ZwrocAktualnaGrupe()->ZwrocAktualnegoKelnera()->UstawStatus(true);
					stolik->ZwrocAktualnaGrupe()->PrzypiszKelnera(nullptr);
				}
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " opuscila lokal." << std::endl;
				delete stolik->ZwrocAktualnaGrupe();
				statystyki_->AktualizujLiczbeWszystkichAlarm();
				stolik->PrzypiszGrupe(nullptr);
				if (stolik->SprawdzCzyPomocniczyPrzypisany())
				{
					stolik->ZwrocPomocniczy()->PrzypiszPomocniczy(nullptr);
					stolik->ZwrocPomocniczy()->ZmienStatus('d', false);
					stolik->ZwrocPomocniczy()->ZmienStatus('w', true);
					stolik->PrzypiszPomocniczy(nullptr);
				}
				stolik = pom2;
				pom2 = nullptr;
			}
			else
			{
				if (pom == nullptr) {
					pom = stolik;
					stolik = stolik->ZwrocNastepnyJedzenie();
					pom->UstawNastepnyJedzenie(nullptr);
					pom5 = pom;
				}
				else
				{
					pom->UstawNastepnyJedzenie(stolik);
					pom = stolik;
					stolik = stolik->ZwrocNastepnyJedzenie();
					pom->UstawNastepnyJedzenie(nullptr);
				}
			}
		}
		while (sala_->WskazListeJedzenie().size() != 0)
		{
			sala_->UsunZJedzenia();
		}
		while (pom5 != nullptr)
		{
			sala_->DodajDoJedzenia(pom5);
			//if (pom5->sprawdzCzyNastepnyJedzenie()) sala_->wskazListeJedzenie() = pom5;
			pom5 = pom5->ZwrocNastepnyJedzenie();
		}
	}
	pom = nullptr;
	std::cout << "ZJEDZONE" << std::endl;
	if (sala_->WskazListeZjedzone().size() > 0) {
		stolik = sala_->WskazListeZjedzone().front();
		for (auto i = 1; i <= sala_->WskazListeZjedzone().size(); i++)
		{
			if (stolik->ZwrocAktualnaGrupe()->SprawdzCzyAlarm())
			{
				pom2 = stolik->ZwrocNastepnyZjedzone();
				stolik->ZmienStatus('n', false);
				stolik->ZmienStatus('j', false);
				stolik->UstawNastepnyZjedzone(nullptr);
				stolik->ZmienStatus('w', true);
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " opuscila lokal." << std::endl;
				delete stolik->ZwrocAktualnaGrupe();
				statystyki_->AktualizujLiczbeWszystkichAlarm();
				stolik->PrzypiszGrupe(nullptr);
				if (stolik->SprawdzCzyPomocniczyPrzypisany())
				{
					stolik->ZwrocPomocniczy()->PrzypiszPomocniczy(nullptr);
					stolik->ZwrocPomocniczy()->ZmienStatus('d', false);
					stolik->ZwrocPomocniczy()->ZmienStatus('w', true);
					stolik->PrzypiszPomocniczy(nullptr);
				}
				stolik = pom2;
				pom2 = nullptr;
			}
			else
			{
				if (pom == nullptr) {
					pom = stolik;
					stolik = stolik->ZwrocNastepnyZjedzone();
					pom->UstawNastepnyZjedzone(nullptr);
					pom5 = pom;
				}
				else
				{
					pom->UstawNastepnyZjedzone(stolik);
					pom = stolik;
					stolik = stolik->ZwrocNastepnyZjedzone();
					pom->UstawNastepnyZjedzone(nullptr);
				}
			}
		}
		while (sala_->WskazListeZjedzone().size() != 0)
		{
			sala_->UsunZeZjedzonych();
		}
		while (pom5 != nullptr)
		{
			sala_->DodajDoZjedzonych(pom5);
			//if (pom5->next_zjedzone == nullptr) Sala::stolik_zjedzone = pom5;
			pom5 = pom5->ZwrocNastepnyZjedzone();
		}
	}
	pom = nullptr;
	std::cout << "KOLEJKA SALA" << std::endl;
	if (restauracja_->ZarzadzajKolejkaDoSali().SprawdzRozmiar() > 0) {
		grupa = restauracja_->ZarzadzajKolejkaDoSali().WskazPierwszy();
		for (auto i = 1; i <= restauracja_->ZarzadzajKolejkaDoSali().SprawdzRozmiar(); i++)
		{
			if (grupa->SprawdzCzyAlarm())
			{
				pom3 = grupa;
				grupa = grupa->ZwrocNastepnyKolejka();
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << pom3->PodajId() << " opuscila lokal." << std::endl;
				delete pom3;
				statystyki_->AktualizujLiczbeWszystkichAlarm();
				statystyki_->AktualizujAlarmKolejki();
				pom3 = nullptr;
			}
			else
			{
				if (pom4 == nullptr)
				{
					pom4 = grupa;
					grupa = grupa->ZwrocNastepnyKolejka();
					pom4->UstawNastepnaKolejka(nullptr);
					pom6 = pom4;
				}
				else
				{
					pom4->UstawNastepnaKolejka(grupa);
					pom4 = grupa;
					grupa = grupa->ZwrocNastepnyKolejka();
					pom4->UstawNastepnaKolejka(nullptr);
				}
			}
		}
		while (restauracja_->ZarzadzajKolejkaDoSali().SprawdzRozmiar() != 0)
		{
			restauracja_->UsunZKolejkiSala();
		}
		while (pom6 != nullptr)
		{
			restauracja_->DodajDoKolejkiSala(pom6);
			if (!pom6->SprawdzCzyNastepnaKolejka()) restauracja_->PrzypiszPomKol(pom6);
			pom6 = pom6->ZwrocNastepnyKolejka();
		}
	}
	if (!statystyki_->SprawdzCzyPierwszySala())
	{
		statystyki_->PrzypiszCzasWagowySala(harmonogram_->PodajCzasSystemowy() - statystyki_->PodajCzasOstatniegoPomiaruSala());
		statystyki_->PrzypiszCzasOstatniegoPomiaruSala(harmonogram_->PodajCzasSystemowy());
		statystyki_->AktualizujSumeCzasowSala(statystyki_->PodajCzasWagowySala());
		statystyki_->ZsumujKolejkaSala(statystyki_->PodajLiczbeKolejkaSala() * statystyki_->PodajCzasWagowySala());
		statystyki_->AktualizujLiczbeKolejkaSala(restauracja_->ZarzadzajKolejkaDoSali().SprawdzRozmiar());
	}
	else
	{
		statystyki_->PrzypiszCzasOstatniegoPomiaruSala(harmonogram_->PodajCzasSystemowy());
		statystyki_->ZmienStatusPierwszegoSala(false);
		statystyki_->AktualizujLiczbeKolejkaSala(restauracja_->ZarzadzajKolejkaDoSali().SprawdzRozmiar());
	}
	pom4 = nullptr;
	std::cout << "KOLEJKA BUFET" << std::endl;
	if (restauracja_->ZarzadzajKolejkaDoBufetu().SprawdzRozmiar() > 0) {
		grupa = restauracja_->ZarzadzajKolejkaDoBufetu().WskazPierwszy();
		for (auto i = 1; i <= restauracja_->ZarzadzajKolejkaDoBufetu().SprawdzRozmiar(); i++)
		{
			if (grupa->SprawdzCzyAlarm())
			{
				pom3 = grupa;
				grupa = grupa->ZwrocNastepnyKolejka();
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << pom3->PodajId() << " opuscila lokal." << std::endl;
				delete pom3;
				statystyki_->AktualizujLiczbeWszystkichAlarm();
				statystyki_->AktualizujAlarmKolejki();
				pom3 = nullptr;
			}
			else
			{
				if (pom4 == nullptr)
				{
					pom4 = grupa;
					grupa = grupa->ZwrocNastepnyKolejka();
					pom4->UstawNastepnaKolejka(nullptr);
					pom6 = pom4;
				}
				else
				{
					pom4->UstawNastepnaKolejka(grupa);
					pom4 = grupa;
					grupa = grupa->ZwrocNastepnyKolejka();
					pom4->UstawNastepnaKolejka(nullptr);
				}
			}
		}
		while (restauracja_->ZarzadzajKolejkaDoBufetu().SprawdzRozmiar() != 0)
		{
			restauracja_->UsunZKolejkiBufet();
		}
		while (pom6 != nullptr)
		{
			restauracja_->DodajDoKolejkiBufet(pom6);
			if (!pom6->SprawdzCzyNastepnaKolejka()) restauracja_->PrzypiszPomKolBuf(pom6);
			pom6 = pom6->ZwrocNastepnyKolejka();
		}
	}
	pom4 = nullptr;
	std::cout << "KOLEJKA KASY" << std::endl;
	if (restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar() > 0) {
		grupa = restauracja_->ZarzadzajKolejkaDoKasy().WskazPierwszy();
		for (auto i = 1; i <= restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar(); i++)
		{
			if (grupa->SprawdzCzyAlarm())
			{
				pom3 = grupa;
				grupa = grupa->ZwrocNastepnyKolejka();
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << pom3->PodajId() << " opuscila lokal." << std::endl;
				delete pom3;
				statystyki_->AktualizujLiczbeWszystkichAlarm();
				statystyki_->AktualizujAlarmKolejki();
				pom3 = nullptr;
			}
			else
			{
				if (pom4 == nullptr)
				{
					pom4 = grupa;
					grupa = grupa->ZwrocNastepnyKolejka();
					pom4->UstawNastepnaKolejka(nullptr);
					pom6 = pom4;
				}
				else
				{
					pom4->UstawNastepnaKolejka(grupa);
					pom4 = grupa;
					grupa = grupa->ZwrocNastepnyKolejka();
					pom4->UstawNastepnaKolejka(nullptr);
				}
			}
		}
		while (restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar() != 0)
		{
			restauracja_->UsunZKolejkiKasy();
		}
		while (pom6 != nullptr)
		{
			restauracja_->DodajDoKolejkiKasy(pom6);
			if (!pom6->SprawdzCzyNastepnaKolejka()) restauracja_->PrzypiszPomKolKas(pom6);
			pom6 = pom6->ZwrocNastepnyKolejka();
		}
	}
	if (!statystyki_->SprawdzCzyPierwszyKasy())
	{
		statystyki_->PrzypiszCzasWagowyKasy(harmonogram_->PodajCzasSystemowy() - statystyki_->PodajCzasOstatniegoPomiaruKasy());
		statystyki_->PrzypiszCzasOstatniegoPomiaruKasy(harmonogram_->PodajCzasSystemowy());
		statystyki_->AktualizujSumeCzasowKasy(statystyki_->PodajCzasWagowyKasy());
		statystyki_->ZsumujKolejkaKasy(statystyki_->PodajLiczbeKolejkaKasy() * statystyki_->PodajCzasWagowyKasy());
		statystyki_->AktualizujLiczbeKolejkaKasy(restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar());
	}
	else
	{
		statystyki_->PrzypiszCzasOstatniegoPomiaruKasy(harmonogram_->PodajCzasSystemowy());
		statystyki_->ZmienStatusPierwszegoKasy(false);
		statystyki_->AktualizujLiczbeKolejkaKasy(restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar());
	}
	pom4 = nullptr;
	std::cout << "BUFET" << std::endl;
	if (restauracja_->ZarzadzajListaBufetu().SprawdzRozmiar() > 0) {
		grupa = restauracja_->ZarzadzajListaBufetu().WskazPierwszy();
		for (auto i = 1; i <= restauracja_->ZarzadzajListaBufetu().SprawdzRozmiar(); i++)
		{
			if (grupa->SprawdzCzyNastepna()) pom3 = grupa->ZwrocNastepny();
			if (grupa->SprawdzCzyAlarm())
			{
				if (restauracja_->ZarzadzajListaBufetu().WskazPierwszy() != grupa)
				{
					if (grupa->SprawdzCzyNastepna())
					{
						grupa->ZwrocPoprzedni()->UstawNastepna(grupa->ZwrocNastepny());
						grupa->ZwrocNastepny()->UstawPoprzednia(grupa->ZwrocPoprzedni());
					}
					grupa->UstawNastepna(nullptr);
					if (restauracja_->ZarzadzajListaBufetu().WskazOstatni() == grupa) grupa->ZwrocPoprzedni()->UstawNastepna(nullptr);
					grupa->UstawPoprzednia(nullptr);
					pom4 = restauracja_->ZarzadzajListaBufetu().WskazPierwszy();
					while (restauracja_->ZarzadzajListaBufetu().SprawdzRozmiar() != 0)
					{
						restauracja_->UsunZBufetu();
					}
					while (pom4 != nullptr)
					{
						restauracja_->DodajDoBufetu(pom4);
						pom4 = pom4->ZwrocNastepny();
					}
				}
				else
				{
					restauracja_->UsunZBufetu();
				}
				bufet_->AktualizujBufet(grupa, '-');
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << grupa->PodajId() << " opuscila lokal." << std::endl;
				delete grupa;
				statystyki_->AktualizujLiczbeWszystkichAlarm();
			}
			grupa = pom3;
		}
	}
	statystyki_->AktualizujLiczbeAlarmow();
	alarm* wlacz_alarm = new alarm(restauracja_, sala_, bufet_, harmonogram_, statystyki_);
	harmonogram_->dodaj(wlacz_alarm);
	std::cout << "KONIEC ALARMU" << std::endl;
}

dokonaniePlatnosci::dokonaniePlatnosci(Restauracja* restauracja, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
	UstawRozklad(6);
	UstawCzasWykonania(harmonogram_);
}

void dokonaniePlatnosci::execute()
{
	auto kasjer = restauracja_->ZwrocListeKasjerow().front();
	auto flaga = false;
	while (!flaga)
	{
		if (kasjer->SprawdzCzyGrupaPrzypisana() && kasjer->ZwrocAktualnaGrupa()->PodajCzasPlacenia() == harmonogram_->PodajCzasSystemowy()) {
			auto grupa = kasjer->ZwrocAktualnaGrupa();
			std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << grupa->PodajId() << " zaplacila za posilek (kasjer " << kasjer->PodajId() << ")" << std::endl;
			kasjer->AktualizujLiczbeObsluzen();
			kasjer->PrzypiszGrupe(nullptr);
			std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << grupa->PodajId() << " opuscila lokal." << std::endl;
			delete grupa;
			statystyki_->AktualizujLiczbeWszystkichObsluzonnych();
			//Statystyki::liczba_obecnych_klientow--;
			flaga = true;
		}
		else kasjer = kasjer->ZwrocNastepna();
	}
}

koniecKonsumpcji::koniecKonsumpcji(Restauracja* restauracja, Sala* sala, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	sala_ = sala;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
	UstawRozklad(5);
	UstawCzasWykonania(harmonogram_);
}

void koniecKonsumpcji::execute()
{
	if (!sala_->WskazListeZjedzone().empty()) {
		auto stolik = sala_->WskazListeZjedzone().front();
		if (!sala_->WskazListeZjedzone().empty())
		{
			stolik->UstawNastepnyZjedzone(nullptr);
			sala_->UsunZeZjedzonych();
		}
		if (restauracja_->ZarzadzajKolejkaDoKasy().SprawdzCzyPusta())
		{
			restauracja_->PrzypiszPomKolKas(stolik->ZwrocAktualnaGrupe());
		}
		else
		{
			restauracja_->PodajPomKolKas()->UstawNastepnaKolejka(stolik->ZwrocAktualnaGrupe());
			restauracja_->PrzypiszPomKolKas(stolik->ZwrocAktualnaGrupe());
		}
		std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " zakonczyla konsumpcje" << std::endl;
		restauracja_->DodajDoKolejkiKasy(stolik->ZwrocAktualnaGrupe());
		std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " oczekuje w kolejce do kasy" << std::endl;

		if (!statystyki_->SprawdzCzyPierwszyKasy())
		{
			statystyki_->PrzypiszCzasWagowyKasy(harmonogram_->PodajCzasSystemowy() - statystyki_->PodajCzasOstatniegoPomiaruKasy());
			statystyki_->PrzypiszCzasOstatniegoPomiaruKasy(harmonogram_->PodajCzasSystemowy());
			statystyki_->AktualizujSumeCzasowKasy(statystyki_->PodajCzasWagowyKasy());
			statystyki_->ZsumujKolejkaKasy(statystyki_->PodajLiczbeKolejkaKasy() * statystyki_->PodajCzasWagowyKasy());
			statystyki_->AktualizujLiczbeKolejkaKasy(restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar());
		}
		else
		{
			statystyki_->PrzypiszCzasOstatniegoPomiaruKasy(harmonogram_->PodajCzasSystemowy());
			statystyki_->ZmienStatusPierwszegoKasy(false);
			statystyki_->AktualizujLiczbeKolejkaKasy(restauracja_->ZarzadzajKolejkaDoKasy().SprawdzRozmiar());
		}

		stolik->PrzypiszGrupe(nullptr);
		stolik->ZmienStatus('w', true);
		stolik->ZmienStatus('j', false);
		stolik->ZmienStatus('n', false);
		if (stolik->SprawdzCzyPomocniczyPrzypisany())
		{
			stolik->ZwrocPomocniczy()->ZmienStatus('d', false);
			stolik->ZwrocPomocniczy()->ZmienStatus('w', true);
			stolik->ZwrocPomocniczy()->PrzypiszPomocniczy(nullptr);
			stolik->PrzypiszPomocniczy(nullptr);
		}
	}
}