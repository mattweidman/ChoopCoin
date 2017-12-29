#ifndef CHOOP_SERIALIZABLE_H
#define CHOOP_SERIALIZABLE_H

#include <string>

/**
 * A Serializable object is an object whose data can be
 * converted to a string that can be hashed or transmitted.
 */
class Serializable {

  public:
    /** Convert object to string. */
    virtual std::string serialize() = 0;

};

#endif // CHOOP_SERIALIZABLE_H