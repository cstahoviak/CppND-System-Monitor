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
    std::vector<float> CpuUsage();    // get CPU usage for all CPUs
    float CpuUsage(std::size_t cpu_n);        // get CPU usage for a single CPU

  // TODO: Declare any necessary private members
  private:
    std::vector<LinuxParser::CPUStates_> cpu_state_;
    // NOTE: maybe cpu_usage_ should be an array because it will never change size
    // once initialized.. but I don't know the size at compile time, so that may
    // be problematic?
    std::vector<float> cpu_usage_;

};

#endif