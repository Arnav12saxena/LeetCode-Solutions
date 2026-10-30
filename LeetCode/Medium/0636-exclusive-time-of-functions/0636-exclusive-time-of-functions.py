class Solution:
    def exclusiveTime(self, n, logs):
        # Result array to store exclusive time of each function
        res = [0] * n
        
        # Stack to keep track of active function calls
        stack = []
        
        # Previous timestamp (used to calculate time slices)
        prev_time = 0

        for log in logs:
            fid, typ, time = log.split(":")
            fid = int(fid)
            time = int(time)

            if typ == "start":
                # If another function is running, pause it
                if stack:
                    res[stack[-1]] += time - prev_time
                
                # Start new function
                stack.append(fid)
                prev_time = time

            else:  # "end"
                # Finish current function
                res[stack.pop()] += time - prev_time + 1
                
                # Move time forward (next execution starts after this)
                prev_time = time + 1

        return res