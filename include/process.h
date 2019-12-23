#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/

// May also choose to implement these functions as "pass-thrus" to the
// LinuxParser namespace functions

class Process {
  public:
    // constructor: added by me
    Process(int pid) : pid_(pid) {}         // constructor has no return type
    int Pid();                              // TODO: See src/process.cpp
    std::string User();                     // TODO: See src/process.cpp
    std::string Command();                  // TODO: See src/process.cpp
    float CpuUtilization();                 // TODO: See src/process.cpp
    std::string Ram();                      // TODO: See src/process.cpp
    long UpTime();                          // TODO: See src/process.cpp
    bool operator>(Process const& a) const; // makes more sense to oveload >

  // TODO: Declare any necessary private members
  private:
  int pid_{0};    // how would I set this?... with the class constructor?
};

#endif