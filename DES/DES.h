#ifndef DATA_ENCRYPTION_STANDARD
#define DATA_ENCRYPTION_STANDARD

#include <bitset>

using namespace std;

class DES {

/*******************************************************************************
--------------------------------Private Constants-------------------------------
*******************************************************************************/
private:
  constexpr static int INIT_PERMUTATION[64] =
    {58,	50,	42,	34,	26,	18,	10,	2,
     60,	52,	44,	36,	28,	20,	12,	4,
     62,	54,	46,	38,	30,	22,	14,	6,
     64,	56,	48,	40,	32,	24,	16,	8,
     57,	49,	41,	33,	25,	17,	9,	1,
     59,	51,	43,	35,	27,	19,	11,	3,
     61,	53,	45,	37,	29,	21,	13,	5,
     63,	55,	47,	39,	31,	23,	15,	7};

  constexpr static int INV_INIT_PERMUTATION[64] =
   {40,	8,	48,	16,	56,	24,	64,	32,
    39,	7,	47,	15,	55,	23,	63,	31,
    38,	6,	46,	14,	54,	22,	62,	30,
    37,	5,	45,	13,	53,	21,	61,	29,
    36,	4,	44,	12, 52,	20,	60,	28,
    35,	3,	43,	11,	51,	19,	59,	27,
    34,	2,	42,	10,	50,	18,	58,	26,
    33,	1,	41,	9,	49,	17,	57,	25};

  constexpr static int EXPANSION[48] =
    {32,	1,	2,	3,	4,	5,
     4,	  5,	6,	7,	8,	9,
     8, 	9,	10,	11,	12,	13,
     12,	13,	14,	15,	16,	17,
     16,	17,	18,	19,	20,	21,
     20,	21,	22,	23,	24,	25,
     24,	25,	26,	27,	28,	29,
     28,	29,	30,	31,	32,	1};

  constexpr static int INV_EXPANSION[32] =
    {2, 3, 4, 5,
     8, 9, 10, 11,
     14, 15, 16, 17,
     20, 21, 22, 23,
     26, 27, 28, 29,
     32, 33, 34, 35,
     38, 39, 40, 41,
     44, 45, 46, 47};

  constexpr static int SBOX[8][4][16] = {
   //S-Box 1
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
   //S-Box 2
    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
     {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
     {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
     {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
   //S-Box 3
    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
     {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
     {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
     {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
   //S-Box 4
    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
     {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
     {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
     {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
   //S-Box 5
    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
     {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
     {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
     {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
   //S-Box 6
    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
     {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
     {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
     {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
   //S-Box 7
    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
     {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
     {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
     {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
   //S-Box 8
    { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
      {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
      {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
      {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
  };

  constexpr static int PERMUTATION[32] =
    {16,  7,  20, 21, 29, 12, 28, 17,
      1,  15, 23, 26, 5,  18, 31, 10,
      2,  8,  24, 14, 32, 27,  3, 9,
      19, 13, 30, 6,  22, 11,  4, 25};

  constexpr static int KEY_SHIFT[16] =
    { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

  constexpr static int KEY_PERMUTATION[48] =
    { 14, 17, 11, 24, 1,  5,
      3,  28, 15, 6,  21, 10,
      23, 19, 12, 4,  26, 8,
      16, 7,  27, 20, 13, 2,
      41, 52, 31, 37, 47, 55,
      30, 40, 51, 45, 33, 48,
      44, 49, 39, 56, 34, 53,
      46, 42, 50, 36, 29, 32};

/*******************************************************************************
--------------------------------Private Functions-------------------------------
*******************************************************************************/

  //Returns a bitset with the original bits permuted according to the initial
  //permutation.  Depends on INIT_PERMUTATION
  static bitset<64> initialPermutation(bitset<64> orig);

  //The inverse of the initial permutation.  Depends on INV_INIT_PERMUTATION
  static bitset<64> finalPermutation(bitset<64> orig);

  //The permutation that all subkeys undergo to reduce the length from 56-bits
  //to 48-bits.  Depends on KEY_PERMUTATION.
  static bitset<48> keyPermutation(bitset<56> orig);

  //Given a 56-bit key, create 16 round keys, each 48 bits in length
  static bitset<48>* createSubkeys(bitset<56> key);

  //Expands the 32-bit half block into a 48-bit block.  Depends on EXPANSION
  static bitset<48> roundExpand(bitset<32> orig);

  //The inverse of the expand function above, depends on the global const
  //INV_EXPANSION
  static bitset<32> roundInvExpand(bitset<48> orig);

  //Substitute a 6-bit input with a 4-bit output from the selected s-box (1-8)
  static bitset<4> roundSBoxSub(int boxNum, bitset<6> orig);

  //Returns a bitset with the original bits permuted according to the round
  //permutation.  Depends on the global const PERMUTATION
  static bitset<32> roundPermutation(bitset<32> orig);

  //The round function used in typical DES operation
  static bitset<32> roundFunction0(bitset<32> orig, bitset<48> key);

  //DES round function without final permutation
  static bitset<32> roundFunction1(bitset<32> orig, bitset<48> key);

  //DES round function using the inverse of the expansion function in place of
  //S-boxes
  static bitset<32> roundFunction2(bitset<32> orig, bitset<48> key);

  //DES round function using the inverse of the expansion function in place of
  //S-boxes and omitting the final permutation
  static bitset<32> roundFunction3(bitset<32> orig, bitset<48> key);

  //Produces an array of 17 64-bit bitsets.  Each is the message as it undergoes
  //each successive round of DES.  The 0th element is the input message while the
  //16th element is the encrypted message.
  static bitset<64>* privateEncryptWithIntermediates(bitset<64> plainText, bitset<56> key, bitset<32> (*roundFunction)(bitset<32>, bitset<48>));

  //Returns just the 64-bit bitset of encrypted text when given text, key, and
  //round function pointer (public facing version has option round specification
  //as an int rather than a function pointer)
  static bitset<64> privateEncrypt(bitset<64> plainText, bitset<56> key, bitset<32> (*roundFunction)(bitset<32>, bitset<48>));

/*******************************************************************************
--------------------------------Public Functions--------------------------------
*******************************************************************************/

public:
  //encryption which returns an array on intermediates.  Wrapper for the private
  //function which requires a function pointer
  static bitset<64>* encryptWithIntermediates(bitset<64> plainText, bitset<56> key, int function = 0);

  //Public facing encryption function, returns only the 64-bit bitset of the
  //cipher text
  static bitset<64> encrypt(bitset<64> plainText, bitset<56> key, int function = 0);

  //Public facing decryption function, the same as the encryption function, but
  //with the subkeys generated used in reverse
  static bitset<64> decrypt(bitset<64> cipherText, bitset<56> key);


};

#endif
