#ifndef CHOOP_UTXO_H
#define CHOOP_UTXO_H

#include <string>

#include "serializable.h"

/**
 * Unspent transaction output. Contains a public
 * key and a denomination. 
 */
class UTXO : Serializable {

  private:
    /** Public key of from account */
    std::string key;
    /** Amount transferred */
    double denomination;

  public:
    /**
     * user: public key of paying account
     * denom: amount transferred
     */
    UTXO(std::string user, double denom);

    /**
     * Convert to string containing public key and
     * denomination.
     */
    std::string serialize() override;

};

#endif //CHOOP_UTXO_H