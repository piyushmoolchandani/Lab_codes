def inverse_pairs(n):
	inverses = {}
	multiplicative = set();
	for i in range(1, n):
		for j in range(1, n):
			if ((i * j) % n == 1):
				multiplicative.add((min(i, j), max(i, j)));
	
	additive = set();
	for i in range(1, n):
		for j in range(1, n):
			if (not (i + j) % n):
				additive.add((min(i, j), max(i, j)));
	
	inverses['additive_inverses'] = additive;
	inverses['multiplicative_inverses'] = multiplicative;
	
	return inverses;

n = int(input("Enter n to add. and mul. inverse pairs: "))
print(inverse_pairs(n));
