#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"

// added by me
#include "linux_parser.h"

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
// 1. update the processes_ vector
// 2. return the processes_ vector
std::vector<Process>& System::Processes() {
  // std::cerr << "entering System::Processes" << std::endl;

  // Q: Why does pids have 1000 elements before it's assigned using LinuxParser::Pids()?
  // std::vector<int> pids{ LinuxParser::Pids() };
  std::vector<int> pids = LinuxParser::Pids();

  // catalogue all existing processes
  std::set<int> extant_pids;
  for (Process process : processes_) {
    extant_pids.insert(process.Pid());
  }

  // add all newly created processes to set
  for (int pid : pids) {
    if (extant_pids.find(pid) == extant_pids.end()) {
      // NOTE: prefer emplace_back() to push_back() for vectors of user-defined types
      // NOTE: do NOT need to create a new Process object before appending it to
      // processes_ vector; emplace_back() will append Process object to end of
      // processes_ vector by passing to emplace_back() the constructor args
      processes_.emplace_back(pid);
    }
  }

  // remove terminated processes from processes_ vector
  int proc_idx = 0;
  for (Process process : processes_) {
    if ( std::find(pids.begin(), pids.end(), process.Pid()) == pids.end() ) {
      // true if process ID is NOT in pids vector
      processes_.erase(processes_.begin()+proc_idx);
    }
    proc_idx++;
  }

  // update CPU utilization (maybe?)

  // sort processes by CPU utilization
  std::sort(processes_.begin(), processes_.end(), std::greater<Process>());

  // std::cerr << "exiting System::Processes" << std::endl;
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
  return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
long System::UpTime() {
  return LinuxParser::UpTime();
}