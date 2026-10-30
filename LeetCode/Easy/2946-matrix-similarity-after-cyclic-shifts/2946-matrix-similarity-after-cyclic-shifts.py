class Solution:
    def areSimilar(self, mat: List[List[int]], k: int) -> bool:
        m=len(mat)
        n=len(mat[0])

        shift= k%n
        
        for i in range (m):
            for j in range (n):
                if i %2 ==0:
                    if mat[i][j] != mat[i][(j+shift)%n]:
                        return False
                else: 
                    if mat[i][j] != mat[i][(j-shift)%n]:
                        return False  

        return True        
