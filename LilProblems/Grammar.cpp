#include <iostream>
#include <string>

using namespace std;

string generateNHelp(int n, string& s){
    string next = string(2*s.length(), '_');
    if(n == 1){
        return s;
    }
    else if(n < 1){
        return "ERROR";
    }
    else{
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '0'){
                next[i*2] = '0';
                next[i*2+1]='1';
            }
            else if(s[i] == '1'){
                next[i*2] = '1';
                next[i*2+1]='0';
            }
        }
        return generateNHelp(n-1,next);
    }
}

u_int get_floor_pow2(u_int val){
    u_int places = 0;
    while(val >>= 1){ //shift right until zero
        places++;
    }
    return (1 << places);
}

bool generateN(int n){
    if(n == 1){
        return false;
    }
    else{
        return !generateN(n - get_floor_pow2(n-1));
    }
}

int main(int argc, char** argv){
    if(argc == 2){
        string s = "0";
        string result = generateNHelp(stoi(argv[1]), s);

        for(int i = 1; i < result.length(); i++){
            bool gen = generateN(i);
            bool passed = (result[i-1] == (gen ? '0' : '1'));
            cout << "i: " << i << "\tGen: " << gen << "\tReal: " << result[i-1] << (passed ? "\tFailed\n" : "\tSuccess\n");
        }
    }
}