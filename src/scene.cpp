#include "scene.hh"

/*!
 * Jeżeli metoda zwróci true - element dodany , jeżeli false - element o podanym kluczu już istnieje
 */
bool Scene::AddCommand(int key, Command *command){
	return (_mapaPolecen.emplace(key,command)).second;
}

Command* Scene::findCommand(const char* name){
const LibInterface *pInterf  = _LibsSet->FindLib4Cmd(name);
	if(pInterf == nullptr){
		cerr<<"Nie ma takiej wtyczki! Wybierz jedna z dostepnych opcji! "<<endl;
		return nullptr;
	} else{
		return pInterf->CreateCmd();
	}		
}


void Scene::refreshActualMap(string nazwaPliku,Command * komenda){

if (aktualnaMapa.count(nazwaPliku) != 0) {
		aktualnaMapa.erase(nazwaPliku);
		aktualnaMapa.insert(
				std::pair<std::string, Command*>(nazwaPliku, komenda));
	} else {
		aktualnaMapa.insert(
				std::pair<std::string, Command*>(nazwaPliku, komenda));
	}
std::cerr<<"Aktualna mapa posiada: "<<aktualnaMapa.size()<<" elementow."<<std::endl;
}

void Scene::Oko_simulateMovement(std::vector<Wektor2D> GornaPowieka,std::vector<Wektor2D> DolnaPowieka,
				std::vector<Wektor2D> poprzedniaGornaPowieka,std::vector<Wektor2D> poprzedniaDolnaPowieka,int szybkoscZmiany){


}

void Scene::Usta_simulateMovement(std::vector<Wektor2D> GornaWarga,std::vector<Wektor2D> DolnaWarga,
				std::vector<Wektor2D> poprzedniaGornaWarga,std::vector<Wektor2D> poprzedniaDolnaWarga,int szybkoscZmiany){
}

void Scene::Brew_simulateMovement(int nrPolecenia,string nazwaPliku){
}

