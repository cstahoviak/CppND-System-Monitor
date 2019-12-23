#ifndef PROCESSOR_H
#define PROCESSOR_H

// added by me
#include "linux_parser.h"

class Processor {
  public:
    Processor() {
      cpu_vec_.reserve(4);
    }
    float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
  private:
    std::vector<LinuxParser::CPUStates_> cpu_vec_;
};

#endif