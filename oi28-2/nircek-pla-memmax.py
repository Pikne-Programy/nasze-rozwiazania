#!/usr/bin/env python3
#n, z = 3, 4
n = int(1e4)
X = n-1
z = int(1e5)
print(n, X, z)
print(' '.join([str(i) for i in range(n)]))
print('\n'.join([str(int(1e4*i)) for i in range(1, z+1)]))
