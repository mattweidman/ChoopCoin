#include <assert.h>
#include <iostream>

#include "utxo.h"

/**
 * Assert whether 2 strings are equal and give meaningful output.
 * expected: expected string
 * computed: computed string
 */
void assert_strs(std::string expected, std::string computed) {
  if (expected.compare(computed) != 0) {
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "but got: " << computed << std::endl;
    assert(false);
  }
}

/**
 * Assert whether 2 strings are equal and give meaningful output.
 * expected: expected string
 * computed: computed string
 * name: name of test
 */
void assert_strs(std::string expected, std::string computed, std::string name) {
  std::cout << "Test: " << name << std::endl;
  assert_strs(expected, computed);
}

int main() {
  // test UTXO
  UTXO u("public_key", 53.294);
  assert_strs("public_key:53.294", u.serialize(), "utxo");

  std::cout << "All tests successful" << std::endl;
}