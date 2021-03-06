#ifndef  ROBOTFACE_H
#define  ROBOTFACE_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cmath>
#include "lacze_do_gnuplota.hh"
#include "Wektor2D.hh"

#include "robotfaceInterface.h"


#define NEUTRALNE_POLOZENIE_KACIKOW_UST 20
#define NEUTRALNE_POLOZENIE_KACIKOW_POWIEK 12
#define STR(x) #x

using namespace std;

class RobotFace : public RobotFaceInterface{

private:
	PzG::LaczeDoGNUPlota Lacze;

/////////////USTA/////////////////
double _PpolozenieDolnejWargi;
double _PpolozenieGornejWargi;
double _PoddalenieKacikowUst;

std::vector<Wektor2D> GornaWarga;
std::vector<Wektor2D> DolnaWarga;

////////////OKO///////////////////
double _PpolozenieDolnejPowieki0;
double _PpolozenieGornejPowieki0;
double _PpolozenieDolnejPowieki1;
double _PpolozenieGornejPowieki1;

std::vector<Wektor2D> GornaPowieka0;
std::vector<Wektor2D> DolnaPowieka0;
std::vector<Wektor2D> GornaPowieka1;
std::vector<Wektor2D> DolnaPowieka1;

////////////BREW///////////////////
double _PpolozenieBrwi0;
double _PpolozenieKatNachylenia0;
double _PpolozenieBrwi1;
double _PpolozenieKatNachylenia1;

std::vector<Wektor2D> Brew0;
std::vector<Wektor2D> Brew1;


public:
	RobotFace(){
		Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
		Lacze.ZmienTrybRys(PzG::TR_2D);
		Lacze.UstawZakresY(-130, 130);
		Lacze.UstawZakresX(-130, 130);
}

	PzG::LaczeDoGNUPlota getLacze();

/////////////USTA/////////////////
	bool Usta_zapisz(int szybkoscZmian);
	void Usta_zbudujPolecenieDlaGnuplota(
		double polozenieDolnejWargi,
		double polozenieGornejWargi,
		double oddalenieKacikowUst); 
	const char* Usta_getFilename();
	void Usta_simulateMovement(double polozenieDolnejWargi,double polozenieGornejWargi,
					double oddalenieKacikowUst,int szybkoscZmiany,std::string filename);

	std::vector<Wektor2D> getGornaWarga(){return GornaWarga;};
	std::vector<Wektor2D> getDolnaWarga(){return DolnaWarga;};


////////////OKO///////////////////
	bool Oko_zapisz(int idOka,int szybkoscZmian);
	void Oko_zbudujPolecenieDlaGnuplota(double polozenieDolnejPowieki,double polozenieGornejPowieki,int idOka); 
	const char* Oko_getFilename();
	void Oko_simulateMovement(double polozenieDolnejPowieki,double polozenieGornejPowieki,
					int szybkoscZmiany,int idOka,std::string filename);		

	std::vector<Wektor2D> getGornaPowieka(){return GornaPowieka0;};
	std::vector<Wektor2D> getDolnaPowieka(){return DolnaPowieka0;};
////////////BREW//////////////////
	bool Brew_zapisz(int idOka,int szybkoscZmian);
	void Brew_zbudujPolecenieDlaGnuplota(double polozenieBrwi,double polozenieKatNachylenia,int idBrwi); 
	void Brew_simulateMovement(double polozenieBrwi,double polozenieKatNachylenia,int szybkoscZmiany,
					int idBrwi,std::string filename);





};

#endif
