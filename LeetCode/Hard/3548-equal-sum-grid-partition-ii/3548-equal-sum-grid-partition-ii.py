from collections import Counter

class Solution:
    def canPartitionGrid(self, grid):
        m, n = len(grid), len(grid[0])
        
        total = sum(sum(row) for row in grid)
        
        # ---------- HORIZONTAL CUTS ----------
        top_counter = Counter()
        bottom_counter = Counter()
        
        # initialize bottom counter
        for row in grid:
            for val in row:
                bottom_counter[val] += 1
        
        top_sum = 0
        
        for i in range(m - 1):  # cut after row i
            for j in range(n):
                val = grid[i][j]
                top_sum += val
                top_counter[val] += 1
                bottom_counter[val] -= 1
                if bottom_counter[val] == 0:
                    del bottom_counter[val]
            
            bottom_sum = total - top_sum
            
            if top_sum == bottom_sum:
                return True
            
            diff = abs(top_sum - bottom_sum)
            
            # decide which side to remove from
            if top_sum > bottom_sum:
                if self.valid_remove(top_counter, grid, 0, i, 0, n - 1, diff):
                    return True
            else:
                if self.valid_remove(bottom_counter, grid, i + 1, m - 1, 0, n - 1, diff):
                    return True
        
        # ---------- VERTICAL CUTS ----------
        left_counter = Counter()
        right_counter = Counter()
        
        # initialize right counter
        for row in grid:
            for val in row:
                right_counter[val] += 1
        
        left_sum = 0
        
        for j in range(n - 1):  # cut after column j
            for i in range(m):
                val = grid[i][j]
                left_sum += val
                left_counter[val] += 1
                right_counter[val] -= 1
                if right_counter[val] == 0:
                    del right_counter[val]
            
            right_sum = total - left_sum
            
            if left_sum == right_sum:
                return True
            
            diff = abs(left_sum - right_sum)
            
            if left_sum > right_sum:
                if self.valid_remove(left_counter, grid, 0, m - 1, 0, j, diff):
                    return True
            else:
                if self.valid_remove(right_counter, grid, 0, m - 1, j + 1, n - 1, diff):
                    return True
        
        return False

    # check if we can remove a cell = diff while keeping connectivity
    def valid_remove(self, counter, grid, r1, r2, c1, c2, diff):
        if diff not in counter:
            return False
        
        rows = r2 - r1 + 1
        cols = c2 - c1 + 1
        
        # if more than 1 row AND more than 1 column → always safe
        if rows > 1 and cols > 1:
            return True
        
        # single row → only edges removable
        if rows == 1:
            if grid[r1][c1] == diff:
                return True
            if grid[r1][c2] == diff:
                return True
            return False
        
        # single column → only edges removable
        if cols == 1:
            if grid[r1][c1] == diff:
                return True
            if grid[r2][c1] == diff:
                return True
            return False
        
        return False