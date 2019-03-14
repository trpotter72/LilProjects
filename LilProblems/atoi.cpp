#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Solution {
public:
   static int myAtoi(string& s){
        long res = 0;
        bool isNeg = false;
        int i = 0;
        int len = s.length();
        while(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'){
            i++; //ignore whitespace
        }

        if(s[i] == '-'){
            isNeg = true;
            i++;
        }
        else if(s[i] == '+'){
            i++;
        }

        try{
            while(s[i] < 58 && s[i] > 47 && i < len){
                //s[i] is a numeral and we're in bounds of the string
                res *= 10;
                res += s[i]-48;
                i++;
                if(res < INT8_MIN || res > INT8_MAX){
                    throw "Error";
                }
            }
        }
       catch(...){
           if(isNeg){
               return INT8_MIN;
           }
           else{
               return INT8_MAX;
           }
       }
        if(isNeg){
            res*=-1;
        }
        return res;
    }
};

int main(int argc, char** argv){
    if(argc != 2){
        cout << "Please provide one string argument to convert to an int\n";
    }
    string s = argv[1];
    
    cout << s << '\t'<< Solution::myAtoi(s) << '\n';
}