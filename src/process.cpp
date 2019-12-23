#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

// added by me
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
// segfault occurs here
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  return LinuxParser::ProcessCpuUtilization( pid_ );
}

// TODO: Return the command that generated this process
string Process::Command() {
  return LinuxParser::Command( pid_ );
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  return LinuxParser::Ram( pid_ );
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  return LinuxParser::User( pid_ );
}

// TODO: Return the age of this process (in seconds)
long Process::UpTime() {
  return LinuxParser::UpTime( pid_ );
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// NOTE: sort via CpuUtilization or RAM - use std::sort() to sort processes
// bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
bool Process::operator>(Process const& a) const {
  return LinuxParser::ProcessCpuUtilization( pid_ ) >
    LinuxParser::ProcessCpuUtilization( a.pid_ );

  // return LinuxParser::Ram( pid_ ) > LinuxParser::Ram( a.pid_ );
}