#include "stdafx.h"
#include "Buffet.h"

Bufet::Bufet()
{
	liczba_osob_ = 0;
}

Bufet::~Bufet() = default;

int Bufet::PodajLiczbeOsob()
{
	return liczba_osob_;
}

const int Bufet::PodajWielkoscBufetu()
{
	return wielkosc_bufetu_;
}

void Bufet::AktualizujBufet(grupaKlientow* grupa, char c)
{
	switch (c)
	{
	case '+':
		liczba_osob_ = liczba_osob_ + grupa->PodajWielkosc();
		break;
	case '-':
		liczba_osob_ = liczba_osob_ - grupa->PodajWielkosc();
		break;
	default:
		break;
	}
}

