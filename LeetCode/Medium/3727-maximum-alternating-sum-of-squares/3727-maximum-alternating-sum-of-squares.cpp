class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> squares(n);

        for(int i = 0; i<n; i++){
            squares[i]= 1LL * nums[i]*nums[i];
        }
        sort(squares.begin(), squares.end());

        long long score = 0;

        for (int i = 0; i <n;i++){
            if (i<n/2){
                score-= squares[i];

            }
            else{
                score+=squares[i];
            }
            
    
        }
        return score;
    }

};