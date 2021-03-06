#ifndef  COMMAND_H
#define  COMMAND_H

#include <string>
#include <iostream>
#include <map>
#include "robotface.h"
 class Command {
  public:
   virtual ~Command() {}
   virtual void PrintCmd() const = 0;
   virtual int ExecCmd( RobotFace   &RobFace ) const = 0;
   virtual bool ReadParams(std::istream& Strm_CmdsList) = 0;
   virtual std::string getFilename() = 0;
   virtual std::string getCommandName() =0;
   virtual int getSzybkoscZmiany() const=0;

 };

#endif
