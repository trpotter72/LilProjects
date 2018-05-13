Classes:
  -Application
  -Analysis
  -DES
  -Bitset-Help

--Application--
This class is intended to be a high level control class.  First, input is read
from the file name provided in the constructor and assigned to member variables.
It calls functions from the Analysis class and DES class to generate the data,
and then writes the formatted data to the output file specified in the
constructor.

--Analysis--
This class works as an interface to collect the differing bits during each phase
of DES encryption.  This data is compiled then averaged.  Finally it is returned
as an array of easy to access integers.  There are functions for the analysis of
the avalanche effect on both key and plaintext.

--DES--
This is a direct implementation on the DES system.  In addition to normal
operation, there are 3 edited round functions which can be used in place of the
standard mode of operation.  There is also the ability to return not just the
cipher text, but also all intermediate texts generated after each round of
encipherment.  A decrypt function is also included, but it is only implemented
for the standard DES round function.

--Bitset-Help--
While not technically a class, it is a set of template functions used to extend
the functionality of the std::bitset class.  These help to simplify the code
found inside of the DES class.
