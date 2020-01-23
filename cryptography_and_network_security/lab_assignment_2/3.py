s = input("Enter String: ")
for j in range(1, 25):
    print(''.join([chr((((ord(i) - 65) - j) % 26) + 97) for i in s]))
