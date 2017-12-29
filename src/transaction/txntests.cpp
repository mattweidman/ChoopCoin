#include <assert.h>
#include <iostream>

#include "utxo.h"

/**
 * Give a meaningful output then throw an assertion error.
 * expected: expected value
 * computed: computed value
 * name: name of test
 */
template <class T>
void assertFalse(T expected, T computed, std::string name) {
  std::cout << "Test: " << name << std::endl;
  std::cout << "Expected: " << expected << std::endl;
  std::cout << "but got: " << computed << std::endl;
  assert(false);
}

/**
 * Assert whether 2 strings are equal and give meaningful output.
 * expected: expected string
 * computed: computed string
 * name: name of test
 */
void assertStrs(std::string expected, std::string computed, std::string name) {
  if (expected.compare(computed) != 0) assertFalse(expected, computed, name);
}

/**
 * Assert whether 2 values are equal and give meaningful output.
 * expected: expected value
 * computed: computed value
 * name: name of test
 */
template <class T>
void assertVals(T expected, T computed, std::string name) {
  if (expected != computed) assertFalse(expected, computed, name);
}

/**
 * Assert whether 2 values are within a certain range of each other.
 * expected: expected value
 * computed: computed value
 * name: name of test
 * diff: minimum difference between values that throws an assertion error
 */
template <class T>
void assertValsInRange(T expected, T computed, std::string name, T diff) {
  T obs_diff = expected - computed;
  if (obs_diff < 0) obs_diff *= -1;
  if (obs_diff > diff) assertFalse(expected, computed, name);
}

int main() {
  double delta = 0.0000001;

  // test UTXO
  UTXO u("public_key", 53.294);
  assertStrs("public_key:53.294", u.serialize(), "utxo");
  assertStrs("public_key", u.getKey(), "utxo");
  assertValsInRange(53.294, u.getDenomination(), "utxo", delta);

  std::cout << "All tests successful" << std::endl;
}