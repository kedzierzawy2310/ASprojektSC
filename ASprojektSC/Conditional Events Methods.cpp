#include "stdafx.h"
#include "Conditional Events.h"
#include "Time Events 2.h"
#include <iostream>

ZdarzenieWarunkowe::ZdarzenieWarunkowe() = default;

ZdarzenieWarunkowe::~ZdarzenieWarunkowe() = default;

void ZdarzenieWarunkowe::execute() {}

przypisanieStolika::przypisanieStolika(Restauracja* restauracja, Sala* sala, Kierownik* kierownik, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	sala_ = sala;
	kierownik_ = kierownik;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
}

void przypisanieStolika::execute()
{
	auto grupa = restauracja_->ZarzadzajKolejkaDoSali().WskazPierwszy();
	kierownik_->PrzypiszGrupe(grupa);
	auto stolik = sala_->WskazListe2().front();
	Stoliki* pom = nullptr;
	if (stolik != nullptr)
	{
		if (grupa->PodajWielkosc() == 2 || grupa->PodajWielkosc() == 1) 
		{
			for (auto i = 0; i < sala_->WskazListe2().size(); i++)
			{
				if (!stolik->SprawdzCzyGrupaPrzypisana())
				{
					goto przypisz;
				}
				if (stolik->SprawdzCzyNastepny()) stolik = stolik->ZwrocNastepny();
				else break;
			}
		}
		if (grupa->PodajWielkosc() == 3 || grupa->PodajWielkosc() == 2 || grupa->PodajWielkosc() == 1) 
		{
			stolik = sala_->WskazListe3().front();
			for (auto i = 0; i < sala_->WskazListe3().size(); i++)
			{
				if (!stolik->SprawdzCzyGrupaPrzypisana())
				{
					goto przypisz;
				}
				if (stolik->SprawdzCzyNastepny()) stolik = stolik->ZwrocNastepny();
				else break;
			}
		}
		stolik = sala_->WskazListe4().front();
		for (auto i = 0; i < sala_->WskazListe4().size(); i++)
		{
			if (!stolik->SprawdzCzyGrupaPrzypisana())
			{
				goto przypisz;
			}
			if (stolik->SprawdzCzyNastepny()) stolik = stolik->ZwrocNastepny();
			else
			{
				if (grupa->PodajWielkosc() == 2|| grupa->PodajWielkosc() == 1) goto nieprzypisuj;
				break;
			}
		}
		if(grupa->PodajWielkosc() == 3 || grupa->PodajWielkosc() == 4)
		{
			stolik = sala_->WskazListe2().front();
			for (auto i = 0; i < sala_->WskazListe2().size(); i++)
			{
				if (stolik->SprawdzStatus('w'))
				{
					pom = stolik;
					if (stolik->SprawdzCzyNastepny()) {
						stolik = stolik->ZwrocNastepny();
						for (auto j = i + 1; j < sala_->WskazListe2().size(); i++)
						{
							if (stolik->SprawdzStatus('w'))
							{
								pom->PrzypiszPomocniczy(stolik);
								stolik = pom;
								goto przypisz;
							}
							if (stolik->SprawdzCzyNastepny()) stolik = stolik->ZwrocNastepny();
							else
							{
								if (grupa->PodajWielkosc() == 4)
								{
									stolik = sala_->WskazListe3().front();
									for (auto i = 0; i < sala_->WskazListe3().size(); i++)
									{
										if (stolik->SprawdzStatus('w'))
										{
											pom->PrzypiszPomocniczy(stolik);
											stolik = pom;
											goto przypisz;
										}
										if (stolik->SprawdzCzyNastepny()) stolik = stolik->ZwrocNastepny();
										else
										{
											pom = nullptr;
											goto nieprzypisuj;
										}
										
									}
								}
								else
								{
									pom = nullptr;
									goto nieprzypisuj;
								}
							}
						
						}
					}
					else
					{
						if (grupa->PodajWielkosc() == 3)
						{
							pom = nullptr;
							goto czekanie;
						}
						goto dalej;
					}
				}
				else
				{
					if (stolik->SprawdzCzyNastepny()) stolik = stolik->ZwrocNastepny();
					else
					{
						if (grupa->PodajWielkosc() == 4)
						{
							dalej:
							stolik = sala_->WskazListe3().front();
							for(auto i = 0; i < sala_->WskazListe3().size(); i++)
							{
								if (stolik->SprawdzStatus('w'))
								{
									if (pom == nullptr) pom = stolik;
									else
									{
										pom->PrzypiszPomocniczy(stolik);
										stolik = pom;
										goto przypisz;
									}
									if (stolik->SprawdzCzyNastepny())
									{
										stolik = stolik->ZwrocNastepny();
										for(auto j = i + 1; j < sala_->WskazListe3().size(); i++)
										{
											if (stolik->SprawdzStatus('w'))
											{
												pom->PrzypiszPomocniczy(stolik);
												stolik = pom;
												goto przypisz;
											}
											if (stolik->SprawdzCzyNastepny()) stolik = stolik->ZwrocNastepny();
											else
											{
												pom = nullptr;
												goto  czekanie;
											}
									
										}
									}
									else
									{
										pom = nullptr;
										goto czekanie;
									}
								}
								else
								{
									if (stolik->SprawdzCzyNastepny()) stolik = stolik->ZwrocNastepny();
									else
									{
										goto nieprzypisuj;
									}
								}
							}
						}
						else 
						{
							czekanie:
							goto nieprzypisuj;
						}
					}
				}
			}
		}
		przypisz:

		if(stolik->SprawdzCzyPomocniczyPrzypisany())
		{
			stolik->ZwrocPomocniczy()->ZmienStatus('d', true);
			stolik->ZwrocPomocniczy()->ZmienStatus('w', false);
			stolik->ZwrocPomocniczy()->PrzypiszPomocniczy(stolik);
		}

		kierownik_->UstawStatus(false);
		stolik->PrzypiszGrupe(grupa);

		if (stolik->ZwrocAktualnaGrupe()->PodajCzasPojawieniaSieNaSali() != 0)
		{
			stolik->ZwrocAktualnaGrupe()->UstawCzasDostaniaStolika(harmonogram_->PodajCzasSystemowy());
			
			statystyki_->ZsumujCzasStolik(grupa->PodajCzasDostaniaStolika() - grupa->PodajCzasPojawieniaSieNaSali());
			statystyki_->AktualizujCounterStoliki();
		
		}

		grupa->UstawNastepnaKolejka(nullptr);
		if (!restauracja_->ZarzadzajKolejkaDoSali().SprawdzCzyPusta()) restauracja_->UsunZKolejkiSala();

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

		stolik->ZmienStatus('w', false);

		if (stolik->SprawdzCzyPomocniczyPrzypisany()) std::cout << harmonogram_->PodajCzasSystemowy() << " Przypisano grupe " << grupa->PodajId() << " do stolika laczonego (" << stolik->PodajWielkosc() << "+" << stolik->ZwrocPomocniczy()->PodajWielkosc() << ")" << std::endl;
		else std::cout << harmonogram_->PodajCzasSystemowy() << " Przypisano grupe " << grupa->PodajId() << " do stolika " << stolik->PodajWielkosc() << "-osobowego" << std::endl;
		statystyki_->AktualizujLiczbeWszystkichSala();

		if (sala_->WskazListeDoObslugi().empty())
		{
			sala_->DodajDoObslugi(stolik);
			std::cout << harmonogram_->PodajCzasSystemowy() << " Stolik grupy " << stolik->ZwrocAktualnaGrupe()->PodajId() << " jest gotowy do obslugi" << std::endl;
		}
		else
		{
			sala_->WskazListeDoObslugi().back()->UstawNastepnyObsluga(stolik);
			sala_->DodajDoObslugi(stolik);
			std::cout << harmonogram_->PodajCzasSystemowy() << " Stolik grupy " << stolik->ZwrocAktualnaGrupe()->PodajId() << " jest gotowy do obslugi" << std::endl;
		}
		
		powrotKierownika* powrot_kierownika = new powrotKierownika(kierownik_, harmonogram_);
		harmonogram_->dodaj(powrot_kierownika);
		goto koniec;
	}

nieprzypisuj:
	std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa o ID: " << grupa->PodajId() << " czeka na stolik" << std::endl;

koniec:;
}

wejscieDoBufetu::wejscieDoBufetu(Restauracja* restauracja, Bufet* bufet, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	bufet_ = bufet;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
}

void wejscieDoBufetu::execute()
{
	auto grupa = restauracja_->ZarzadzajKolejkaDoBufetu().WskazPierwszy();
	grupaKlientow* pom;
	if (bufet_->PodajWielkoscBufetu() - bufet_->PodajLiczbeOsob() >= grupa->PodajWielkosc())
	{
		if (restauracja_->ZarzadzajListaBufetu().SprawdzCzyPusta())
		{
			pom = grupa;
		}
		else
		{
			pom = restauracja_->ZarzadzajListaBufetu().WskazOstatni();
			pom->UstawNastepna(grupa);
			grupa->UstawPoprzednia(pom);
			pom = grupa;
		}
		powrotZBufetu* powrot_z_bufetu = new powrotZBufetu(restauracja_, bufet_, harmonogram_, statystyki_);
		harmonogram_->dodaj(powrot_z_bufetu);
		grupa->UstawCzasOpuszczeniaBufetu(powrot_z_bufetu->PodajCzasWykonania());
		restauracja_->DodajDoBufetu(grupa);
		statystyki_->AktualizujLiczbeWszystkichBufet();
		bufet_->AktualizujBufet(grupa, '+');
		pom = restauracja_->ZarzadzajKolejkaDoBufetu().WskazPierwszy();
		pom->UstawNastepnaKolejka(nullptr);
		restauracja_->UsunZKolejkiBufet();
		//Statystyki::liczba_kolejka_do_bufetu--;
		std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << grupa->PodajId() << " weszla do bufetu" << std::endl;
		std::cout << harmonogram_->PodajCzasSystemowy() << " Obecny stan bufetu: " << bufet_->PodajLiczbeOsob() << " z " << bufet_->PodajWielkoscBufetu() << std::endl;
	}
	else std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << grupa->PodajId() << " oczekuje na wolne miejsce w bufecie (stan bufetu: " << bufet_->PodajLiczbeOsob() << "/" << bufet_->PodajWielkoscBufetu() << ", wielkosc grupy: " << grupa->PodajWielkosc() << ")" << std::endl;
}

obslugaNapoje::obslugaNapoje(Sala* sala, Harmonogram* harmonogram, Statystyki* statystyki)
{
	sala_ = sala;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
}

void obslugaNapoje::execute()
{
	auto kelner = sala_->WskazListeKelnera().front();
	auto stolik = sala_->WskazListeDoObslugi().front();

	for (auto i = 0; i < sala_->WskazListeKelnera().size(); i++)
	{
		if (stolik->SprawdzCzyGrupaPrzypisana() && !stolik->SprawdzStatus('n'))
		{
			if (kelner->SprawdzCzyWolny())
			{
				if (stolik->ZwrocAktualnaGrupe()->SprawdzCzyKelnerPrzypisany()) break;
				stolik->ZwrocAktualnaGrupe()->PrzypiszKelnera(kelner);
				kelner->UstawStatus(false);
				if (!sala_->WskazListeNapoje().empty())
				{
					sala_->WskazListeNapoje().back()->UstawNastepnyNapoje(stolik);
				}
				sala_->DodajDoNapojow(stolik);
				if (stolik->ZwrocAktualnaGrupe()->PodajCzasDostaniaStolika() != 0)
				{
					stolik->ZwrocAktualnaGrupe()->UstawCzasObslugi(harmonogram_->PodajCzasSystemowy());

					statystyki_->ZsumujCzasObsluga(stolik->ZwrocAktualnaGrupe()->PodajCzasObslugi() - stolik->ZwrocAktualnaGrupe()->PodajCzasDostaniaStolika());
					statystyki_->AktualizujCounterObsluga();
				}
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " oczekuje na napoje (kelner " << kelner->PodajId() << ")" << std::endl;
				if (!sala_->WskazListeDoObslugi().empty())
				{
					sala_->WskazListeDoObslugi().front()->UstawNastepnyObsluga(nullptr);
					sala_->UsunZObslugi();
				}
				auto podanie_napojow = new podanieNapojow(sala_, harmonogram_);
				harmonogram_->dodaj(podanie_napojow);
				if (kelner->SprawdzCzyNastepny() && stolik->SprawdzCzyNastepnyObsluga())
				{
					kelner = kelner->ZwrocNastepny();
					stolik = stolik->ZwrocNastepnyObsluga();
				}
				else goto koniec;
			}
			else
			{
				if (kelner->SprawdzCzyNastepny()) kelner = kelner->ZwrocNastepny();
			}
		}
		else
		{
			if (stolik->SprawdzCzyNastepnyObsluga()) 
			{
				stolik = stolik->ZwrocNastepnyObsluga();
				sala_->WskazListeDoObslugi().front()->UstawNastepnyObsluga(nullptr);
			}
			if (!sala_->WskazListeDoObslugi().empty()) sala_->UsunZObslugi();
		}
	}
koniec:;
}

placenie::placenie(Restauracja* restauracja, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
}

obslugaJedzenie::obslugaJedzenie(Restauracja* restauracja, Sala* sala, Harmonogram* harmonogram, Statystyki* statystyki)
{
	restauracja_ = restauracja;
	sala_ = sala;
	harmonogram_ = harmonogram;
	statystyki_ = statystyki;
}

void obslugaJedzenie::execute()
{
	auto kelner = sala_->WskazListeKelnera().front();
	auto stolik = sala_->WskazListeJedzenie().front();

	for (auto i = 0; i < sala_->WskazListeKelnera().size(); i++)
	{
		if (stolik->SprawdzCzyGrupaPrzypisana() && stolik->SprawdzStatus('n') && !stolik->SprawdzStatus('j'))
		{
			if (kelner->SprawdzCzyWolny())
			{
				if (stolik->ZwrocAktualnaGrupe()->SprawdzCzyKelnerPrzypisany()) break;
				stolik->ZwrocAktualnaGrupe()->PrzypiszKelnera(kelner);
				kelner->UstawStatus(false);
				std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << stolik->ZwrocAktualnaGrupe()->PodajId() << " oczekuje na jedzenie (kelner " << kelner->PodajId() << ")" << std::endl;
				auto podanie_dan = new podanieDan(restauracja_, sala_, harmonogram_, statystyki_);
				harmonogram_->dodaj(podanie_dan);
				if (kelner->SprawdzCzyNastepny() && stolik->SprawdzCzyNastepnyJedzenie())
				{
					kelner = kelner->ZwrocNastepny();
					stolik = stolik->ZwrocNastepnyJedzenie();
				}
				else goto koniec;
			}
			else
			{
				if (kelner->SprawdzCzyNastepny()) kelner = kelner->ZwrocNastepny();
			}
		}
		else
		{
			if (stolik->SprawdzCzyNastepnyJedzenie()) stolik = stolik->ZwrocNastepnyJedzenie();
			if (!sala_->WskazListeJedzenie().empty()) sala_->UsunZJedzenia();
		}
	}
koniec:;
}

void placenie::execute()
{
	auto kasjer = restauracja_->ZwrocListeKasjerow().front();
	grupaKlientow* grupa;
	for (auto i = 0; i < restauracja_->ZwrocListeKasjerow().size(); i++) {
		if (!restauracja_->ZarzadzajKolejkaDoKasy().SprawdzCzyPusta()) grupa = restauracja_->ZarzadzajKolejkaDoKasy().WskazPierwszy();
		else goto koniec;
		if (!kasjer->SprawdzCzyGrupaPrzypisana())
		{
			kasjer->PrzypiszGrupe(grupa);
			restauracja_->UsunZKolejkiKasy();
			std::cout << harmonogram_->PodajCzasSystemowy() << " Grupa " << grupa->PodajId() << " dokonuje platnosci u kasjera " << kasjer->PodajId() << std::endl;
			auto dokonanie_platnosci = new dokonaniePlatnosci(restauracja_, harmonogram_, statystyki_);
			harmonogram_->dodaj(dokonanie_platnosci);
			grupa->UstawCzasPlacenia(dokonanie_platnosci->PodajCzasWykonania());
			if (kasjer->SprawdzCzyNastepna()) kasjer = kasjer->ZwrocNastepna();
			else
			{
				goto koniec;
			}
		}
		else
		{
			if (kasjer->SprawdzCzyNastepna()) kasjer = kasjer->ZwrocNastepna();
			else
			{
				goto koniec;
			}
		}
	}
koniec:
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
}
