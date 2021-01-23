#include <cctype>

class Solution {
public:
    bool isNumber(string s) {
        if(s.empty())
            return false;
        auto i = s.begin();
        if(*i == '+' || *i == '-')
            i++;
        bool notEmpty = false;
        bool hasDecimal = false;
        while (true){
            if (i == s.end()){
                return notEmpty;
            } else if (std::isdigit(*i)){
                notEmpty = true;
                i++;
                continue;
            } else if (*i == '.'){
                if (hasDecimal)
                    return false;
                hasDecimal = true;
                i++;
                continue;
            } else if (*i == 'e' || *i == 'E'){
                if (!notEmpty)
                    return false;
                i++;
                break;
            } else {
                return false;
            }   
        }
        
        if(*i == '+' || *i == '-'){
            i++;
        }
        bool expNotEmpty = false;
            
        while (true){
            if (i == s.end()){
                return expNotEmpty;
            } else if (std::isdigit(*i)){
                expNotEmpty = true;
                i++;
                continue;
            } else {
                return false;
            }   
        }
    return false;
    }
};