#include <string>
#include <bitset>
#include <iostream>
#include <fstream>
#include <exception>
#include "Bitset-Help.h"
#include "DES.h"
#include "Analysis.h"
#include "Application.h"


using namespace std;

int main(int argc, char** argv) {
  try {
    //Check to see if the user inputted either 2 or 3 additional args
    if(argc <=2 || argc >= 5){
      throw runtime_error((string)"Please use input and output file names as command line "
        + "arguments. An optional \'-d\' or \'-e\' to specify decryption or "
        + "encryption (encryption is assumed by default)");
    }

    //Assign 1st arg to input file, and 2nd to output file
    string input, output;
    string mode = "e";  //default the mode of operation to encryption
    input = argv[1];
    output = argv[2];
    //If the user inputted a mode of operation char, set mode to that value
    if(argc == 4){
      mode = argv[3];
    }

    //Run ecryption mode of application
    if (mode == "e" || mode == "E" || mode == "-e" || mode == "-E" ||
      mode == "encrypt" || mode == "Encrypt" || mode == "-encrypt" ||
      mode == "-Encrypt"){
        Application run(input, output, 'e');
      }

    //Run decryption mod of application
    else if (mode == "d" || mode == "D" || mode == "-d" || mode == "-D" ||
        mode == "decrypt" || mode == "Decrypt" || mode == "-decrypt" ||
        mode == "-Decrypt"){
          Application run(input, output, 'd');
        }
        
    //This occurs when the user has entered a mode which does not match with
    //the above options
    else {
    throw runtime_error((string)"The operation mode inputted: \'" + mode +
                    "\' should be either \'-d\' for decryption or \'-e\' for " +
                    "encryption\n");
    }
  }
  //Catch any errors which weren't dealt with deeper down in the program and
  //report them to the console
  catch (const exception &e){
    cout << e.what() << endl;
  }
}
