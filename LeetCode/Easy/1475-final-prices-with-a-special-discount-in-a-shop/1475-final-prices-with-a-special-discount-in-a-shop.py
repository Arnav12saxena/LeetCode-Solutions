class Solution:
    def finalPrices(self, prices: List[int]) -> List[int]:
        n = len(prices)
        answer = prices[:]
        stack = []

        for i in range (n):
            while stack and prices[i]<= prices[stack[-1]]:
                idx = stack.pop()
                answer[idx] -= prices [i]
            stack.append(i)
        return answer    
