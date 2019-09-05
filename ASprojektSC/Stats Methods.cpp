#include "stdafx.h"
#include "Stats.h"

Statystyki::Statystyki()
{
	czas_wagowy_sala_ = 0;
	czas_wagowy_kasa_ = 0;
	liczba_obecnych_grup_ = 0;
	liczba_alarm_kolejki_ = 0;
	liczba_alarmow_ = 0;
	liczba_kolejka_kasy_ = 0;
	liczba_kolejka_sala_ = 0;
	liczba_wszystkich_grup_alarm_ = 0;
	liczba_wszystkich_grup_bufet_ = 0;
	liczba_wszystkich_grup_sala_ = 0;
	liczba_wszystkich_obsluzonych_grup_ = 0;
	liczba_wszystkich_utworzonych_grup_ = 0;
	w_s_ = 0;
	w_b_ = 0;
}


void Statystyki::AktualizujLiczbeWszystkichUtworzonych()
{
	liczba_wszystkich_utworzonych_grup_++;
}

void Statystyki::AktualizujLiczbeWszystkichObsluzonnych()
{
	liczba_wszystkich_obsluzonych_grup_++;
}

void Statystyki::AktualizujLiczbeWszystkichSala()
{
	liczba_wszystkich_grup_sala_++;
}

void Statystyki::AktualizujLiczbeWszystkichBufet()
{
	liczba_wszystkich_grup_bufet_++;
}

void Statystyki::AktualizujLiczbeWszystkichAlarm()
{
	liczba_wszystkich_grup_alarm_++;
}

void Statystyki::AktualizujAlarmKolejki()
{
	liczba_alarm_kolejki_++;
}

void Statystyki::AktualizujWS()
{
	w_s_++;
}

void Statystyki::AktualizujWB()
{
	w_b_++;
}

void Statystyki::AktualizujLiczbeAlarmow()
{
	liczba_alarmow_++;
}

void Statystyki::AktualizujLiczbeObecnych(char c)
{
	switch (c)
	{
	case '+':
		liczba_obecnych_grup_++;
		break;
	case '-':
		liczba_obecnych_grup_--;
		break;
	default:
		break;
	}	
}

void Statystyki::AktualizujLiczbeKolejkaSala(int i)
{
	liczba_kolejka_sala_ = i;
}

void Statystyki::AktualizujLiczbeKolejkaKasy(int i)
{
	liczba_kolejka_kasy_ = i;
}

void Statystyki::AktualizujCounterStoliki()
{
	count_stolik_++;
}

void Statystyki::AktualizujCounterObsluga()
{
	count_obsluga_++;
}

void Statystyki::PrzypiszCzasWagowySala(double d)
{
	czas_wagowy_sala_ = d;
}

void Statystyki::PrzypiszCzasWagowyKasy(double d)
{
	czas_wagowy_kasa_ = d;
}

void Statystyki::ZmienStatusPierwszegoSala(bool b)
{
	pierwszy_pomiar_sala_ = b;
}

void Statystyki::ZmienStatusPierwszegoKasy(bool b)
{
	pierwszy_pomiar_kasa_ = b;
}

void Statystyki::AktualizujSumeCzasowSala(double d)
{
	suma_czasow_sala_ = suma_czasow_sala_ + d;
}

void Statystyki::AktualizujSumeCzasowKasy(double d)
{
	suma_czasow_kasy_ = suma_czasow_kasy_ + d;
}

void Statystyki::PrzypiszCzasOstatniegoPomiaruSala(double d)
{
	czas_ostatniego_pomiaru_sala_ = d;
}

void Statystyki::PrzypiszCzasOstatniegoPomiaruKasy(double d)
{
	czas_ostatniego_pomiaru_kasy_ = d;
}

void Statystyki::ZsumujKolejkaSala(double d)
{
	suma_liczba_kolejka_do_sali_ = suma_liczba_kolejka_do_sali_ + d;
}

void Statystyki::ZsumujKolejkaKasy(double d)
{
	suma_liczba_kolejka_do_kasy_ = suma_liczba_kolejka_do_kasy_ + d;
}

void Statystyki::ZsumujCzasStolik(double d)
{
	suma_czasow_stolik_ = suma_czasow_stolik_ + d;
}

void Statystyki::ZsumujCzasObsluga(double d)
{
	suma_czasow_obsluga_ = suma_czasow_obsluga_ + d;
}

int Statystyki::PodajLiczbeWszystkichUtworzonych()
{
	return liczba_wszystkich_utworzonych_grup_;
}

int Statystyki::PodajLiczbeWszystkichObsluzonych()
{
	return liczba_wszystkich_obsluzonych_grup_;
}

int Statystyki::PodajLiczbeWszystkichBufet()
{
	return liczba_wszystkich_grup_bufet_;
}

int Statystyki::PodajLiczbeWszystkichSala()
{
	return liczba_wszystkich_grup_sala_;
}

int Statystyki::PodajLiczbeWszystkichAlarm()
{
	return liczba_wszystkich_grup_alarm_;
}

int Statystyki::PodajLiczbeAlarmow()
{
	return liczba_alarmow_;
}

int Statystyki::PodajLiczbeObecnych()
{
	return liczba_obecnych_grup_;
}

int Statystyki::PodajLiczbeKolejkaSala()
{
	return liczba_kolejka_sala_;
}

int Statystyki::PodajLiczbeKolejkaKasy()
{
	return liczba_kolejka_kasy_;
}

int Statystyki::PodajCounterStoliki()
{
	return count_stolik_;
}

int Statystyki::PodajCounterObsluga()
{
	return count_obsluga_;
}

int Statystyki::PodajAlarmKolejki()
{
	return liczba_alarm_kolejki_;
}

int Statystyki::PodajWB()
{
	return w_b_;
}

int Statystyki::PodajWS()
{
	return w_s_;
}

double Statystyki::PodajSumeKolejkiSala()
{
	return suma_liczba_kolejka_do_sali_;
}

double Statystyki::PodajSumeKolejkiKasy()
{
	return suma_liczba_kolejka_do_kasy_;
}

double Statystyki::PodajCzasWagowySala()
{
	return czas_wagowy_sala_;
}

double Statystyki::PodajCzasWagowyKasy()
{
	return czas_wagowy_kasa_;
}

double Statystyki::PodajSumaCzasowSala()
{
	return suma_czasow_sala_;
}

double Statystyki::PodajSumaCzasowKasy()
{
	return suma_czasow_kasy_;
}

double Statystyki::PodajSumaCzasowStolik()
{
	return suma_czasow_stolik_;
}

double Statystyki::PodajSumaCzasowObsluga()
{
	return suma_czasow_obsluga_;
}

double Statystyki::PodajCzasOstatniegoPomiaruSala()
{
	return czas_ostatniego_pomiaru_sala_;
}

double Statystyki::PodajCzasOstatniegoPomiaruKasy()
{
	return czas_ostatniego_pomiaru_kasy_;
}

bool Statystyki::SprawdzCzyPierwszySala()
{
	if (pierwszy_pomiar_sala_) return true;
	return false;
}

bool Statystyki::SprawdzCzyPierwszyKasy()
{
	if(pierwszy_pomiar_kasa_) return true;
	return false;
}
