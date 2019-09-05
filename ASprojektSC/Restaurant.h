#pragma once
#include "Queue.h"
#include "Buffet.h"
#include "Cash.h"
#include <queue>

class Restauracja {
	Kolejka klienci_;
	Kolejka kolejka_sala_;
	Kolejka kolejka_bufet_;
	Kolejka kolejka_kasy_;
	Kolejka bufet_lista_;
	std::queue<Kasa*> lista_kasjerow_;
	const int liczba_kasjerow_ = 6;
	Bufet* bufet_;
	Kasa* kasjer_;
	grupaKlientow* pom_kol_;
	grupaKlientow* pom_kol_kasa_;
	grupaKlientow* pom_kol_buf_;

public:
	Restauracja();
	virtual ~Restauracja();
	void DodajDoKolejkiSala(grupaKlientow* grupa);
	void DodajDoKolejkiBufet(grupaKlientow* grupa);
	void DodajDoKolejkiKasy(grupaKlientow* grupa);
	void DodajDoBufetu(grupaKlientow* grupa);
	void UsunZKolejkiSala();
	void UsunZKolejkiBufet();
	void UsunZKolejkiKasy();
	void UsunZBufetu();
	void UsunZListyKasjerow();
	void PrzypiszPomKol(grupaKlientow* grupa);
	void PrzypiszPomKolBuf(grupaKlientow* grupa);
	void PrzypiszPomKolKas(grupaKlientow* grupa);
	int SprawdzRozmiarSala();
	int SprawdzRozmiarBufet();
	int SprawdzRozmiarKasy();
	Kolejka ZarzadzajKolejkaDoSali();
	Kolejka ZarzadzajKolejkaDoBufetu();
	Kolejka ZarzadzajKolejkaDoKasy();
	Kolejka ZarzadzajListaBufetu();
	Kolejka DaneKlientow();
	grupaKlientow* PodajPomKol();
	grupaKlientow* PodajPomKolBuf();
	grupaKlientow* PodajPomKolKas();
	std::queue<Kasa*> ZwrocListeKasjerow();
};
