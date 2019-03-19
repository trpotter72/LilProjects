class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        for(int( i = 0; i < s.length(); i++)){
            res+=getValue(s,i);
        }
        return res;
    }

    int getValue(const string& s, int pos){
        if(pos >= s.length()-1){
            switch(s[pos]){
                case 'I':
                    return 1;
                    break;
                case 'V':
                    return 5;
                    break;
                case 'X':
                    return 10;
                    break;
                case 'L':
                    return 50;
                    break;
                case 'C':
                    return 100;
                    break;
                case 'D':
                    return 500;
                    break;
                case 'M':
                    return 1000;
                    break;
            }
        }

        switch (s[pos])
        {
            case 'I':
                if(s[pos+1] == 'V' || s[pos+1] == 'X'){
                    return -1;                
                }
                else{
                    return 1;
                }
                break;
           
            case 'V':
                return 5;
                break;
           
            case 'X':
                if(s[pos+1] == 'L' || s[pos+1] == 'C'){
                    return -10;                
                }
                else{
                    return 10;
                }
                break;
           
            case 'L':
                return 50;
                break;
           
            case 'C':
                if(s[pos+1] == 'D' || s[pos+1] == 'M'){
                    return -100;                
                }
                else{
                    return 100;
                }
                break;
           
            case 'D':
                return 500;
                break;
        
            case 'M':
                return 1000;
                break;
        
            default:
                break;
        }
    }
};