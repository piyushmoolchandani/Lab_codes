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

print("Enter numbers to find the gcd using extended Euclidean algorithm")
a = int(input("Enter first: "))
b = int(input("Enter second: "))
ans = extended_gcd(a, b);
print("GCD of given numbers is:", ans[0]);
print("Equation:", a, "*", ans[1], "+", b, "*", ans[2], "=", ans[0])
