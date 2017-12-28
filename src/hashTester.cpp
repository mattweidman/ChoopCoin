#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "sha256.h"

/** Returns the contents of the file at path [fileName]. */
std::string getFileContents(std::string fileName) {
  std::ifstream inFile;

  // open file
  inFile.open(fileName.data());
  if (!inFile) {
    std::cerr << "Unable to open " + fileName + "\n";
    exit(1);
  }

  // create buffer
  inFile.seekg(0, inFile.end);
  int bufLength = inFile.tellg();
  char* buffer = new char[bufLength];

  // read whole file
  inFile.seekg(0, inFile.beg);
  inFile.read(buffer, bufLength);

  inFile.close();

  // convert to vector
  return std::string(buffer);
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cout << "Wrong number of arguments: " << argc-1 << std::endl;
    std::cout << "Requires name of file to be hashed" << std::endl;
    exit(1);
  }
  std::string contents = getFileContents(argv[1]);
  std::cout << Sha256::hash(contents) << std::endl;
}