class Solution:
    def findRotation(self, mat, target):
        
        def rotate(matrix):
            n = len(matrix)
            new = [[0]*n for _ in range(n)]
            
            for i in range(n):
                for j in range(n):
                    new[j][n-1-i] = matrix[i][j]
            
            return new
        
        for _ in range(4):
            if mat == target:
                return True
            mat = rotate(mat)
        
        return False