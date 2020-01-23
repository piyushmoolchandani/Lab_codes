s = input("Enter string: ")
z_26 = [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25]
for j in z_26:
    print(j, " : ", ''.join([chr((((ord(i) - 65) * mul_inverse(26, j)) % 26) + 97) for i in s]))
    

for j in range(1, 25):
    print(j, " : ", ''.join([chr((((ord(i) - 65) - j) % 26) + 97) for i in s]))
