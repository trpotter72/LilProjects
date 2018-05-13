#include <bitset>
#include <string>


//Used to compare the number of bits differing from one bitset to another
template <size_t size>
int bitsDifferent(std::bitset<size> one, std::bitset<size> two){
  int length = size;
  int count = 0;
  //Iterate through the bitsets comparing each bit
  for(int i = 0; i < size; i++){
 if(one[i] ^ two[i]){
   count++;
 }
  }
  return count;
}

//Takes one bitset of length 'size' and returns a pointer to two 'size/2' bit
//bitsets. You can access each bitset using array access operators on the result
template <size_t size>
std::bitset<size/2>* split(std::bitset<size> orig){
  std::bitset<size/2>* split = new std::bitset<size/2>[2];
  for (unsigned int bit = 0; bit < (size/2); bit++) {
    split[0][bit] = orig[bit];
    split[1][bit] = orig[bit + (size/2)];
  }
  return split;
}

template <int start, int stop, size_t size>
std::bitset<stop - start + 2> slice(std::bitset<size> bits){
  std::bitset<stop - start + 2> answer;
  for(int i = 0; i < (stop - start + 2); i++){
    answer[i] = bits [i + start];
  }
  return answer;
}

template <size_t size>
std::bitset<6> slice6(std::bitset<size> bits, int start){
  std::bitset<6> answer;
  for(int i = 0; i < 7; i++){
    answer[i] = bits [i + start];
  }
  return answer;
}


template <size_t size1, size_t size2>
std::bitset<size1 + size2> concat(std::bitset<size1> bits1, std::bitset<size2> bits2) {
  //Converts the bitsets to strings, concatenates them, and then creates a new
  //bitset from the result
  return std::bitset<size1 + size2>(bits1.to_string() + bits2.to_string());
}

//Takes bits and shifts them left a given number of spaces.  The shift given
///maybe negative for a right shift i.e. "1101" shifted 1 time = "1011"
template <size_t size>
std::bitset<size> circularLeftShift(std::bitset<size> bits, int shift){
  //recursive case for left shift
  if (shift > 0) {
    bool saveBit = bits[size-1];
    bits = (bits << 1);
    bits[0] = saveBit;
    return circularLeftShift(bits, shift - 1);
  }
  //recursive case for right shift
  else if (shift < 0) {
    bool saveBit = bits[0];
    bits = (bits >> 1);
    bits[size - 1] = saveBit;
    return circularLeftShift(bits, shift - 1);
  }
  //base case where shift = 0
  else {
    return bits;
  }
}
