class Solution:
    def countStudents(self, students: List[int], sandwiches: List[int]) -> int:
        # Count how many students prefer circular (0) and square (1)
        count_0 = students.count(0)
        count_1 = students.count(1)
        
        # Go through each sandwich (top to bottom)
        for sandwich in sandwiches:
            
            # If the current sandwich is circular
            if sandwich == 0:
                
                # Check: does ANY student want circular?
                if count_0 == 0:
                    # No one wants it → process stops
                    # All remaining students (who want 1) cannot eat
                    return count_1
                
                # One student eats the circular sandwich
                count_0 -= 1
            
            # If the current sandwich is square
            else:
                
                # Check: does ANY student want square?
                if count_1 == 0:
                    # No one wants it → process stops
                    # All remaining students (who want 0) cannot eat
                    return count_0
                
                # One student eats the square sandwich
                count_1 -= 1
        
        # If all sandwiches are eaten, no student is left
        return 0