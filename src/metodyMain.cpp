#include "metodyMain.h"

bool ReadFile(const char* sFileName, Scene& Scn)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLParser4Scene(Scn);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("grammar/scene.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/scene.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}

void listing(Set4LibInterfaces  &LibsSet){
  cout << "Listing wszystkich wgranych polecen:" << endl;
  for (map<string,LibInterface*>::const_iterator Iter = LibsSet.begin();
       Iter != LibsSet.end();  ++Iter) {
    cout << "     " << Iter->second->GetCmdName() << endl;
  }
  cout << endl;
}

void displayMenu(void){
	cout<<endl;
	cout<<"w - wczytanie z pliku sekwencji instrukcji i ich wykonanie"<<endl;
	cout<<"s - start wykonywania sekwencji instrukcji"<<endl;
	cout<<"p - pokaz wczytana sekwencje instrukcji"<<endl;
	cout<<"i - pokaz dostepne instrukcje"<<endl;
	cout<<"d - dodanie nowej wtyczki (instrukcji)"<<endl;
	cout<<"u - usuniecie wtyczki (instrukcji)"<<endl;
	cout<<"? - wyswietl ponownie menu"<<endl;
	cout<<endl;
	cout<<"k - koniec dzialania programu"<<endl;
	cout<<endl;
}

void displayMenu_CaseI(Set4LibInterfaces  &LibsSet){
cout<<"Dostepne polecenia: "<<endl;
for (map<string,LibInterface*>::const_iterator Iter = LibsSet.begin();
       Iter != LibsSet.end();  ++Iter) {
     Iter->second->PrintSyntax();
  }
  cout << endl;
}

void displayMenu_CaseD(Set4LibInterfaces  &LibsSet){
	string nazwaWtyczki;
	cout<<"Podaj nazwe wtyczki, ktora chcesz wgrac: ";
	cin >>nazwaWtyczki;

	if(!LibsSet.AddLib(nazwaWtyczki.c_str())){
		cerr << "Wczytanie nie powiodlo sie! Sprawdz czy biblioteka jest w odpowiednim miejscu! "<<endl;
	}
}

void displayMenu_CaseU(Set4LibInterfaces  &LibsSet){
	string nazwaWtyczkiDoUsuniecia;

	listing(LibsSet);

	cout<<" Podaj nazwe wtyczki do usuniecia: ";
	cin>>nazwaWtyczkiDoUsuniecia;
	const LibInterface *pInterf  = LibsSet.FindLib4Cmd(nazwaWtyczkiDoUsuniecia.c_str());
	if(pInterf == nullptr){
		cerr<<"Nie ma takiej wtyczki! Wybierz jedna z dostepnych opcji! "<<endl;
	}else{
		LibsSet.DeleteLib(nazwaWtyczkiDoUsuniecia.c_str());
	}
}



void displayMenu_CaseW(Scene  &Scn,RobotFace &robotFace){
 
	string nazwaPlikuXML;
	robotFace.getLacze().UsunWszystkieNazwyPlikow();

	cout<<"Podaj nazwe pliku XML: "<<endl;
	cin>>nazwaPlikuXML;
	Scn.clearMapaPolecen();
	 if (!ReadFile(nazwaPlikuXML.c_str(),Scn)){
		cerr<<"Wczytanie nie powiodlo sie! "<<endl;
	}else{
		cout << STR(Ilosc polecen do wykonania: ) << Scn.get_mapaPolecen().size() << endl;

		for (auto& x: Scn.get_mapaPolecen()) {
    			x.second->ExecCmd(robotFace);
  		}
	}
}

void displayMenu_CaseS(Scene  &Scn,RobotFace &robotFace){

if(Scn.get_mapaPolecen().size() !=0){
for (auto& x: Scn.get_mapaPolecen()) {
    			x.second->ExecCmd(robotFace);
  		}
} else {
std::cerr<<"Blad: Nie wczytano jeszcze polecen. Uzyj najpierw opcji 'w'"<<std::endl;
}
}

void displayMenu_CaseP(Scene  &Scn){
		for (auto& x: Scn.get_mapaPolecen()) {
    			x.second->PrintCmd();
  		}
}
