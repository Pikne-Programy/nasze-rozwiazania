#!/usr/bin/env python3
from random import randint, sample
'''
limits = {
    'n': 1e6,
    'X': 1e9,
    'z': 1e5,
    'k': 1e5 # 1e9
}
'''
limits = {
    'n': 10,
    'X': 100,
    'z': 4,
    'k': 20
}
X = randint(0, limits['X']+1)
k = [0] + sample(range(1,X), randint(0, min(limits['n']-1, X-2))) + [X]
k.sort()
z = [randint(1, limits['k']) for _ in range(randint(1, limits['z']+1))]
k, z = [str(e) for e in k], [str(e) for e in z]
print(len(k), X, len(z))
print(' '.join(k))
print('\n'.join(z))
