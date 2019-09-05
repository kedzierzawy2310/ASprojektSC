#pragma once
#include "Restaurant.h"
#include "Manager.h"
#include "Hall.h"
#include "Stats.h"

class Harmonogram;

class ZdarzeniaCzasowe
{
	double czas_wykonania_;
	int rozklad_;
	//------------------------------------------------------------------------------------------- PARAMETRY GENERATORÓW -----------------------------------------------------------------------------------------------------------------

	double mean_a_ = 650; //modyfikacja mo¿liwa - 1500
	double sigma_a_ = 10;	//modyyfikacja mo¿liwa - 100
	double mean_b_ = 2900;
	double sigma_b_ = 80; //modyfikacja mo¿liwa - 80
	double mean_c_ = 4200;
	double sigma_c_ = 50;
	double lambda_kasy_ = 1 / 3000.0; //modyfikacja mo¿liwa - 1/220
	double lambda_konsumpcja_ = 1 / 2020.0;
	double lambda_jedzenie_ = 1 / 3000.0; //modyfikacja mo¿liwa - 1/2000
	double lambda_napoje_ = 1 / 6000.0; //modyfikacja mo¿liwa - 1/370

public:
	ZdarzeniaCzasowe();
	virtual ~ZdarzeniaCzasowe();
	virtual void execute();
	void UstawRozklad(int i);
	double PodajCzasWykonania();
	void UstawCzasWykonania(Harmonogram* harmonogram);
	double losuj(int rozklad, Harmonogram* harmonogram);
	int PodajRozklad();
};

class nowaGrupa:public ZdarzeniaCzasowe
{
	Restauracja* restauracja_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	nowaGrupa(Restauracja* restauracja, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class powrotKierownika :public ZdarzeniaCzasowe
{
	Kierownik * kierownik_;
	Harmonogram* harmonogram_;
public:
	powrotKierownika(Kierownik* kierownik, Harmonogram* harmonogram);
	void execute() override;
};

class podanieNapojow :public ZdarzeniaCzasowe
{
	Sala* sala_;
	Harmonogram* harmonogram_;
public:
	podanieNapojow(Sala* sala, Harmonogram* harmonogram);
	void execute() override;
};

class podanieDan :public ZdarzeniaCzasowe
{
	Restauracja * restauracja_;
	Sala * sala_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	podanieDan(Restauracja* restauracja, Sala* sala, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class powrotZBufetu :public ZdarzeniaCzasowe
{
	Restauracja* restauracja_;
	Bufet* bufet_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	powrotZBufetu(Restauracja* restauracja, Bufet* bufet, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class koniecKonsumpcji :public ZdarzeniaCzasowe
{
	Restauracja * restauracja_;
	Sala* sala_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	koniecKonsumpcji(Restauracja* restauracja, Sala* sala, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class dokonaniePlatnosci :public ZdarzeniaCzasowe
{
	Restauracja * restauracja_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	dokonaniePlatnosci(Restauracja* restauracja, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};

class alarm :public ZdarzeniaCzasowe
{
	Restauracja * restauracja_;
	Sala* sala_;
	Bufet* bufet_;
	Harmonogram* harmonogram_;
	Statystyki* statystyki_;
public:
	alarm(Restauracja* restauracja, Sala* sala, Bufet* bufet, Harmonogram* harmonogram, Statystyki* statystyki);
	void execute() override;
};