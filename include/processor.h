#ifndef PROCESSOR_H
#define PROCESSOR_H

// added by me
#include "linux_parser.h"

class Processor {
  public:
    // Processor() {
    //   cpu_state_.reserve(5);    // not sure if this is the right thing to do..
    // }
    float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
  private:
    std::vector<LinuxParser::CPUStates_> cpu_state_;
    float cpu_usage_{0.0f};
};

#endif