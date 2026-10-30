class Solution:
    def constructProductMatrix(self, grid):
        MOD = 12345
        n, m = len(grid), len(grid[0])
        
        ans = [[1]*m for _ in range(n)]
        
        # prefix pass
        prod = 1
        for i in range(n):
            for j in range(m):
                ans[i][j] = prod
                prod = (prod * grid[i][j]) % MOD
        
        # suffix pass
        prod = 1
        for i in range(n-1, -1, -1):
            for j in range(m-1, -1, -1):
                ans[i][j] = (ans[i][j] * prod) % MOD
                prod = (prod * grid[i][j]) % MOD
        
        return ans