N=2000
print(N)
for i in range(1,1024):
    if 2*i <= 2000:
        print(i, 2*i, 'A')
    if 2*i+1 <= 2000:
        print(i, 2*i+1, 'A')
