#ifndef APPLICATION
#define APPLICATION

#include <string>
#include <bitset>

using namespace std;

class Application{
private:
  string inputFile;
  string outputFile;
  bitset<64> plainText;
  bitset<56> key;
  bitset<64> cipherText;
  //Stores testing results in 4x64 value 2d array
  int** textMutationResults;
  //Stores testing results in 4x56 value 2d array
  int** keyMutationResults;
  //Prints to the specified output file
  void writeEncryptionResults(string outputFile);
  //Prints to the specified output file
  void writeDecryptionResults(string outputFile);
public:
  //Constructor handles program operation and hands off appropriate tasks
  //to Analysis class, DES class, and writeResult functions above
  Application(string inputFile, string outputFile, char mode);
  //Responsible for cleaning up the results to limit memory leaks should
  //this code be reused later in a larger project
  ~Application();
};

#endif
