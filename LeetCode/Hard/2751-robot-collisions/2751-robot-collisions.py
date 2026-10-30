class Solution:
    def survivedRobotsHealths(self, positions, healths, directions):
        n = len(positions)
        
        # Combine and sort by position
        robots = sorted(
            [(positions[i], healths[i], directions[i], i) for i in range(n)]
        )
        
        stack = []  # store indices of robots moving right
        alive = [True] * n
        
        # Convert to mutable health list
        healths = healths[:]
        
        for pos, health, direction, idx in robots:
            if direction == 'R':
                stack.append(idx)
            else:
                # process collisions
                while stack and alive[idx]:
                    top = stack[-1]
                    
                    if not alive[top]:
                        stack.pop()
                        continue
                    
                    if healths[top] < healths[idx]:
                        # right robot dies
                        alive[top] = False
                        stack.pop()
                        healths[idx] -= 1
                    elif healths[top] > healths[idx]:
                        # left robot dies
                        alive[idx] = False
                        healths[top] -= 1
                        break
                    else:
                        # both die
                        alive[top] = False
                        alive[idx] = False
                        stack.pop()
                        break
        
        # Collect survivors in original order
        result = []
        for i in range(n):
            if alive[i]:
                result.append(healths[i])
        
        return result