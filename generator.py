import math as  m

def f(x):
    return m.cos(x) - x

a = float(input())
b = float(input())
c = float(input())

fileName = str(input())
print(fileName)
fl = open(fileName + ".txt", 'w')
while (a < b):
    fl.write(str(a)+ ";"+ str(f(a))+"\n")
    a += c

fl.close()
