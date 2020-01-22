def gcd(a, b):
    if (b == 0):
        return a;
    else:
        return gcd(b, a % b);
    
def inverse_pairs(n):
    inverses = {}
    
    additive = set();
    for i in range(n):
        for j in range(i, n):
            if (not (i + j) % n):
                additive.add((i, j));
    
    multiplicative = set();
    for i in range(1, n):
        if gcd(n, i) == 1:
            for j in range(i, n):
                if ((i * j) % n == 1):
                    multiplicative.add((i, j));

    inverses['additive_inverses'] = additive;
    inverses['multiplicative_inverses'] = multiplicative;

    return inverses;

n = int(input("Enter n to add. and mul. inverse pairs: "))
print(inverse_pairs(n));
