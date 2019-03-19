#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


template <typename T>
string printVec(vector<T>& v){
    stringstream ss;
    ss << '{';
    for(int i = 0; i < v.size(); i++){
        ss << v[i];
        if(i == v.size()-1){
            ss << '}';
        }
        else{
            ss << ", ";
        }
    }
    return ss.str();
}

vector<vector<char>> test1 = {{'.','.','.','.','.','.','.','.','.'},
                              {'.','.','.','.','.','.','.','.','.'},
                              {'.','9','.','.','.','.','.','.','1'},
                              {'8','.','.','.','.','.','.','.','.'},
                              {'.','9','9','3','5','7','.','.','.'},
                              {'.','.','.','.','.','.','.','4','.'},
                              {'.','.','.','8','.','.','.','.','.'},
                              {'.','1','.','.','.','.','4','.','9'},
                              {'.','.','.','5','.','4','.','.','.'}};

class Solution {
public:
    vector<int> v = vector<int>(9,0);
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int i = 0; i < 9; i++){
            if(!checkRow(board,i))
                return false;
            if(!checkCol(board,i))
                return false;
        }
        
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++)
                if(!checkSquare(board,i*3,j*3))
                    return false;
        }
        return true;
    }
    
    void clear(vector<int>& v){
        for(int& i : v)
            i = 0;
    }
    
    bool checkSquare(vector<vector<char>>& board, int x, int y){
        char temp;
        //cout << endl << "x: " << x << "\ty: " << y << endl;
        for(int i = x; i < x+3; i++){
            for(int j = y; j < y+3; j++){
                //cout << "i: " << i << "\tj: " << j << '\t' << printVec(v) << '\n';
                temp = board[i][j] - '0';
                if(temp < 9 && temp >= 0)
                    if((v[temp]) == 1){
                        //cout << "Returing false" << endl;
                        return false;
                    }
                    else{
                        v[temp] += 1;   
                    }
            }
        }
        clear(v);
        return true;
    }
    
    bool checkCol(vector<vector<char>>& board, int x){
        char temp;
        
        //cout << "x: " << x << '\n';
        
        for(int i = 0; i < 9; i ++){
            //cout << i << ' ';
            temp = board[i][x] - '0';
            if(temp < 9 && temp >= 0)
                if( (v[temp]) == 1){
                    //cout << "Return false\n";
                    return false;
                }
                else{
                    v[temp] += 1;
                }
        }
        ////cout << "\n\n";
        clear(v);
        return true;
    }
    
    bool checkRow(vector<vector<char>>& board, int x){
        char temp;
        
        ////cout << "y: " << x << '\n';
        
        for(int i = 0; i < 9; i ++){
            //cout << i << ' ';
            temp = board[x][i] - '0';
            if(temp < 9 && temp >= 0)
                if((v[temp]) == 1){
                    //cout << "Return false\n";
                    return false;
                }
                else{
                    v[temp] += 1;
                }
        }
        //cout << "\n\n";
        clear(v);
        return true;
    }
};

int main(int argc, char** argv){

    Solution s;
    cout << int('0') << int('9');
    cout << "Result: " << (s.isValidSudoku(test1) ? "Sucess" : "Failure") << endl;


}