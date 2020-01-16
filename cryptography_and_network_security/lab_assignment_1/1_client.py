import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
port = 7777;
s.connect(('127.0.0.1', port))

print("Connected now, check connection by giving two integers as input, whose sum server will return")
a = int(input("Enter first number: "))
b = int(input("Enter second number: "))
s.send((str(a) + ' ' + str(b)).encode())
print(s.recv(1024).decode())
s.close() 
