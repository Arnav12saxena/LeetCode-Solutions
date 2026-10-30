class Solution:
    def canPartitionGrid(self, grid):
        m, n = len(grid), len(grid[0])
        
        # Total sum of grid
        total = sum(sum(row) for row in grid)
        
        # If total is odd, can't split equally
        if total % 2 != 0:
            return False
        
        # 🔹 Horizontal cuts
        curr = 0
        for i in range(m - 1):  # ensure both parts are non-empty
            curr += sum(grid[i])  # add current row
            if curr * 2 == total:
                return True
        
        # 🔹 Vertical cuts
        
        # Step 1: compute column sums
        col_sums = [0] * n
        for j in range(n):
            for i in range(m):
                col_sums[j] += grid[i][j]
        
        # Step 2: try splitting columns
        curr = 0
        for j in range(n - 1):  # ensure both parts are non-empty
            curr += col_sums[j]
            if curr * 2 == total:
                return True
        
        return False