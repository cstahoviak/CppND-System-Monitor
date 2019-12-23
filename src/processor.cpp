#include "processor.h"

// added by me
#include "linux_parser.h"

using std::vector;

/* BONUS:
* You might want to update the system monitor to report the current utilization
* of the processor, rather than the long-term average utilization since boot.
* You would need to measure the difference in system utilization between two
* points in time relatively close to the present. A formula like:
*   delta_active_time_untis / delta_total_time_units
*/

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  int prevIdle, prevNonIdle, prevTotal;
  int idle, nonIdle, total;
  int delta_total, delta_idle;
  // float cpu_usage{0.0f};

  // get current CPU utilization state
  vector<LinuxParser::CPUStates_> cpu_state = LinuxParser::CpuUtilization();

  // implement CPU utilization calculation
  if( !cpu_state_.empty() ) {
    // cpu_state_[0] represents the aggregate cpu (cpu0:3) statistics
    prevIdle = cpu_state_[0].kIdle_ + cpu_state_[0].kIOwait_;
    idle     = cpu_state[0].kIdle_ + cpu_state[0].kIOwait_;

    prevNonIdle = cpu_state_[0].kUser_ + cpu_state_[0].kNice_ + cpu_state_[0].kSystem_
      + cpu_state_[0].kIRQ_ + cpu_state_[0].kSoftIRQ_ + cpu_state_[0].kSteal_;
    nonIdle = cpu_state[0].kUser_ + cpu_state[0].kNice_ + cpu_state[0].kSystem_
      + cpu_state[0].kIRQ_ + cpu_state[0].kSoftIRQ_ + cpu_state[0].kSteal_;

    prevTotal = prevIdle + prevNonIdle;
    total     = idle + nonIdle;

    delta_total = total - prevTotal;
    delta_idle  = idle - prevIdle;
    
    cpu_usage_ = (float)(delta_total - delta_idle) / delta_total;
  }
  else {
    cpu_usage_ = 0.0f;
  }

  // update previous CPU state
  cpu_state_ = cpu_state;

  return cpu_usage_;
}