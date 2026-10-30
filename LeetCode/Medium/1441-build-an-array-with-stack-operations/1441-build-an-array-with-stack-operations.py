class Solution:
    def buildArray(self, target: List[int], n: int) -> List[str]:
        result=[]
        i=0
        for num in range(1, n+1):
            if i== len(target):
                break

            result.append("Push")

            if num== target[i]:
                i+=1
            else: 
                result.append("Pop")
        return result