q = int(input())
for i in range(q):
    k = int(input())
    print(2*(k-1) if bin(2*(k-1)).count('1') % 2 == 0 else 2*(k-1)+1)
