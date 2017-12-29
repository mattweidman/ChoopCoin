#ifndef CHOOP_TRANSACTION_H
#define CHOOP_TRANSACTION_H

#include <string>
#include <vector>

#include "utxo.h"

class TxnInput : Serializable {

  private:
    /** Unspent transaction: public key + denomination */
    UTXO utxo;
    /** Signature of UTXO that can be verified using key */
    std::string signature;

  public:
    /**
     * utxo: unspent transaction output for this input
     * signature: signature of utxo
     */
    TxnInput(UTXO utxo, std::string signature);

    /** Get UTXO of input */
    UTXO getUTXO();

    /** Get signature of utxo */
    std::string getSignature();

    /** Convert to string */
    std::string serialize();

    /** 
     * Verify the following:
     * - transaction is signed by holder of public key
     * - denomination > 0
     */
    bool verify();

};

class Transaction {

  private:
    /** List of inputs */
    std::vector<TxnInput> inputs;
    /** List of outputs */
    std::vector<UTXO> outputs;

  public: 
    /** Add to list of donors */
    void addInput(TxnInput);

    /** Add to list of recipients */
    void addOutput(UTXO);

    /** Convert to string */
    std::string serialize();

};

#endif // CHOOP_TRANSACTION_H