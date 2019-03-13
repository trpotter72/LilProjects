#include <iostream>

using namespace std;

//123 -> 321
int reverseInt(int i){
    int res = 0;
    while(i != 0){
        res*=10;
        res+=i%10;
        i/=10;
    }
    return res;
}

int main(int argc, char** argv){
    if(argc != 2){
        cout << "Please provide 1 integer argument\n";
        return 1;
    }
    cout << reverseInt(stoi(argv[1])) << '\n';
    return 0;
}