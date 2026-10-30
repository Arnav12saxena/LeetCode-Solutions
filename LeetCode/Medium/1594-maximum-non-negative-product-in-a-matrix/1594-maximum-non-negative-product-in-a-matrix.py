class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])

        maxDP = [[0]*n for _ in range(m)]
        minDP = [[0]*n for _ in range(m)]

        maxDP[0][0] = minDP[0][0] = grid[0][0]

        # first row
        for j in range(1, n):
            val = grid[0][j]
            maxDP[0][j] = maxDP[0][j-1] * val
            minDP[0][j] = minDP[0][j-1] * val

        # first column
        for i in range(1, m):
            val = grid[i][0]
            maxDP[i][0] = maxDP[i-1][0] * val
            minDP[i][0] = minDP[i-1][0] * val

        # fill rest
        for i in range(1, m):
            for j in range(1, n):
                val = grid[i][j]

                candidates = [
                    maxDP[i-1][j] * val,
                    minDP[i-1][j] * val,
                    maxDP[i][j-1] * val,
                    minDP[i][j-1] * val
                ]

                maxDP[i][j] = max(candidates)
                minDP[i][j] = min(candidates)

        result = maxDP[m-1][n-1]

        return result % MOD if result >= 0 else -1