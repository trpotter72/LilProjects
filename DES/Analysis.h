#ifndef ANALYSIS
#define ANALYSIS

#include <bitset>

using namespace std;

class Analysis {
private:
  //Contrasts input text blocks at each round of encryption using the
  //corresponding round function.  Returns a pointer to a 17-value array with
  //the number of bits different on the ith round in the ith position
  static int* contrastPlainTexts(bitset<64> t1, bitset<64> t2, bitset<56> key, int function);

  //Given two different input keys, compares the resulting differences in the
  //intermediate ciphertexts.  Returns a pointer to a 17-value array with
  //the number of bits different on the ith round in the ith position
  static int* contrastKeys(bitset<64> text, bitset<56> k1, bitset<56> k2, int function);

  //Compares the differences in each intermediate step for all 64
  //1-bit-different starting texts
  static int* testTextMutations(bitset<64> text, bitset<56> key, int function);

  //Compares differences in each intermediate step for all 56 different
  //1-bit-different starting keys.  Values are averaged and returned as length
  //17 array
  static int* testKeyMutations(bitset<64> text, bitset<56> key, int function);

public:
  //Calls and stores results from testTextMutations() for each of the 4
  //round functions.  Returns a 2D array where int[function#][round#]
  static int** textMutationAnalysis(bitset<64> text, bitset<56> key);

  //Calls and stores results from testKeyMutations() for each of the 4
  //round functions.  Returns a 2D array where int[function#][round#]
  static int** keyMutationAnalysis(bitset<64> text, bitset<56> key);

};


#endif
