s, r = input(), int(input())
r %= len(s)
print(s[r:]+s[:r])
