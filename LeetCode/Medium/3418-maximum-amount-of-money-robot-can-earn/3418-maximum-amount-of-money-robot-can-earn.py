from math import inf

class Solution:
    def maximumAmount(self, coins):
        m, n = len(coins), len(coins[0])
        
        # dp[j][k]: max coins at column j with k neutralizations used
        dp = [[-inf] * 3 for _ in range(n)]
        
        # Initialize starting cell
        for k in range(3):
            if coins[0][0] < 0 and k > 0:
                dp[0][k] = 0  # neutralize
            elif k == 0:
                dp[0][k] = coins[0][0]
        
        # Fill first row
        for j in range(1, n):
            new_dp = [[-inf] * 3 for _ in range(n)]
            for k in range(3):
                if dp[j-1][k] != -inf:
                    val = coins[0][j]
                    
                    # Don't neutralize
                    new_dp[j][k] = max(new_dp[j][k], dp[j-1][k] + val)
                    
                    # Neutralize if negative
                    if val < 0 and k < 2:
                        new_dp[j][k+1] = max(new_dp[j][k+1], dp[j-1][k])
            
            for k in range(3):
                dp[j][k] = new_dp[j][k]
        
        # Process remaining rows
        for i in range(1, m):
            new_dp = [[-inf] * 3 for _ in range(n)]
            
            for j in range(n):
                for k in range(3):
                    val = coins[i][j]
                    
                    # From top
                    if dp[j][k] != -inf:
                        # Don't neutralize
                        new_dp[j][k] = max(new_dp[j][k], dp[j][k] + val)
                        
                        # Neutralize
                        if val < 0 and k < 2:
                            new_dp[j][k+1] = max(new_dp[j][k+1], dp[j][k])
                    
                    # From left
                    if j > 0 and new_dp[j-1][k] != -inf:
                        # Don't neutralize
                        new_dp[j][k] = max(new_dp[j][k], new_dp[j-1][k] + val)
                        
                        # Neutralize
                        if val < 0 and k < 2:
                            new_dp[j][k+1] = max(new_dp[j][k+1], new_dp[j-1][k])
            
            dp = new_dp
        
        return max(dp[n-1])