#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

// added by me
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> pids{ LinuxParser::Pids() };
  vector<Process> procs;

  // catalogue all existing processes
  set<int> extant_pids;
  for (Process process : processes_) {
    extant_pids.insert(process.Pid());
  }

  // add all newly created processes to set
  for (int pid : pids) {
    if (extant_pids.find(pid) == extant_pids.end()) {
      // processes_.emplace_back(pid);
      Process new_proc = Process(pid);
      processes_.push_back(new_proc);
    }
  }

  // update CPU utilization (??)

  // sort processes by CPU utilization
  std::sort(processes_.begin(), processes_.end(), std::less<Process>() );

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
  // long test = LinuxParser::UpTime();
  return LinuxParser::UpTime();
}