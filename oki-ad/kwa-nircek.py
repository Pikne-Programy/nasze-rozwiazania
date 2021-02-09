a, x, n = map(int, input().split())
s = {x}
for _ in range(n):
    x = (pow(x, 2, n) + a) % n
    if x in s:
        break
    s.add(x)
print(len(s))
