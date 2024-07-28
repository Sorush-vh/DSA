def min_distinguishing_length(type1, type2):
    n = len(type1)
    m = len(type1[0])
    
    # Check for all lengths from 1 to m
    for k in range(1, m + 1):
        for i in range(m - k + 1):
            type1_substrings = set()
            type2_substrings = set()

            for s in type1:
                type1_substrings.add(s[i:i + k])
        

            for s in type2:
                type2_substrings.add(s[i:i + k])

            if not type1_substrings & type2_substrings:
                return k
    
    return m

n, m = map(int, input().split())
type1 = [None] * n
type2 = [None] * n

for i in range(n):
    type1[i] = input()

for i in range(n):
    type2[i] = input()
print(min_distinguishing_length(type1, type2))
