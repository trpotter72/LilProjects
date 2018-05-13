#include "DES.h"
#include <string>
#include "Bitset-Help.h"

using namespace std;

//Must use constexpr to allow static functions, allows for compiler optimization
//and not recreate variables for each instance of DES object
constexpr int DES::INIT_PERMUTATION[64];

constexpr int DES::INV_INIT_PERMUTATION[64];

constexpr int DES::EXPANSION[48];

constexpr int DES::INV_EXPANSION[32];

constexpr int DES::SBOX[8][4][16];

constexpr int DES::PERMUTATION[32];

constexpr int DES::KEY_SHIFT[16];

constexpr int DES::KEY_PERMUTATION[48];

/*******************************************************************************
--------------------------------Private Functions-------------------------------
*******************************************************************************/

bitset<64> DES::initialPermutation(bitset<64> orig){
  bitset<64> permuted;
  for (int bit = 0; bit < 64; bit++){
    permuted[63 - bit] = orig[63 - (INIT_PERMUTATION[bit] - 1)];
  }
  return permuted;
}

bitset<64> DES::finalPermutation(bitset<64> orig){
  bitset<64> permuted;
  for (int bit = 0; bit < 64; bit++){
 permuted[63 - bit] = orig[63 - (INV_INIT_PERMUTATION[bit] - 1)];
  }
  return permuted;
}

bitset<48> DES::keyPermutation(bitset<56> orig){
  bitset<48> permuted;
  for (int bit = 0; bit < 48; bit++){
    permuted[47 - bit] = orig[55 - (KEY_PERMUTATION[bit] - 1)];
  }
  return permuted;
}

bitset<48>* DES::createSubkeys(bitset<56> key){
  //Split the key into right and left halves
  bitset<28>* initialBlocks = split(key);
  //generate all blocks through shifting each round of keys
  bitset<28> leftBlocks[16];
  bitset<28> rightBlocks[16];
  leftBlocks[0] = circularLeftShift(initialBlocks[1], KEY_SHIFT[0]);
  rightBlocks[0] = circularLeftShift(initialBlocks[0], KEY_SHIFT[0]);
  for(int i = 1; i < 16; i++){
    leftBlocks[i] = circularLeftShift(leftBlocks[i-1], KEY_SHIFT[i]);
    rightBlocks[i] = circularLeftShift(rightBlocks[i-1], KEY_SHIFT[i]);
  }
  //Concat the two halves together and then permute
  bitset<48>* subkeys;
  subkeys = new bitset<48>[16];
  for(int i = 0; i < 16; i++){
    bitset<56> combined = concat(leftBlocks[i],rightBlocks[i]);
    subkeys[i] = keyPermutation(combined);
  }
  delete[] initialBlocks;
  //return array of 16 subkeys
  return subkeys;
}

bitset<48> DES::roundExpand(bitset<32> orig){
  bitset<48> expanded;
  for (int bit = 0; bit < 48; bit++){
 expanded[47 - bit] = orig[31 - (EXPANSION[bit] - 1)];
  }
  return expanded;
}

bitset<32> DES::roundInvExpand(bitset<48> orig){
  bitset<32> condensed;
  for (int bit = 0; bit < 32; bit++){
 condensed[31 - bit] = orig[47 - (INV_EXPANSION[bit] - 1)];
  }
  return condensed;
}

bitset<4> DES::roundSBoxSub(int boxNum, bitset<6> orig){
  //Given X _ _ _ _ Y as a bitstring, set row to XY
  bitset<2> row;
  row[0] = orig[0];
  row[1] = orig[5];
  //Given _ W X Y Z _ as a bitstring, set col to WXYZ
  bitset<4> col;
  col[0] = orig[1];
  col[1] = orig[2];
  col[2] = orig[3];
  col[3] = orig[4];
  //Look up the replacement value from the inputed S-Box
  bitset<4> answer(SBOX[boxNum - 1][row.to_ulong()][col.to_ulong()]);
  return answer;
}

bitset<32> DES::roundPermutation(bitset<32> orig){
  bitset<32> permuted;
  for (int bit = 0; bit < 32; bit++){
 permuted[31 - bit] = orig[ 31 - (PERMUTATION[bit] - 1)];
  }
  return permuted;
}

bitset<32> DES::roundFunction0(bitset<32> orig, bitset<48> key){
  //Initial expansion
  bitset<48> expanded = roundExpand(orig);

  //XOR with key
  expanded = expanded ^ key;

  //S-Box condesing from 48 to 32 bits
  for(int i = 0; i < 8; i++){
    //note that the odd arithmetic is due to bitset array access [] working with
    //LSB being in [0].  This is the reverse of how many of the operations in
    //DES view ordering (Sboxes increase left to right, permutations, etc.)
    bitset<4> temp = roundSBoxSub(i+1, slice6(expanded,6*(7-i)));
    orig[(4*(7-i)) + 3] = temp[3];
    orig[(4*(7-i)) + 2] = temp[2];
    orig[(4*(7-i)) + 1] = temp[1];
    orig[(4*(7-i)) + 0] = temp[0];
  }
  //end of round permutation
  return roundPermutation(orig);
}

bitset<32> DES::roundFunction1(bitset<32> orig, bitset<48> key){
  bitset<48> expanded = roundExpand(orig);
  expanded = expanded ^ key;
  for(int i = 0; i < 8; i++){
    bitset<4> temp = roundSBoxSub(i+1, slice6(expanded,6*(7-i)));
    orig[(4*(7-i)) + 3] = temp[3];
    orig[(4*(7-i)) + 2] = temp[2];
    orig[(4*(7-i)) + 1] = temp[1];
    orig[(4*(7-i)) + 0] = temp[0];
  }
  //Note the lacking roundPermutation() when compared to DES0 above
  return orig;
}

bitset<32> DES::roundFunction2(bitset<32> orig, bitset<48> key){
  bitset<48> expanded = roundExpand(orig);
  expanded = expanded ^ key;
  //Using the inverse expansion function rather than S-boxes
  orig = roundInvExpand(expanded);
  return roundPermutation(orig);
}

bitset<32> DES::roundFunction3(bitset<32> orig, bitset<48> key){
  bitset<48> expanded = roundExpand(orig);
  expanded = expanded ^ key;
  //Using the inverse expansion function rather than S-boxes
  orig = roundInvExpand(expanded);
  //and omitting the final permutation
  return orig;
}

bitset<64>* DES::privateEncryptWithIntermediates(bitset<64> plainText, bitset<56> key, bitset<32> (*roundFunction)(bitset<32>, bitset<48>)){
  bitset<64>* intermediates = new bitset<64>[17];
  plainText = initialPermutation(plainText);
  //Split the input into left and right blocks
  bitset<32> left = split(plainText)[1], right = split(plainText)[0];
  //Used to hold intermediate values while the left and right side swap between rounds
  bitset<32> temp;
  //Generation of 16 subkeys (one for each round)
  bitset<48>* subkey = createSubkeys(key);
  for (int round = 0; round < 16; round++){
    intermediates[round] = concat(left, right);
    temp = right;
    //R[i] = L[i-1] XOR f(R[i-1],K[i])
    right = left ^ roundFunction(right, subkey[round]);
    //L[i] = R[i-1]
    left = temp;
  }
  delete[] subkey;
  plainText = concat(right, left);
  plainText = finalPermutation(plainText);
  intermediates[16] = plainText;
  return intermediates;
}

bitset<64> DES::privateEncrypt(bitset<64> plainText, bitset<56> key, bitset<32> (*roundFunction)(bitset<32>, bitset<48>)){
  bitset<64>* intermediates = privateEncryptWithIntermediates(plainText, key, roundFunction);
  bitset<64> answer = intermediates[16];
  delete[] intermediates;
  return (answer);
}

/*******************************************************************************
--------------------------------Public Functions--------------------------------
*******************************************************************************/

bitset<64>* DES::encryptWithIntermediates(bitset<64> plainText,bitset<56> key, int function){
  switch (function) {
    case 0: return (privateEncryptWithIntermediates(plainText, key, roundFunction0));
            break;
    case 1: return (privateEncryptWithIntermediates(plainText, key, roundFunction1));
            break;
    case 2: return (privateEncryptWithIntermediates(plainText, key, roundFunction2));
            break;
    case 3: return (privateEncryptWithIntermediates(plainText, key, roundFunction3));
            break;
    default: throw("Invalid encryption function passed to encryptWithIntermediates");
              break;
  }
  return nullptr;
}

bitset<64> DES::encrypt(bitset<64> plainText, bitset<56> key, int function){
  switch (function) {
    case 0: return (privateEncrypt(plainText, key, roundFunction0));
            break;
    case 1: return (privateEncrypt(plainText, key, roundFunction1));
            break;
    case 2: return (privateEncrypt(plainText, key, roundFunction2));
            break;
    case 3: return (privateEncrypt(plainText, key, roundFunction3));
            break;
    default: throw("Invalid encryption function passed to encrypt");
              break;
  }
}

bitset<64> DES::decrypt(bitset<64> cipherText, bitset<56> key){
    cipherText = initialPermutation(cipherText);
    //Split the input into left and right blocks
    bitset<32> left = split(cipherText)[1], right = split(cipherText)[0];
    //Used to hold intermediate values while the left and right side swap between rounds
    bitset<32> temp;
    //Generation of 16 subkeys (one for each round)
    bitset<48>* subkey = createSubkeys(key);
    for (int round = 0; round < 16; round++){
      temp = right;
      //R[i] = L[i-1] XOR f(R[i-1],K[i])
      right = left ^ roundFunction0(right, subkey[15 - round]); //keys used in reverse here
      //L[i] = R[i-1]
      left = temp;
    }
    delete[] subkey;
    cipherText = concat(right, left);
    cipherText = finalPermutation(cipherText);
    return cipherText;
  }
