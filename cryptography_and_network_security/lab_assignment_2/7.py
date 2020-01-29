from collections import Counter

def additive_statistical(s):
    """
    Input: ascii 97 to 122
    Output: ascii 97 to 122
    
    """
    s = s.lower()
    char_count = Counter(s).most_common(1)
    
    most_occuring_char_text = char_count[0][0]
    most_occuring_chars_established = ['e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'q', 'x', 'z']

    for i in most_occuring_chars_established:
        diff = (ord(i) - ord(most_occuring_char_text)) % 26
        print()
        print("Additive key:", diff, "for", most_occuring_char_text, "encoded as", i, "=>", ''.join(chr((((ord(k) - 97) + diff) % 26) + 97) for k in s))

def decrypt_with_given_pattern(s, key):
    return ''.join([chr(key.index(i) + 97) for i in s])

def pattern_attack(s, key = 'abcdefghijklmnopqrstuvwxyz', n = 0):
    if n == 26:
        print("\nKey:", key, " =>", decrypt_with_given_pattern(s, key))
        return
    
    for i in range(n, 26):
        temp = list(key)
        temp[n], temp[i] = temp[i], temp[n]
        key = ''.join(temp)
        pattern_attack(s, key, n + 1)
        temp = list(key)
        temp[n], temp[i] = temp[i], temp[n]
        key = ''.join(temp)
        
s = input("Enter the encoded string: ")
s = ''.join(s.split())
print("\nStatistical Attack -")
additive_statistical(s)
print("\n -----------------------------------------------------------------------------------------------------------------")
print("\nPattern Attack -")
pattern_attack(s)
