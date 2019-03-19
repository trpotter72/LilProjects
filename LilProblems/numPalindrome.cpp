#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    static bool isPalindrome(int x) {
        
        if(x == 0){
            return true;
        }
        int lg = 0;
        int temp = x;
        while(temp > 0)
            temp/=10, lg++;
        
        int num[lg];
        temp = x;
        for(int i = 0; i < lg; i++){
            num[i] =temp%10;
            temp /= 10;
        }
        

        for(int i = 0; i <= lg/2; i++){
            if(num[i] != num[lg-i-1]){
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char** argv){
    if(argc != 2){
        cout << "Please provide one integer argument\n";
    }
    cout << argv[1] << '\t' << Solution::isPalindrome(atoi(argv[1])) << '\n';
}