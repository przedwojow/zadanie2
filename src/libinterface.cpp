#include "libinterface.hh"
#include <string>
#include <iostream>

using std::string;
using std::cerr;
using std::endl;


/*
 * Uwaga: Ta jest tylko na potrzeby tego przykładu.
 *        W finalnym programie nie powinno jej być
 *        w tym miejscu.
 */
const char* GetName_EyeCmd() 
  { return "Oko"; }

/*
 * Uwaga: Ta jest tylko na potrzeby tego przykładu.
 *        W finalnym programie nie powinno jej być
 *        w tym miejscu.
 */
const char* GetName_LipsCmd() 
  { return "Usta"; }


/*!
 *
 * \warning [Uwaga!!!] Ta metoda powinna otwierać bibliotekę
 * dynamicznie konsolidowaną
 * i odnaleźć wskaźniki na funkcje stanowiące interfejs biblioteki.
 * Jednak dla uproszenia przykładu definicja tej metody jest nieco
 * oszukana.
 */
bool LibInterface::Init4Lib(const char* sLibName)
{
  /*
   * Uwaga!!! Poniższa definicja metody jest uproszczona i nie
   * należy się na niej wzorować.
   */
  string Name4Lib="libs/";
Name4Lib+=sLibName;


_pLibHandle=dlopen(Name4Lib.c_str(),RTLD_LAZY);

  if (!_pLibHandle) {
    cerr << "!!! Brak biblioteki: "<<sLibName << endl;
    return 1;
  }

pFun = dlsym(_pLibHandle,"GetCmdName"); 
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  _pFun_GetCmdName = *reinterpret_cast<const char* (**)()>(&pFun);

pFun = dlsym(_pLibHandle,"CreateCmd");
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  _pFun_pCreateCmd = *reinterpret_cast<Command* (**)(void)>(&pFun);


  pFun = dlsym(_pLibHandle,"PrintSyntax"); 
  if (!pFun) {
    cerr << dlerror() << endl;
    return 1;
  }
  _pFun_pPrintSyntax = *reinterpret_cast<void (**)()>(&pFun);


    return true;
  
  cerr << ":( Inicjalizacja biblioteki \"" << sLibName << "\"" << endl
       << ":( nie powiodla sie." << endl;
  return false;
}