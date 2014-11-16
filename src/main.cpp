#include "metodyMain.h"

int main (int argc, char* args[]) 
{
	Scene  Scn;
	RobotFace robotFace;
  	Set4LibInterfaces  LibsSet;
	char Opcja;

  	if (!LibsSet.AddLib("libPolecenie_Oko.so")) return 1;
  	if (!LibsSet.AddLib("libPolecenie_Usta.so")) return 1;
  	if (!LibsSet.AddLib("libPolecenie_Brew.so")) return 1;
 	 listing(LibsSet);
  	Scn.AddLibSet(LibsSet);

	char wyborMenu;
	displayMenu();
	do {
		//cout << "Twoj wybor (? - menu): ";
		cin >> wyborMenu;

		switch (wyborMenu) {
		case 'w':
			displayMenu_CaseW(Scn,robotFace);
			break;
		case 's':
			displayMenu_CaseS(Scn,robotFace);
			break;	
		case 'p':
			displayMenu_CaseP(Scn);
			break;
		case 'i':
			displayMenu_CaseI(LibsSet);
			break;
		case '?':
			displayMenu();
			break;
		case 'k':
			std::cout << std::endl << "Koniec dzialania programu." << std::endl;
			break;
		case 'd':
			displayMenu_CaseD(LibsSet);
			break;
		case 'u':
			displayMenu_CaseU(LibsSet);
			break;
		default:
			cout << "Nieznana komenda." << endl;
			break;
		}
	} while (wyborMenu != 'k');

return 0;
}
