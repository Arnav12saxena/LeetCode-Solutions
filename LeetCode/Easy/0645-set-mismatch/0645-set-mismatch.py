class Solution:
    def findErrorNums(self, nums):
        n = len(nums)
        freq = [0] * (n + 1)

        # Count frequency
        for num in nums:
            freq[num] += 1

        duplicate = -1
        missing = -1

        # Find duplicate and missing
        for i in range(1, n + 1):
            if freq[i] == 2:
                duplicate = i
            elif freq[i] == 0:
                missing = i

        return [duplicate, missing]