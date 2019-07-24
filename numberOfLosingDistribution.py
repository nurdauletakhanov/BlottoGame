import math
all = math.factorial(109)//(math.factorial(100) * math.factorial(9))
print(all)

a=[0]*10
a[5] = 34
a[6] = 33
a[7] = 33


cnt = 0
for i in range(34):
    for j in range(33):
        for k in range(33):
            d = 100 - i - j - k
            cnt += math.factorial(6+d)//(math.factorial(6)*math.factorial(d))
print(cnt)
print(cnt * 1.0/all)


