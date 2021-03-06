#include "processor.h"

// added by me
#include "linux_parser.h"

/* BONUS:
* You might want to update the system monitor to report the current utilization
* of the processor, rather than the long-term average utilization since boot.
* You would need to measure the difference in system utilization between two
* points in time relatively close to the present. A formula like:
*   delta_active_time_untis / delta_total_time_units
*/

Processor::Processor() {
  /* NOTE:
  *   This constructor will initialize the cpu_state_ vector in order to determine
  *   the number of additional lines to add to the upper box of the NCurses display
  *   where utilization statistics for individual CPUs will be displayed.
  */
  cpu_state_ = LinuxParser::CpuUtilization();
  // Q: would a call to vector::reserve improve efficiency? (see line below)
  // cpu_usage_.reserve(cpu_state_.size());
  cpu_usage_.insert(cpu_usage_.begin(), cpu_state_.size(), 0.0f);
}

// TODO: Return the aggregate CPU utilization
// float Processor::Utilization() {
void Processor::Utilization() {
  int prevIdle, prevNonIdle, prevTotal;
  int idle, nonIdle, total;
  int delta_total, delta_idle;
  float cpu_usage{0.0f};

  // get current CPU utilization state
  std::vector<LinuxParser::CPUStates_> cpu_state = LinuxParser::CpuUtilization();

  // implement CPU utilization calculation
  for( std::size_t i=0; i<cpu_state_.size(); i++ ) {
    prevIdle = cpu_state_[i].kIdle_ + cpu_state_[i].kIOwait_;
    idle     = cpu_state[i].kIdle_ + cpu_state[i].kIOwait_;

    prevNonIdle = cpu_state_[i].kUser_ + cpu_state_[i].kNice_
      + cpu_state_[i].kSystem_ + cpu_state_[i].kIRQ_
      + cpu_state_[i].kSoftIRQ_ + cpu_state_[i].kSteal_;
    nonIdle = cpu_state[i].kUser_ + cpu_state[i].kNice_
      + cpu_state[i].kSystem_ + cpu_state[i].kIRQ_
      + cpu_state[i].kSoftIRQ_ + cpu_state[i].kSteal_;

    prevTotal = prevIdle + prevNonIdle;
    total     = idle + nonIdle;

    delta_total = total - prevTotal;
    delta_idle  = idle - prevIdle;

    // check for division by zero
    if( delta_total != 0 ) {
      cpu_usage = (float)(delta_total - delta_idle) / delta_total;
    }
    else {
      cpu_usage = 0.0f;
    }
    // update cpu utilization
    cpu_usage_[i] = cpu_usage;
  }

  // update current CPU state
  cpu_state_ = cpu_state;
  return;
}

// assessor for private member variable cpu_state_
std::vector<LinuxParser::CPUStates_> Processor::CpuState() {
  return cpu_state_;
}

// assessor for private member variable cpu_usage_
std::vector<float> Processor::CpuUsage() {
  return cpu_usage_;
}

// assessor for private member variable cpu_usage_
float Processor::CpuUsage(std::size_t cpu_n) {
  // Q: is cpu_n a valid index for cpu_usage_ vector?
  // NOTE: cpu_usage_ will never be empty if initialized in constructor
  if( cpu_n < cpu_usage_.size() ) {
    return cpu_usage_[cpu_n];
  }
  else {
    return 0.0f;
  }
}