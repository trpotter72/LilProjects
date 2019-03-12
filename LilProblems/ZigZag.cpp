#include <iostream>
#include <string>

using namespace std;
class Solution {
public:
    static string convert(string s, int numRows) {
        if(numRows >= s.length() || numRows == 1){
            return s;
        }
        
        string res = string(s.length(), '_');
        int period = (numRows-1)*2;
        int place = 0;
        int row = 0;
        
        
        while(place < s.length()){
            for(int i = 0; i <= s.length()/numRows && place<s.length(); i++){
                
                if(period*i-row >= 0 && period*i-row < s.l  ength()){
                    res[place] = s[period*i - row];
                    place++;
                }

                if(row != 0 && row != numRows-1 && period*i+row < s.length()){
                    res[place] = s[period*i + row];
                    place++;
                }
                cout << "i: " << i <<"\trow: " << row << "\t" << res << endl;
            }
            row++;
        }
        return res;
        
    }
};

/*

P A Y P A L I S H I R  I  N  G
0 1 2 3 4 5 6 7 8 9 10 11 12 13
    
0           6             12     n = 4
  1       5   7        11    13
    2   4       8   10 

0 6 12 1 5 7 11 13 2 4 8 10
    
((period * i)+row)-+1 -->
    
    
0       4       8         12     n = 3

*/

int main(int argc, char** argv){
    if(argc != 3){
        exit(1);
    }
    else{
        cout << argv[1] << endl << Solution::convert(argv[1], stoi(argv[2])) << endl;
    }
}
