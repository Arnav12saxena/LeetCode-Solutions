class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        
        // Store obstacles in a set for O(1) lookup
        set<pair<int,int>> obs;
        for (auto &o : obstacles) {
            obs.insert({o[0], o[1]});
        }
        
        // Directions: North, East, South, West
        vector<int> dx = {0, 1, 0, -1};
        vector<int> dy = {1, 0, -1, 0};
        
        int dir = 0; // start facing North
        int x = 0, y = 0;
        int maxDist = 0;
        
        for (int cmd : commands) {
            
            if (cmd == -2) {
                // turn left
                dir = (dir + 3) % 4;
            }
            else if (cmd == -1) {
                // turn right
                dir = (dir + 1) % 4;
            }
            else {
                // move forward step by step
                for (int i = 0; i < cmd; i++) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    
                    // check obstacle
                    if (obs.count({nx, ny})) break;
                    
                    x = nx;
                    y = ny;
                    
                    // update max distance squared
                    maxDist = max(maxDist, x*x + y*y);
                }
            }
        }
        
        return maxDist;
    }
};