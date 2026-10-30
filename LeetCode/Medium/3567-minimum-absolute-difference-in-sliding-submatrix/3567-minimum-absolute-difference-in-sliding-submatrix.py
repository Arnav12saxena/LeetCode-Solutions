class Solution:
    def minAbsDiff(self, grid: list[list[int]], k: int) -> list[list[int]]:
        m, n = len(grid), len(grid[0])
        ans = []
        rows_out = m - k + 1
        cols_out = n - k + 1

        for i in range(rows_out):
            # Pre-slice rows once per i
            grid_rows = [grid[i + di] for di in range(k)]
            row = []
            for j in range(cols_out):
                vals = []
                for r in grid_rows:
                    vals += r[j:j+k]
                vals.sort()
                
                min_diff = 0
                prev = vals[0]
                for curr in vals[1:]:
                    if curr != prev:
                        diff = curr - prev
                        if diff == 1:
                            min_diff = 1
                            break
                        if min_diff == 0 or diff < min_diff:
                            min_diff = diff
                        prev = curr

                row.append(min_diff)
            ans.append(row)
        
        return ans