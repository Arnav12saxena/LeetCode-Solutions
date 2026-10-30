#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        
        unordered_map<int, vector<int>> mp;
        
        // map values to indices
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }
        
        vector<int> ans;
        
        for (int idx : queries) {
            auto& pos = mp[nums[idx]];
            
            // if only one occurrence
            if (pos.size() == 1) {
                ans.push_back(-1);
                continue;
            }
            
            int i = lower_bound(pos.begin(), pos.end(), idx) - pos.begin();
            int m = pos.size();
            
            int best = INT_MAX;
            
            // check previous and next (circular)
            for (int d : {-1, 1}) {
                int ni = (i + d + m) % m;
                int j = pos[ni];
                
                int dist = abs(idx - j);
                best = min(best, min(dist, n - dist));
            }
            
            ans.push_back(best);
        }
        
        return ans;
    }
};