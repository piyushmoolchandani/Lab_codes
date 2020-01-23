s = input("Enter String: ")
for j in range(1, 25):
    print(''.join([chr((((ord(i) - 97) - j) % 26) + 65) for i in s]))
