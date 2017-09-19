#pragma once

#define ELPP_THREAD_SAFE
#define ELPP_CUSTOM_COUT std::cerr
#define ELPP_STL_LOGGING
#define ELPP_LOG_STD_ARRAY
#define ELPP_LOG_UNORDERED_MAP
#define ELPP_LOG_UNORDERED_SET
#define ELPP_DISABLE_DEFAULT_CRASH_HANDLING
#define ELPP_WINSOCK2
#define ELPP_FEATURE_CRASH_LOG

#include <string>
#include <vector>

#include <easylogging++.h>

namespace vertexai {

// Returns a log configuration built from the command line flags passed to the
// program.  This should be only be used after command line flag parsing is
// complete.
el::Configurations LogConfigurationFromFlags(const std::string& app_name);
}  // namespace vertexai

#define IVLOG(N, rest)   \
  do {                   \
    if (VLOG_IS_ON(N)) { \
      VLOG(N) << rest;   \
    }                    \
  } while (0);

// printf style logging
#define PIVLOG(N, ...)                                            \
  do {                                                            \
    if (VLOG_IS_ON(N)) {                                          \
      el::Loggers::getLogger("default")->verbose(N, __VA_ARGS__); \
    }                                                             \
  } while (0);

// VLOGs and writes to a stream.
#define SVLOG(s, N, rest) \
  do {                    \
    if (VLOG_IS_ON(N)) {  \
      VLOG(N) << rest;    \
    }                     \
    s << rest << "\n";    \
  } while (0);

template <class IT>
std::string stringify_collection(IT begin, IT end) {
  using std::to_string;
  std::string r = "{ ";
  while (begin != end) {
    r += to_string(*begin);
    begin++;
    if (begin != end) {
      r += ", ";
    }
  }
  r += "}";
  return r;
}

namespace std {

inline std::string to_string(const std::string& x) { return x; }

template <class T>
std::string to_string(const std::vector<T>& x) {
  return stringify_collection(x.begin(), x.end());
}

}  // namespace std
