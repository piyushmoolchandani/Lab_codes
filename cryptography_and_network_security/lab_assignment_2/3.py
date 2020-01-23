s = input("Enter String: ")
for j in range(1, 25):
    print(''.join([chr((((ord(i) - 65) - j) % 26) + 97) for i in s]))
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

s = input("Enter string: ")
z_26 = [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25]
for j in z_26:
    print(j, " : ", ''.join([chr((((ord(i) - 65) * mul_inverse(26, j)) % 26) + 97) for i in s]))
    

for j in range(1, 25):
    print(j, " : ", ''.join([chr((((ord(i) - 65) - j) % 26) + 97) for i in s]))
