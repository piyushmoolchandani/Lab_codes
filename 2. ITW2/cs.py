def fact(a):
    if a == 1:
        return 1
    return a * fact(a - 1)

def fib(n):
    if n <= 2:
        return 1;
    else: 
        return fib(n - 1) + fib(n - 2)

def sum_series(n):
    sum = 0;
    for x in range(n+1):
        sum += x ** (x % 2 + 2)
    return sum;