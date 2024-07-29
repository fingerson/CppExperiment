#include <utils.h>

namespace utils {
  int add2 (int a, int b) {
    return a+b;
  }
  
  void log(const std::string &message) {
    std::cout << message << std::endl;
  }

  void exitWithError( const std::string &errorMessage) {
    log("ERROR: " + errorMessage);
    exit(1);
  }
}