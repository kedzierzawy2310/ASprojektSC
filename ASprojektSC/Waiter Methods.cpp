#include "stdafx.h"
#include "Waiter.h"

Kelner::Kelner()
{
	liczba_obsluzen_ = 0;
	id_kelnera_ = 0;
	wolny_kelner_ = true;
	next_ = nullptr;
}

Kelner::~Kelner() = default;

void Kelner::UstawId(int id)
{
	id_kelnera_ = id;
}

void Kelner::UstawStatus(bool b)
{
	wolny_kelner_ = b;
}

void Kelner::UstawNastepny(Kelner* kelner)
{
	next_ = kelner;
}

void Kelner::AktualizujLiczbeObsluzen()
{
	liczba_obsluzen_++;
}

int Kelner::PodajLiczbeObsluzen()
{
	return liczba_obsluzen_;
}

int Kelner::PodajId()
{
	return id_kelnera_;
}

bool Kelner::SprawdzCzyWolny()
{
	if (wolny_kelner_) return true;
	return false;
}

bool Kelner::SprawdzCzyNastepny()
{
	if (next_ != nullptr) return true;
	return false;
}

Kelner* Kelner::ZwrocNastepny()
{
	return next_;
}
