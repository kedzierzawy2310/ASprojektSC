#pragma once
#include "Waiter.h"
#include "Tables.h"
#include "Manager.h"
#include <queue>

class Sala {
	int liczba_kelnerow_;
	int liczba_stolikow2_os_;
	int liczba_stolikow3_os_;
	int liczba_stolikow4_os_;

	Kierownik* kierownik_sali_;
	std::queue<Kelner*> lista_kelnerow_;
	std::queue <Stoliki*> pom_stolik_napoje_;
	std::queue <Stoliki*> pom_stolik_zjedzone_;
	std::queue <Stoliki*> pom_stolik_jedzenie_;
	std::queue <Stoliki*> lista_stolikow2_;
	std::queue <Stoliki*> lista_stolikow3_;
	std::queue <Stoliki*> lista_stolikow4_;
	std::queue <Stoliki*> stoliki_do_obslugi_;
	std::queue <Stoliki*> wszystkie_stoliki_;

	Kelner* kelner_;
	Stoliki* stolik_;
	Stoliki* stolik_obs³uga_;
	Stoliki* stolik_zjedzone_;
	Stoliki* stolik_jedzenie_;
	Stoliki* stolik_do_usuwania_;
	Stoliki* stolik_napoje_;

	Kelner* pom1_;
	Stoliki* pom2_;
	Stoliki* pom3_;
	Stoliki* pom4_;

public:
	Sala();
	virtual ~Sala();
	void PrzypiszKierownika(Kierownik* kierownik);
	void DodajDoObslugi(Stoliki* stoliki);
	void UsunZObslugi();
	void DodajDoNapojow(Stoliki* stoliki);
	void UsunZNapojow();
	void DodajDoJedzenia(Stoliki* stoliki);
	void UsunZJedzenia();
	void DodajDoZjedzonych(Stoliki* stoliki);
	void UsunZeZjedzonych();
	void UsunZeWszystkich();
	void UsunZListyKelnerow();
	int podajRozimar2();

	std::queue <Kelner*> WskazListeKelnera();
	std::queue <Stoliki*> WskazListe2();
	std::queue <Stoliki*> WskazListe3();
	std::queue <Stoliki*> WskazListe4();
	std::queue <Stoliki*> WskazListeDoObslugi();
	std::queue <Stoliki*> WskazListeNapoje();
	std::queue <Stoliki*> WskazListeJedzenie();
	std::queue <Stoliki*> WskazListeZjedzone();
	std::queue <Stoliki*> WskazListeWszystkie();
};
