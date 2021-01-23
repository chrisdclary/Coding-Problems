#include <unordered_map>
#include <string>

class vecHash {
    public:
        std::size_t operator()(std::vector<int> const& vec) const {
            std::size_t seed = vec.size();
            for(auto& i : vec) {
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
};


class Solution {
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        
        // Map to hold a vector for all patterns of length m and count their repetitions
        unordered_map<vector<int>, int, vecHash> map;
        
        // Build the first pattern from the beginning
        int end = 0;
        vector<int> pattern;
        for(end = 0; end < m; end++){
            pattern.push_back(arr[end]);
        }
        map[pattern]++;
        
        // add every pattern of size m to the map
        while(end < arr.size() ){
            pattern.push_back(arr[end]);
            pattern.erase(pattern.begin());
            map[pattern]++;
            end++;
        }
        
        // iterate through map to see if any patterns repeated k or more times
        for(auto& [p, c] : map){
            if(c >= k)
                return true;
        }
        return false;
    }
};