#pragma once
#include "Customer Group.h"

class Bufet {
	int liczba_osob_;
	const int wielkosc_bufetu_ = 20;
public:
	Bufet();
	virtual ~Bufet();
	int PodajLiczbeOsob();
	const int PodajWielkoscBufetu();
	void AktualizujBufet(grupaKlientow* grupa, char c);
};