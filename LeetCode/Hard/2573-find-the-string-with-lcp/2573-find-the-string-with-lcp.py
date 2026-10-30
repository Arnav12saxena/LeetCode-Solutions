class Solution:
    def findTheString(self, lcp):
        n = len(lcp)

        # Step 1: basic validation
        for i in range(n):
            if lcp[i][i] != n - i:
                return ""
            for j in range(n):
                if lcp[i][j] != lcp[j][i]:
                    return ""

        # Step 2: Union-Find to group indices
        parent = list(range(n))

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            parent[find(x)] = find(y)

        # merge indices with lcp > 0
        for i in range(n):
            for j in range(i + 1, n):
                if lcp[i][j] > 0:
                    union(i, j)

        # Step 3: assign characters
        char_map = {}
        res = [''] * n
        curr_char = ord('a')

        for i in range(n):
            root = find(i)
            if root not in char_map:
                if curr_char > ord('z'):
                    return ""
                char_map[root] = chr(curr_char)
                curr_char += 1
            res[i] = char_map[root]

        word = "".join(res)

        # Step 4: validate by recomputing LCP
        dp = [[0] * (n + 1) for _ in range(n + 1)]

        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if word[i] == word[j]:
                    dp[i][j] = dp[i + 1][j + 1] + 1

        for i in range(n):
            for j in range(n):
                if dp[i][j] != lcp[i][j]:
                    return ""

        return word