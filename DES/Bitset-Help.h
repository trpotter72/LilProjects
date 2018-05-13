#ifndef BITSETHELP
#define BITSETHELP

template <size_t size>
int bitsDifferent(std::bitset<size> one, std::bitset<size> two);

template <size_t size>
std::bitset<size/2>* split(std::bitset<size> orig);

//This version for an any size of slice returning a correctly sized bitset
//It's not used in the actual implementation for two reasons:
// 1) Due to the need for start and stop values to be template parameters,
//    each instance of differing stop, start, and size slices will compile
//    a new binary function (code bloat)
// 2) Having a function which looks like this 'slice<start,stop>(bits)'
//    clashes with expected design principles.
//I couldn't figure out a way to have a dynamically sized bitstring returned
//without having to also compile a new function for each new start-stop pair
template <int start, int stop, size_t size>
std::bitset<stop - start + 2> slice(std::bitset<size> bits);

//Important to note this starts on the RHS and moves left. i.e.
//slice6('1001111111',1) ='111111' NOT '001111'
template <size_t size>
std::bitset<6> slice6(std::bitset<size> bits, int start);

template <size_t size1, size_t size2>
std::bitset<size1 + size2> concat(std::bitset<size1> bits1, std::bitset<size2> bits2);

template <size_t size>
std::bitset<size> circularLeftShift(std::bitset<size> bits, int shift);

//Because bitset-help uses templated functions, the compiler will need access
//to the implementation, not just the declaration during object creation time
#include "bitset-help.hpp"
#endif
