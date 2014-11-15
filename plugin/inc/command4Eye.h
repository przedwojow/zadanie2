#ifndef  COMMAND4EYE_HH
#define  COMMAND4EYE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "command.h"
#include "robotfaceInterface.h"

class Command4Eye: public Command {
	
private:
	int idOka;
	double polozenieDolnejPowieki;
	double polozenieGornejPowieki;
	int szybkoscZmiany;

 public:
  Command4Eye();  
  virtual void PrintCmd() const;
  virtual int ExecCmd( RobotFace   &pRobFace ) const;
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  static const char* GetCmdName();
  static Command* CreateCmd();
  static void PrintSyntax();
///////////////////////////////////////////////////
///////////////////////////////////////////////////
	int getIdOka() const;
	void setIdOka(double idOka);
	double getPolozenieDolnejPowieki() const;
	void setPolozenieDolnejPowieki(double polozenieDolnejPowieki);
	double getPolozenieGornejPowieki() const;
	void setPolozenieGornejPowieki(double polozenieGornejPowieki);
	int getSzybkoscZmiany() const;
	void setSzybkoscZmiany(double szybkoscZmiany);

///////////////////////////////////////////////////
///////////////////////////////////////////////////
 };

#endif
