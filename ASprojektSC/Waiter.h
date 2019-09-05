#pragma once

class Kelner {
	int liczba_obsluzen_;
	int id_kelnera_;
	bool wolny_kelner_;
	Kelner* next_;

public:
	Kelner();
	virtual ~Kelner();
	void UstawId(int id);
	void UstawStatus(bool b);
	void UstawNastepny(Kelner* kelner);
	void AktualizujLiczbeObsluzen();
	int PodajLiczbeObsluzen();
	int PodajId();
	bool SprawdzCzyWolny();
	bool SprawdzCzyNastepny();
	Kelner* ZwrocNastepny();
};