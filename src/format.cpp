#include <string>

#include "format.h"

using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
std::string Format::ElapsedTime(long total_secs) {
  int hrs, mins, secs;

	hrs = total_secs / 3600;
	total_secs = total_secs % 3600;
	mins = total_secs / 60;
	total_secs = total_secs % 60;
	secs = total_secs;

  return to_string(hrs) + ":" + to_string(mins) + ":" + to_string(secs);
}