#include "robotface.h"

#define DLUGOSC_BRWI 15
#define NEUTRALNE_POLOZENIE_BRWI 10

bool RobotFace::Brew_zapisz(int idBrwi,int szybkoscZmian){
std::stringstream ss;
	double translacja_Y = 100;
	double translacja_X = 30;
	
	ss<<"dat/Brew"<<idBrwi<<".dat";
	std::ofstream StrmWy(ss.str());

	if (!StrmWy.is_open())
		return false;
if(idBrwi == 0 ) {
Wektor2D GP;
	for (auto Iter = Brew0.begin(); Iter != Brew0.end(); ++Iter) {
		GP = *Iter;
		GP.y += -1.1 * NEUTRALNE_POLOZENIE_BRWI  + translacja_Y;
		GP.x += -1.1 * NEUTRALNE_POLOZENIE_BRWI 
				+ translacja_X * idBrwi;
		StrmWy << GP << std::endl;
	}
	return !StrmWy.fail();
}
if(idBrwi == 1 ) {
Wektor2D GP;
	for (auto Iter = Brew1.begin(); Iter != Brew1.end(); ++Iter) {
		GP = *Iter;
		GP.y += -1.1 * NEUTRALNE_POLOZENIE_BRWI + translacja_Y;
		GP.x += -1.1 * NEUTRALNE_POLOZENIE_BRWI
				+ translacja_X * idBrwi;
		StrmWy << GP << std::endl;
	}
	return !StrmWy.fail();
}	

}


void RobotFace::Brew_zbudujPolecenieDlaGnuplota(double polozenieBrwi,double polozenieKatNachylenia,int idBrwi){

if(idBrwi ==0) {
	if(!Brew0.empty()){
		_PpolozenieBrwi0=Brew0[0].y;
		_PpolozenieKatNachylenia0=((- Brew0[1].y  )/DLUGOSC_BRWI)+_PpolozenieBrwi0;

		}
		Brew0 = { {-NEUTRALNE_POLOZENIE_BRWI,polozenieBrwi}
			, {-NEUTRALNE_POLOZENIE_BRWI+DLUGOSC_BRWI,polozenieBrwi+(DLUGOSC_BRWI*polozenieKatNachylenia/100)}};
	
}
if(idBrwi ==1) {

	if(!Brew1.empty()){
		_PpolozenieBrwi1=Brew1[0].y;
		_PpolozenieKatNachylenia1=((- Brew1[1].y  )/DLUGOSC_BRWI)+_PpolozenieBrwi1;
		}
	
		Brew1 = { {-NEUTRALNE_POLOZENIE_BRWI,polozenieBrwi}
			, {-NEUTRALNE_POLOZENIE_BRWI+DLUGOSC_BRWI,polozenieBrwi+(DLUGOSC_BRWI*polozenieKatNachylenia/100)}};
}
}


void RobotFace::Brew_simulateMovement(double polozenieBrwi,double polozenieKatNachylenia,int szybkoscZmiany,
					int idBrwi,std::string filename){

double roznicaPolozeniaBrwi = 0;
double roznicaPolozeniaKatNachylenia = 0;
int iloscRuchow = 0;
double aktualnePolozeniaBrwi = 0;
double aktualnePolozeniaKatNachylenia = 0;

Brew_zbudujPolecenieDlaGnuplota(aktualnePolozeniaBrwi,aktualnePolozeniaKatNachylenia,idBrwi); 
/*!
 * mikroruch dla brwi
 */
if(idBrwi == 0 ) {
roznicaPolozeniaBrwi = (polozenieBrwi - this->_PpolozenieBrwi0) /  (10*(szybkoscZmiany/100)+1);

/*!
 * mikroruch dla dolnej powieki
 */
roznicaPolozeniaKatNachylenia = (polozenieKatNachylenia - this->_PpolozenieKatNachylenia0) /  (10*(szybkoscZmiany/100)+1);
	
iloscRuchow = 10*(szybkoscZmiany/100)+1;//abs((int)(polozenieGornejPowieki - this->_PpolozenieGornejPowieki0)) /abs(roznicaGornejPowieki);
aktualnePolozeniaBrwi = this->_PpolozenieBrwi0;
aktualnePolozeniaKatNachylenia = this->_PpolozenieKatNachylenia0;
}

else if(idBrwi == 1 ) {

roznicaPolozeniaBrwi = (polozenieBrwi - this->_PpolozenieBrwi1) /  (10*(szybkoscZmiany/100)+1);

/*!
 * mikroruch dla dolnej powieki
 */
roznicaPolozeniaKatNachylenia = (polozenieKatNachylenia - this->_PpolozenieKatNachylenia1) /  (10*(szybkoscZmiany/100)+1);
	
iloscRuchow = 10*(szybkoscZmiany/100)+1;//abs((int)(polozenieGornejPowieki - this->_PpolozenieGornejPowieki0)) /abs(roznicaGornejPowieki);
aktualnePolozeniaBrwi = this->_PpolozenieBrwi1;
aktualnePolozeniaKatNachylenia = this->_PpolozenieKatNachylenia1;
}
for(int i=0;i<iloscRuchow;i++){
	aktualnePolozeniaBrwi+=roznicaPolozeniaBrwi;
	aktualnePolozeniaKatNachylenia+=roznicaPolozeniaKatNachylenia;
	Brew_zbudujPolecenieDlaGnuplota(aktualnePolozeniaBrwi,aktualnePolozeniaKatNachylenia,idBrwi); 

	Brew_zapisz(idBrwi,0);
	getLacze().DodajNazwePliku(filename.c_str(), PzG::RR_Ciagly, 6);
	getLacze().Rysuj();
	 usleep(50 * 1000);
}

}
