class Solution:
    def smallerNumbersThanCurrent(self, nums):
        freq = [0] * 101

        # count frequency
        for num in nums:
            freq[num] += 1

        # prefix sum (how many numbers smaller)
        for i in range(1, 101):
            freq[i] += freq[i - 1]

        result = []
        for num in nums:
            if num == 0:
                result.append(0)
            else:
                result.append(freq[num - 1])

        return result