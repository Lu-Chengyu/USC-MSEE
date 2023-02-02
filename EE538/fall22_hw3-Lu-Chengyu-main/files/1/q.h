#include <chrono>
#include <iostream>
//-----------------------------------------------------------------------------
// No need to change or view this file! See q.cc.
// This is not a coding question.
// The following definitions are used for measuring the time of an operation.
//-----------------------------------------------------------------------------

// A global variable that stores the start time.
std::chrono::time_point<std::chrono::system_clock> g_start_time;

// A function that stores the current time into g_start_time;
void StoreStartTime() { g_start_time = std::chrono::system_clock::now(); }

// A function that returns the difference from the current time to
// g_start_time in seconds.
double PrintAndGetDuration() {
  auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - g_start_time);
  std::cout << "Operation took: " << diff.count() << " milliseconds"
            << std::endl;

  return diff.count();
}