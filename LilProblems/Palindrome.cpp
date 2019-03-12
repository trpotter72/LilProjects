#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution{

    public:

    static string longestPalindrome(const string& s){
        int len = s.length();
        if(len == 0)
            return "";
        else if(len == 1)
            return s;

        bool palindrome[len][len];
        for(int kayli = 0;kayli< len;kayli++){
            for(int mylah = 0;mylah< len;mylah++){
                palindrome[kayli][mylah] = false;
            }
        }

        int x = 0,y = 0;
        for(int i = 0; i < len; i++){
            palindrome[i][i] = true;
        }
        for(int i = 0; i < len; i++){
            if(s[i] == s[i+1])
                palindrome[i][i+1] = true;
                x = i;
                y = i + 1;
        }
        bool found = true;
        int size = 2;
        while(size < len){
            size++;
            found = false;
            for(int i = 0; i < len-size+1; i++){
                if(palindrome[i+1][i+size-2] && s[i] == s[i+size-1]){
                    found = true;
                    palindrome[i][i+size-1] = true;
                    x = i;
                    y = i + size -1;
                }
            }   
        }
        return s.substr(x,y-x+1);
    }
};

int main(int argc, char** argv){
    if(argc != 2){
        exit(0);
    }
    string pal = argv[1];
    cout << pal << endl;
    cout << Solution::longestPalindrome(pal) << endl;
}