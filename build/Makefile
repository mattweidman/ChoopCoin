crypto:
	g++ -std=c++11 -c ../src/crypto/sha256.cpp ../src/crypto/hashtests.cpp \
	&& g++ -o sha256 sha256.o hashtests.o \
	&& ./sha256 ../data/data.txt

transaction:
	g++ -std=c++11 -c ../src/transaction/utxo.cpp ../src/transaction/txntests.cpp \
	&& g++ -o txn utxo.o txntests.o \
	&& ./txn