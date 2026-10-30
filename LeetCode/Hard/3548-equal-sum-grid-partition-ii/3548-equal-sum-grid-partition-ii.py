from typing import List

MAX_VAL = 100001  # grid[i][j] <= 1e5

class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])

        def try_horizontal():
            row_sums = list(map(sum, grid))   # map() faster than list comprehension
            total = sum(row_sums)

            # Two plain lists instead of defaultdict + set.
            # sf[v] = count of v remaining in suffix (right/bottom section)
            # pf[v] = count of v accumulated in prefix (left/top section)
            sf = [0] * MAX_VAL
            for row in grid:
                for v in row:
                    sf[v] += 1
            pf = [0] * MAX_VAL

            prefix = 0
            for i in range(m - 1):
                prefix += row_sums[i]
                # Avoid computing suffix = total - prefix; use 2*prefix - total instead
                diff = prefix + prefix - total   # >0: top bigger, <0: bottom bigger

                if diff == 0:
                    return True

                top_h = i + 1
                bot_h = m - 1 - i

                if diff > 0:
                    abs_diff = diff
                    if abs_diff < MAX_VAL:
                        if top_h == 1:
                            # Single-row top: only corner cells are removable
                            if n != 1:
                                row = grid[i]
                                if row[0] == abs_diff or row[-1] == abs_diff:
                                    return True
                            # top_h==1 and n==1 -> only 1 cell, can't remove it
                        elif n == 1:
                            # Single-col strips: only top/bottom boundary removable
                            if grid[0][0] == abs_diff or grid[i][0] == abs_diff:
                                return True
                        elif pf[abs_diff]:           # O(1) array lookup, no hashing
                            return True
                else:
                    abs_diff = -diff
                    if abs_diff < MAX_VAL:
                        if bot_h == 1:
                            if n != 1:
                                row = grid[i + 1]
                                if row[0] == abs_diff or row[-1] == abs_diff:
                                    return True
                        elif n == 1:
                            if grid[i+1][0] == abs_diff or grid[m-1][0] == abs_diff:
                                return True
                        elif sf[abs_diff]:
                            return True

                # Slide row i from suffix → prefix
                for v in grid[i]:                    # iterate row directly, no range(n)
                    sf[v] -= 1
                    pf[v] += 1

            return False

        def try_vertical():
            col_sums = [0] * n
            for row in grid:
                for c in range(n):
                    col_sums[c] += row[c]
            total = sum(col_sums)

            sf = [0] * MAX_VAL
            for row in grid:
                for v in row:
                    sf[v] += 1
            pf = [0] * MAX_VAL

            prefix = 0
            for j in range(n - 1):
                prefix += col_sums[j]
                diff = prefix + prefix - total

                if diff == 0:
                    return True

                left_w = j + 1
                right_w = n - 1 - j

                if diff > 0:
                    abs_diff = diff
                    if abs_diff < MAX_VAL:
                        if left_w == 1:
                            if m != 1:
                                if grid[0][j] == abs_diff or grid[m-1][j] == abs_diff:
                                    return True
                        elif m == 1:
                            if grid[0][0] == abs_diff or grid[0][j] == abs_diff:
                                return True
                        elif pf[abs_diff]:
                            return True
                else:
                    abs_diff = -diff
                    if abs_diff < MAX_VAL:
                        if right_w == 1:
                            if m != 1:
                                if grid[0][j+1] == abs_diff or grid[m-1][j+1] == abs_diff:
                                    return True
                        elif m == 1:
                            if grid[0][j+1] == abs_diff or grid[0][n-1] == abs_diff:
                                return True
                        elif sf[abs_diff]:
                            return True

                for r in range(m):
                    v = grid[r][j]
                    sf[v] -= 1
                    pf[v] += 1

            return False

        return try_horizontal() or try_vertical()