#include "set4libinterfaces.hh"

using namespace std;



/*!
 *
 */
Set4LibInterfaces::~Set4LibInterfaces()
{
  /*
   * Tutaj interujemy zawartosc dziedziczonego kontenera map<>
   */
  for (pair<string,LibInterface*> Element : *this ) {
    /*
     * W petli otrzymujemy kolejne elementy kontenera map<string,LibInterface*>.
     * Sa nimi obiekty instancji szablonu pair<string,LibInterface*>.
     * Szablon ten ma dwa pola: first i second. Sa one typow, ktore sa
     * wymienione sa dokladnie w tej samej kolejnosci w liscie parametrow
     * tego szablonu.
     */
     
    /*
     * To jest tylko po to, aby pokazac jak sie dostac do pola klasy
     * obiektu instacji szablonu pair<string,LibInterface*>.
     */
    cout << "Chce usunac: " << Element.first << endl;

    /*
     *  Tutaj trzeba wpisac odpowiedni kod aby usunc 
     *  zmienne dynamiczna zawiazana z interfejsem biblioteki.
     */
  }
}



/*!
 * \brief Dodaje nowa biblioteke
 *
 * Dodaje nowa bibliotekę, która zawiera implementację nowego 
 * polecenia.
 * \param[in] sLibName - nazwa pliku z biblioteką, która ma zostać
 *                       załadowana i dodana do zbioru bibliotek zawierających
 *                       implementację poszczególnych poleceń.
 * \retval true - operacja powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool Set4LibInterfaces::AddLib(const char*  sLibName)
{
  LibInterface   *pInterf4Copy = new LibInterface();

  if (!pInterf4Copy->Init4Lib(sLibName)) { delete pInterf4Copy;  return false; }

  insert(pair<string,LibInterface*>
			(pInterf4Copy->GetCmdName(),pInterf4Copy));

  return true;
}



/*!
 * Szuka obiektu pełniącego rolę interfejsu biblioteki, który 
 * odpowiada poleceniu o podanej nazwie np. Move.
 *
 * \param sCmdName - nazwa polecenia, dla którego szukany jest
 *                   interfejs do biblioteki zawierającej 
 *                   implementację danego polecenia.
 * \return Jeśli obiekt reprezentujący interfejs biblioteki 
 *         danego polecenia zostanie znaleziony, to zwracany
 *         jest jego adres. W przypadku przeciwnym zwracany
 *         jest adres \p nullptr.
 */
const LibInterface* Set4LibInterfaces::FindLib4Cmd(const char*  sCmdName) const
{
  map<string,LibInterface*>::const_iterator  Iter = 
                                       map<string,LibInterface*>::find(sCmdName);

  if (Iter == end()) return nullptr;
  return Iter->second;
}

