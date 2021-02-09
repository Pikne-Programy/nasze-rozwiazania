x1, y1 = map(int, input().split())
x2, y2 = map(int, input().split())
x3, y3 = map(int, input().split())
print('ZGODNIE' if (y3-y1)*(x2-x1)-(y2-y1)*(x3-x1) < 0 else 'PRZECIWNIE')
