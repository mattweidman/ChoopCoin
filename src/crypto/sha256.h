#ifndef CHOOP_SHA256_H
#define CHOOP_SHA256_H

#include <string>

namespace Sha256 {
  
  /**
   * Takes the SHA-256 hash of a string.
   */
  std::string hash(std::string data);
  
}

#endif // CHOOP_SHA256_H_