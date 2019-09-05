#pragma once
#include "Waiter.h"
#include "Stats.h"

class grupaKlientow {
	int wielkosc_grupy_;
	int id_grupy_;
	int alarmowe_;
	bool bufet_;
	bool alarm_;
	double czas_opuszczenia_bufetu_;
	double czas_placenia_;
	double czas_pojawienia_sie_na_sali_;
	double czas_dostania_stolika_;
	double czas_obslugi_;
	Kelner* aktualny_kelner_;
	grupaKlientow* next_;
	grupaKlientow* previous_;
	grupaKlientow* next_kolejka_;

	double prawd_grupy1_ = 0.11 * 100;
	double prawd_grupy2_ = 0.33 * 100;
	double prawd_grupy3_ = 0.33 * 100;
	double prawd_grupy4_ = 0.23 * 100;
	double prawd_alarmu_ = 0.70 * 100;

public:
	grupaKlientow();
	virtual ~grupaKlientow();
	void UstawNastepnaKolejka(grupaKlientow* grupa);
	void UstawNastepna(grupaKlientow* grupa);
	void UstawPoprzednia(grupaKlientow* grupa);
	void zeruj();
	void UstawId(Statystyki* statystyki);
	void UstawCzasOpuszczeniaBufetu(double czas);
	void UstawCzasPlacenia(double czas);
	void UstawCzasPojawieniaSieNaSali(double czas);
	void UstawCzasDostaniaStolika(double czas);
	void UstawCzasObslugi(double czas);
	void PrzypiszKelnera(Kelner* kelner);
	bool SprawdzCzyNastepna();
	bool SprawdzCzyPoprzednia();
	bool SprawdzCzyNastepnaKolejka();
	bool SprawdzCzyBufet();
	bool SprawdzCzyAlarm();
	bool SprawdzCzyKelnerPrzypisany();
	int PodajId();
	int PodajWielkosc();
	double PodajCzasPlacenia();
	double PodajCzasOpuszczeniaBufetu();
	double PodajCzasPojawieniaSieNaSali();
	double PodajCzasDostaniaStolika();
	double PodajCzasObslugi();
	Kelner* ZwrocAktualnegoKelnera();
	grupaKlientow* ZwrocNastepny();
	grupaKlientow* ZwrocPoprzedni();
	grupaKlientow* ZwrocNastepnyKolejka();
};
