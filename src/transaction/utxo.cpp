#include <sstream>
#include <string>

#include "serializable.h"
#include "utxo.h"

UTXO::UTXO(std::string user, double denom) {
  key = user;
  denomination = denom;
}

std::string UTXO::getKey() {
  return key;
}

double UTXO::getDenomination() {
  return denomination;
}

std::string UTXO::serialize() {
  std::ostringstream oss;
  oss << denomination;
  std::string denom_str = oss.str();

  return key + ":" + denom_str;
}