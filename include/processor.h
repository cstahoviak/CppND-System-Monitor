#ifndef PROCESSOR_H
#define PROCESSOR_H

// added by me
#include "linux_parser.h"

class Processor {
  public:
    // added by me: constructor
    Processor();
    // float Utilization();  // TODO: See src/processor.cpp
    void Utilization();

    // added by me
    std::vector<LinuxParser::CPUStates_> CpuState();  // cpu_state_ accessor fcn
    std::vector<float> TotalCpuUsage();
    float SingleCpuUsage(int cpu_n); 

  // TODO: Declare any necessary private members
  private:
    std::vector<LinuxParser::CPUStates_> cpu_state_;
    std::vector<float> cpu_usage_;
};

#endif