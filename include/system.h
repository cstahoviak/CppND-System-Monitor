#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

/* What is the relationship b/w the System class and the LinuxParser namespace?
* - System::Uptime() might call the function of the same name in the LinuxParser
    namespace. System::Uptime() would then be considered a "pass-thru". In this
    way, an object of the System class would store no data on the system's "uptime".

    Alternately, could store the value returned by System::Uptime() as a private
    variable (uptime_) of the System class. However, uptime_ and other values like
    it are dynamic, and so an update function, System::Update() perhaps, could be
    used to update the stored values within the System class.
*/

class System {
  public:
    // accessor functions that return refs to private member variables
    Processor& Cpu();                   // TODO: See src/system.cpp
    std::vector<Process>& Processes();  // TODO: See src/system.cpp
    
    float MemoryUtilization();          // TODO: See src/system.cpp
    long UpTime();                      // TODO: See src/system.cpp
    int TotalProcesses();               // TODO: See src/system.cpp
    int RunningProcesses();             // TODO: See src/system.cpp
    std::string Kernel();               // TODO: See src/system.cpp
    std::string OperatingSystem();      // TODO: See src/system.cpp

  // TODO: Define any necessary private members
  private:
    Processor cpu_ = {};
    std::vector<Process> processes_ = {};
};

#endif