#include "Analysis.h"
#include "DES.h"
#include "Bitset-Help.h"

int* Analysis::contrastPlainTexts(bitset<64> t1, bitset<64> t2, bitset<56> key, int function){
 bitset<64>* original = DES::encryptWithIntermediates(t1, key, function);
 bitset<64>* tweaked = DES::encryptWithIntermediates(t2, key, function);
 int* answer = new int[17];
 for(int i = 0; i < 17; i++){
   //compare the intermediates and store the number of bits different
   answer[i] = bitsDifferent(original[i], tweaked[i]);
 }
 delete[] original;
 delete[] tweaked;
 return answer;
}

int* Analysis::contrastKeys(bitset<64> text, bitset<56> k1, bitset<56> k2, int function){
 bitset<64>* original = DES::encryptWithIntermediates(text, k1, function);
 bitset<64>* tweaked = DES::encryptWithIntermediates(text, k2, function);
 int* answer = new  int[17];
 for(int i = 0; i < 17; i++){
   answer[i] = bitsDifferent(original[i], tweaked[i]);
 }
 delete[] original;
 delete[] tweaked;
 return answer;
}

int* Analysis::testTextMutations(bitset<64> text, bitset<56> key, int function){
  int* results = new int[17];
  for (int i = 0; i < 17; i++){
    results[i] = 0;
  }
  bitset<64> textEdit = text;
  int* roundResults;
  for (int i = 0; i < 64; i++){
   //flip bit in the ith position
   textEdit.flip(i);
   roundResults = contrastPlainTexts(text, textEdit, key, function);
   for (int i = 0; i < 17; i++){
     results[i] += roundResults[i];
   }
   delete[] roundResults;
   //return the originally flipped bit so that the next iteration can flip
   //the ith + 1 bit without having to recopy the original text
   textEdit.flip(i);
 }
 for (int i = 0; i < 17; i++){
   //Important to note that this is integer division, so a floor function is
   //effectively applied to the result (this may be misleading depending on what
   //you are using the results for)
   results[i] = results[i] / 64;
 }
 return results;
}

int* Analysis::testKeyMutations(bitset<64> text, bitset<56> key, int function){
  int* results = new int[17];
  for (int i = 0; i < 17; i++){
    results[i] = 0;
  }
  bitset<56> keyEdit = key;
  int* roundResults;
  for (int i = 0; i < 56; i++){
   //flip bit in the ith position
   keyEdit.flip(i);
   roundResults = contrastKeys(text, key, keyEdit, function);
   for (int i = 0; i < 17; i++){
     results[i] += roundResults[i];
   }
   delete[] roundResults;
   //return the originally flipped bit so that the next iteration can flip
   //the ith + 1 bit without having to recopy the original text
   keyEdit.flip(i);
 }
 for (int i = 0; i < 17; i++){
   results[i] = results[i] / 56;
 }
 return results;
}

int** Analysis::textMutationAnalysis(bitset<64> text, bitset<56> key){
  int** results = new int*[4];
  for (int i = 0; i< 4; i++){
    results[i] = testTextMutations(text, key, i);
  }
  return results;
}

int** Analysis::keyMutationAnalysis(bitset<64> text, bitset<56> key){
  int** results = new int*[4];
  for (int i = 0; i< 4; i++){
    results[i] = testKeyMutations(text, key, i);
  }
  return results;
}
