#ifndef SCENE_HH
#define SCENE_HH


/*!
 * \file
 * 
 * \brief Zawiera ...
 *
 *  ...
 */

/*!
 * \brief Scena robocza, na której działa robot
 *
 *  Klasa ...
 */
#include <map>
#include <string>

#include "command.h"
#include "libinterface.hh"
#include "set4libinterfaces.hh"
using namespace std;



class Scene {

private:
/*!
 * Mapa polecen, gdzie kluczem jest numer w kolejnosci polecenia a wartoscia jest sama komenda
 */	int numerPolecenia;
	map<int,Command*> _mapaPolecen;
	Set4LibInterfaces *_LibsSet;

public:
Scene(){
numerPolecenia = 0;
}
bool AddLibSet(Set4LibInterfaces &LibsSet){_LibsSet=&LibsSet; return true;};
bool findCommand(const char* name);

bool AddCommand(int key, Command *command);
int getNumerPolecenia(){ return numerPolecenia;};
void setNumerPolecenia(int n){numerPolecenia=n;};

};


#endif
