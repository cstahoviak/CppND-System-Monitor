#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
// NOTE: for a MULTI LINE string
string LinuxParser::OperatingSystem() {
  string line, key, value;
  
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    // while loop to iterate thru multi-line file
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      // don't understand how the below logical condition is being evaluated
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
// NOTE: for a SINGLE LINE string
string LinuxParser::Kernel() {
  string line, os, version, kernel;

  // create input filestream
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    // get line from open stream and store in line var
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

/* PARSING STEPS:
* 1. open file
* 2. check if file is open
* 3. loop through lines using getline() until matching 'token' (eg PRETTY_NAME) is found
* 3. pull lines off file and return part of line that we're interested in
*/

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line, key, value;

  vector<string> keys;
  vector<float> values;
  
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    // while loop to iterate thru multi-line file
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');

      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Active") {
        break;
      }
      else {
        // std::cout << key << "\t" << value << "\n";
        keys.push_back(key);
        values.push_back(std::stol(value));
      }
    }
  }

  // implement memory utilization math
  float util = values[2] / values[0];
  return util;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line, uptime, idletime;

  // create input filestream
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    // get line from open stream and store in line var
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idletime;
  }

  // long test = std::stol(uptime);
  return std::stol(uptime);   // convert string to long int
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
// vector<string> LinuxParser::CpuUtilization() {
vector<LinuxParser::CPUStates_> LinuxParser::CpuUtilization() {
  string line, cpu_id;
  LinuxParser::CPUStates_ cpu;
  vector<LinuxParser::CPUStates_> cpu_vec;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    // while loop to iterate thru multi-line file
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> cpu_id >> cpu.kUser_ >> cpu.kNice_ >> cpu.kSystem_ >>
        cpu.kIdle_ >> cpu.kIOwait_ >> cpu.kIRQ_ >> cpu.kSoftIRQ_ >> cpu.kSteal_ >>
        cpu.kGuest_ >> cpu.kGuestNice_;
      if (cpu_id == "intr") {
        break;
      }
      else {
        cpu_vec.push_back(cpu);
      }
    }
  }
  return cpu_vec;
} 

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key, value;
  int processes{0};
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    // while loop to iterate thru multi-line file
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
        processes = std::stoi(value);
        return processes;
      }
    }
  }
  return processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key, value;
  int procs_running{0};
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    // while loop to iterate thru multi-line file
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") {
        procs_running = std::stoi(value);
        return procs_running;
      }
    }
  }
  return procs_running;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }