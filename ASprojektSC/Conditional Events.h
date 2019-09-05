#pragma once
#include "Hall.h"
#include "Schedule.h"

class ZdarzenieWarunkowe
{
public:
	ZdarzenieWarunkowe();
	virtual ~ZdarzenieWarunkowe();
	virtual void execute();
};

class przypisanieStolika :public ZdarzenieWarunkowe
{
	Restauracja * restauracja_;
	Sala * sala_;
	Kierownik * kierownik_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	przypisanieStolika(Restauracja* restauracja, Sala* sala, Kierownik* kierownik, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class wejscieDoBufetu :public ZdarzenieWarunkowe
{
	Restauracja * restauracja_;
	Bufet* bufet_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	wejscieDoBufetu(Restauracja* restauracja, Bufet* bufet, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class obslugaNapoje :public ZdarzenieWarunkowe
{
	Sala * sala_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	obslugaNapoje(Sala* sala, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class obslugaJedzenie :public ZdarzenieWarunkowe
{
	Restauracja * restauracja_;
	Sala * sala_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	obslugaJedzenie(Restauracja* restauracja, Sala* sala, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class placenie :public ZdarzenieWarunkowe
{
	Restauracja * restauracja_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	placenie(Restauracja* restauracja, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};