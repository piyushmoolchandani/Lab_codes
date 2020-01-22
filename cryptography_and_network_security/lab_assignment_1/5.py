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

def inverse(n, b):
    if gcd(n, b) == 1:
        return [(n - b) % n, extended_gcd(n, b)[2] % n]
    else:
        return [n - b, "Does not exist"]

print("Additive and Multiplicative inverse of b in Zn using extended euclidean algo")
n = int(input("Enter n: "))
b = int(input("Enter b: "))
ans = inverse(n, b)
print("Additive Inverse:", ans[0], ", Multiplicative inverse:", ans[1])
