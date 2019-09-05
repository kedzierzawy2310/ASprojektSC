#include "stdafx.h"
#include "Queue.h"

Kolejka::Kolejka() = default;

Kolejka::~Kolejka() = default;

void Kolejka::dodaj(grupaKlientow* grupa)
{
	kolejka_.push(grupa);
}

void Kolejka::usun()
{
	kolejka_.pop();
}

grupaKlientow* Kolejka::WskazPierwszy()
{
	return kolejka_.front();
}
grupaKlientow* Kolejka::WskazOstatni()
{
	return kolejka_.back();
}

bool Kolejka::SprawdzCzyPusta()
{
	if (kolejka_.empty()) return true;
	return false;
}

 int Kolejka::SprawdzRozmiar()
{
	return kolejka_.size();
}