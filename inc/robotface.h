#ifndef  ROBOTFACE_H
#define  ROBOTFACE_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <unistd.h>
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
std::vector<Wektor2D> poprzedniaGornaWarga;
std::vector<Wektor2D> poprzedniaDolnaWarga;

std::vector<Wektor2D> GornaWarga;
std::vector<Wektor2D> DolnaWarga;

////////////OKO///////////////////
std::vector<Wektor2D> poprzedniaGornaPowieka;
std::vector<Wektor2D> poprzedniaDolnaPowieka;

std::vector<Wektor2D> GornaPowieka;
std::vector<Wektor2D> DolnaPowieka;

public:
	PzG::LaczeDoGNUPlota getLacze();

/////////////USTA/////////////////
	bool Usta_zapisz(int szybkoscZmian);
	void Usta_zbudujPolecenieDlaGnuplota(
		double polozenieDolnejWargi,
		double polozenieDolnejPowieki,
		double polozenieGornejPowieki); 
	const char* Usta_getFilename();
	void Usta_zmienPozycje();

	std::vector<Wektor2D> getGornaWarga(){return GornaWarga;};
	std::vector<Wektor2D> getDolnaWarga(){return DolnaWarga;};
	std::vector<Wektor2D> getPoprzedniaGornaWarga(){return poprzedniaGornaWarga;};
	std::vector<Wektor2D> getPoprzedniaDolnaWarga(){return poprzedniaDolnaWarga;};

////////////OKO///////////////////
	bool Oko_zapisz(int idOka,int szybkoscZmian);
	void Oko_zbudujPolecenieDlaGnuplota(double polozenieDolnejPowieki,double polozenieGornejPowieki); 
	const char* Oko_getFilename();
	void Oko_zmienPozycje();

	std::vector<Wektor2D> getGornaPowieka(){return GornaPowieka;};
	std::vector<Wektor2D> getDolnaPowieka(){return DolnaPowieka;};
	std::vector<Wektor2D> getPoprzedniaGornaPowieka(){return poprzedniaGornaPowieka;};
	std::vector<Wektor2D> getPoprzedniaDolnaPowieka(){return poprzedniaDolnaPowieka;};
////////////BREW//////////////////
//	void zapiszBrew();
//	void Brew_zbudujPolecenieDlaGnuplota(); 

};

#endif
