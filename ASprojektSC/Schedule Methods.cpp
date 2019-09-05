#include "stdafx.h"
#include "Schedule.h"

Harmonogram::Harmonogram()
{
	czas_systemowy_ = 0.0;
	koniec_symulacji_ = 0.0;
	zdarzenia_czasowe_.empty();
}

void Harmonogram::dodaj(ZdarzeniaCzasowe* zdarzenia)
{
	for (auto i = 0; i<zdarzenia_czasowe_.size(); i++)
	{
		if (zdarzenia_czasowe_[0] != nullptr && zdarzenia->PodajCzasWykonania() >= zdarzenia_czasowe_[i]->PodajCzasWykonania())
		{
			zdarzenia_czasowe_.insert(zdarzenia_czasowe_.begin() + i, zdarzenia); return;
		}
	}
	zdarzenia_czasowe_.push_back(zdarzenia);
}

void Harmonogram::usuñ()
{
	zdarzenia_czasowe_.pop_back();
}

void Harmonogram::AktualizujCzasSystemowy(ZdarzeniaCzasowe* zdarzenia)
{
	czas_systemowy_ = zdarzenia->PodajCzasWykonania();
}

double Harmonogram::PodajCzasSystemowy()
{
	return czas_systemowy_;
}

double Harmonogram::PodajKoniecSymulacji()
{
	koniec_symulacji_ = czas_systemowy_;
	return koniec_symulacji_;
}

std::vector<ZdarzeniaCzasowe*> Harmonogram::ZarzadzajZdarzeniami()
{
	return zdarzenia_czasowe_;
}
