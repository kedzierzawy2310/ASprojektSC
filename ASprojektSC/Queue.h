#pragma once
#include "Customer Group.h"
#include <queue>

class Kolejka
{
	std::queue<grupaKlientow*> kolejka_;
public:
	Kolejka();
	virtual ~Kolejka();
	void dodaj(grupaKlientow* grupa);
	void usun();
	grupaKlientow* WskazPierwszy();
	grupaKlientow* WskazOstatni();
	bool SprawdzCzyPusta();
	int SprawdzRozmiar();
};
