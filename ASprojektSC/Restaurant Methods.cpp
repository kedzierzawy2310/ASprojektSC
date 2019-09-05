#include "stdafx.h"
#include "Restaurant.h"

Restauracja::Restauracja()
{
	auto pom = new Kasa;
	pom->UstawId(1);
	lista_kasjerow_.push(pom);

	for (auto i = 2; i <= liczba_kasjerow_; i++) {
		auto kasa = new Kasa;
		kasa->UstawId(i);
		pom->UstawNastepna(kasa);
		pom = kasa;
		lista_kasjerow_.push(kasa);
	}
}

Restauracja::~Restauracja()
{
	grupaKlientow* grupa = nullptr;

	while (!kolejka_sala_.SprawdzCzyPusta())
	{
		grupa = kolejka_sala_.WskazPierwszy();
		kolejka_sala_.usun();
		delete grupa;
	}
	while (!kolejka_kasy_.SprawdzCzyPusta())
	{
		grupa = kolejka_kasy_.WskazPierwszy();
		kolejka_kasy_.usun();
		delete grupa;
	}
	while (!kolejka_bufet_.SprawdzCzyPusta())
	{
		grupa = kolejka_bufet_.WskazPierwszy();
		kolejka_bufet_.usun();
		delete grupa;
	}
	while (!bufet_lista_.SprawdzCzyPusta())
	{
		grupa = bufet_lista_.WskazPierwszy();
		bufet_lista_.usun();
		delete grupa;
	}

};

void Restauracja::DodajDoBufetu(grupaKlientow* grupa)
{
	grupaKlientow* pom;
	if (bufet_lista_.SprawdzCzyPusta())
	{
		 pom = grupa;
	}
	else
	{
		pom = bufet_lista_.WskazOstatni();
		pom->UstawNastepna(grupa);
		grupa->UstawPoprzednia(pom);
	}
	bufet_lista_.dodaj(grupa);
}

void Restauracja::UsunZKolejkiSala()
{
	kolejka_sala_.usun();
}

void Restauracja::UsunZKolejkiBufet()
{
	kolejka_bufet_.usun();
}

void Restauracja::UsunZKolejkiKasy()
{
	kolejka_kasy_.usun();
}

void Restauracja::UsunZBufetu()
{
	bufet_lista_.usun();
}

void Restauracja::UsunZListyKasjerow()
{
	lista_kasjerow_.pop();
}

int Restauracja::SprawdzRozmiarSala()
{
	return kolejka_sala_.SprawdzRozmiar();
}

int Restauracja::SprawdzRozmiarBufet()
{
	return kolejka_sala_.SprawdzRozmiar();
}

int Restauracja::SprawdzRozmiarKasy()
{
	return kolejka_sala_.SprawdzRozmiar();
}

Kolejka Restauracja::ZarzadzajKolejkaDoSali()
{
	return kolejka_sala_;
}

Kolejka Restauracja::ZarzadzajKolejkaDoBufetu()
{
	return kolejka_bufet_;
}

Kolejka Restauracja::ZarzadzajKolejkaDoKasy()
{
	return kolejka_kasy_;
}

Kolejka Restauracja::ZarzadzajListaBufetu()
{
	return bufet_lista_;
}

Kolejka Restauracja::DaneKlientow()
{
	return klienci_;
}

grupaKlientow* Restauracja::PodajPomKol()
{
	return pom_kol_;
}

grupaKlientow* Restauracja::PodajPomKolBuf()
{
	return pom_kol_buf_;
}

grupaKlientow* Restauracja::PodajPomKolKas()
{
	return pom_kol_kasa_;
}

std::queue<Kasa*> Restauracja::ZwrocListeKasjerow()
{
	return lista_kasjerow_;
}

void Restauracja::DodajDoKolejkiSala(grupaKlientow* grupa)
{
	grupaKlientow* pom = nullptr;
	grupa->zeruj();
	if (kolejka_sala_.SprawdzCzyPusta()) pom = grupa;
	else
	{
		pom = kolejka_sala_.WskazOstatni();
		pom->UstawNastepnaKolejka(grupa);
		pom = grupa;
	}
	kolejka_sala_.dodaj(grupa);
}

void Restauracja::DodajDoKolejkiBufet(grupaKlientow* grupa)
{
	grupaKlientow* pom = nullptr;
	grupa->zeruj();
	if (kolejka_bufet_.SprawdzCzyPusta()) pom = grupa;
	else
	{
		pom = kolejka_bufet_.WskazOstatni();
		pom->UstawNastepnaKolejka(grupa);
		pom = grupa;
	}
	kolejka_bufet_.dodaj(grupa);
}

void Restauracja::DodajDoKolejkiKasy(grupaKlientow* grupa)
{
	grupa->zeruj();
	grupaKlientow* pom = nullptr;
	if (kolejka_kasy_.SprawdzCzyPusta()) pom = grupa;
	else
	{
		pom = kolejka_kasy_.WskazOstatni();
		pom->UstawNastepnaKolejka(grupa);
		pom = grupa;
	}
	kolejka_kasy_.dodaj(grupa);
}

void Restauracja::PrzypiszPomKol(grupaKlientow* grupa)
{
	pom_kol_ = grupa;
}

void Restauracja::PrzypiszPomKolBuf(grupaKlientow* grupa)
{
	pom_kol_buf_ = grupa;
}

void Restauracja::PrzypiszPomKolKas(grupaKlientow* grupa)
{
	pom_kol_kasa_ = grupa;
}