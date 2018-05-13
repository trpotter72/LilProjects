#include "Application.h"
#include <string>
#include <bitset>
#include <exception>
#include <fstream>
#include "Analysis.h"
#include "DES.h"
#include <iostream>

Application::Application(string inputFile, string outputFile, char mode){
  //Parse in the input file and convert into a bitset
  ifstream inFile;
  inFile.open(inputFile);
  if(!inFile.is_open()){
    throw runtime_error((string)"Could not open file: " + inputFile);
  }
  bitset<64> inputText;
  try{
    string temp;
    inFile >> temp;
    inputText = bitset<64>(temp);
    inFile >> temp;
    key = bitset<56>(temp);
    inFile.close();
  }
  catch (const exception &e){
    throw runtime_error((string)"Could not read input file.  Incorrect format.");
  }
  if(mode == 'e'){
    //generate cipher text and run analysis on text and key mutations
    plainText = inputText;
    cipherText = DES::encrypt(plainText, key);
    textMutationResults = Analysis::textMutationAnalysis(plainText, key);
    keyMutationResults = Analysis::keyMutationAnalysis(plainText, key);
    //Write the results to the previously specified output file
    writeEncryptionResults(outputFile);
  }
  if(mode == 'd'){
    //generate cipher text and run analysis on text and key mutations
    cipherText = inputText;
    plainText = DES::decrypt(cipherText, key);
    //Write the results to the previously specified output file
    writeDecryptionResults(outputFile);
  }
}

Application::~Application(){
  delete[] textMutationResults[0];
  delete[] textMutationResults[1];
  delete[] textMutationResults[2];
  delete[] textMutationResults[3];
  delete[] textMutationResults;
  delete[] keyMutationResults[0];
  delete[] keyMutationResults[1];
  delete[] keyMutationResults[2];
  delete[] keyMutationResults[3];
  delete[] keyMutationResults;
}

void Application::writeEncryptionResults(string outputFile){
  try{
    ofstream outFile;
    outFile.open(outputFile);
    outFile << "ENCRYPTION\n";
    outFile << "Plaintext P: " << plainText << '\n';
    outFile << "Key K:" << key << '\n';
    outFile << "Ciphertext C: " << cipherText << '\n';
    outFile << "Avalanche:\n";
    outFile << "P and Pi under K\n";
    outFile << "Round\tDES0\tDES1\tDES2\tDES3\n";
    for (int i = 0; i < 17; i++){
      outFile << i << '\t' << textMutationResults[0][i] << '\t' << textMutationResults[1][i]
        <<  '\t' << textMutationResults[2][i]  << '\t' << textMutationResults[3][i] <<'\n';
    }
    outFile << "\nP under K and Ki\n";
    outFile << "Round\tDES0\tDES1\tDES2\tDES3\n";
    for (int i = 0; i < 17; i++){
      outFile << i << '\t' << keyMutationResults[0][i] << '\t' << keyMutationResults[1][i]
        <<  '\t' << keyMutationResults[2][i]  << '\t' << keyMutationResults[3][i] <<'\n';
    }
    outFile.flush();
  }
  catch(const exception &e){
    throw runtime_error((string)"Could not write output file.  Error message:\n" + e.what());
  }
}

void Application::writeDecryptionResults(string outputFile){
  try{
    ofstream outFile;
    outFile.open(outputFile);
    outFile << "DECRYPTION\n";
    outFile << "Ciphertext C: " << cipherText << '\n';
    outFile << "Key K:" << key << '\n';
    outFile << "Plaintext P: " << plainText << '\n';
    outFile.flush();
  }
  catch(const exception &e){
    throw runtime_error((string)"Could not write output file.  Error message:\n" + e.what());
  }
}
