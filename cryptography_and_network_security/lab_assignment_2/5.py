def affine_attack(s):
    s = s.lower()
    z_26_mul = [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25]
    patterns = {}
    for i in z_26_mul:
        for j in range(1, 25):
            patterns[(i, j)] = ''.join([chr(((((ord(K) - 97 - j) % 26) * mul_inverse(26, i)) % 26) + 97) for K in s])
    return patterns

def decode_affine(s, key):
    s = s.lower()
    return ''.join([chr(((((ord(K) - 97 - key[1]) % 26) * mul_inverse(26, key[0])) % 26) + 97) for K in s])

s = input("Enter String: ")
patterns = affine_attack('GL')
for i in patterns:
    if (patterns[i] == 'ab'):
        key = i
print(decode_affine(s, key))
