def gcd(a, b):
    if (b == 0):
        return a;
    else:
        return gcd(b, a % b);

def extended_gcd(a, b):
    r1 = a
    r2 = b
    s1 = 1
    s2 = 0
    t1 = 0
    t2 = 1
    while(r2 > 0):
        q = r1 // r2

        r = r1 - q * r2
        r1 = r2
        r2 = r

        s = s1 - q * s2
        s1 = s2
        s2 = s

        t = t1 - q * t2
        t1 = t2
        t2 = t
    return [r1, s1, t1]

def mul_inverse(n, b):
    if gcd(n, b) == 1:
        return extended_gcd(n, b)[2] % n
    else:
        return -1
    
print("For equation Ax + B congruent C (mod D)")
A = int(input("Enter A: "))
B = int(input("Enter B: "))
C = int(input("Enter C: "))
D = int(input("Enter D: "))

C = (C - B) % D

temp = gcd(D, A)
if (C / temp != C // temp):
    print("No Solution.")
else:
    gcd_ab = gcd(A, C)
    gcd_abc = gcd(gcd_ab, D)
    A /= gcd_abc
    C /= gcd_abc
    D /= gcd_abc
    print(A, B, C, D, gcd_abc)
    sol = set()
    x0 = C * mul_inverse(D, A) % D
    for i in range(temp):
        sol.add(int(x0 + (i * D * gcd_abc / temp)))
    print(sol)
