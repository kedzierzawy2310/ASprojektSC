#pragma once
#include <vector>

class Statystyki
{
	int liczba_wszystkich_utworzonych_grup_;
	int liczba_wszystkich_obsluzonych_grup_;
	int liczba_wszystkich_grup_sala_;
	int liczba_wszystkich_grup_bufet_;
	int liczba_wszystkich_grup_alarm_;
	int liczba_alarm_kolejki_;
	int liczba_obecnych_grup_;
	int liczba_kolejka_sala_;
	int liczba_kolejka_kasy_;
	int liczba_alarmow_;
	double suma_liczba_kolejka_do_kasy_;
	double suma_liczba_kolejka_do_sali_;
	double czas_ostatniego_pomiaru_sala_;
	double czas_ostatniego_pomiaru_kasy_;
	double czas_wagowy_sala_;
	double czas_wagowy_kasa_;
	double suma_czasow_sala_;
	double suma_czasow_kasy_;
	double suma_czasow_stolik_;
	double suma_czasow_obsluga_;
	double suma_wagowych_sala_;
	double suma_wagowych_kasa_;
	bool pierwszy_pomiar_sala_;
	bool pierwszy_pomiar_kasa_;

	int w_s_;
	int w_b_;

	int count_stolik_;
	int count_obsluga_;
	std::vector<double> losowanie_klienci_;
	std::vector<double> losowanie_bufet_;
	std::vector<double> losowanie_konsumpcja_;
	std::vector<double> losowanie_jedzenie_;
	std::vector<double> losowanie_napoje_;
	std::vector<double> losowanie_kasy_;
	std::vector<double> losowanie_alarm_;
public:
	Statystyki();
	void AktualizujLiczbeWszystkichUtworzonych();
	void AktualizujLiczbeWszystkichObsluzonnych();
	void AktualizujLiczbeWszystkichSala();
	void AktualizujLiczbeWszystkichBufet();
	void AktualizujLiczbeWszystkichAlarm();

	void AktualizujAlarmKolejki();
	void AktualizujWS();
	void AktualizujWB();

	void AktualizujLiczbeAlarmow();
	void AktualizujLiczbeObecnych(char c);
	void AktualizujLiczbeKolejkaSala(int i);
	void AktualizujLiczbeKolejkaKasy(int i);
	void AktualizujCounterStoliki();
	void AktualizujCounterObsluga();
	void PrzypiszCzasWagowySala(double d);
	void PrzypiszCzasWagowyKasy(double d);
	void ZmienStatusPierwszegoSala(bool b);
	void ZmienStatusPierwszegoKasy(bool b);
	void AktualizujSumeCzasowSala(double d);
	void AktualizujSumeCzasowKasy(double d);
	void PrzypiszCzasOstatniegoPomiaruSala(double d);
	void PrzypiszCzasOstatniegoPomiaruKasy(double d);
	void ZsumujKolejkaSala(double d);
	void ZsumujKolejkaKasy(double d);
	void ZsumujCzasStolik(double d);
	void ZsumujCzasObsluga(double d);

	int PodajLiczbeWszystkichUtworzonych();
	int PodajLiczbeWszystkichObsluzonych();
	int PodajLiczbeWszystkichSala();
	int PodajLiczbeWszystkichBufet();
	int PodajLiczbeWszystkichAlarm();
	int PodajLiczbeAlarmow();
	int PodajLiczbeObecnych();
	int PodajLiczbeKolejkaSala();
	int PodajLiczbeKolejkaKasy();
	int PodajCounterStoliki();
	int PodajCounterObsluga();

	int PodajAlarmKolejki();
	int PodajWB();
	int PodajWS();

	double PodajSumeKolejkiSala();
	double PodajSumeKolejkiKasy();
	double PodajCzasWagowySala();
	double PodajCzasWagowyKasy();
	double PodajSumaCzasowSala();
	double PodajSumaCzasowKasy();
	double PodajSumaCzasowStolik();
	double PodajSumaCzasowObsluga();
	double PodajCzasOstatniegoPomiaruSala();
	double PodajCzasOstatniegoPomiaruKasy();
	bool SprawdzCzyPierwszySala();
	bool SprawdzCzyPierwszyKasy();
};
